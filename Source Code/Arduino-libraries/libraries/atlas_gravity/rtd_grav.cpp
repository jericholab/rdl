
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "rtd_grav.h"
#include "EEPROM.h"


Gravity_RTD::Gravity_RTD(uint8_t pin){
	this->pin = pin;
    this->EEPROM_offset = (pin) * EEPROM_SIZE_CONST;
    //to lay the calibration parameters out in EEPROM we map their locations to the analog pin numbers
    //we assume a maximum size of EEPROM_SIZE_CONST for every struct we're saving  
}

bool Gravity_RTD::begin(){
    #if defined(ESP8266) || defined(ESP32)
        EEPROM.begin(1024);
    #endif 
	if((EEPROM.read(this->EEPROM_offset) == magic_char)
    && (EEPROM.read(this->EEPROM_offset + sizeof(uint8_t)) == GRAV_RTD)){
		EEPROM.get(this->EEPROM_offset, rtd);
		return true;
    }
	return false;
}

float Gravity_RTD::read_voltage() {
    float voltage_mV = 0;
    for (int i = 0; i < volt_avg_len; ++i) {
	#if defined(ESP32)
	//ESP32 has significant nonlinearity in its ADC, we will attempt to compensate 
	//but you're on your own to some extent
	//this compensation is only for the ESP32
	//https://github.com/espressif/arduino-esp32/issues/92
		voltage_mV += analogRead(this->pin) / 4095.0 * 3300.0 + 130;
	#else
		voltage_mV += analogRead(this->pin) / 1024.0 * 5000.0;
    #endif 
    }
    voltage_mV /= volt_avg_len;
    return voltage_mV;
}

float Gravity_RTD::read_calibrated_voltage(){
	return (read_voltage() - this->rtd.voltage_offset_mV);
}

float Gravity_RTD::secondary_temp_correction(float vcal){
	//5E-06x2 - 0.0043x - 0.2768
	return 5E-06*vcal*vcal - 0.0043*vcal - 0.2768;	
}

float Gravity_RTD::read_RTD_temp_C(float voltage_mV){
	float vcal = (voltage_mV - this->rtd.voltage_offset_mV);
	float temp = (0.109 * vcal) + secondary_temp_correction(vcal);
    return temp; //- 126.21 );
}

float Gravity_RTD::read_RTD_temp_C(){
    return read_RTD_temp_C(read_voltage());
}

//(0°C × 9/5) + 32 = 32°F
float Gravity_RTD::read_RTD_temp_F(){
    return read_RTD_temp_C()*9.0/5.0 + 32.0;
}

void Gravity_RTD::cal(float cal_temp_C) {
	float vcal = read_calibrated_voltage();
	float correction_C = secondary_temp_correction(vcal);
    this->rtd.voltage_offset_mV = 0;
    this->rtd.voltage_offset_mV = (read_voltage()* 0.109 + correction_C - cal_temp_C)/ 0.109;
    EEPROM.put(this->EEPROM_offset,rtd);
    #if defined(ESP8266) || defined(ESP32)
        EEPROM.commit(); 
    #endif
}

void Gravity_RTD::cal_clear() {
    this->rtd.voltage_offset_mV = DEFAULT_OFFSET_VOLTAGE;
    EEPROM.put(this->EEPROM_offset,rtd);
    #if defined(ESP8266) || defined(ESP32)
        EEPROM.commit(); 
    #endif
}


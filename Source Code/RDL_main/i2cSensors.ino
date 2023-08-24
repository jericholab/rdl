//-------------------------------------------------------------------
// FONCTION: i2cSensors
// PURPOSE: read the digital sensors connected to the i2c pins of the arduino. Example with SHT40 sensor.
// INPUT: none
// OUTPUT: none

int i2cSensors(){

sht4.setPrecision(SHT4X_LOW_PRECISION);   //set to low precision measurement, quick
//sht4.setPrecision(SHT4X_MEDIUM_PRECISION);   //set to medium precision measurement, 
//sht4.setPrecision(SHT4X_HIGH_PRECISION);   //set to high precision measurement, slow
sht4.setHeater(SHT4X_NO_HEATER);  //set to 'no heat'
//sht4.setHeater(SHT4X_HIGH_HEATER_1S);  //set to 'high heat for 1 second'
//sht4.setHeater(SHT4X_HIGH_HEATER_100MS);  
//sht4.setHeater(SHT4X_MED_HEATER_1S);  
//sht4.setHeater(SHT4X_MED_HEATER_100MS);  
//sht4.setHeater(SHT4X_LOW_HEATER_1S); 
//sht4.setHeater(SHT4X_LOW_HEATER_100MS); 

sensors_event_t humidity, temp;  //define two events (objects)

if(SHT4_present == 1){
    sht4.getEvent(&humidity, &temp);                             //populate temp and humidity objects with fresh data
    Serial.print(temp.temperature);                              //print the temperature
    spacing(temp.temperature,12); 
    Serial.print(humidity.relative_humidity);                    //print the relative humidity
    spacing(humidity.relative_humidity,12);
}

else{
    Serial.print("0.00");                               //print the temperature    //////////// Text can be sent to Flash memory with a single variable
    spacing2("0.00",12); 
    Serial.print("0.00");                               //print the relative humidity
    spacing2("0.00",12);
}
  }
  

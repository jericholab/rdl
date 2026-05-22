#ifndef RTD_GRAV_H
#define RTD_GRAV_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <base_grav.h>

#define DEFAULT_OFFSET_VOLTAGE_CONST 1067.90

class Gravity_RTD : public Gravity_Base{
	public:
        Gravity_RTD(uint8_t pin);
		
		bool begin();
        virtual float read_voltage();
        float read_RTD_temp_C(float voltage_mV);
        float read_RTD_temp_C();
		float read_RTD_temp_F();
        void cal(float cal_temp_C);
        void cal_clear();
        
    protected:
		static const int volt_avg_len = 5000;
		
		float read_calibrated_voltage();
		
	private:
	
		float secondary_temp_correction(float vcal);
		
        const float DEFAULT_OFFSET_VOLTAGE = DEFAULT_OFFSET_VOLTAGE_CONST;
		struct RTD {
		  const uint8_t magic = magic_char;
          const uint8_t type = GRAV_RTD;
		  float voltage_offset_mV = DEFAULT_OFFSET_VOLTAGE_CONST;
		};
		struct RTD rtd;
};

#endif
//-------------------------------------------------------------------
// FONCTION: sht40Func
// PURPOSE: Obtain a measurement from the selected SHT40 sensor
// INPUT: none
// OUTPUT: none

void sht40Func(){

    if ((SHT40Display == 1)&(SHT4_present ==0)){       // if the SHT40 sensr is desired and has not been found yet
      if(sht4.begin()){                                // ... we try to initialize and if it works.... 
        SHT4_present = 1;                              // the sensor is considered present (this variable affects SHT40Func()).
      }
    }

    Serial.print(F("*"));
    spacing2(F("*"),12); 
    
    //sht4.setPrecision(SHT4X_LOW_PRECISION);        //set to low precision measurement, fast
    //sht4.setPrecision(SHT4X_MEDIUM_PRECISION);     //set to medium precision measurement, medium
    sht4.setPrecision(SHT4X_HIGH_PRECISION);         //set to high precision measurement, slow
    
    if (SHT40_heatPulse ==0){
      sht4.setHeater(SHT4X_MED_HEATER_1S);           //set to 'med heat for 1 second' (first dose)
      //sht4.setHeater(SHT4X_MED_HEATER_1S);         //set to 'med heat for 1 second' (optional second dose)
      SHT40_heatPulse = 1;                           //change value to 1, which prevents the heat pulse after the initial run (temporary strategy before timer implementation)
      Serial.print("&");                             //indicate the heating happened with an 'ampersand' sign
    }
    else{
      sht4.setHeater(SHT4X_NO_HEATER);              //set sensor to 'no heat'  
    }
    
    //sht4.setHeater(SHT4X_NO_HEATER);              //set to 'no heat'
    //sht4.setHeater(SHT4X_HIGH_HEATER_1S);         //set to 'high heat for 1 second'
    //sht4.setHeater(SHT4X_HIGH_HEATER_100MS);  
    //sht4.setHeater(SHT4X_MED_HEATER_1S);  
    //sht4.setHeater(SHT4X_MED_HEATER_100MS);  
    //sht4.setHeater(SHT4X_LOW_HEATER_1S); 
    //sht4.setHeater(SHT4X_LOW_HEATER_100MS); 
    
    sensors_event_t humidity, temp;                                  //define two events (objects)       
    
    if(SHT4_present == 1){
        sht4.getEvent(&humidity, &temp);                             //populate temp and humidity objects with fresh data
        Serial.print(temp.temperature);                              //print the temperature
        spacing1(temp.temperature,12); 
        Serial.print(humidity.relative_humidity);                    //print the relative humidity
        spacing1(humidity.relative_humidity,12);
    }
    
    else{
        Serial.print(F("0.00"));                               //print the temperature
        spacing2(F("0.00"),12); 
        Serial.print(F("0.00"));                               //print the relative humidity
        spacing2(F("0.00"),12);
    }
}
  

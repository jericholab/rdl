//-------------------------------------------------------------------
// FONCTION: phFunc
// PURPOSE: Communicate with the DFROBOT pH meter and provide pH values
// INPUT: none
// OUTPUT: none

// ********* THIS CODE WILL BE TRANSFORMED TO WELCOME THE ATLAS SUBSYSTEM


// PH METER: PSEUDO CODE OF WHAT NEEDS TO BE DONE (TRANSFER TO SAD LATER)
// Note: We assume that we have analog pH meters only. An I2C pH meter will be different process.
// 1. We activate the power supply of the selected analog channel.
// 2. The function receives as an input the ADC selected for the measurement. (This way we can have one sensor type with ADS and another with Nano ADC)
// 3. If applicable, change external reference (If we use Nano ADC, thermistor operates on 3.3V and pH on 5V supply.)(If we use ADS1115, the external ref does not matter).
// 4. If applicable, multiple readings are required to let the PMU/ADC adapt to the new voltage reference
// 5. Read EEPROM to find calibration data, if available.
// 6. Delay a few milliseconds to let the sensor stabilize
// 7. Measure data signal with readVoltFunc(), with the ADC choice as input.
// 8. Calculate pH value.
// 9. Print out pH value.
// 10. If applicable, change back the external reference to 3.3V.

void phFunc(int channel, bool readMode){

      Serial.print("*");
      spacing2("*",12);   
  
      // 1. We activate the power supply of the selected analog channel.
      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      setMultiplexer(5);                             // select the multiplexer channel      
      
      // 2. The function receives as an input the ADC selected for the measurement. (This way we can have one sensor type with ADS and another with Nano ADC)
      // No action needed.
      
      // 3. If applicable, change external reference (If we use Nano ADC, thermistor operates on 3.3V and pH on 5V supply.)(If we use ADS1115, the Nano ADC ref does not matter).
      if (readMode ==0){
        analogReference(INTERNAL);  
      }
      
      // 4. If applicable, multiple readings are required to let the ADC adapt to the new voltage reference
      if (readMode ==0){   
          for (int i= 1; i<5; i++){
            float sensorValue = analogRead(channel);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
          }
      }

      // 5. Read EEPROM to find calibration data, if available.
      // To be written later. For now we will use default values. //////////////////


      
      // 6. Delay a few milliseconds to let the sensor stabilize
      delay(100);                                    //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      
      // 7. Measure data signal with readVoltFunc(), with the ADC choice as input.
      float voltage = getVoltFunc(channel); 

      // 8. Optional printout of the raw voltage measurement
      bool debug =0;     // normal operation (0) or debug (1) for more information.   
      if (debug ==1){
        Serial.print(voltage);  // temporary print out of the raw voltage measurement
        spacing1(voltage,12);             
      }
            
      // 9. Calculate pH value from the voltage
      float sensorValue = ph.readPH(voltage,25);

      // 10. Print out pH value.
      Serial.print(sensorValue);
      spacing1(sensorValue,12); 
          
      // 11. If applicable, change back the external reference to 3.3V.
      if (readMode ==0){
        analogReference(EXTERNAL);  
      }

//      delay(100);  // give time for sensor to stabilize after power up
//      Serial.print("*");
//      spacing2("*",12); 
//      float voltage = getVoltFunc(readMode);  // read the voltage while assuming a 5000mV voltage reference
      



  
}

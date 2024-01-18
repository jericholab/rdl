//-------------------------------------------------------------------
// FONCTION: currentFunc
// PURPOSE: calculates the current value of the Hall effect sensor, based on DC, SineRMS or TrueRMS algorithm.
// INPUT: averaging algorithm, selected ADC, input channel
// OUTPUT: none

float currentFunc(uint8_t algo, bool readMode, uint8_t channel){
      
    // PREPARATION

    int n = 10;                                    // size of the sample to be collected
    int i;                                         // integer for loop iteration
    float rms_value = 0;                           // initialize average value
    float volts;                                   // initialize variable 
    float V_offset = 0; //2.542;                      // offset value (no load) to calibrate the sensor      //////// TEST
    float hallRatio = 50/1.5;                      // Hall effect sensor ratio (Amps/Volt) for the TAMURA L01Z050S05
    Serial.print("*");
    spacing2("*",12); 

    digitalWrite(enable_V_MUX, LOW);               // toggle pin to LOW value in order turn on the V_MUX
    setMultiplexer(channel);                       // select the multiplexer channel
    pcf1.digitalWrite(channel, LOW);               // turn LED on by sinking current to ground
    pcf2.digitalWrite(channel, HIGH);              // turn LED on by sinking current to ground
    delay(500);

    // MEASUREMENT WITH ARITHMETIC AVERAGE
    if (algo == 0){                                          //"DC" mode which is arithmetic average
      for (i=0; i< n; i++)
          { 
            volts = getVoltFunc(readMode)-V_offset;         //Because of the way the abs() function is implemented, avoid using other functions inside the brackets, it may lead to incorrect results.
            rms_value += volts;                             //sum the signal
          }
      rms_value = rms_value/float(n);            
    }

    // MEASUREMENT WITH SINEWAVE RMS
    // Explanation: since the average value of a half-wave rectified sine wave is approximately 0.637 times peak value, and its RMS value is about 0.707 times the peak value,
    // we can deduct the RMS value from the average value if we assume a perfect sine wave.
    
    if (algo == 1){                                         // "sine RMS" mode
      for (i=0; i< n; i++)
          { 
            volts = getVoltFunc(readMode)-V_offset;         //Because of the way the abs() function is implemented, avoid using other functions inside the brackets, it may lead to incorrect results.
            volts = abs(volts);                             //rectify the signal
            rms_value += volts;                             //sum the signal
          }
      rms_value = rms_value/float(n) * 1.10989;             //average the signal  and applying correction factor (0.707 /0.637 = 1.10989)
    }
    

    // MEASUREMENT WITH TRUE RMS
    if (algo == 2 ){   //"true RMS " mode
        for (i=0; i< n; i++)
          {
          volts = getVoltFunc(readMode)-V_offset; 
          rms_value += pow(volts,2);            // sum of the squared sample values
          delay(2);                             // delay (ms) for proper sampling of the signal
          }
         rms_value = sqrt(rms_value / float(n));       // rest of the rms algorithm (mean and root)
        }
                
    // CONVERT TO AMPS & PRINT
    Serial.print(rms_value,4);         //print out the value you calculated.
    spacing1(rms_value,10);            // since two bonus decimal is printed, the spacing requirement is reduced by two units.
    //float amps2 = (rms_value - V_offset) * 50/1.5;                      // Finalize conversion to instantaneous amps  (Removing V_offset after RMS allow negative currents)
    float amps2 = rms_value * hallRatio;                      // Finalize conversion to instantaneous amps  (Removing V_offset after RMS allow negative currents)
    Serial.print(amps2,3);         //print out the value you read. Test with 3 decimals
    spacing1(amps2,11);            // since a bonus decimal is printed, the spacing requirement is reduced by one unit.
    
    pcf1.digitalWrite(channel, HIGH); //turn LED off by turning off sinking transistor
    pcf2.digitalWrite(channel, LOW);  //turn LED off by turning off sinking transistor
}

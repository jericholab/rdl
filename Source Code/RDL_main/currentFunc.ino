//-------------------------------------------------------------------
// FONCTION: currentFunc
// PURPOSE: calculates the current value of the Hall effect sensor, based on DC, SineRMS or TrueRMS algorithm.
// INPUT: none /////////// well it has two input now.///////////////
// OUTPUT: none

float currentFunc(uint8_t algo, bool readMode){
      
    // PREPARATION

    int n = 100;                                   //size of the sample to be collected
    int i;                                         //  integer for loop iteration
    float rms_value = 0;                           // initialize average value
    float volts;                                   // initialize variable 
    float V_offset = 2.544;                        // offset value (no load) to calibrate the sensor
    //digitalWrite(enable_V_MUX, LOW);             // toggle pin to LOW value in order turn on the V_MUX
    //delay(100);                                  //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
    //setMultiplexer(0);                           // select the multiplexer channel                   
    //delay(500);
    float hallRatio = 50/1.5;                      //hall effect sensor ratio (Amps/Volt) for the TAMURA L01Z050S05
    Serial.print("*");
    spacing2("*",12); 
    


    if (algo == "DC"){
      
    }


    // MEASUREMENT WITH SINEWAVE RMS
    //Explanation: since the average value of a half-wave rectified sine wave is approximately 0.637 times the peak value, and its RMS value is about 0.707 times the peak value,
    //we can deduct the RMS value from the average value if we assume a perfect sine wave).
    
    if (algo == "sine"){
      for (i=0; i< n; i++)
          { 
            volts = getVoltFunc(readMode)-V_offset;         //Because of the way the abs() function is implemented, avoid using other functions inside the brackets, it may lead to incorrect results.
            volts = abs(volts);                  //rectify the signal
            rms_value += volts;                  //sum the signal
          }
      rms_value = rms_value/float(n) * 1.10989;  //average the signal  and applying correction factor (0.707 /0.637)
    }
    
          
    // MEASUREMENT WITH TRUE RMS
    if (algo == "true"){
        for (i=0; i< n; i++)
          {
          volts = getVoltFunc(readMode)-V_offset; 
          rms_value += pow(volts,2);            // sum of the squared sample values
          delay(2);                           // delay (ms) for proper sampling of the signal
          }
         rms_value = sqrt(rms_value / float(n));       // rest of the rms algorithm (mean and root)
        
        // CONVERT TO AMPS & PRINT
        
        Serial.print(rms_value,4);         //print out the value you ready.
        spacing1(rms_value,12); 
        //float amps2 = (rms_value - V_offset) * 50/1.5;                      // Finalize conversion to instantaneous amps  (Removing V_offset after RMS allow negative currents)
        float amps2 = rms_value * hallRatio;                      // Finalize conversion to instantaneous amps  (Removing V_offset after RMS allow negative currents)
        Serial.print(amps2,3);         //print out the value you read. Test with 3 decimals
        spacing1(amps2,11);  // since a bonus decimal is printed, the spacing requirement is reduced by one unit.
    }
}

//-------------------------------------------------------------------
// FONCTION: currentFunc
// PURPOSE: calculates the true RMS current value of the Hall effect sensor
// INPUT: none
// OUTPUT: none

void currentFunc(){
      
//      analogReference(DEFAULT);      //put the analog reference back to 5V to allow reading 0-5V signals
//      delay(10);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
//      int sensorValue;               //variable declaration
//      for (int i= 1; i<5; i++){
//        sensorValue = analogRead(CURRENT_PIN);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
//      }
      
//      int n = 5;                                   //size of the sample to be collected
      int i;                                                        //  integer for loop iteration
      float rms_value = 0;                                                 // initialize average value
      float V_offset = 2.831;                             // offset value (no load) to calibrate the sensor
//      float V_ref = 5;                                    // Analog reference
//      for (i=0; i< n; i++)                                  // take N samples in a row, with a slight delay    
//      {
//        float value = analogRead(CURRENT_PIN);
//        float amps = value * (V_ref / 1023.0);                  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      //analogReference(DEFAULT);                    //put the analog reference back to 5V to allow reading 0-5V signals
      delay(100);                                    //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      setMultiplexer(0);                             // select the multiplexer channel                   
      delay(100);
      Serial.print("*");
      spacing2("*",12); 
      float amps = voltFunc();                      // TEMP TEST USING ADS1015 call
      Serial.print("*");
      spacing2("*",12);      
      Serial.print(amps,3);         //print out the value you read. Test with 3 decimals
      
      float amps2 = (amps - V_offset) * 50/1.5;                      // Finalize conversion to instantaneous amps
//      rms_value += pow(amps2,2);                           // sum of the squared sample values
//      delay(1);                                           // delay (ms) for proper sampling of the signal
//      }

//      Serial.print("*");
//      spacing2("*",12);      
//      Serial.print(amps2,3);         //print out the value you read. Test with 3 decimals

      //rms_value = sqrt(rms_value / n);                                // rms function
      Serial.print("*");
      spacing2("*",12);      
      //Serial.print(rms_value,3);         //print out the value you read. Test with 3 decimals
      Serial.print(amps2,3);         //print out the value you read. Test with 3 decimals
      //spacing(rms_value,12); 
      //spacing2("0.000",12);  
      spacing(rms_value,11);  // since a bonus decimal is printed, the spacing requirement is reduced by one unit.
   

//      analogReference(EXTERNAL);                 //put the analog reference back to 3.3V
//      for (int i= 1; i<5; i++){
//        sensorValue = analogRead(CURRENT_PIN);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
//      }


//////////

//      for (i=0; i< sample_size; i++)                              // take N samples in a row
//      {
//        float amps = samples2[i] * (5 / 1023.0);                  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
//        /// CONVERSION TO AMPS -----------
//        // reference value (center value) is 2.513V
//        // current reading range is 50A
//        // voltage range (positive side) is 1.5V for the reading range
//        float V_ref = 2.532;                             // offset value (no load) to calibrate the sensor
//        amps= (amps - V_ref) * 50/1.5;   
//        samples2[i] = amps;                              // store ADC current value to index 'i' of array 'samples'
//        
//      }


//////////////
//// Alternative code for visualization of sinewave (Succesfully used once, might contain errors)

//      int sample_size = 100;                                   //size of the sample to be collected (too high number can freeze the Nano (stack overflow))
//      float samples2[sample_size];                                  // define vector for sampling purpose of the voltFunction() function  
//      int i;                                                        //  integer for loop iteration
//      for (i=0; i< sample_size; i++)                                // take N samples in a row, with a slight delay    
//      {
//        float value = analogRead(CURRENT_PIN);
//        samples2[i] = value;                                      // store ADC current value to index 'i' of array 'samples'
//        //int rnd = random(750,1250);                                  //generate random numbers between 1 and 2 to avoid window alignment with frequency of signal
//        delay(1);
//      }
//
//      for (i=0; i< sample_size; i++)                              // take N samples in a row
//      {
//        float amps = samples2[i] * (5 / 1023.0);                  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
//        /// CONVERSION TO AMPS -----------
//        // reference value (center value) is 2.513V
//        // current reading range is 50A
//        // voltage range (positive side) is 1.5V for the reading range
//        float V_ref = 2.532;                             // offset value (no load) to calibrate the sensor
//        amps= (amps - V_ref) * 50/1.5;   
//        samples2[i] = amps;                              // store ADC current value to index 'i' of array 'samples'
//      }
//      analogReference(EXTERNAL);     //put the analog reference back to 3.3V
//      
//      for (i=0; i< sample_size; i++)                              // take N samples in a row
//      {
//        Serial.println(samples2[i],3);                    
//      }
//      delay(1000);
//      float rms_value = 0;                                                 // initialize average value
//      for (i=0; i< sample_size; i++)
//          {
//          rms_value += pow(samples2[i],2);                                       // sum of the squared sample values
//          }
//      rms_value = sqrt(rms_value / sample_size);                                // rms function
//      Serial.print("*");
//      spacing2("*",12);      
//      Serial.print(rms_value,3);         //print out the value you read. Test with 3 decimals
//      //spacing(rms_value,12); 
//      spacing2("0.000",12);   
///////////////
          
//      float rms_value = 0;                                                 // initialize average value
//      for (i=0; i< sample_size; i++)
//          {
//          rms_value += pow(samples2[i],2);                                       // sum of the squared sample values
//          }
//
//      
//   
}
  
      

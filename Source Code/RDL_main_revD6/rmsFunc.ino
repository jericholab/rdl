//-------------------------------------------------------------------
// FONCTION: rmsFunc
// PURPOSE: calculates the True RMS current value of the Hall effect sensor
// INPUT: none
// OUTPUT: none

int rmsFunc(){




      voltFunc();    ///////////// TEMP TEST TO SEE THE OFFSET
      
      analogReference(DEFAULT);      //put the analog reference back to 5V to allow reading 0-5V signals
      delay(100);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      ////TEST//////////// TO AVOID BAD READINGS
      int sensorValue;               //variable declaration
      for (int i= 1; i<5; i++){
        sensorValue = analogRead(CURRENT_PIN);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
      }
      ////TEST////////////

      
      int sample_size = 100;                                   //size of the sample to be collected (too high number can freeze the Nano (stack overflow))
      float samples2[sample_size];                                  // define vector for sampling purpose of the voltFunction() function  
      int i;                                                        //  integer for loop iteration
      for (i=0; i< sample_size; i++)                                // take N samples in a row, with a slight delay    
      {
        float value = analogRead(CURRENT_PIN);
        samples2[i] = value;                                      // store ADC current value to index 'i' of array 'samples'
        //int rnd = random(750,1250);                                  //generate random numbers between 1 and 2 to avoid window alignment with frequency of signal
        delay(1);
      }

      
      for (i=0; i< sample_size; i++)                              // take N samples in a row
      {
        float amps = samples2[i] * (5 / 1023.0);                  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
        /// CONVERSION TO AMPS -----------
        // reference value (center value) is 2.513V
        // current reading range is 50A
        // voltage range (positive side) is 1.5V for the reading range
        float V_ref = 2.532;                          //calibration required
        //float V_ref = 2.546;                          //calibration required
        amps= (amps - V_ref) * 50/1.5;   
        samples2[i] = amps;                              // store ADC current value to index 'i' of array 'samples'
      }
      analogReference(EXTERNAL);     //put the analog reference back to 3.3V

//////////////
//// For visualization of sinewave
//      for (i=0; i< sample_size; i++)                              // take N samples in a row
//      {
//        Serial.println(samples2[i],3);                    
//      }
//      delay(1000);
///////////////
          
      float rms_value = 0;                                                 // initialize average value
      for (i=0; i< sample_size; i++)
          {
          rms_value += pow(samples2[i],2);                                       // sum of the squared sample values
          }
      rms_value = sqrt(rms_value / sample_size);                                // rms function
      Serial.print("*");
      spacing2("*",12);      
      Serial.print(rms_value,3);         //print out the value you read. Test with 3 decimals
      //spacing(rms_value,12); 
      spacing2("0.000",12);     
      
   
}
  
      

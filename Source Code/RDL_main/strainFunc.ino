
//-------------------------------------------------------------------
// FONCTION NAME: strainFunc
// PURPOSE: Obtain a measurement from the selected strain gauge load cell
// INPUT: channel
// OUTPUT: none

void strainFunc() {

  float val = -1.00;            // define a default value.
  float b = 20000;              // DUMMY VALUE. Calibration value. ADC value when load cell has no load.
  float a = 1000;               // DUMMY VALUE. Calibration value. Load cell ratio (Newton/ADC) measured experimentally.
  
  if ((strainDisplay == 1)&(strain_present ==0)){
    if (!nau_ada.begin()) {       //The begin() statement most probably contains instance creation.
      //Serial.print("Failed to find NAU7802");
      delay(1000);
    }
    else{ 
      strain_present=1;   // the sensor is considered present
    } 
  }

  if(strain_present == 1){        // If sensor found by strain_init()

 
        //nau_ada.reset();                /////////////// TEST TO AVOID UNRESPONSIVE STRAIN SENSOR AFTER POWER IS LOST.
        //nau_ada.enable(true);             // Prescribe the sensor to power up. Does not seem sufficient to enable readings. This is not an instanciation.
        //nau_ada.reset();  //////// TEST TO AVOID EMPTY READINGS
        nau_ada.begin();


        
////// TEST BLOCK 4
//        nau_ada.setLDO(NAU7802_3V0);      // Test for the Adafruit library
//        nau_ada.setGain(NAU7802_GAIN_128);    // Test for the Adafruit library
//        nau_ada.setRate(NAU7802_RATE_10SPS);   // Test for the Adafruit library
        // Take 10 readings to flush out readings
        for (uint8_t i=0; i<10; i++) {
          while (! nau_ada.available()) delay(1);
          nau_ada.read();
          
        }
//        while (! nau_ada.calibrate(NAU7802_CALMOD_INTERNAL)) {
//          Serial.println("Failed to calibrate internal offset, retrying!");
//          delay(1000);
//        }
//        while (! nau_ada.calibrate(NAU7802_CALMOD_OFFSET)) {
//          Serial.println("Failed to calibrate system offset, retrying!");
//          delay(1000);
//        }
////// TEST BLOCK 4 (END)



    
    val= nau_ada.read();            // Read sensor  //Adafruit library only
   //Serial.print("The code made it up to here");

   
    Serial.print(F("*"));
    spacing2(F("*"),12); 
    Serial.print(val,0);
    spacing1(val,15); //extra two spaces because we removed two decimals.
    
    float force = (val-b)/a;    //[N] Force applied on load cell. Linear equation convert ADC to force based on calibration values.
    Serial.print(force);
    spacing1(force,12); 
  }
  else{
      Serial.print(F("*"));
      spacing2(F("*"),12); 
      Serial.print(F("0.00"));                               //print the temperature
      spacing2(F("0.00"),12); 
      Serial.print(F("0.00"));                               //print the relative humidity
      spacing2(F("0.00"),12);
    } 
  }

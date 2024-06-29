
//-------------------------------------------------------------------
// FONCTION NAME: strainFunc
// PURPOSE: Obtain a measurement from the selected strain gauge load cell
// INPUT: channel
// OUTPUT: none

void strainFunc() {

  float val = -1.00;            // define a default value.
  float b = 20000;              // DUMMY VALUE. Calibration value. ADC value when load cell has no load.
  float a = 1000;               // DUMMY VALUE. Calibration value. Load cell ratio (Newton/ADC) measured experimentally.
  
  strainDevice = 1;             // TEMPORARY STATEMENT TO FORCE READING.
  
  if (! nau_ada.begin()) {
    Serial.print("Failed to find NAU7802");
  }
  Serial.print("Found NAU7802");

////// TEST BLOCK 4
//        nau_ada.setLDO(NAU7802_3V0);      // Test for the Adafruit library
//        nau_ada.setGain(NAU7802_GAIN_128);    // Test for the Adafruit library
//        nau_ada.setRate(NAU7802_RATE_10SPS);   // Test for the Adafruit library
//        // Take 10 readings to flush out readings
//        for (uint8_t i=0; i<10; i++) {
//          while (! nau_ada.available()) delay(1);
//          nau_ada.read();
//        }
//        while (! nau_ada.calibrate(NAU7802_CALMOD_INTERNAL)) {
//          Serial.println("Failed to calibrate internal offset, retrying!");
//          delay(1000);
//        }
//        while (! nau_ada.calibrate(NAU7802_CALMOD_OFFSET)) {
//          Serial.println("Failed to calibrate system offset, retrying!");
//          delay(1000);
//        }
////// TEST BLOCK 4 (END)

  if(strainDevice == 1){        // If sensor found by strain_init()

    //nau.begin();              // Includes a full reset. // The begin() statement is necessary at each power cycle. Calibration is NOT necessary at each power cycle.
    //nau.begin(Wire, false);     // TEST to avoid full reset (call for the Sparkfun library only)
    //val = nau.getReading();     // Read sensor  //Sparkfun library only
    val= nau_ada.read();            // Read sensor  //Adafruit library only
   
    Serial.print(F("*"));
    spacing2(F("*"),12); 
    Serial.print(val);
    spacing1(val,12); 
    
    float force = (val-b)/a;    //[N] Force applied on load cell. Linear equation convert ADC to force based on calibration values.
    Serial.print(force);
    spacing1(force,12); 
  }
  }


//-------------------------------------------------------------------
// FONCTION NAME: strainFunc
// PURPOSE: Obtain a measurement from the selected strain gauge load cell
// INPUT: channel
// OUTPUT: none

void strainFunc() {

  float val = -1.00;            // define a default value.
  
  //strain_init();                // sensor must be initialized after each power up.  ///////// This is a problem in a multiplexed scenario /////
  if(strainDevice == 1){        // if sensor found by strain_init()
    val = nau.getReading();     //sparkfun's (raw values)
  //Wire.endTransmission();  
//    Failed attempt to zero, calibrate and display weight:
//    bool allowNegativeWeights = false;
//    uint8_t samplesToTake = 8;
//    val = nau.getWeight(allowNegativeWeights, samplesToTake); //Once you've set zero offset and cal factor, you can ask the library to do the calculations for you.
  }
    
    Serial.print(F("*"));
    spacing2(F("*"),12); 
    Serial.print(val);
    spacing1(val,12); 
    
  }

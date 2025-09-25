
//-------------------------------------------------------------------
// FONCTION NAME: strain_init
// PURPOSE: initialize the strain gauge cell (Sparkfun library)
// INPUT: none
// OUTPUT: none

//bool strain_init() {
//  bool value;
//  if (! nau_ada.begin()) {                              //if device is not found, we skip the initialization
//    value = 0;
//    Serial.print(F("NAU7802 device not found. No calibration. "));
//  }
//  else{                                               //otherwise, we initialize with the NAU7802 library
//    for (uint8_t i=0; i<10; i++) {
//      while (! nau_ada.available()) delay(1);
//      //nau.getReading();                                 //take 10 readings to flush out readings  // Applies to Sparkfun library only
//      nau_ada.read();
//    }
//    void calculateZeroOffset(uint8_t averageAmount = 8);    //tare function
//    Serial.print(F("NAU7802 calibration done. "));
//  
//    value = 1;
//  }
//  return value;
//  }
  
  

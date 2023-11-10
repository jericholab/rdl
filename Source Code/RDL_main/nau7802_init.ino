
//-------------------------------------------------------------------
// FONCTION NAME: nau7802_init
// PURPOSE: initialize the strain gauge cell (Sparkfun library)
// INPUT:  
// OUTPUT: none

bool nau7802_init() {
  
  if (! nau.begin()) {                              //if device is not found, we skip the initialization
    Serial.println();
    Serial.println("Failed to find NAU7802");
    delay(1000);
  }
  else{                                               //otherwise, we initialize with the NAU7802 library
    
  // Take 10 readings to flush out readings
  for (uint8_t i=0; i<10; i++) {
    while (! nau.available()) delay(1);
    nau.getReading();
  }

  void calculateZeroOffset(uint8_t averageAmount = 8);    //tare function  //test 2023-08-23
  Serial.println("NAU7802 calibration done.");

  bool value = 1;
  return value;

  
  }
  }
  
  

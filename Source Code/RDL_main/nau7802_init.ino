
//-------------------------------------------------------------------
// FONCTION NAME: nau7802_init
// PURPOSE: initialize the strain gauge cell
// INPUT: xxxxxxxxxxxxxxxxx 
// OUTPUT: none

bool nau7802_init() {



  //Serial.println("NAU7802");
  if (! nau.begin()) {                              //if device is not found, we skip the initialization
    Serial.println();
    Serial.println("Failed to find NAU7802");
    delay(1000);
  }
  else{                                               //otherwise, we initialize with the NAU7802 library
    
  //Serial.print("LDO voltage set to ");
  switch (nau.getLDO()) {
    case NAU7802_4V5: break; // Serial.println("4.5V"); break; //
    case NAU7802_4V2: break; // Serial.println("4.2V"); break;
    case NAU7802_3V9: break; // Serial.println("3.9V"); break;
    case NAU7802_3V6: break; // Serial.println("3.6V"); break;
    case NAU7802_3V3: break; // Serial.println("3.3V"); break;
    case NAU7802_3V0: break; // Serial.println("3.0V"); break;
    case NAU7802_2V7: break; // Serial.println("2.7V"); break;
    case NAU7802_2V4: break; // Serial.println("2.4V"); break;
    case NAU7802_EXTERNAL: break; // Serial.println("External"); break;
  }

  nau.setGain(NAU7802_GAIN_128);
  //Serial.print("Gain set to ");
  switch (nau.getGain()) {
    case NAU7802_GAIN_1: break; //Serial.println("1x"); break;
    case NAU7802_GAIN_2: break; //Serial.println("2x"); break;
    case NAU7802_GAIN_4: break; //Serial.println("4x"); break;
    case NAU7802_GAIN_8: break; //Serial.println("8x"); break;
    case NAU7802_GAIN_16: break;// Serial.println("16x"); break;
    case NAU7802_GAIN_32:  break;//Serial.println("32x"); break;
    case NAU7802_GAIN_64: break; //Serial.println("64x"); break;
    case NAU7802_GAIN_128:  break; //Serial.println("128x"); break;
  }

  nau.setRate(NAU7802_RATE_10SPS);
  //Serial.print("Conversion rate set to ");
  switch (nau.getRate()) {
    case NAU7802_RATE_10SPS: break; //Serial.println("10 SPS"); break;
    case NAU7802_RATE_20SPS: break; //Serial.println("20 SPS"); break;
    case NAU7802_RATE_40SPS: break; //Serial.println("40 SPS"); break;
    case NAU7802_RATE_80SPS: break; //Serial.println("80 SPS"); break;
    case NAU7802_RATE_320SPS: break; //Serial.println("320 SPS"); break;
  }

  // Take 10 readings to flush out readings
  for (uint8_t i=0; i<10; i++) {
    while (! nau.available()) delay(1);
    nau.read();
  }

  while (! nau.calibrate(NAU7802_CALMOD_INTERNAL)) {
    Serial.println("Failed to calibrate internal offset, retrying!");
    delay(1000);
  }
  //Serial.println("Calibrated internal offset");

  while (! nau.calibrate(NAU7802_CALMOD_OFFSET)) {
    Serial.println("Failed to calibrate system offset, retrying!");
    delay(1000);
  }
  //Serial.println("Calibrated system offset");
  //Serial.println("Found NAU7802");
  nau.setLDO(NAU7802_3V0);   //ORIGINAL line
  bool value = 1;
  return value;

  
  }
  }
  
  

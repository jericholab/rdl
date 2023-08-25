
//-------------------------------------------------------------------
// FONCTION NAME: nau7802Function
// PURPOSE: Obtain a measurement from the strain gauge cell
// INPUT: none
// OUTPUT: none

void nau7802Function() {

  float val = -1.00;
  
  if(strainDevice == 1){
    //val = nau.read();  //adafruit's
    val = nau.getReading();  //sparkfun's (raw values)
//    Failed attempt to zero, calibrate and display weight:
//    bool allowNegativeWeights = false;
//    uint8_t samplesToTake = 8;
//    val = nau.getWeight(allowNegativeWeights, samplesToTake); //Once you've set zero offset and cal factor, you can ask the library to do the calculations for you.
  }
    
    Serial.print("*");
    spacing2("*",12); 
    Serial.print(val);
    spacing(val,12); 
    
  }

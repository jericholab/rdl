
//-------------------------------------------------------------------
// FONCTION NAME: nau7802Function
// PURPOSE: obtain a measurement from the strain gauge cell
// INPUT: none
// OUTPUT: none

void nau7802Function() {

  //int32_t val = -1;
  float val = -1.00;
  
  if(strainDevice == 1){
    val = nau.read();
  }
    
    Serial.print("*");
    spacing2("*",12); 
    Serial.print(val);
    spacing(val,12); 
    
  }

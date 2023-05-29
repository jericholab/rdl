
//-------------------------------------------------------------------
// FONCTION NAME: nau7802Function
// PURPOSE: obtain a measurement from the strain gauge cell
// INPUT: none
// OUTPUT: none

void nau7802Function() {

  while (! nau.available()) {
    delay(1);
  }

  Serial.print("*");
  spacing2("*",12); 
  int32_t val = nau.read();
  Serial.print(val);
  Serial.print("   ");
  }

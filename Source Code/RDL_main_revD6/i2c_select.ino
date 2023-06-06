
//-------------------------------------------------------------------
// FONCTION NAME: i2c_select
// PURPOSE: select the channel (0-7) on the i2c multiplexer (PCA9548A)
// INPUT: none
// OUTPUT: none

void i2c_select(uint8_t i) {    //define a small function to select the i2c multiplexer channel
  if (i > 7) return;           //ensure that the selected channel value is between 0 and 7 (8 channel i2c mux)
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);    //// ????? Bitwise left shift operation ??
  Wire.endTransmission();  
}  

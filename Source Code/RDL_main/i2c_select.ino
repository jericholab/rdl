//-------------------------------------------------------------------
// FONCTION NAME: i2c_select
// PURPOSE: select the channel (0-7) on the i2c multiplexer (PCA9548A) and supply power to this channel
// INPUT: desired multiplexer channel as an integer, from 0 to 7
// OUTPUT: none

void i2c_select(uint8_t i) {    //define a small function to select the i2c multiplexer channel
  if (i > 7) return;           //ensure that the selected channel value is between 0 and 7 (8 channel i2c mux)
  tcaselect(i);
}

// Arduino.cc Reference: There are both 7 and 8-bit versions of I2C addresses. 7 bits identify the device, and the eighth bit determines
// if it’s being written to or read from. The Wire library uses 7 bit addresses throughout.
// If you have a datasheet or sample code that uses 8-bit address, you’ll want to drop the low bit
//(i.e. shift the value one bit to the right), yielding an address between 0 and 127."

//------------------------------------------------------------------
// FONCTION: setMultiplexer
// PURPOSE: set the multiplexer to the desired channel to allow reading the specific channel sensor
// INPUT: desired multiplexer channel as an integer, from 0 to 7
// RETURN: none

void setMultiplexer(int channel){
  digitalWrite(S0, bitRead(channel, 0));  // uses the first three bits of the channel number to set the channel select pins
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));          
}
//------------------------------------------------------------------

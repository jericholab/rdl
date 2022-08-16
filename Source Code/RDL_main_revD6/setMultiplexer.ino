//------------------------------------------------------------------
// FONCTION: setMultiplexer
// PURPOSE: set the multiplexer to the desired channel to allow reading the speiic channel sensor
// INPUT: desired multiplexer channel as an integer, from 0 to 15
// RETURN: none

int setMultiplexer(int channel)
{
// uses the first four bits of the channel number to set the channel select pins
digitalWrite(S0, bitRead(channel, 0));
digitalWrite(S1, bitRead(channel, 1));
digitalWrite(S2, bitRead(channel, 2));          
digitalWrite(S3, bitRead(channel, 3));

}
//------------------------------------------------------------------

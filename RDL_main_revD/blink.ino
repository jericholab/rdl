
//-------------------------------------------------------------------
// FONCTION: blink
// INPUT: duration of blinking effect, number of blinks
// OUTPUT: none
int blink(int duration, int times)
{
for (int i=1; i<(times+1); i++)
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
  delay(duration);                   // wait for a certain amount of time (milliseconds)
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  delay(duration);                   // wait for a certain amount of time (milliseconds)
}
}
//-------------------------------------------------------------------

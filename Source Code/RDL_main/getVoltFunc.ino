//-------------------------------------------------------------------
// FONCTION: getVoltFunc
// PURPOSE: measure sample, average and display the voltage tension value at the corresponding terminal
// INPUT: readMode
// OUTPUT: voltage

float getVoltFunc(bool readMode) {

  if (readMode == 1) {      //if the ADS115 is selected,

    ads1115.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
    //ads1115.setGain(GAIN_ONE);      // 1x gain   +/- 4.096V  1 bit = 2mV   // GAIN_ONE improves the resolution, but we don't get the full range (0-5V)
    //ads1115.setGain(GAIN_TWO);      // 2x gain   +/- 2.048V  1 bit = 1mV
    //ads1115.setGain(GAIN_FOUR);     // 4x gain   +/- 1.024V  1 bit = 0.5mV
    //ads1115.setGain(GAIN_EIGHT);    // 8x gain   +/- 0.512V  1 bit = 0.25mV
    //ads1115.setGain(GAIN_SIXTEEN);  // 16x gain  +/- 0.256V  1 bit = 0.125mV

    //ads1115.setDataRate(RATE_ads1115_128SPS);    //slow sample rate
    //ads1115.setDataRate(RATE_ads1115_1600SPS);   //medium sample rate (default)
    //ads1115.setDataRate(RATE_ads1115_3300SPS);   //fast sample rate
  }

  uint16_t i;                                                  // unsigned integer (16 bit) for loop iteration (between 0 and 65,535)
  float average = 0;                                           // create a new variable to store the sample average

  for (i = 0; i < NUMSAMPLES; i++) {                           // take N samples in a row, with a slight delay
    if (readMode == 0) {
      average += analogRead(VOLT_PIN);                        //read Nano ADC channel (Remember that Nano ADC saturates at 3.3V (due to permanent AREF=3.3V).
    }
    if (readMode == 1) {
      //else{

      average += ads1115.readADC_SingleEnded(ADS_V_PIN);              //read channel 1 of ads1115 and add to temporary sum
    }
  }
  average /= NUMSAMPLES;

  if (readMode == 0) {
    voltage = average / 1023 * V_ref; //convert ADC value to a voltage
  }
  else {
    voltage = average * 0.0001875;                               // PGA (Programmable Gain) (VREF*2/ADC_RANGE=6.144*2/65536 = 0.0001875)
  }
  ads1115.setGain(GAIN_TWOTHIRDS);                                // Reset to default in case it has been modified  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
  return voltage;
}

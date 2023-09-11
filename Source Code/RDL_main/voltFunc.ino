//-------------------------------------------------------------------
// FONCTION: voltFunc
// PURPOSE: measure and display the voltage tension value at the corresponding terminal
// INPUT: none
// OUTPUT: voltage

float voltFunc(){
      ads1015.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
      // ads1015.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
      // ads1015.setGain(GAIN_TWO);     // 2x gain   +/- 2.048V  1 bit = 1mV
      // ads1015.setGain(GAIN_FOUR);    // 4x gain   +/- 1.024V  1 bit = 0.5mV
      // ads1015.setGain(GAIN_EIGHT);   // 8x gain   +/- 0.512V  1 bit = 0.25mV
      // ads1015.setGain(GAIN_SIXTEEN); // 16x gain  +/- 0.256V  1 bit = 0.125mV
      
      uint16_t i;                                                   // unsigned integer (16 bit) for loop iteration (between 0 and 65,535)
      float average;                                               // create a new variable to store sample average
      average = 0;  
      for (i=0; i< NUMSAMPLES; i++)                                // take N samples in a row, with a slight delay
      {
       average += ads1015.readADC_SingleEnded(1);                   //read channel 1 (0, 1, 2, 3) ADS1015 and add to temporary sum
      }
      average /= NUMSAMPLES;
      float voltage = average * 0.003;        // PGA (Programmable Gain) (VREF*2/ADC_RANGE=6.144*2/4096 = 0.003)   
      Serial.print(voltage,3);         //print out the value you read.
      spacing(voltage,11);      
      return voltage;

}
  
      

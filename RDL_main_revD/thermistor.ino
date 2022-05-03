

//-------------------------------------------------------------------
// FONCTION NAME:thermistor
// INPUT: thermistorpin, seriesresistor, A, B, C
// OUTPUT: ohm value (ohm) and temperature value (oC) in a structure

struct STRUCT1 thermistor(float A, float B, float C, int channel)   //this creates a function called thermistor that is a member of the class SRUCT1
{
  uint8_t i;                                                   // unsigned integer (1 byte) for loop iteration
  float average;                                               // create a new variable to store sample average
  for (i=0; i< NUMSAMPLES; i++)                                // take N samples in a row, with a slight delay
  {
   samples[i] = analogRead(THERMISTORPIN);                     // store ADC current value to index 'i' of array 'samples'
  }
  average = 0;                                                 // initialize average temperature 
  for (i=0; i< NUMSAMPLES; i++)
  {
  average += samples[i];                                       // average all the samples out
  }
  average /= NUMSAMPLES;
  if(average==1023){                                           // avoid division by zero for ohmvalue
    average=1022;
  }
  float ohmvalue = Seriesresistor/(1023 / average - 1);        // ohms // convert the ADC average value to resistance
  ohmvalue = ohmvalue - R_MUX - R_wire[(channel-1)];           // ohms //remove electric resistance of multiplexer and extension wire.
  float steinhart;                                             // define steinhart as a placeholder floating number
  steinhart = log(ohmvalue);                                   //log(x) means natural logarithm in Arduino 
  steinhart = A + B * steinhart + C*steinhart*steinhart*steinhart;  //using 'a*a*a' to avoid exponential operations (would require loading library 'math.h')
  steinhart =  1.0 / steinhart;
  if (units == 0){
      steinhart = steinhart - 273.15;                          // convert temperature from Kelvin to Celcius
  }
  if (units == 1){
      steinhart = (steinhart - 273.15)*9/5+32;                 // convert temperature from Kelvin to Celcius to Fahrenheit
  }
  if (units == 2){
  // leave temperature as kelvin (do nothing)
  }
  STRUCT1 values = { ohmvalue, steinhart };                    // a function can only return one value that is seen in the main scope of the program. However, the return can be a structure. So we create another member of the class STRUCT1 called values.
  return values;
}

//-------------------------------------------------------------------

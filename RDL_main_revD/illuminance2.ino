//-------------------------------------------------------------------
// FONCTION NAME: illuminance
// INPUT: resistance (ohm)
// OUTPUT: illuminance (lux)

struct STRUCT1 illuminance2(int channel)   //this creates a function called relhum that is a member of the class SRUCT2, that is a struct data type.

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
  if(average==1023){                                           // avoid division by zero for ohmvalue
    average=0;
  }
  average /= NUMSAMPLES;
  float ohmvalue = Seriesresistor/(1023 / average - 1);        // ohms // convert the ADC average value to resistance
  ohmvalue = ohmvalue - R_MUX - R_wire[(channel-1)];           // ohms //remove electric resistance of multiplexer and extension wire.
  float temp1=(4.4451-log10(ohmvalue))/0.6;
  float value = pow(10,temp1);                                 //raises base to the exponent (pow(base,exponent))
  value = round(value);                                        //round float value to nearest integer
  STRUCT1 illuminance = {ohmvalue,value};                      // a function can only return one value that is seen in the main scope of the program. However, the return can be a structure. So we create another member of the class STRUCT1 called values.
  return illuminance;
}
//-------------------------------------------------------------------

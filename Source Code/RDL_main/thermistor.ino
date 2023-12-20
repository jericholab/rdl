//-------------------------------------------------------------------
// FONCTION NAME: thermistor
// PURPOSE: measure the resistance value of a thermistor probe and convert it to temperature, based on applicable calibration coefficients.
// INPUT: thermistorpin, seriesresistor, A, B, C
// OUTPUT: ohm value (ohm) and temperature value (oC) in a structure

struct STRUCT1 thermistor(float A, float B, float C, int channel)   //this creates a function called thermistor that is a member of the class STRUCT1
{
  uint16_t i;                                                   // unsigned integer (16 bit) for loop iteration (between 0 and 65,535)
  //long average;  //test 2023-09-22 to try to accelerate loop sums
  float average;       /////////// I should find a way to make the sampling using 'Long' average but later transform to float to allow math operations (see below)/////////
  float ohmvalue;  //initialize variable
  bool readMode = 1;  //////// Temporary, until I add readMode to function inputs///////////////

  //float average;                                               // create a new variable to store sample average
  average = 0;  
  for (i=0; i< NUMSAMPLES; i++)                                // take N samples in a row, with a slight delay
  {
   if (readMode ==0){
     average += analogRead(THERMISTORPIN);                       //read Nano ADC channel
   }
   if (readMode ==1){
     average += ads1115.readADC_SingleEnded(0);                   //read channel 0 of ADS1015 and add to temporary sum  ////////////TEMPORARY COMMENTED
   }
   
  }
  average /= NUMSAMPLES;
  if(average==ADCrange){                                           // avoid division by zero for ohmvalue
    average=ADCrange - 1;
  }
  
  
  if (readMode ==0){

    ohmvalue = Seriesresistor/(1023 / average - 1);        // ohms // convert the ADC average value to resistance

  }
  if (readMode ==1){
    float voltage = average * 0.003;                               // PGA (Programmable Gain) (VREF*2/ADC_RANGE=6.144*2/4096 = 0.003) 
    if (voltage>3.3){
      voltage=3.2999;    //cap voltage reading at 3.3V to avoid NaN print out.
    }
    ohmvalue = Seriesresistor * voltage /(3.3-voltage);      // (ADC logic voltage (6.144V) is not the same as the ARef voltage now (3.3V), so the voltages reappear in the equations.
  }

  ohmvalue = ohmvalue - R_MUX - R_wire[(channel-1)];           // ohms //remove electric resistance of multiplexer and extension wire.

  //Serial.println(ohmvalue); 
  
  float steinhart;                                             // define steinhart as a placeholder floating number
  steinhart = log(ohmvalue);                                   // log(x) means natural logarithm in Arduino 
  steinhart = A + B * steinhart + C*steinhart*steinhart*steinhart;  //using 'a*a*a' to avoid exponential operations (would require loading library 'math.h')
  steinhart =  1.0 / steinhart;
  if (units_T == 0){
      steinhart = steinhart - 273.15;                          // convert temperature from Kelvin to Celcius
  }
  if (units_T == 1){
      steinhart = (steinhart - 273.15)*9/5+32;                 // convert temperature from Kelvin to Celcius to Fahrenheit
  }
  if (units_T == 2){
  // leave temperature as kelvin (do nothing)
  }
  STRUCT1 values = { ohmvalue, steinhart };                    // a function can only return one value that is seen in the main scope of the program. However, the return can be a structure. So we create another member of the class STRUCT1 called values.
  return values;
}

//-------------------------------------------------------------------

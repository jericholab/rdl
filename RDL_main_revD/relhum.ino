//-------------------------------------------------------------------
// FONCTION NAME: relhum
// INPUT: dry bulb temperature (Celcius), wet bulb temperature (Celcius), atmospheric pressure (hPa) , units (-)
// OUTPUT: relative humidity 
// (in the future, the absolute humidity and dew point might be added as outputs)

//struct STRUCT2 relhum(float dryBulb, float wetBulb, int atmPress, int units)   //this creates a function called relhum that is a member of the class SRUCT2, that is a struct data type.
float relhum(float dryBulb, float wetBulb, int atmPress, int units)   //this creates a function called relhum that is a member of the class SRUCT2, that is a struct data type.
{
  
 if (units == 0){
      //do nothing                          // if the TDL is operating in Celcius, then the temperatures are already compatible
  }
  if (units == 1){                           // if the TDL is operating in Fahrenheit, then the temperatures need to be converted to Celcius first
      dryBulb = (dryBulb-32)*5/9;
      wetBulb = (wetBulb-32)*5/9;              
  }
  if (units == 2){                               // if the TDL is operating in Kelvin, then the temperatures need to be converted to Celcius first
      dryBulb = dryBulb -273.15;
      wetBulb = wetBulb - 273.15;
  }
  
  float ed = 6.112 * exp((17.67 * dryBulb) / (dryBulb + 243.5));    //dry bulb saturation pressure ?
  float ew = 6.112 * exp((17.67 * wetBulb) / (wetBulb + 243.5));     //wet bulb saturation pressure ?
  float N = 0.6687451584;      //////// I am not too sure about the version of my equations for relative humidity calculations. what is my reference ?
  float value = (ew - N * (1 + 0.00115 * wetBulb) * (dryBulb - wetBulb)) / ed;
  value = round(100*value);

  //STRUCT2 relhum = {value};                    // a function can only return one value that is seen in the main scope of the program. However, the return can be a structure. 
  
  //return relhum;
  return value;
}
//-------------------------------------------------------------------

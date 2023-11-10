////-------------------------------------------------------------------
//// FONCTION NAME: relhum
//// PURPOSE: calculate the relative humidity of the air based on dry and wet bulb values
//// INPUT: dry bulb temperature (Celcius), wet bulb temperature (Celcius), atmospheric pressure (hPa) , units (-)
//// OUTPUT: relative humidity 
//
//float relhum(float dryBulb, float wetBulb, int atmPress, int units)   //this creates a function called relhum that is a member of the class SRUCT2, that is a struct data type.
//{
//  
// if (units == 0){
//      //do nothing                          // if the RDL is operating in Celcius, then the temperatures are already compatible
//  }
//  if (units == 1){                           // if the RDL is operating in Fahrenheit, then the temperatures need to be converted to Celcius first
//      dryBulb = (dryBulb-32)*5/9;
//      wetBulb = (wetBulb-32)*5/9;              
//  }
//  if (units == 2){                               // if the RDL is operating in Kelvin, then the temperatures need to be converted to Celcius first
//      dryBulb = dryBulb -273.15;
//      wetBulb = wetBulb - 273.15;
//  }
//
//// Weather.gov version of the Antoine equation (https://www.weather.gov/epz/wxcalc_wetbulb)
////  float ed = 6.112 * exp((17.67 * dryBulb) / (dryBulb + 243.5));    // saturation vapor pressure (ed)
////  float ew = 6.112 * exp((17.67 * wetBulb) / (wetBulb + 243.5));     //vapor pressure related to the wet bulb temperature (ew)
////  float N = 0.6687451584; 
////  float value = (ew - N * (1 + 0.00115 * wetBulb) * (dryBulb - wetBulb)) / ed;
////  value = round(100*value);
//
//// New humidity equation (Not tested yet) (Butler and Garcia-Suarez, 2012)
//float es_db = exp((16.78 * dryBulb - 116.9)/(dryBulb + 237.3));  //saturated vapor pressure at dry bulb temperature 
//float es_wb = exp((16.78 * wetBulb - 116.9)/(wetBulb + 237.3));  //saturated vapor pressure at wet bulb temperature
//float A= 0.00066*(1.0 + 0.00115*wetBulb);  //conversion factor
//float P = 101.3;   //mean atmospheric pressure (kPa)
//float e_db = es_wb - A * P * (dryBulb - wetBulb);  //real vapor pressure
//float value = 100 * e_db/es_db;  //relative humidity (%)
//
////Specific humidity equation by Buck (1996)
////(w= 216.7 * e / Tk) //http://www.hygrometers.com/wp-content/uploads/CR-1A-users-manual-2009-12.pdf
////Tk = dryBulb + 273.15;  //dry temperature (K)
////float value = 216.7 * e_db /Tk;  //specific humidity (kg/kg)
//
//  return value;
//}
////-------------------------------------------------------------------

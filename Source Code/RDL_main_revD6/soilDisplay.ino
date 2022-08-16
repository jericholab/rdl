
//-------------------------------------------------------------------
// FONCTION: soilFunc
// PURPOSE: convert the gypsum block resistance to a soil water content value, with temperature compensation.
// INPUT: none
// OUTPUT: none

int soilFunc(){
      float soil_R = arrayR[0] ;   //plaster block resistance, fixed channel (C1 = array 0, C2 is array 1, etc.)
      float soil_T = arrayV[1] ;   //temperature probe for temperature compensation of the plaster block reading
      //float soilWater = 10;      //temp test //soil water content (g/cm3)
      float soilWater_uncorr = 0.0577*pow(log10(soil_R),2) - 0.6996*(log10(soil_R))+2.0933;    //water content, uncorrected for temperature
      float soilWater = soilWater_uncorr-0.0017*(soil_T-21);                        //water content, corrected for temperature, referenced at 21C.
      //Serial.print(soil_R); //optional printing of the raw resistance value of the plaster block
      //Serial.print(soil_T); //optional printing of the raw temperature value (temperature compensation)
      //spacing2("*",12); //optional printing
      Serial.print(soilWater,3);   //print with 3 decimals  
      spacing(soilWater,12);     

}

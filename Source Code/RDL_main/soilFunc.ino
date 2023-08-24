
//-------------------------------------------------------------------
// FONCTION: soilFunc
// PURPOSE: convert the gypsum block resistance to a soil water content value, with temperature compensation.
// INPUT: none
// OUTPUT: none

int soilFunc(){    
      int T_compensation = 1;          //optional temperature compensation of the gypsum block measurement (1 = yes, 0 = no)
      float soil_R = arrayR[0] ;   //plaster block resistance, fixed channel (C1 = array 0, C2 is array 1, etc.)
      float soil_T = arrayV[1] ;   //temperature probe for temperature compensation of the plaster block reading
      float soilWater_uncorr = 0.0577*pow(log10(soil_R),2) - 0.6996*(log10(soil_R))+2.0933;    //water content equation, uncorrected for temperature
      float soilWater = soilWater_uncorr-0.0017*(soil_T-21);  //water content, corrected for temperature, referenced at 21C.   
      if (T_compensation ==1){
        Serial.print(soilWater,3);   //print temperature-corrected value with 3 decimals
        spacing(soilWater,11);     //13 instead of 12 because a third decimal is printed but the spacing() function assumes 2.
      }
      else{
        Serial.print(soilWater_uncorr,3);   //print uncorrected value with 3 decimals. Decomment this line and deactivate the previous one if you want to use non-tempertaure-compensated mode.  
        spacing(soilWater,11);     //13 instead of 12 because a third decimal is printed but the spacing() function assumes 2.
      }
      


}

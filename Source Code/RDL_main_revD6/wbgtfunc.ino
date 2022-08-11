
//-------------------------------------------------------------------
// FONCTION: WBGTfunc
// INPUT: none
// OUTPUT: none

int wbgtFunc(){
      float WetBulb= arrayV[WBGT_wet-1];    // "Minus 1" to convert Channel number to Multiplexer Array (indexed to 0)
      float BlackGlobe=arrayV[WBGT_globe-1] ; 
      float DryBulb=arrayV[WBGT_dry-1];
      float WBGT = 0.7*WetBulb + 0.2*BlackGlobe + 0.1*DryBulb;  //WBGT equation for outdoors
      Serial.print(WBGT);  
      spacing(WBGT,12);  
}

//-------------------------------------------------------------------
// FONCTION: voltMainFunc
// PURPOSE: Operate the 3 MUX to enable reading channels associated with analog sensors
// INPUT: none
// OUTPUT: none

void voltMainFunc(){

      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the A_MUX
      Serial.print("*");
      spacing2("*",12);  
      for (int i=0; i< (numberV); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel                   
        int channel = i+1;                            //channel being measured
        voltFunc();                                   // storing voltages to array  
        delay(50);
      }
      //digitalWrite(enable_V_MUX, HIGH);                          // toggle pin to LOW value in order turn on the A_MUX     
}
  
      

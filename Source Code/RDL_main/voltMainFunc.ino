//-------------------------------------------------------------------
// FONCTION: voltMainFunc
// PURPOSE: Operate the 3 MUX to enable reading channels associated with analog sensors
// INPUT: none
// OUTPUT: none

void voltMainFunc(){

      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the A_MUX
      analogReference(DEFAULT);      //put the analog reference back to 5V to allow reading 0-5V signals
      delay(10);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      Serial.print("*");
      spacing2("*",12);  
      for (int i=0; i< (numberV); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel                   
        delay(50);
        int channel = i+1;                            //channel being measured
        voltFunc();                                   // storing voltages to array  
        //delay(50);
      }
      //digitalWrite(enable_V_MUX, HIGH);               //TEST           // toggle pin to LOW value in order turn on the A_MUX     
      analogReference(EXTERNAL);     //put the analog reference back to 3.3V
}
  
      

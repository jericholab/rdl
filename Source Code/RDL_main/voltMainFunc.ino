//-------------------------------------------------------------------
// FONCTION: voltMainFunc
// PURPOSE: Operate the 3 MUX to enable reading channels associated with analog sensors
// INPUT: none
// OUTPUT: none

void voltMainFunc(){
  
      float value;                                              //local variable declaration
      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      delay(100);                                              //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      Serial.print("*");
      spacing2("*",12);  

      for (int i=0; i< (numberV); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel                   
        delay(100);
        value=voltFunc();                             // storing voltages 
        Serial.print(value,2);
        spacing(value,12);
      }
      //digitalWrite(enable_V_MUX, HIGH);                         // toggle pin to HIGH value in order turn off the V_MUX     
}
  
      

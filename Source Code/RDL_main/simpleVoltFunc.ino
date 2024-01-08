//-------------------------------------------------------------------
// FONCTION: simpleVoltFunc
// PURPOSE: Provides a simple voltage reading from all available channels.
// INPUT: none
// OUTPUT: none

void simpleVoltFunc(){
      bool readMode = 1;  
      float value;                                              //local variable declaration
      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      delay(100);                                              //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      Serial.print("*");
      spacing2("*",12);  

      for (int i=0; i< (numberV); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel
        pcf1.digitalWrite(i, LOW);  // turn LED on by sinking current to ground
        pcf2.digitalWrite(i, HIGH);  // turn LED on by sinking current to ground
        delay(100);
        value=getVoltFunc(readMode);                             // storing voltages 
        Serial.print(value,2);
        spacing1(value,12);
        pcf1.digitalWrite(i, HIGH); //turn LED off by turning off sinking transistor
        pcf2.digitalWrite(i, LOW);  //turn LED off by turning off sinking transistor
      }
}
  
      

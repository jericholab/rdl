//-------------------------------------------------------------------
// FONCTION: simpleVoltFunc
// PURPOSE: Provides a voltage reading from all activated channels.
// INPUT: none
// OUTPUT: none

void simpleVoltFunc(){
      bool readModeVolt = 1;         // Value 0 = Nano ADC (for 0-3.3V readings only). Value 1 = ADS1115 (for 0-5V readings only).
      float value;                                              //local variable declaration
      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      delay(100);                                               //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      Serial.print("*");
      spacing2("*",12);  

      for (int i=0; i< (numberV); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel
        pcf1.digitalWrite(i, LOW);  // turn LED on by sinking current to ground
        pcf2.digitalWrite(i, HIGH);  // turn LED on by sinking current to ground
        delay(100);
        value=getVoltFunc(readModeVolt);                             // storing voltages 
        Serial.print(value,4);
        spacing1(value,10);
        pcf1.digitalWrite(i, HIGH); //turn LED off by turning off sinking transistor
        pcf2.digitalWrite(i, LOW);  //turn LED off by turning off sinking transistor
      }
}
  
      

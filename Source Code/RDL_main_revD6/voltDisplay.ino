//-------------------------------------------------------------------
// FONCTION: voltFunc
// PURPOSE: measure and display the voltage tension value at the corresponding terminal
// INPUT: none
// OUTPUT: none

int voltFunc(){
      analogReference(DEFAULT);      //put the analog reference back to 5V to allow reading 0-5V signals
      delay(10);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      int sensorValue;               //variable declaration
      for (int i= 1; i<5; i++){
        sensorValue = analogRead(A1);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
      }
      analogReference(EXTERNAL);     //put the analog reference back to 3.3V
      float voltage = sensorValue * (V_ref / 1023.0);  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
      Serial.print("*");
      spacing2("*",12);      
      Serial.print(voltage);         //print out the value you read.
}
  
      

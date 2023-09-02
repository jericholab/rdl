//-------------------------------------------------------------------
// FONCTION: voltFunc
// PURPOSE: measure and display the voltage tension value at the corresponding terminal
// INPUT: none
// OUTPUT: none

void voltFunc(){

      int sensorValue;               //variable declaration
      //for (int i= 1; i<5; i++){
        sensorValue = analogRead(A1);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
      //}
      float voltage = sensorValue * (V_ref / 1023.0);  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
    
      Serial.print(voltage,2);         //print out the value you read.
      spacing(voltage,12);      

}
  
      

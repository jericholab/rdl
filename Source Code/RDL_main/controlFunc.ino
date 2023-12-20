//-------------------------------------------------------------------
// FONCTION NAME: controlFunc
// PURPOSE: Update the control signal (code example: if temperature is warmer inside than outside start the fan)
// INPUT: none
// OUTPUT: none

void controlFunc(){
  int value;                         //initialize variable
  if(arrayV[0]<arrayV[1]){
    digitalWrite(9, HIGH);           //example function with conditional digital output
    value = 1;
  }
  else{
    digitalWrite(9, LOW);
    value = 0;
  }
   
  Serial.print(F("*"));
  spacing2(F("*"),12);      
  Serial.print(value);                          //print out the control signal.
}

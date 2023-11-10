//-------------------------------------------------------------------
// FONCTION NAME: controlSignal
// PURPOSE: update the control signal (code example: if temperature is warmer inside than outside start the fan)
// INPUT: none
// OUTPUT: binary value (0,1)

void controlFunc(){
  int value;
  
  if(arrayV[0]<arrayV[1]){
    digitalWrite(9, HIGH);                            /// SAMPLE TEST OF CONDITIONAL DIGITAL OUTPUT SIGNAL CONTROL
    value = 1;
  }
  else{
    digitalWrite(9, LOW);
    value = 0;
  }
  
  //return value;
  
  Serial.print(F("*"));
  spacing2("*",12);      
  Serial.print(value);         //print out the control signal.
}

//-------------------------------------------------------------------
// FONCTION: terosFunc
// PURPOSE: Print to serial monitor some informations about the RDL parameters
// INPUT: none
// OUTPUT: none

int terosFunc(){
  
  digitalWrite(9, HIGH);                           //set pin D9 to HIGH (VCC 5V)
  
  delay (100); //wait 1000ms
  
  int sensorValue = analogRead(A2);  // read the input on analog pin 0:

  digitalWrite(9, LOW);                           //set pin D9 to HIGH (VCC 5V)
  
  //Serial.print(sensorValue); // print out the value you read:
  //Serial.print("   ");
  Serial.print("*");
  spacing2("*",12);      
  float voltage1 = sensorValue * (V_ref / 1023.0) * 1000;  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5000mV)
  Serial.print(voltage1,3);  //mVolts
  Serial.print("   ");

  float VWC = 4.824E-10 * pow(voltage1,3) - 2.278E-06*pow(voltage1,2) + 3.898E-03*voltage1 - 2.154;
  Serial.print(VWC,3);  //mVolts
  //Serial.println();

  
  }

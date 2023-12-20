//-------------------------------------------------------------------
// FONCTION: terosFunc
// PURPOSE: Print to serial monitor some informations about the RDL parameters
// INPUT: none
// OUTPUT: none


///// To Do: Test the arduino code that GPT created for the van genuchten equation (water retention curve)

void terosFunc(){
  
  //digitalWrite(9, HIGH);                           //set pin D9 to HIGH (VCC 5V) /////////////////// still valid?
  //delay (100); //wait 1000ms

  digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
  delay(50);                                    //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
  setMultiplexer(3);                             // select the multiplexer channel                   
  delay(500);
  bool readMode = 1;
  float sensorValue = getVoltFunc(readMode);  // read the voltage while assuming a 5000mV voltage reference

  //digitalWrite(9, LOW);                           //set pin D9 to HIGH (VCC 5V)   /////////////////// still valid?
  
  //Serial.print(sensorValue); // print out the value you read:
  //Serial.print("   ");
  Serial.print("*");
  spacing2("*",12);      
  //float voltage1 = sensorValue * (V_ref / 1023.0) * 1000;  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5000mV)
  float voltage1 = sensorValue * 1000;
  Serial.print(voltage1,2);  //mVolts
  spacing1(voltage1,12);


  float VWC = 4.824E-10 * pow(voltage1,3) - 2.278E-06*pow(voltage1,2) + 3.898E-03*voltage1 - 2.154;
  Serial.print(VWC,3);  //mVolts
  spacing1(VWC,11);  // since a bonus decimal is printed, the spacing requirement is reduced by one unit.
  }

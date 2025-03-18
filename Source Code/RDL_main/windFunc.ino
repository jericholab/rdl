//-------------------------------------------------------------------
// FONCTION: windFunc
// PURPOSE: Calculates the current value of the TEROS 10 soil humidity sensor, based on manufacturer VWC eq. and van genuchten equation (pressure)
// INPUT: none
// OUTPUT: none


void windFunc(uint8_t channel){                                  
//  pinMode(VOLT_PIN, INPUT);    // Set VOLT_PIN back to input mode for analog reading (if needed)

  Serial.println("We reached windFunc() content");    //TEST ////////////////////
  delay(1000);  // part of test

  digitalWrite(enable_V_MUX, LOW);               // toggle pin to LOW value in order turn on the V_MUX
  Serial.println("We  achieved enable_V_MUX in windFunc");    //TEST ////////////////////
  setMultiplexer(channel);                       // select the multiplexer channel
  pcf1.digitalWrite(channel, LOW);               // turn LED on by sinking current to ground
  pcf2.digitalWrite(channel, HIGH);              // turn LED on by sinking current to ground
  delay(500);  //TEMPORARY COMMENT TO MAKE LONG MEASUREMENT VIA MULTIMETER
  //delay (5000);  //TEMPORARY COMMENT TO MAKE LONG MEASUREMENT VIA MULTIMETER

  //Serial.println("We reached achieved initialization windFunc");    //TEST ////////////////////


  bool readMode = 1;
  float sensorVoltage = getVoltFunc(readMode);           // read the voltage while assuming a 5000mV voltage reference

  float minVoltage = 0.4; // Voltage corresponding to 0 m/s wind speed
  float maxVoltage = 2.0; // Voltage corresponding to 32.4 m/s wind speed
  float maxWindSpeed = 32.4; // in m/s

  float windSpeed = mapFloat(sensorVoltage, minVoltage, maxVoltage, 0, maxWindSpeed);
  Serial.print("*");
  spacing2("*",12);      
  Serial.print(windSpeed,2);                            // m/s
  spacing1(windSpeed,12);

  pcf1.digitalWrite(channel, HIGH); //turn LED off by turning off sinking transistor
  pcf2.digitalWrite(channel, LOW);  //turn LED off by turning off sinking transistor

  }

  ///// WATER TENSION FUNCTION TETA (VAN GENUCHTEN EQUATION)

// Function to map float values
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

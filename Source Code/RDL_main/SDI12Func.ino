//-------------------------------------------------------------------
// FUNCTION: SDI12Func
// PURPOSE: Query and retrieve data from the pyranometer sensors
// INPUT: channel on which the pyranometer is connected
// OUTPUT: none


void SDI12Func(uint8_t channel){

  /// Serial.println("We reached SDI12Func() content");    //TEST ////////////////////
  
  pinMode(VOLT_PIN, OUTPUT);   // Set VOLT_PIN as digital output for SDI-12 communication

  String irradiationCmd = "0M!";    // command to measure irradiation 
  String tiltAngleCmd = "0M3!";      // command to measure tilt angle
  String retrieveDataCmd = "0D0!";   // command to retrieve reading from the sensor

  digitalWrite(enable_V_MUX, LOW);               // toggle pin to LOW value in order turn on the V_MUX
  delay(200);
  setMultiplexer(channel);                       // select the multiplexer channel
  pcf1.digitalWrite(channel, LOW);               // turn LED on by sinking current to ground
  pcf2.digitalWrite(channel, HIGH);              // turn LED on by sinking current to ground
  delay(500);  //TEMPORARY COMMENT TO MAKE LONG MEASUREMENT VIA MULTIMETER
  //delay (5000);  //TEMPORARY COMMENT TO MAKE LONG MEASUREMENT VIA MULTIMETER

  String sensorResponse = "";   // string to store the sensor response after a query
  
  // Retrieve and print Irradiation Data
  sensorResponse = getSDI12Data(irradiationCmd);    // send command to measure irradiation
  String sensorIrradiationValue = getSDI12Data(retrieveDataCmd);  // string that holds retrieved incoming irradiation data 
  sensorIrradiationValue.trim();   // remove ending characters
  float irradiationData = sensorIrradiationValue.toFloat();    // convert to float
  Serial.print("*");
  spacing2("*",12);  
  Serial.print(irradiationData, 2);     // print measurement value only (W/m²)
  spacing1(irradiationData,12);

  if (tiltAngleDisplay == 1){
    // Retrieve Tilt Angle Data
    sensorResponse = getSDI12Data(tiltAngleCmd);      // send command to measure tilt angle
    String sensorTiltAngleValue = getSDI12Data(retrieveDataCmd);    // string that holds retrieved incoming tilt angle data 
    sensorTiltAngleValue.trim();   // remove ending characters
    float tiltAngleData = sensorTiltAngleValue.toFloat();    // convert to float
    Serial.print(tiltAngleData, 2);       // print measurement value only
    spacing1(tiltAngleData,13);
  }
  
  digitalWrite(enable_V_MUX, HIGH);               // toggle pin to HIGH value in order turn OFF the V_MUX
  delay(100);
  pinMode(VOLT_PIN, INPUT);    // Set VOLT_PIN back to input mode for analog reading (if needed)
  
  pcf1.digitalWrite(channel, HIGH); //turn LED off by turning off sinking transistor
  pcf2.digitalWrite(channel, LOW);  //turn LED off by turning off sinking transistor
  delay(500);  //troubleshoot test

}

// Function to send an SDI-12 command and retrieve data
String getSDI12Data(String command) {
  String response = "";  // String to hold incoming bytes

  mySDI12.sendCommand(command);   // send command to sensor
  delay(2000);                     // wait a while for a response

  // As long as there is data in the sensor line
  while (mySDI12.available()) {  
    char incomingChar = mySDI12.read();  // Read each byte as a character
    response += incomingChar;            // Append the character to the string
  }

  return response.substring(2);  // Return the data as a string
}

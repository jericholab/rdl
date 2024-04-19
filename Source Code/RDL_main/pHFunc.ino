//-------------------------------------------------------------------
// FONCTION: phFunc
// PURPOSE: Communicate with the ATLAS EZO-pH meter and provide pH values
// INPUT: none
// OUTPUT: none

void phFunc(){

  #define address 99               //default I2C ID number for EZO pH Circuit.
  char computerdata[20];           //we make a 20 byte character array to hold incoming data from a pc/mac/other.
  byte received_from_computer = 0; //we need to know how many characters have been received.
  byte serial_event = 0;           //a flag to signal when data has been received from the pc/mac/other.
  byte code = 0;                   //used to hold the I2C response code.
  char ph_data[32];                //we make a 32 byte character array to hold incoming data from the pH circuit.
  byte in_char = 0;                //used as a 1 byte buffer to store inbound bytes from the pH Circuit.
  byte i = 0;                      //counter used for ph_data array.
  int time_ = 815;                 //used to change the delay needed depending on the command sent to the EZO Class pH Circuit. 815 ms are required for reading or calib commands.
  float ph_float;                  //float var used to hold the float value of the pH.


  strcpy(computerdata, "r");                   // 'r' is the command expected by the Atlas MCU for reading pH
  serial_event = true;  
  delay(500);

  
  Wire.beginTransmission(address);                                              //call the circuit by its ID number.
  Wire.setClock(clockSpeed);                         // clockSpeed must be prescribed after library begins because it overrides the parameter by reinitializing the Wire library.
  Wire.write(computerdata);                                                     //transmit the command that was sent through the serial port.
  Wire.endTransmission();                                                       //end the I2C data transmission.

  delay(time_);                                                               //wait the correct amount of time for the circuit to complete its instruction.

  Wire.requestFrom(address, 32, 1);                                           //call the circuit and request 32 bytes (this may be more than we need)
  code = Wire.read();                                                         //the first byte is the response code, we read this separately.

  while (Wire.available()) {            //are there bytes to receive.
    in_char = Wire.read();              //receive a byte.
    ph_data[i] = in_char;               //load this byte into our array.
    i += 1;                             //incur the counter for the array element.
    if (in_char == 0) {                 //if we see that we have been sent a null command.
      i = 0;                            //reset the counter i to 0.
      break;                            //exit the while loop.
    }
  }

  ph_float=atof(ph_data);                 // take the pH value and convert it into floating point number.

  Serial.print(F("*"));
  spacing2(F("*"),12); 
  Serial.print(ph_float,3);             //print the data.
  spacing1(ph_float,11);

}

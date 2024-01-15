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
  int time_ = 815;                 //used to change the delay needed depending on the command sent to the EZO Class pH Circuit.
  float ph_float;                  //float var used to hold the float value of the pH.


  strcpy(computerdata, "R");                   // 'R' is the command expected by the Atlas MCU for reading pH
  serial_event = true;  
  delay(500);

    for (i = 0; i <= received_from_computer; i++) {                               //set all char to lower case, this is just so this exact sample code can recognize the "sleep" command.
      computerdata[i] = tolower(computerdata[i]);                                 //"Sleep" ≠ "sleep"
    }
    i=0;                                                                          //reset i, we will need it later 
    if (computerdata[0] == 'c' || computerdata[0] == 'r')time_ = 815;             //if a command has been sent to calibrate or take a reading we wait 815ms so that the circuit has time to take the reading.
    else time_ = 250;                                                             //if any other command has been sent we wait only 250ms.
    

    Wire.beginTransmission(address);                                              //call the circuit by its ID number.
    Wire.write(computerdata);                                                     //transmit the command that was sent through the serial port.
    Wire.endTransmission();                                                       //end the I2C data transmission.


    if (strcmp(computerdata, "sleep") != 0) {                                      //if the command that has been sent is NOT the sleep command, wait the correct amount of time and request data.
                                                                                  //if it is the sleep command, we do nothing. Issuing a sleep command and then requesting data will wake the circuit.

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

 
    ph_float=atof(ph_data);    // take the pH value and convert it into floating point number.

      Serial.print(F("*"));
      spacing2(F("*"),12); 
      Serial.print(ph_float);              //print the data.
      spacing1(ph_float,12);
    } 
}

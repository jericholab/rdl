/* CALIBRATION OF PH METER FOR RESISTANCE DATA LOGGER (RDL) SOURCE CODE
   Copyright (c) 2024 Jericho Laboratory Inc.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. 

This code will output data to the Arduino serial monitor.
Set variable AUTO_READ to true to enable auto-read or false to disable.
It assumes that the pH meter is already in I2C mode. To switch from UART mode to I2C mode, use the ezo-ph_switch-to-i2c code from the Github repository.
Type commands into the Arduino serial monitor to control the Ph circuit.
For more information about the Atlas Scientific EZO PH meter: https://files.atlas-scientific.com/pH_EZO_Datasheet.pdf

Popular commands syntax
Baud            switch back to UART mode
Cal,mid,7.00    single point calibration at midpoint
Cal,low,4.00    two point calibration at lowpoint
Calhigh,10.00   three point calibration at highpoint
Cal, clear      delete calibration data
Cal,?           device calibrated?
Export          export calibration
Factory –       enable factory reset
Find            finds device with blinking white LED
i               device information
I2C             change I²C address
Import          import calibration
L               enable/disable LED
Name            set/show name of device
pHext           enable/disable extended pH scale
Plock           enable/disable protocol lock
R               returns a single reading
Sleep           enter sleep mode/low power
Slope           returns the slope of the pH probe
Status          retrieve status information
T               temperature compensation
*/

#include <Wire.h>                //enable I2C.
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

// -------- AUTO-READ additions --------
bool AUTO_READ = false;                          // Set to true to enable auto-read or false to disable
const unsigned long AUTO_PERIOD_MS = 5000;      // 5 seconds
unsigned long _auto_last_ms = 0;
// -------------------------------------

void setup()                     //hardware initialization.
{
  Serial.begin(57600);           //enable serial port.
  Wire.begin();                 //enable I2C port.
}

void serialEvent() {                                                              //this interrupt will trigger when the data coming from the serial monitor(pc/mac/other) is received.
  received_from_computer = Serial.readBytesUntil(13, computerdata, 20);           //we read the data sent from the serial monitor(pc/mac/other) until we see a <CR>. We also count how many characters have been received.
  computerdata[received_from_computer] = 0;                                       //stop the buffer from transmitting leftovers or garbage.
  serial_event = true;                                                            //set the serial event flag.
}

void loop() {                                                                     //the main loop.

  // -------- AUTO-READ additions --------
  if (AUTO_READ && !serial_event) {                       // don't override a manual command
    unsigned long now = millis();
    if (now - _auto_last_ms >= AUTO_PERIOD_MS) {
      strcpy(computerdata, "r");                          // send a read command
      received_from_computer = 1;                         // length of "r"
      serial_event = true;                                // trigger the existing handling path
      _auto_last_ms = now;                                // reset timer
    }
  }
  // -------------------------------------

  if (serial_event == true) {                                                     //if a command was sent to the EZO device.
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

      switch (code) {                       //switch case based on what the response code is.
        case 1:                             //decimal 1.
          Serial.println("Success");        //means the command was successful.
          break;                            //exits the switch case.

        case 2:                             //decimal 2.
          Serial.println("Failed");         //means the command has failed.
          break;                            //exits the switch case.

        case 254:                           //decimal 254.
          Serial.println("Pending");        //means the command has not yet been finished calculating.
          break;                            //exits the switch case.

        case 255:                           //decimal 255.
          Serial.println("No Data");        //means there is no further data to send.
          break;                            //exits the switch case.
      }

      while (Wire.available()) {            //are there bytes to receive.
        in_char = Wire.read();              //receive a byte.
        ph_data[i] = in_char;               //load this byte into our array.
        i += 1;                             //incur the counter for the array element.
        if (in_char == 0) {                 //if we see that we have been sent a null command.
          i = 0;                            //reset the counter i to 0.
          break;                            //exit the while loop.
        }
      }

      Serial.println(ph_data);              //print the data.
    }
    serial_event = false;                   //reset the serial event flag.
  }
  //Uncomment this section if you want to take the pH value and convert it into floating point number.
  //ph_float=atof(ph_data);
}

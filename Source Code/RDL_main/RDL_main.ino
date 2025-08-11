/* RESISTANCE DATA LOGGER (RDL) SOURCE CODE
   Copyright (c) 2024 Jericho Laboratory Inc.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

////////// USER PARAMETERS ////////////

bool headerDisplay = 1;                 // optional display of headerprint (1 = yes, 0 = no)
bool timeDisplay = 1;                   // optional display of timestamp (1 = yes, 0 = no)
bool idDisplay = 1;                     // optional display of identification number of measurement (1 = yes, 0 = no)
bool tDisplay = 1;                      // optional measurement and display of temperature/illuminance values (1 = yes, 0 = no)
bool ohmDisplay = 0;                    // optional display of probes resistance values (ohm) (1 = yes, 0 = no)
bool SHT40Display = 0;                  // optional measurement and display of i2c sensor values (1 = yes, 0 = no)
bool voltDisplay = 0;                   // optional measurement and display of voltage reading values (1 = yes, 0 = no)
bool currentDisplay = 1;                // optional measurement and display of True RMS current values (1 = yes, 0 = no)
bool terosDisplay = 0;                  // optional measurement and display of Teros 10 meter reading values (soil humidity) (1 = yes, 0 = no)
bool strainDisplay = 0;                 // optional measurement and display of strain gauge cell values (1 = yes, 0 = no)
bool phDisplay = 0;                     // optional measurement and display of pH meter values (1 = yes, 0 = no)
bool ControlSignal = 0;                 // optional activation of the signal control functions
bool periodicHeader = 1;                // optional activation of a printed header every given interval
bool currentTComp = 1;                  // optional activation of a temperature compensation on the current sensors (1 = yes, 0 = no)
bool dstRegion = 1;                     // define if you are in area where DST (Daylight Saving Time) is applied (1), or not (0).
int i2cChannels_sht40[] = {1};          // define array to store the list of shield channels dedicated to air humidity sensors (channels 1 to 8)
int i2cChannels_strain[] = {1,2,3,4};         // define array to store the list of shield channels dedicated to strain sensors  (channels 1 to 8)
int i2cChannels_ph[] = {2};             // define array to store the list of shield channels dedicated to pH sensors  (channels 1 to 8)
int i2cChannels_current[] = {1,2,3};        // define array to store the list of analog channels dedicated to current sensors (channels 0 to 7)
int channels_teros[] = {0};           // define array to store the list of analog channels dedicated to TEROS sensors (channels 0 to 7)

////////// PROGRAMMER PARAMETERS ////////////

#define headerInterval 1800000          // (ms) Interval at which the header (sensors identification and units) is printed out (1800000 = 30min)  
#define Seriesresistor 10000            // (ohms) the value of the series resistor for T1 (based on the specifications of your RDL unit)
#define baudRate 57600                  // (bps) data rate at which data is transmitted between the Arduino and the PC, through the serial monitor (max = 115200)
#define ADCrange 65535                  // value range for 16-bit ADC (ADC1115) is 0-65535
  
//////////  LIBRARIES INCLUDED //////////
#include "EEPROM.h"                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)
#include "RTClib.h"                    // library required for the Real-Time Clock (RTC). Can be installed via the Library Manager.
#include "Jericho_Adafruit_NAU7802.h"   // Jericho version of Adafruit of the NAU7802 library
#include "Wire.h"                      // library required to control the I2C multiplexer
#include "Adafruit_SHT4x.h"            // library required for the SHT40 humidity sensor. Can be installed via the Library Manager.  
#include "Adafruit_ADS1X15.h"          // library required for the ADS1115 I2C ADC.
#include "Adafruit_PCF8574.h"          // library required for the PCF8574 (I2C GPIO Expander).
#include "MemoryFree.h"                // library required for a test to determine if I have memory leak related to begin() statements with Strain NAU7802
#include "Adafruit_SleepyDog.h"        // library required for the watchdog function (avoid i2c jams).
#include "Coeff_gen/coefficients_strain.h"    // file containing the strain coefficients. File generated by python script from excel file.
#include "Coeff_gen/current_coefficients.h"    // file containing the strain coefficients. File generated by python script from excel file.

//OTHER INITIALIZATIONS

long readInterval = 1000;              // (ms) Default interval at which temperature is measured, then stored in volatile memory SRAM and sent to PC [1000 ms = 1s, 86400000 ms = 1 day]
long readInterval0 = 2000;             // (ms) Temporary storage variable for read interval
unsigned long time1 = 0;               // initialize variable to control read cycles
unsigned long time2 = 0;               // initialize variable to control header print cycles
uint8_t numberC = 8;                    // default number of active thermistor channels. Must be an integer between 1 and 8.
uint8_t numberV = 8;                    // default number of active voltage channels. Must be an integer between 1 and 8.
bool sensors_present = 0;               // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'sensors'.
uint8_t numberC10 = numberC;            // (ms) Temporary storage variable for quantity of thermistor channels used
uint8_t numberV10 = numberV;            // (ms) Temporary storage variable for quantity of voltage channels used
uint8_t units_T = 0;                    // default temperature units are Celcius (0).

Adafruit_NAU7802 nau_ada;                // Create instance of the Adafruit_NAU7802 class (Adafruit library)       /////// TEMPORARY COMMENTED TO WORK ON CURRENT SENSOR (SPARKFUN)
//NAU7802 nau_current;                   //Create instance of the NAU7802 class (Sparkfun library)
Adafruit_NAU7802 nau_current;           //Create instance of the NAU7802 class dedicated to the current measurements (Sparkfun library)
Adafruit_ADS1115 ads1115;              //Create an instance of ADS1115
Adafruit_SHT4x sht4 = Adafruit_SHT4x();  //creates an object named sht4 of the class Adafruit_SHT4x, using its default constructor (i.e. Adafruit_SHT4x).
RTC_DS3231 rtc;                        // define the RTC model number used by the RTClib.h
#define R_MUX 70                       // Internal resistance of a single CD74 multiplexer (ohms)    ////////// The resistance of the second MUX will have to be added.
#define NUMSAMPLES 10                  // Reduced sample size for the ADS1115. It might be necessary to give NUMSAMPLES as input of function voltFunc to have flexibility.
float V_ref = 5;                       // calibration value for voltage measurements with channel A1
bool SHT4_present = 0;                 // initialize the variable that will indicate if a sensor is present
bool strain_present = 0;                 // initialize the variable that will indicate if a strain sensor is present
bool current_present = 0;                  // initialize the variable that will indicate if a current sensor is present
uint8_t strain_initiated = 0;             //initialize the variable that counts the number of strain sensors having been initiated with begin()
uint8_t current_initiated = 0;             //initialize the variable that counts the number of current sensors having been initiated with begin()
bool SHT40_heatPulse = 0;              // initialize the variable that holds the desired state for SHT heater. (Turns to '1' when heat is required)
#define Bsize round(WriteInterval/ReadInterval) // size of buffer array required to average temperatures
#define TCAADDR 0x70                   // TCA ADDRESS, used by i2c_select()   ??? If there is more than one TCA9548 on the bus, wouldn't it create a conflict????
Adafruit_PCF8574 pcf1;                 //RDL: create an instance of PCF8574 for the chip dedicated to the high-side MOSFETs
Adafruit_PCF8574 pcf2;                 //RDL: create an instance of PCF8574 for the chip dedicated to the low-side MOSFETs
Adafruit_PCF8574 pcf3;                 //I2C SHIELD: create an instance of PCF8574 for the chip dedicated to the high-side MOSFETs
Adafruit_PCF8574 pcf4;                 //I2C SHIELD: create an instance of PCF8574 for the chip dedicated to the low-side MOSFETs

//-------------------------------------------------------------------

// STEINHART-HART GENERIC COEFFICIENTS FOR 10K (B25/50 = 3950K) NTC THERMISTORS BASED ON GNU OCTAVE CALCULATIONS
#define GEN_A 1.0222793532E-03
#define GEN_B 2.5316558834E-04
#define GEN_C -5.3213022916E-12

float arrayV[8];                       // define array to store values of all probes before Serial print
float arrayR[8];                       // define array to store resistances of all probes before Serial print
float R_wire[] = {0, 0, 0, 0, 0, 0, 0, 0};         // define array to store the thermistor extension wire values

String str;                            // define str in the general scope of the program
long readCycle2 = 0;                   // initialization of tag for live data (read function) (long type allows a high count values)
#define enable_T_MUX 11                // Define the Nano digital pin that enables/disables the Thermistors multiplexer
#define enable_V_MUX 10                // Define the Nano digital pin that enables/disables the Voltages multiplexer
#define S0 2                             // Digital Pin 2 // CD74 Multiplexers are controlled by 3 I/O pins
#define S1 3                             // Digital Pin 3 // CD74 Multiplexers are controlled by 3 I/O pins
#define S2 4                             // Digital Pin 4 // CD74 Multiplexers are controlled by 3 I/O pins
struct STRUCT1 {
  float o;
  float t;
};     // define a new structure class called 'STRUCT1 that will enable the thermistor function



unsigned long timePassed = 0;            // initialize variable to keep track of time passed between each measurement.
bool flag1 = 1;                          // define a boolean that forces a measurement independently of time elapse
unsigned long timePassedHeader;          // initialize variable to keep track of time passed between each measurement
void(* resetFunc) (void) = 0;            // define a reset function for the arduino micro-controller
bool strainDevice;                       // define a boolean that indicates the presence of a strain device
uint8_t addr;                            // define an address variable for i2c multiplexer channel selection
float voltage, phValue;                  // define the variables for pH meter (voltage, pH values and temperature (for temperature compensation)(initialized at 25C))
int qty_sht40;                           // define the variable that holds the number of sht40 devices connected to the i2c shield
int qty_strain;                          // define the variable that holds the number of strain devices connected to the i2c shield
int qty_ph;                              // define the variable that holds the number of pH devices connected to the i2c shield
int qty_current;                         // define the variable that holds the number of current devices connected to the RDL
int qty_teros;                           // define the variable that holds the number of teros devices connected to the RDL

//----------------------
// DEFINE THE PINS TO WHICH THE SENSORS ARE CONNECTED
#define THERMISTORPIN A0               // Analog signals from all thermistors are multiplexed to a single pin
#define VOLT_PIN A1                    // Analog signal pin for voltage readings or current sensor readings
#define CTRL_PIN 9                     // Define the digital pin dedicated to the control signal example
#define ADS_T_PIN 0                    // ADS1115 channel for thermistor
#define ADS_V_PIN 1                    // ADS1115 channel for voltage measurements
//----------------------

//sensors_event_t humidity, temp;                                  //define two events (objects) --- Commented for unknown reason, unknown test

////// SETUP ////////

void setup(void) {

  Serial.begin(baudRate);                     //initialize serial monitor at the specified baud rate (e.g. 9600)
  Serial.println();                           //create space after reset of the Arduino

  // Close I2C MUX channels and reset the Wire library (I2C bus)
  Wire.begin();    //test to see if this function exists in my verison of the library
  Wire.setWireTimeout(2000000 /* us */, true /* reset_on_timeout */);  //Activate the timeout (microseconds) on the I2C bus, with hardware reset when timeout flagged.

  tca_init();
  readEEPROM();                               //call function to read the EEPROM memory to see if there are some parameters stored

  if (headerDisplay == 1) {
    Serial.println(); Serial.println();
    Serial.println(F("Jericho Lab inc. // Resistance Data Logger (RDL) RevE5 Code"));
    Serial.print(F("Compiled: "));
    Serial.print(F(__DATE__));
    Serial.print(F("  "));
    Serial.println(F(__TIME__));
    Serial.print(F("I2C Bus: "));
    Serial.print(getI2Cfreq());
    Serial.println(F(" Hz"));
    startMessage();    // print informations after startup
  }

  analogReference(EXTERNAL);                         // tells the Nano to use the external voltage as a reference (value used at the top of the Nano ADC range)

  pinMode(enable_T_MUX, OUTPUT);                               // define pin 11 as an output pin.
  digitalWrite(enable_T_MUX, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid Joule effect and MUX consumption)

  pinMode(enable_V_MUX, OUTPUT);                     // define pin 10 as an output pin.
  digitalWrite(enable_V_MUX, HIGH);                  // toggle pin to HIGH value in order turn off MUX while not used (avoid Joule effect and MUX consumption)

  pinMode(VOLT_PIN, INPUT);                          //set pin as an input for voltage readings. INPUT mode explicitly disables the internal pullups.
  pinMode(CTRL_PIN, OUTPUT);                         //set pin as an input for voltage readings to allow sending a control signal    //

  delay(100);                                        // let some time pass before trying to communicate with the RTC
  initRTC();                                         //initialize the Real Time Clock
  ads1115.begin();                                 // initialize the ADS1015 chip

  pinMode(13, OUTPUT);                              // board Led 'L' is controlled by pin 13. Pin 13 is set to Output mode
  pinMode(S0, OUTPUT);                              // Configure pins dedicated to the thermistor multiplexor to 'output'mode (default mode is 'input')
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  qty_sht40 = sizeof(i2cChannels_sht40) / sizeof(i2cChannels_sht40[0]);
  qty_strain = sizeof(i2cChannels_strain) / sizeof(i2cChannels_strain[0]);
  qty_ph = sizeof(i2cChannels_ph) / sizeof(i2cChannels_ph[0]);
  qty_current = sizeof(i2cChannels_current) / sizeof(i2cChannels_current[0]);
  qty_teros = sizeof(channels_teros) / sizeof(channels_teros[0]);

  if (!pcf1.begin(0x20, &Wire)) {
    Serial.print(F("Couldn't find PCF8574 "));
    Serial.println(" #1");
  }

  if (!pcf2.begin(0x21, &Wire)) {
    Serial.print(F("Couldn't find PCF8574 "));
    Serial.println(" #2");
  }

  for (uint8_t p = 0; p < 8; p++) {
    pcf1.pinMode(p, OUTPUT);
    pcf2.pinMode(p, OUTPUT);
    pcf1.digitalWrite(p, HIGH); // initialize each channel off
    pcf2.digitalWrite(p, LOW); // initialize each channel off
  }

  // -------------- SHIELD PCF8574 ACTIVATION/RE-ACTIVATION ----------- //
  if (!pcf3.begin(0x22, &Wire)) {
    Serial.print(F("Couldn't find PCF8574 "));
    Serial.print(F("#3 "));
    Serial.println(F("(I2C Shield)"));
  }
  if (!pcf4.begin(0x23, &Wire)) {
    Serial.print(F("Couldn't find PCF8574 "));
    Serial.print(F("#4 "));
    Serial.println(F("(I2C Shield)"));
  }
  for (uint8_t p = 0; p < 8; p++) {
    pcf3.pinMode(p, OUTPUT);
    pcf4.pinMode(p, OUTPUT);
    pcf3.digitalWrite(p, HIGH); // initialize each channel off
    pcf4.digitalWrite(p, LOW); // initialize each channel off
    delay(200);              // Minimum delay required to let PCF close each channel (verify datasheet)
  }
  tca_init();       // initialize the TCA9548 I2C MUX chip to ensure that no channel is connected, as it will cause an I2C bus jam.

  if (headerDisplay == 1) {         // it is necessary to deactivate the startMessage() function in order for the Serial Plotter to function properly
    printHeader();                // this function prints the header (T1, T2, R1, T2, etc)
  }
}

///// MAIN LOOP //////////

void loop(void) {
    
  if (flag1 || timePassed >= readInterval)          // if flag is true or enough time has passed, read the sensors
 
  {
    flag1 = 0;                                      // reset flag
    Serial.println();                               // new line of measurement
    time1 = millis();                               // each time a reading is taken, time1 is reset
    readCycle2 = readCycle2 + 1;                    // increment the read cycle number at each turn

    if (timeDisplay == 1) {
      runRTC();                                       // call the RTC and display timestamp
    }

    if (idDisplay == 1) {
      Serial.print(readCycle2);                       // display sequential ID number
      spacing1(readCycle2, 15);                        // 15 characters instead of 12 are considered because the variable readCycle2 is LONG type, without the two decimals and dot of the FLOAT type
    }

    if (tDisplay == 1 or ohmDisplay == 1) {

      digitalWrite(enable_T_MUX, LOW);                  // toggle pin to LOW value in order turn on the THERMISTOR MUX
      for (int i = 0; i < (numberC); i++) {
        setMultiplexer(i);                            // select the multiplexer channel
        int channel = i + 1;                          //channel being measured
        bool readMode = 0;                            // readMode ==0 (Nano ADC) and readMode == 1 (ADS1115 ADC)
        struct STRUCT1 valeurs = thermistor(GEN_A, GEN_B, GEN_C, channel, readMode ); //call 'thermistor' function and store results in a structure
        arrayV[i] = valeurs.t;                        // storing temperature to array
        arrayR[i] = valeurs.o;                        // storing resistances (ohm) to array
      }
      digitalWrite(enable_T_MUX, HIGH);                  // toggle pin to HIGH value in order turn off MUX while not used (avoid self-heating effect and MUX consumption)

      if (tDisplay == 1) {
        for (int i = 0; i < (numberC); i++) {            // print all probes temperature with a loop
          Serial.print(arrayV[i], 2);                    // print value from array with 2 decimals
          spacing1(arrayV[i], 12);
        }
      }

      if (ohmDisplay == 1) {
        Serial.print("*");
        spacing2("*", 12);
        for (int i = 0; i < (numberC); i++) {
          Serial.print(arrayR[i], 0);                     // print all probes resistance with a loop (optionnal)¸, without printing the decimals
          spacing1(arrayR[i], 14);                         //the large resistance values to display require more spacing (14) than the rest (12) because the usual two decimals are not printed
        }
      }
    }

    if (SHT40Display == 1) {
      for (int i = 0; i < qty_sht40; i++) {
        addr = i2cChannels_sht40[i] - 1;   // we choose the channel X on the 0-index array
        pcf3.digitalWrite(addr, LOW);    // turn on by sinking current to ground
        pcf4.digitalWrite(addr, HIGH);   // turn on by sinking current to ground
        delay(1000);                      //A delay is required to avoid miscommunication. Delay value not optimized yet.
        i2c_select(addr);
        delay(1000);                        //A delay is required to avoid miscommunication. Delay value not optimized yet.
        Wire.beginTransmission(addr);
        delay(1000);                          //A delay is required to avoid miscommunication. Delay value not optimized yet.
        sht40Func();
        Wire.endTransmission(addr);
        delay(1000);                          //A delay is required to avoid miscommunication. Delay value not optimized yet.
        tca_init();                        // initialize the TCA9548 I2C MUX chip to ensure that no channel remains connected too late, as it will cause an I2C bus jam.
        pcf3.digitalWrite(addr, HIGH); // turn off by turning off sinking transistor
        pcf4.digitalWrite(addr, LOW); // turn off by turning off sinking transistor
      }
    }
    watchSerial(); //  Watching for incoming commands from the serial port half-way through the loop
    
    if (voltDisplay == 1) {
      simpleVoltFunc();   //run function for simple voltage measurement (all channels required by the current QTY-V parameter).
    }

    watchSerial(); //  Watching for incoming commands from the serial port half-way through the loop

    if (currentDisplay == 1) {
      for (int i = 0; i < qty_current; i++) {
        addr = i2cChannels_current[i] - 1;   // we choose the channel X on the 0-index array
        pcf3.digitalWrite(addr, LOW);    // turn on by sinking current to ground
        pcf4.digitalWrite(addr, HIGH);   // turn on by sinking current to ground
        delay(100);
        i2c_select(addr);
        delay(100);
        Wire.beginTransmission(addr);
        delay(400);                 //I suspect that the board requires time to charge up. An increased delay seems to reduce miscommunication and/or bad readings.
        currentNAU7802(current_T_channel[i], current_offset[i], current_T_ref[i]);        //run the NAU7802 version of the current measurement function (e.g.  temperature compensation cannel (1-8))
        Wire.endTransmission(addr);
        delay(100); //1000                         //A delay is required to avoid miscommunication. Delay value not optimized yet.
        tca_init();                        // initialize the TCA9548 I2C MUX chip to ensure that no channel remains connected too late, as it will cause an I2C bus jam.
        pcf3.digitalWrite(addr, HIGH);     // turn off by turning off sinking transistor
        pcf4.digitalWrite(addr, LOW);      // turn off by turning off sinking transistor
      }
    }

    watchSerial(); //  Watching for incoming commands from the serial port half-way through the loop

    if (terosDisplay == 1) {
      for (int i = 0; i < qty_teros; i++) {
        addr = channels_teros[i];       // we choose the analog channel X
        terosFunc(addr);
      }
    }

    watchSerial(); //  Watching for incoming commands from the serial port half-way through the loop

    if (strainDisplay == 1) {
      for (int i = 0; i < qty_strain; i++) {
        addr = i2cChannels_strain[i] - 1;   // we choose the channel X on the 0-index array
        pcf3.digitalWrite(addr, LOW);    // turn on by sinking current to ground
        pcf4.digitalWrite(addr, HIGH);   // turn on by sinking current to ground
        delay(100); //100
        i2c_select(addr);
        delay(100); //100
        Wire.beginTransmission(addr);
        delay(400);//1000
        strainFunc(strain_matrix[i][0],strain_matrix[i][1]);                      // run Strain sensor function with pointers to the matrix of coefficients
        Wire.endTransmission(addr);
        delay(100);                          //A delay is required to avoid miscommunication. Delay value not optimized yet.
        tca_init();                        // initialize the TCA9548 I2C MUX chip to ensure that no channel remains connected too late, as it will cause an I2C bus jam.
        pcf3.digitalWrite(addr, HIGH);     // turn off by turning off sinking transistor
        pcf4.digitalWrite(addr, LOW);      // turn off by turning off sinking transistor
      }

    }

    watchSerial(); //  Watching for incoming commands from the serial port half-way through the loop

    if (phDisplay == 1) {

      for (int i = 0; i < qty_ph; i++) {
        addr = i2cChannels_ph[i] - 1;   // we choose the channel X on the 0-index array
        pcf3.digitalWrite(addr, LOW);    // turn on by sinking current to ground
        pcf4.digitalWrite(addr, HIGH);   // turn on by sinking current to ground
        delay(1000);                      // A delay is required to avoid miscommunication. Delay value not optimized yet.        
        delay(120000);                  // Long 2-min delay required to warmup the pH sensor
        //delay (10000);                    // Short 10 sec delay for probes who equilibrate faster or continuous measurements (single sensor).
        i2c_select(addr);
        delay(1000);                        //A delay is required to avoid miscommunication. Delay value not optimized yet.
        Wire.beginTransmission(addr);
        delay(2000);                          //A delay is required to avoid miscommunication. Delay value not optimized yet.
        phFunc();                         // run pH function
        Wire.endTransmission(addr);
        delay(1000);                          //A delay is required to avoid miscommunication. Delay value not optimized yet.
        tca_init();                        // initialize the TCA9548 I2C MUX chip to ensure that no channel remains connected too late, as it will cause an I2C bus jam.
        pcf3.digitalWrite(addr, HIGH); // turn off by turning off sinking transistor
        pcf4.digitalWrite(addr, LOW); // turn off by turning off sinking transistor

      }
    }

    if (ControlSignal == 1) {
      controlFunc();
    }
  }

  if ((periodicHeader == 1) && (timePassedHeader >= headerInterval)) {             // if enough time has passed, printHeader
    printHeader();
    time2 = millis();                               //each time a reading is taken, time1 is reset
  }
  watchSerial(); //  Watching for incoming commands from the serial port

  // this block must be positionned right before the decision to read or not the group of thermistors (timePassed>= ReadInterval)
  timePassed = millis() - time1;              // time elapsed since last read cycle (serial monitor)
  timePassedHeader = millis() - time2;              // time elapsed since last header printing

  // Check if a timeout has occurred during any read/write operation
  if (Wire.getWireTimeoutFlag()) {
    Serial.print("   Wire timeout occurred.");
    // Clear the timeout flag so future transmissions aren’t marked as timed out
    Wire.clearWireTimeoutFlag();
    //Serial.print("Timeout flag cleared. Attempting next operation...");
  } else {
    //Serial.print("No Wire timeout flag detected.");
  }

}  //end of main loop()


//-------------------- end

/* RESISTANCE DATA LOGGER (RDL) SOURCE CODE
 * Copyright (c) 2022 Jericho Laboratory Inc.
 * 
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#define __FILENAME_WIN__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)   //Creates a C macro based on standard macro __FILE__ that prints the filename instead of system path
#define __FILENAME_LINUX__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)   // Equivalent macro for linux systems
#define word1 strlen(__FILENAME_WIN__)
#define word2 strlen(__FILENAME_LINUX__)
#define __FILENAME__ ((word1)<(word2)? (__FILENAME_WIN__) : (__FILENAME_LINUX__))  // Linux and Windows do not use the same character. so the preprocessor compares the two lengths and pick the string that worked.

////////// USER PARAMETERS ////////////

bool headerDisplay=1;                   // optional display of headerprint (1 = yes, 0 = no)
bool timeDisplay=1;                     // optional display of timestamp (1 = yes, 0 = no)
bool idDisplay=1;                       // optional display of identification number of measurement (1 = yes, 0 = no)
bool tDisplay=1;                        // optional display of temperature/illuminance values (1 = yes, 0 = no)
bool ohmDisplay = 0;                    // optional display of probes resistance values (ohm) (1 = yes, 0 = no)
//bool humDisplay = 1;                  // optional calculations and display of relative humidities (1 = yes, 0 = no)
bool i2cDisplay = 0;                    // optional display of i2c sensor values (1 = yes, 0 = no)
//bool WBGTDisplay = 1;                 // optional display of WBGT values (1 = yes, 0 = no)
bool voltDisplay = 0;                   // optional display of voltage reading values (1 = yes, 0 = no)  
bool currentDisplay = 0;                // optional display of True RMS current values (1 = yes, 0 = no)  
bool terosDisplay = 0;                  // optional display of Teros 10 meter reading values (1 = yes, 0 = no) 
bool strainDisplay = 0;                 // optional display of strain gauge cell values (1 = yes, 0 = no) 
bool pHDisplay = 0;                     // optional display of pH meter values (1 = yes, 0 = no)
bool ControlSignal = 0;                 // optional activation of the signal control functions
bool noiseControl = 0;                  // optional delay when noise filter desired (1 = yes, 0 = no)

////////// PROGRAMMER PARAMETERS ////////////

char sensors[9]="TTTTTTTT";            // define array of 8 characters to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . Factory default.
char sensors_temp[9]="TTTTTTTT";       // initiating the temporary holder
//char humidities[9]="ABCD1234";         // define array of 8 elements to indicate the type of sensor in each channel  (letters=dry bulb, numbers = wet bulb).
//char humidities_temp[9]="00000000";    // initiating the temporary holder
//#define WBGT_dry 1                   // defining which channel has the dry bulb of the WBGT index  (1 = C1, 2 = C2, etc.)
//#define WBGT_wet 4                      // defining which channel has the wet bulb of the WBGT index  (1 = C1, 2 = C2, etc.)
//uint8_t WBGT_globe = 3;                    // defining which channel has the globe probe of the WBGT index (1 = C1, 2 = C2, etc.)
//#define WBGT_globe 3                   // defining which channel has the globe probe of the WBGT index (1 = C1, 2 = C2, etc.)
//int sortedHum[]={-1,-1,-1,-1,-1,-1,-1,-1};   // initiating the array of integers that will hold the sorted humidity channels (later the array (global variable) is modified by sortHum())
unsigned long time1 = 0;               // initialize variable to control read cycles
unsigned long time2 = 0;               // initialize variable to control header print cycles
uint8_t numberC=8;                        // default number of active thermistor channels. Must be an integer between 1 and 8.
uint8_t numberV =8;                     // default number of active voltage channels. Must be an integer between 1 and 8.
bool sensors_present=0;                 // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'sensors'.
//bool humidities_present=0;              // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'humidities'.
uint8_t numberC10 = numberC;               // (ms) Temporary storage variable for quantity of thermistor channels used
uint8_t numberV10 = numberV;            // (ms) Temporary storage variable for quantity of voltage channels used 
uint8_t units = 0;                         // default temperature units are Celcius (0).
long readInterval = 1000;              // (ms) Default interval at which temperature is measured, then stored in volatile memory SRAM and sent to PC [1000 ms = 1s, 86400000 ms = 1 day]
long readInterval0 = 2000;             // (ms) Temporary storage variable for read interval
#define headerInterval 1800000          // (ms) Interval at which the header (sensors identification and units) is printed out (1800000 = 30min)  
#define Seriesresistor 4700            // (ohms) the value of the series resistor for T1 (based on the specifications of your RDL unit)
#define Bsize round(WriteInterval/ReadInterval) // size of buffer array required to average temperatures
#define baudRate 57600                // (bps) data rate at which data is transmitted between the Arduino and the PC, through the serial monitor (max = 115200)
#define ADCrange 4095                // value range for 12-bit ADC (ADC1015) is 0-4095.

//LIBRARIES INCLUDED
#include "EEPROM.h"                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)
#include "RTClib.h"                    // library required for the Real-Time Clock (RTC). Can be installed via the Library Manager.
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_NAU8702//TEST 2023-08-24
#include "Wire.h"                      // library required to control the I2C multiplexer
#include "Adafruit_SHT4x.h"            // library required for the SHT40 humidity sensor. Can be installed via the Library Manager.  
#include "DFRobot_PH.h"                // library required for the pH meter.
#include "Adafruit_ADS1X15.h"          // library required for the ADS1015 I2C ADC.

NAU7802 nau;                           //Create instance of the NAU7802 class  //TEST 2023-08-24
Adafruit_ADS1015 ads1015;              //Create an instance of ADS1015
#define TCAADDR 0x70                   // TCA ADDRESS, used by i2c_select()
Adafruit_SHT4x sht4 = Adafruit_SHT4x();  // define the sht4 variable
RTC_DS3231 rtc;                        // define the RTC model number used by the RTClib.h
#define R_MUX 70                       // Internal resistance of the multiplexer (ohms)
#define NUMSAMPLES 10                   // how many samples to take and average at each reading (smooth the noise)
float V_ref = 5;                       // calibration value for voltage measurements with channel A1
bool SHT4_present = 0;                 // initialize the variable that will indicate if a sensor is present
bool score;                            // define the variable "score" for evaluation of user input algorithm
long HighSpeedClock = 100;             //value for high speed i2c bus clock (Hz). Default is 100,000.
long LowSpeedClock = 100;              //value for low speed i2c bus clock (Hz)
bool SHT40_heatPulse = 0;              // temporary test to see if I can send a single pulse of heat and then turn this value to '1' to avoid heat at every loop
//-------------------------------------------------------------------

// STEINHART-HART GENERIC COEFFICIENTS FOR 10K (B25/50 = 3950K) NTC THERMISTORS

#define GEN_A 1.0222793532E-03
#define GEN_B 2.5316558834E-04
#define GEN_C -5.3213022916E-12

//int samples[NUMSAMPLES];           // define vector for sampling purpose of the thermistor() function  
float arrayV[16];                  // define array to store values of all probes before Serial print 
float arrayR[16];                  // define array to store resistances of all probes before Serial print
float arrayH[16];                  // define array to store humidities of all couples before Serial print

float R_wire[] = {0, 0, 0, 0, 0, 0, 0, 0};         // define array to store the extension wire values

String str;                            // define str in the general scope of the program
long readCycle2 = 0;                   // initialization of tag for live data (read function) (long type allows a high count values)
#define THERMISTORPIN A0               // Analog signals from all thermistors are multiplexed to a single pin
#define VOLT_PIN A1                    // Analog signal pin for voltage readings or current sensor readings
#define CURRENT_PIN A1                 // Analog signal pin for current sensor readings
#define PH_PIN A2                      // Define the analog pin for the pH meter input
//#define TEROS_PIN A3                   // Analog signal pin for soil meter  //Test 2023-08-27
#define TEROS_PIN A1                   // Analog signal pin for soil meter
#define RTC_supply 12                  // Define the Nano digital pin that supplies power to the RTC chip
#define enable_T_MUX 11                // Define the Nano digital pin that enables/disables the Thermistors multiplexer
#define enable_V_MUX 10               // Define the Nano digital pin that enables/disables the Voltages multiplexer

#define S0 2                           // Digital Pin 2 // Multiplexer #1 is controlled by 4 I/O pins
#define S1 3                           // Digital Pin 3 // Multiplexer #1 is controlled by 4 I/O pins
#define S2 4                           // Digital Pin 4 // Multiplexer #1 is controlled by 4 I/O pins   
#define S3 5                           // Digital Pin 5 // Multiplexer #1 is controlled by 4 I/O pins
struct STRUCT1 {float o; float t; };   // define a new structure class called 'STRUCT1 that will enable the thermistor function
struct STRUCT2 {float a;};               // define a new structure class called 'STRUCT2 that will enable the relhum function
unsigned long timePassed;              //initialize variable to keep track of time passed between each measurement
unsigned long timePassedHeader;              //initialize variable to keep track of time passed between each measurement
void(* resetFunc) (void) = 0;            // define a reset function for the arduino micro-controller
bool strainDevice;                      //define a boolean that indicates the presence of a strain device
uint8_t addr;                           // define an address variable for i2c multiplexer channel selection   ////// temp test


float voltage,phValue;    // define the varaibles for pH meter (voltage, pH values and temperature (for temperature compensation)(initialized at 25C))
DFRobot_PH ph;                             // load pH meter library under shorter name 'ph'


////// SETUP ////////

void setup(void) {

    Serial.println();   //create space after reset of the Arduino
    Serial.begin(baudRate);                            // initialize serial monitor at the specified baud rate (e.g. 9600) 
    readEEPROM();                                     // call function to read the EEPROM memory to see if there are some parameters stored

    if (headerDisplay == 1){          // it is necessary to deactivate the startMessage() function in order for the Serial Plotter to function properly
        Serial.println(); Serial.println(); 
        Serial.println(F("Jericho Laboratory inc. // Resistance Data Logger (RDL) RevE1"));
        Serial.print(F("Compiled: "));
        Serial.println(F(__DATE__));
        startMessage();    // print informations after startup
    }
    
    analogReference(EXTERNAL);                         // tells the MPU to use the external voltage as a reference (value used at the top of the ADC range)

    pinMode(RTC_supply, OUTPUT);                               // define pin 12 as an output pin.
    digitalWrite(RTC_supply, HIGH);                            // toggle pin 12 to HIGH value in order to supply RTC clock and I2C with a supply voltage (VCC15)

    pinMode(enable_T_MUX, OUTPUT);                               // define pin 11 as an output pin.
    digitalWrite(enable_T_MUX, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid Joule effect and MUX consumption)

    pinMode(enable_V_MUX, OUTPUT);                               // define pin 10 as an output pin.
    //digitalWrite(enable_V_MUX, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid Joule effect and MUX consumption)
    digitalWrite(enable_V_MUX, LOW);   /////// TEST 2023-08-26
    
    pinMode(VOLT_PIN, INPUT);                          // Set pin as an input for voltage readings. INPUT mode explicitly disables the internal pullups.

    pinMode(9, OUTPUT);                                // define pin 9 as an output pin to allow sending a control signal


    initRTC();                                         // call function to initialize Real Time Clock 

    if (i2cDisplay == 1){
      Wire.setClock(LowSpeedClock);

      if(sht4.begin()){                                // if the SHT40 humidity sensor can be initialized...
        SHT4_present = 1;                         
      }

      Wire.setClock(HighSpeedClock);
    }

      ads1015.begin();                                 // initialize the ADS1015 chip
      ads1015.setGain(GAIN_TWOTHIRDS);                 // set the gain. 2/3x gain +/- 6.144V  1 bit = 3mV (default)
      //ads1015.setGain(GAIN_ONE);                     // set the gain. 1x gain   +/- 4.096V  1 bit = 2mV

   timePassed= readInterval;                          // initializing reading timer at readInterval to force a first reading when entering loop()


    pinMode(13,OUTPUT);                               // board Led 'L' is controlled by pin 13. Pin 13 is set to Output mode
    pinMode(S0, OUTPUT);                              // Configure pins dedicated to the thermistor multiplexor to 'output'mode (default mode is 'input')
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

//    TEMPORARY COMMENTED (Applies to multiplexed i2c strain devices)
//    if (strainDisplay ==1){
//      addr = 2;
//      i2c_select(addr);    // TEST     // Choose channel 1
//      Wire.beginTransmission(TCAADDR);  
//      strainDevice = nau7802_init();      // initialize the nau7802 sensor . Boolean = 1 if device is detected.
//      Wire.endTransmission();  
//      }

    if (strainDisplay ==1){
      strainDevice = nau7802_init();      // initialize the nau7802 sensor . Boolean = 1 if device is detected.
      }

   if (pHDisplay == 1){
    ph.begin();      ///// this is the function call that outputs unrequired text ("_acidVoltage:2032.44"). Library might have to be modified.//////
    
   }      

//    sortHum();           // this function is run once at setup to determine what are the channels humidity couples (dry and wet)

    if (headerDisplay == 1){          // it is necessary to deactivate the startMessage() function in order for the Serial Plotter to function properly
        printHeader();     // this function prints the header (T1, T2, R1, T2, etc)
    }


}
//------------------------------------------------------------- 

///// MAIN LOOP //////////

void loop(void) {

if (timePassed >= readInterval)                     // if enough time has passed, read the channels       
{
    time1=millis();                                 // each time a reading is taken, time1 is reset     
    readCycle2=readCycle2 + 1;                      // increment the read cycle number at each turn     
    
    if (timeDisplay == 1){
        runRTC();                                       // display timestamp 
    }

    if (idDisplay ==1){        
        Serial.print(readCycle2);                       // display sequential ID number
        spacing(readCycle2, 15);                        // 15 characters instead of 12 are considered because the variable readCycle2 is LONG type, without the two decimals and dot of the FLOAT type
    }

    if (tDisplay == 1 or ohmDisplay == 1){
  
      digitalWrite(enable_T_MUX, LOW);                  // toggle pin to LOW value in order turn on the THERMISTOR MUX
      for (int i=0; i< (numberC); i++) {              
        
          setMultiplexer(i);                            // select the multiplexer channel
          if(noiseControl ==1){
            delay(500);                                /// DELAY (MILLISECONDS) FOR NOISE FILTER TEST
            }
          else{
            delay(5);
            }
          int channel = i+1;                            //channel being measured
          if(sensors[i]=='T'){        //if sensor on channel is a thermoresistor
            struct STRUCT1 valeurs = thermistor(GEN_A, GEN_B, GEN_C,channel);   //call 'thermistor' function and store results in a structure
            arrayV[i] = valeurs.t;                        // storing temperature to array
            arrayR[i] = valeurs.o;                        // storing resistances (ohm) to array       
                }  
          }
        digitalWrite(enable_T_MUX, HIGH);                  // toggle pin to HIGH value in order turn off MUX while not used (avoid self-heating effect and MUX consumption)        

      if (tDisplay == 1){
          for (int i=0; i< (numberC); i++) {               // print all probes temperature with a loop
            Serial.print(arrayV[i],2);                     // print value from array with 2 decimals  
            spacing(arrayV[i], 12);
          }  
      }
        
      if (ohmDisplay == 1){
          Serial.print("*"); 
          spacing2("*",12);         
              for (int i=0; i< (numberC); i++) {
                Serial.print(arrayR[i],0);                      // print all probes resistance with a loop (optionnal)¸, without printing the decimals
                spacing(arrayR[i], 14);                         //the large resistance values to display require more spacing (14) than the rest (12) because the usual two decimals are not printed
        }
        }
    }
    
//    if (humDisplay == 1){
//      Serial.print(F("*"));
//      spacing2("*",12); 
//      for (int i=0; i<4; i++){
//        int db_channel=sortedHum[2*i];
//        int wb_channel=sortedHum[2*i+1];
//        if (db_channel!=-1){                                   //if there is a humidity probe defined by the user, then calculate the relative humidity
//           arrayH[i]=relhum(arrayV[db_channel],arrayV[wb_channel],1013, units);
//        }
//        if (arrayH[i]>100){     //if value is non-physical, print an easily distinguishable value
//          arrayH[i]=111;
//          }
//        if (arrayH[i]<0){       //if value is non-physical, print an easily distinguishable value
//          arrayH[i]=0;  
//        }
//      }
//      for (int i=0; i<4; i++){
//      Serial.print(arrayH[i]);         //print relative humidity.
//      spacing(arrayH[i],12);
//      }
//    }

    if (i2cDisplay == 1){

      Wire.setClock(LowSpeedClock);
      // SENSOR 0 - Channel 0
      Serial.print("*");   
      spacing2("*",12);
      addr = 0;
      i2c_select(addr);    // TEST     // Choose channel 0
      delay(100);    ////// TEST // Delay to allow better communication after channel change
      
      i2cSensors(); 
      //Wire.endTransmission();
      //SENSOR 1 - Channel 1
      Serial.print("*");   
      spacing2("*",12);
      addr = 1;
      i2c_select(addr);         // Choose channel 1
      delay(100);               // Delay to allow better communication after channel change
      i2cSensors(); 
      Wire.setClock(HighSpeedClock);
    }

//    if (WBGTDisplay ==1){     //optional print of the Wet Bulb Globe Temperature (WBGT) based on fixed channels.
//      Serial.print("*");
//      spacing2("*",12);
//      wbgtFunc();             //run function to calculate and display the WBGT value
//    }

    if (voltDisplay==1){
      voltMainFunc();   
    }
    if (currentDisplay==1){
      currentFunc();    
    }

    if (terosDisplay==1){
      terosFunc();             //run function
    }

    if (strainDisplay==1){   

      //SENSOR 1 - Channel 1
      addr = 2;   //NAU7802   /////TEMP TEST
      i2c_select(addr);    // TEST     // Choose channel 1
      Wire.beginTransmission(TCAADDR);
      nau7802Function();             //run function
      Wire.endTransmission();      
      i2c_select(0);    // TEST
    }

    if (pHDisplay==1){
      pHFunc();             //run function
    }

    if (ControlSignal==1){
      controlFunc();             //run function

    }
    
    Serial.println();          //new line for the next measurements
}

if (timePassedHeader >= headerInterval){                 // if enough time has passed, printHeader
    printHeader();
    time2=millis();                                 // each time a reading is taken, time1 is reset     
}
watchSerial(); //  Watching for incoming commands from the serial port

// this block must be positionned right before the decision to read or not the group of thermistors (timePassed>= ReadInterval)
timePassed=millis()-time1;                  // time elapsed since last read cycle (serial monitor)
timePassedHeader=millis()-time2;                  // time elapsed since last header printing
}  //end of main loop()

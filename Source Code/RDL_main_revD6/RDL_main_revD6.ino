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

int generic=1;                         // use of generic thermistor coefficients (generic = 1) or custom coefficients for calibrated thermistors (generic = 0)
int headerDisplay=1;                   // optional display of headerprint (1 = yes, 0 = no)
int timeDisplay=1;                     // optional display of timestamp (1 = yes, 0 = no)
int idDisplay=1;                       // optional display of identification number of measurement (1 = yes, 0 = no)
int tDisplay=1;                        // optional display of temperature/illuminance values (1 = yes, 0 = no)
int ohmDisplay = 0;                    // optional display of probes resistance values (ohm) (1 = yes, 0 = no)
int humDisplay = 0;                    // optional calculations and display of relative humidities (1 = yes, 0 = no)
int i2cDisplay = 1;                    // optional display of i2c sensor values (1 = yes, 0 = no)
int WBGTDisplay = 0;                   // optional display of WBGT values (1 = yes, 0 = no)
int SoilDisplay = 0;                   // optional display of soil water content values (gypsum matrix) (1 = yes, 0 = no)
int voltDisplay = 0;                   // optional display of voltage reading values (1 = yes, 0 = no)  
int currentDisplay = 0;                // optional display of True RMS current values (1 = yes, 0 = no)  
int terosDisplay = 1;                  // optional display of teros 10 meter reading values (1 = yes, 0 = no) 
int strainDisplay = 1;                 // optional display of strain gauge cell values (1 = yes, 0 = no) 
int pHDisplay = 0;                     // optional display of pH meter values (1 = yes, 0 = no)
int ControlSignal = 0;                 // optional activation of the signal control functions
int noiseControl = 0;                  // optional delay when noise filter desired (1 = yes, 0 = no)

////////// PROGRAMMER PARAMETERS ////////////

char sensors[17]="TTTTTTTTTTTTTTTT";            // define array of 16 characters to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . Factory default.
char sensors_temp[17]="TTTTTTTTTTTTTTTT";       // initiating the temporary holder
char humidities[9]="ABCD1234";         // define array of 8 elements to indicate the type of sensor in each channel  (letters=dry bulb, numbers = wet bulb). ///////// To be updated.
char humidities_temp[9]="00000000";    // initiating the temporary holder
int WBGT_dry = 1;                      // defining which channel has the dry bulb of the WBGT index  (1 = C1, 2 = C2, etc.)
int WBGT_wet = 4;                      // defining which channel has the wet bulb of the WBGT index  (1 = C1, 2 = C2, etc.)
int WBGT_globe = 3;                    // defining which channel has the globe probe of the WBGT index (1 = C1, 2 = C2, etc.)
int sortedHum[]={-1,-1,-1,-1,-1,-1,-1,-1};   // initiating the array of integers that will hold the sorted humidity channels (later the array (global variable) is modified by sortHum())
unsigned long time1 = 0;               // initialize variable to control read cycles
int numberC=16;                        // default number of active channels. Must be an integer between 1 and 8.
int sensors_present=0;                 // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'sensors'.
int humidities_present=0;              // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'humidities'.
int numberC10 = numberC;               // (ms) Temporary storage variable for quantity of channels used
int units = 0;                         // default temperature units are Celcius (0).
long readInterval = 1000;              // (ms) Default interval at which temperature is measured, then stored in volatile memory SRAM and sent to PC [1000 ms = 1s, 86400000 ms = 1 day]
long readInterval0 = 2000;             // (ms) Temporary storage variable for read interval
int Seriesresistor = 10000;            // (ohms) the value of the series resistor for T1 (based on the specifications of your RDL unit)
#define Bsize round(WriteInterval/ReadInterval) // size of buffer array required to average temperatures
long baudRate = 57600;                // (bps) data rate at which data is transmitted between the Arduino and the PC, through the serial monitor (max = 115200)

//LIBRARIES INCLUDED
#include <EEPROM.h>                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)
#include "RTClib.h"                    // library required for the Real-Time Clock (RTC). Can be installed via the Library Manager.
#include <Adafruit_NAU7802.h>          // library required for the NAU7802 chip used for strain gauge cell measurements
#include "Wire.h"                      // library required to control the I2C multiplexer
#include "Adafruit_SHT4x.h"            // library required for the SHT40 humidity sensor. Can be installed via the Library Manager.  
#include "DFRobot_PH.h"                // library required for the pH meter.

Adafruit_NAU7802 nau;
#define TCAADDR 0x70                   //(TCA ADDRESS, used by i2c_select())
Adafruit_SHT4x sht4 = Adafruit_SHT4x();  // define the sht4 variable
RTC_DS1307 rtc;                        // define the RTC model number used by the RTClib.h
int R_MUX = 70;                        // Internal resistance of the multiplexer (ohms)
#define NUMSAMPLES 1                   // how many samples to take and average at each reading (smooth the noise)
float V_ref = 5;                       // calibration value for voltage measurements with channel A1 (exact value of the VCC supply must be measured with multimeter for improved accuracy)
int SHT4_present = 0;                   //initialize the variable that will indicate if a sensor is present
int score;                             // define the variable "score" for evaluation of user input algorithm
//-------------------------------------------------------------------

char C1_ID[] = "T01";   //Unique serial number of each thermistor used
char C2_ID[] = "T02";
char C3_ID[] = "T03";
char C4_ID[] = "T04"; 
char C5_ID[] = "T05";
char C6_ID[] = "T06";
char C7_ID[] = "T07";
char C8_ID[] = "T08";
char C9_ID[] = "T09";
char C10_ID[] = "T10";
char C11_ID[] = "T11";
char C12_ID[] = "T12";
char C13_ID[] = "T13";
char C14_ID[] = "T14";
char C15_ID[] = "T15";
char C16_ID[] = "T16";

//-------------------------------------------------------------------

// STEINHART-HART GENERIC COEFFICIENTS FOR 10K (B25/50 = 3950K) NTC THERMISTORS

float GEN_A =  1.0222793532E-03;
float GEN_B =  2.5316558834E-04;
float GEN_C =  -5.3213022916E-12;

// COEFFICIENTS MATRIX (COPY/PASTE FROM THE OCTAVE SCRIPT OUTPUT TEXT FILE) (8 decimals minimum required)
// Example: First line and first column is the coefficient A of the Steinhart-Hart model for channel 1. 8 decimals required.

float C[16][3] = {
{1.2610084065E-03, 2.1114631980E-04, 1.9023374978E-07},  
{1.2675806791E-03, 2.0979557309E-04, 1.9822805307E-07},
{1.2638846806E-03, 2.1055130024E-04, 1.9382524717E-07},
{1.2718419861E-03, 2.0908957579E-04, 1.9934840352E-07},
{1.2670354615E-03, 2.0990013899E-04, 1.9774405298E-07},
{1.2461782151E-03, 2.1381439152E-04, 1.8265011582E-07},
{1.2534484825E-03, 2.1247717154E-04, 1.8637129521E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
{1.2592342994E-03, 2.1205448461E-04, 1.8599202135E-07},
};

float arrayA[] = {C[0][0], C[1][0], C[2][0], C[3][0], C[4][0], C[5][0], C[6][0], C[7][0], C[8][0], C[9][0], C[10][0], C[11][0], C[12][0], C[13][0], C[14][0], C[15][0]};         // declare array and store values for coefficient A
float arrayB[] = {C[0][1], C[1][1], C[2][1], C[3][1], C[4][1], C[5][1], C[6][1], C[7][1], C[8][1], C[9][1], C[10][1], C[11][1], C[12][1], C[13][1], C[14][1], C[15][1]};         // declare array and store values for coefficient B
float arrayC[] = {C[0][2], C[1][2], C[2][2], C[3][2], C[4][2], C[5][2], C[6][2], C[7][2], C[8][2], C[9][2], C[10][2], C[11][2], C[12][2], C[13][2], C[14][2], C[15][2]};         // declare array and store values for coefficient C

int samples[NUMSAMPLES];           // define vector for sampling purpose of the thermistor() function  
float arrayV[16];                  // define array to store values of all probes before Serial print 
float arrayR[16];                  // define array to store resistances of all probes before Serial print
float arrayH[16];                  // define array to store humidities of all couples before Serial print

float R_wire[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};         // define array to store the extension wire values

String str;                            // define str in the general scope of the program
long readCycle2 = 0;                   // initialization of tag for live data (read function) (long type allows a high count values)
#define THERMISTORPIN A0               // Analog signals from all thermistors are multiplexed to a single pin
#define VOLT_PIN A1                    // Analog signal pin for voltage readings
#define PH_PIN A2                      // Define the analog pin for the pH meter input
#define TEROS_PIN A3                   // Analog signal pin for soil meter
#define S0 2                           // Digital Pin 2 // Multiplexer #1 is controlled by 4 I/O pins
#define S1 3                           // Digital Pin 3 // Multiplexer #1 is controlled by 4 I/O pins
#define S2 4                           // Digital Pin 4 // Multiplexer #1 is controlled by 4 I/O pins   
#define S3 5                           // Digital Pin 5 // Multiplexer #1 is controlled by 4 I/O pins
struct STRUCT1 {float o; float t; };   // define a new structure class called 'STRUCT1 that will enable the thermistor function
struct STRUCT2 {float a;};               // define a new structure class called 'STRUCT2 that will enable the relhum function
unsigned long timePassed;              //initialize variable to keep track of time passed between each measurement
void(* resetFunc) (void) = 0;            // define a reset function for the arduino micro-controller
bool strainDevice;                      //define a boolean that indicates the presence of a strain device
uint8_t addr;                           // define an address variable for i2c multiplexer channel selection   ////// temp test


float voltage,phValue,temperature = 25;    // define the varaibles for pH meter (voltage, pH values and temperature (for temperature compensation)(initialized at 25C))
DFRobot_PH ph;                             // load pH meter library under shorter name 'ph'


////// SETUP ////////

void setup(void) {

    if (generic == 1){                  //if generic thermistor coefficient active, make the substitution in the coefficient arrays.
      for (int i=0; i< 16; i++) { 
        arrayA[i]= GEN_A;  //attribute generic value
        arrayB[i]= GEN_B;  //attribute generic value
        arrayC[i]= GEN_C;  //attribute generic value
      }
    }
    
    Serial.begin(baudRate);                           // initialize serial monitor at the specified baud rate (e.g. 9600) 
    analogReference(EXTERNAL);                        // tells the MPU to use the external voltage as a reference (value used at the top of the ADC range)

    pinMode(12, OUTPUT);                               // define pin 12 as an output pin.
    digitalWrite(12, HIGH);                            // toggle pin 12 to HIGH value in order to supply RTC clock and I2C with a supply voltage (VCC15)

    pinMode(11, OUTPUT);                               // define pin 14 as an output pin.
    digitalWrite(11, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid Joule effect and MUX consumption)
    
    pinMode(VOLT_PIN, INPUT);                               // Set A1 as an input for voltage readings. INPUT mode explicitly disables the internal pullups.

    pinMode(9, OUTPUT);                               // define pin 9 as an output pin to allow sending a control signal


    initRTC();                                      // call function to initialize Real Time Clock 

    if (i2cDisplay == 1){
      if(sht4.begin()){                                //if the SHT40 humidity sensor can be initialized...
        SHT4_present = 1;                              
      }
    }
    
    readEEPROM();                                     // call function to read the EEPROM memory to see if there are some parameters stored

   timePassed= readInterval; // initializing reading timer at readInterval to force a first reading when entering loop()    /////////////// TEST 


    pinMode(13,OUTPUT);                               // board Led 'L' is controlled by pin 13. Pin 13 is set to Output mode
    pinMode(S0, OUTPUT);                              // Configure pins dedicated to the thermistor multiplexor to 'output'mode (default mode is 'input')
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    if (strainDisplay ==1){
      addr = 2;
      i2c_select(addr);    // TEST     // Choose channel 1
      Wire.beginTransmission(TCAADDR);     //TEST ////////////////
      strainDevice = nau7802_init();      // initialize the nau7802 sensor . Boolean = 1 if device is detected.
      Wire.endTransmission();  
      }

   if (pHDisplay == 1){
    ph.begin();      ///// this is the function call that outputs unrequired text ("_acidVoltage:2032.44"). Library might have to be modified.
    
   }      

    if (headerDisplay == 1){          // it is necessary to deactivate the startMessage() function in order for the Serial Plotter to function properly
        Serial.println();
        Serial.println();
        Serial.println(F("Jericho Laboratory inc. // Resistance Data Logger (RDL)"));
        Serial.print(F("Code version: "));
        Serial.println(__FILENAME__);
        startMessage();    // print informations after startup
        printHeader();     // this function prints the header (T1, T2, R1, T2, etc)
    }
    
    sortHum();           // this function is run once at setup to determine what are the channels humidity couples (dry and wet)



}
//------------------------------------------------------------- 

///// MAIN LOOP //////////

void loop(void) {

if (timePassed >= readInterval)                 // if enough time has passed, read the channels       
{
  
    digitalWrite(11, LOW);                          // toggle pin to LOW value in order turn on the MUX  (D11)
    time1=millis();                                 // each time a reading is taken, time1 is reset     
    readCycle2=readCycle2 + 1;                      // increment the read cycle number at each turn     

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
        struct STRUCT1 valeurs = thermistor(arrayA[i], arrayB[i], arrayC[i],channel);   //call 'thermistor' function and store results in a structure
        arrayV[i] = valeurs.t;                        // storing temperature to array
        arrayR[i] = valeurs.o;                        // storing resistances (ohm) to array       
            }
      if(sensors[i]=='P'){            //if sensor on channel is a photoresistor
        struct STRUCT1 lux1 = illuminance(channel);
        arrayV[i] = lux1.t;           // storing illuminance to array of values
        arrayR[i] = lux1.o;           // storing resistances (ohm) to array
      }   
    }
    digitalWrite(11, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid self-heating effect and MUX consumption)
    
    if (timeDisplay == 1){
        runRTC();                                       // display timestamp 
    }

    if (idDisplay ==1){        
        Serial.print(readCycle2);                       // display sequential ID number
        spacing(readCycle2, 15);                        // 15 characters instead of 12 are considered because the variable readCycle2 is LONG type, without the two decimals and dot of the FLOAT type
    }
    
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

    if (humDisplay == 1){
      Serial.print(F("*"));
      spacing2("*",12); 
      for (int i=0; i<4; i++){
        int db_channel=sortedHum[2*i];
        int wb_channel=sortedHum[2*i+1];
        if (db_channel!=-1){                                   //if there is a humidity probe defined by the user, then calculate the relative humidity
           arrayH[i]=relhum(arrayV[db_channel],arrayV[wb_channel],1013, units);
        }
        if (arrayH[i]>100){     //if value is non-physical, print an easily distinguishable value
          arrayH[i]=111;
          }
        if (arrayH[i]<0){       //if value is non-physical, print an easily distinguishable value
          arrayH[i]=0;  
        }
      }
      for (int i=0; i<4; i++){
      Serial.print(arrayH[i]);         //print relative humidity.
      spacing(arrayH[i],12);
      }
    }

    if (i2cDisplay == 1){
      // SENSOR 0 - Channel 0
      Serial.print("*");   
      spacing2("*",12);
      addr = 0;
      i2c_select(addr);    // TEST     // Choose channel 0
      delay(100);    ////// TEST // Delay to allow better communication after channel change
//      while(!sht4.begin())
//      {
//        /* There was a problem detecting the HMC5883 ... check your connections */
//        //Serial.println("Ooops, no SHT4X detected ... Check your wiring!");
//        delay(2000);
//      }
      
      i2cSensors(); 
      //Wire.endTransmission();
      //SENSOR 1 - Channel 1
      Serial.print("*");   
      spacing2("*",12);
      addr = 1;
      i2c_select(addr);    // TEST     // Choose channel 1
      delay(100);    ////// TEST // Delay to allow better communication after channel change
      i2cSensors(); 
    }

    if (WBGTDisplay ==1){     //optional print of the Wet Bulb Globe Temperature (WBGT) based on fixed channels.
      Serial.print("*");
      spacing2("*",12);
      wbgtFunc();             //run function to calculate and display the WBGT value
    }

    if (SoilDisplay ==1){     //optional print of the soil water content values, based on fixed channels.
      Serial.print("*");
      spacing2("*",12); 
      soilFunc();             //run function 
    }

    if (voltDisplay==1){
      voltFunc();    
      
    }
    if (currentDisplay==1){
      rmsFunc();    
    }

    if (terosDisplay==1){
      terosFunc();             //run function
    }

    if (strainDisplay==1){      ///////////////////////////////// TEST. WIP.

      //SENSOR 1 - Channel 1
////      Serial.print("*");   
////      spacing2("*",12);
      addr = 2;   //NAU7802   /////TEMP TEST
      //addr = 1;  //SHT40    /////TEMP TEST
      i2c_select(addr);    // TEST     // Choose channel 1
//      Wire.beginTransmission(addr);     ///////////////////////// ChatGPT suggest that I should not be using the same address for Wire.beginTransmission than i2c_select... (#define TCAADDR 0x70)
      Wire.beginTransmission(TCAADDR);
      nau7802Function();             //run function
      Wire.endTransmission();      
      i2c_select(0);    // TEST     // Choose channel 1 TEST ////////////////
    }

    if (pHDisplay==1){
      pHFunc();             //run function
    }

    if (ControlSignal==1){
      controlFunc();             //run function

    }
    
    Serial.println();          //new line for the next measurements
}

watchSerial(); //  Watching for incoming commands from the serial port

// this block must be positionned right before the decision to read or not the group of thermistors (timePassed>= ReadInterval)
timePassed=millis()-time1;                  // time elapsed since last read cycle (serial monitor)
}  //end of main loop()

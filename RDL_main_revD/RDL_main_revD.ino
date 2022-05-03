/* RESISTANCE DATA LOGGER (TDL) SOURCE CODE
 * Copyright (c) 2022 Jericho Laboratory Inc.
 * 
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFIchaTS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#define __FILENAME_WIN__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)   //Creates a C macro based on standard macro __FILE__ that prints the filename instead of system path
#define __FILENAME_LINUX__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)   // Equivalent macro for linux systems
#define word1 strlen(__FILENAME_WIN__)
#define word2 strlen(__FILENAME_LINUX__)
#define __FILENAME__ ((word1)<(word2)? (__FILENAME_WIN__) : (__FILENAME_LINUX__))  // Linux and Windows do not use the same character. so the preprocessor compares the two lengths and pick the string that worked.

////////// PROGRAMMER PARAMETERS ////////////

char sensors[17]="TTTTTTTTTTTTTTTT";            // define array of X elements to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . factory default.
char sensors_temp[17]="TTTTTTTTTTTTTTTT";       // initiating the temporary holder
char humidities[9]="ABCD1234";         // define array of 8 elements to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . factory default.
char humidities_temp[9]="00000000";    // initiating the temporary holder
int sortedHum[]={0,0,0,0,0,0,0,0};     // initiating the array of integers that will hold the sorted humidity channels 
unsigned long time1 = 0;               // initialize variable to control read cycles
int numberC=16;                         // default number of active channels. Must be an integer between 1 and 8.
int sensors_present=0;                 // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'sensors'.
int humidities_present=0;              // we initialize this variable with 0. If there is valid data on the EEPROM, the boolean will change to 1, and we will use this data for 'humidities'.
int numberC10 = numberC;               // (ms) Temporary storage variable for quantity of channels used
int units = 0;                         // default temperature units are Celcius (0).
int ohmDisplay = 0;                    // optional display of probes resistance values (ohm) (1 = yes, 0 = no )
int humDisplay = 1;                    // optional calculations and display of relative humidities (1 = yes, 0 = no )
long readInterval = 1000;              // (ms) Default interval at which temperature is measured, then stored in volatile memory SRAM and sent to PC [1000 ms = 1s, 86400000 ms = 1 day]
long readInterval0 = 2000;             // (ms) Temporary storage variable for read interval
int Seriesresistor = 10000;            // (ohms) the value of the series resistor for T1 (based on specifications of your RDL unit)
#define Bsize round(WriteInterval/ReadInterval) // size of buffer array required to average temperatures
long baudRate = 115200;                // (bps) data rate at which data is transmitted between the Arduino and the PC, through the serial monitor
#include <EEPROM.h>                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)
#include "RTClib.h"                    // library required for the Real-Time Clock
RTC_PCF8523 rtc;                       // define the RTC model number
int R_MUX = 70;                        // Internal resistance of the multiplexer (ohms)
#define NUMSAMPLES 1                   // how many samples to take and average at each reading (smooth the noise)

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
char C15_ID[] = "T14";
char C16_ID[] = "T14";

float C1_A =  1.186988543e-3;         // channel C1 thermistor coefficient A of the Steinhart-Hart model (based on calibration). 8 decimals required.
float C1_B =  2.261319871e-4;         // channel C1 thermistor coefficient B of the Steinhart-Hart model (based on calibration). 8 decimals required.
float C1_C =  1.121412769e-7;         // channel C1 thermistor coefficient C of the Steinhart-Hart model (based on calibration). 8 decimals required.

float C2_A =  1.186988543e-3;
float C2_B =  2.261319871e-4;
float C2_C =  1.121412769e-7;

float C3_A =  1.186988543e-3;
float C3_B =  2.261319871e-4;
float C3_C =  1.121412769e-7;

float C4_A =  1.186988543e-3;
float C4_B =  2.261319871e-4;
float C4_C =  1.121412769e-7;

float C5_A =  1.186988543e-3;
float C5_B =  2.261319871e-4;
float C5_C =  1.121412769e-7;

float C6_A =  1.186988543e-3;
float C6_B =  2.261319871e-4;
float C6_C =  1.121412769e-7;

float C7_A =  1.186988543e-3;
float C7_B =  2.261319871e-4;
float C7_C =  1.121412769e-7;

float C8_A =  1.186988543e-3; 
float C8_B =  2.261319871e-4; 
float C8_C =  1.121412769e-7; 
//-------------------------------------------------------------------

int samples[NUMSAMPLES];           // define vector for sampling purpose of the thermistor() function  
float arrayV[16];                   // define array to store values of all probes before Serial print 
float arrayR[16];                   // define array to store resistances of all probes before Serial print
float arrayH[16];                   // define array to store humidities of all couples before Serial print
float arrayA[] = {C1_A, C2_A, C3_A, C4_A, C5_A, C6_A, C7_A, C8_A, C8_A, C8_A, C8_A, C8_A, C8_A, C8_A, C8_A, C8_A};         // define array to store thermistor coefficient A
float arrayB[] = {C1_B, C2_B, C3_B, C4_B, C5_B, C6_B, C7_B, C8_B, C8_B, C8_B, C8_B, C8_B, C8_B, C8_B, C8_B, C8_B};         // define array to store thermistor coefficient B
float arrayC[] = {C1_C, C2_C, C3_C, C4_C, C5_C, C6_C, C7_C, C8_C, C8_C, C8_C, C8_C, C8_C, C8_C, C8_C, C8_C, C8_C};         // define array to store thermistor coefficient C
float R_wire[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};         // define array to store the extension wire values

String str;                            // define str in the general scope of the program
long readCycle2 = 0;                    // initialization of tag for live data (read function) (long type allows a high count values)
#define THERMISTORPIN A0               // Analog signals from all thermistors are multiplexed to a single pin
#define S0 2                           // Digital Pin 2 // Multiplexer #1 is controlled by 4 I/O pins
#define S1 3                           // Digital Pin 3 // Multiplexer #1 is controlled by 4 I/O pins
#define S2 4                           // Digital Pin 4 // Multiplexer #1 is controlled by 4 I/O pins
#define S3 5                           // Digital Pin 5 // Multiplexer #1 is controlled by 4 I/O pins
struct STRUCT1 {float o; float t; };   // define a new structure class called 'STRUCT1 that will enable the thermistor function
struct STRUCT2 {float a;};               // define a new structure class called 'STRUCT2 that will enable the relhum function
unsigned long timePassed= readInterval + 1; // initializing reading timer at (ReadInterval + 1); to force a first reading right at the start
void(* resetFunc) (void) = 0;    // define a reset function for the arduino micro-controller

////// SETUP ////////
 
void setup(void) {
    
    Serial.begin(baudRate);                           // initialize serial monitor at the specified baud rate (e.g. 9600) 
    analogReference(EXTERNAL);                        // tells the MPU to use the external voltage as a reference (value used at the top of the ADC range)

/////////// RTC SECTION - START
    if (! rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      Serial.flush();
    }
    if (! rtc.initialized() || rtc.lostPower()) {
      Serial.println("RTC is NOT initialized, let's set the time!");
      // When time needs to be set on a new device, or after a power loss, the
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    // When time needs to be re-set on a previously configured device, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));  
    // When the RTC was stopped and stays connected to the battery, it has
    // to be restarted by clearing the STOP bit. Let's do this to ensure
    // the RTC is running.
    rtc.start();
 ////////// RTC SECTION - END
    
    units =  EEPROM.read(0);                          // read EEPROM in case, temperature units were previously defined
    long readInterval_ROM;                            // define readInterval_ROM before using it to store data extracted from EEPROM, if any
    EEPROM.get(4, readInterval_ROM);                  // Read EEPROM address that could contain readInterval and store to temporary variable
    
    if (readInterval_ROM !=0){                        // If readInterval present ...
      readInterval = readInterval_ROM;}               // ... use that stored value.

    int numberC_ROM = EEPROM.read(8);
    if (numberC_ROM !=0){                              // If numberC present ...
      numberC = numberC_ROM;}                         // ... use that stored value.

//- - - - -       
    char sensors_ROM[9];                              //initialize variable
    
    EEPROM.get(20, sensors_ROM);                      // Read EEPROM address that could contain readInterval and store to temporary variable
    for(int i=0; i<8; i++)
      {
         if (sensors_ROM[i]!=0){
          int sensors_present=1;  
         }
      }
    if (sensors_present=1){
          for(int i=0; i<8; i++){
      {
         sensors[i] = sensors_ROM[i];                 //In the arduino language, you must substitute character by character the array
      }
    }
    }
  //- - - - - 
  char humidities_ROM[9];                              //initialize variable
  EEPROM.get(30, humidities_ROM);                      // Read EEPROM address that could contain humidities and store to temporary variable
        for(int i=0; i<8; i++)
      {
         if (humidities_ROM[i]!=0){
          int humidities_present=1;                 
         }
      }
    if (humidities_present=1){
          for(int i=0; i<8; i++){
      {
         humidities[i] = humidities_ROM[i];                 //In the Arduino language, you must substitute character by character the array
      }
    }
    }
      
    pinMode(13,OUTPUT);                               // board Led 'L' is controlled by pin 13. Pin 13 is set to Output mode
    pinMode(S0, OUTPUT);                              // Configure pins dedicated to thermistor multiplexor to 'output'mode (default mode is 'input')
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    Serial.println();
    Serial.println();
    Serial.println(F("Jericho Laboratory inc. // Resistance Data Logger (RDL)"));
    Serial.print(F("Code version: "));
    Serial.println(__FILENAME__);
    Serial.println(F("Starting device...Starting live transmission of data...   "));
    Serial.print(F("Temperatures in "));
    //Serial.println(units);
    if (units == 0){
          Serial.print(F("Celcius"));
    }
    if (units == 1){
      Serial.print(F("Fahrenheit"));
    }
    if (units == 2){
      Serial.print(F("Kelvin"));
    }

    Serial.println(F(". Resistances in Ohms."));
    Serial.print(F("Current interval: " ));
    Serial.print(readInterval);
    Serial.println(F(" ms"));  
    Serial.print(F("Number of probes: "));
    Serial.println(numberC);
    Serial.print(F("Sensors: "));
    Serial.println(sensors);
    Serial.print(F("Humidities: "));
    Serial.println(humidities);
    Serial.println(F("For a list of commands, type 'help'"));
    //Serial.println("Temporarily there is a fixed calculation of relative humidity (last column) based on Channels C2 (dry bulb) and C3 (wet bulb)");
    Serial.print(F("Extension wire for channels 1 to 8 (ohms): "));
    for(int i=0; i<8; i++){
          Serial.print(R_wire[i],0);
          Serial.print(F(" ,"));
    }
    Serial.println();
    Serial.println();
    Serial.print(F("Date     "));
    Serial.print(F("Time     "));
    Serial.print(F("  #  "));
    //Serial.print(F("#"));
    spacing2("1",13);
    for (int i=1; i<(numberC+1); i++){
      Serial.print(sensors[i-1]);
      Serial.print(i);
      spacing2("Ti",12);
    }
    if (ohmDisplay == 1)
      Serial.print(F("*"));
      spacing2("*",12);
      for (int i=1; i<(numberC+1); i++){
        Serial.print(F("R"));
        Serial.print(i);
        spacing2("Ti",12);
    }
    Serial.println();
    Serial.println();
    sortHum();                               //this function is run once at setup to determine what are the channels humidity couples (dry and wet)    /////////
}
//------------------------------------------------------------- 

///// MAIN LOOP //////////

void loop(void) {

//-------------------------------------------------------------
// this block must be positionned right before the decision to read or not the group of thermistors (timePassed>= ReadInterval) to ensure correct timers
timePassed=millis()-time1;                  // time elapsed since last read cycle (serial monitor)
//-------------------------------------------------------------

if (timePassed >= readInterval)                 // if enough time has passed, read the channels             
{
    time1=millis();                                 // each time a reading is taken, time1 is reset     
    readCycle2=readCycle2 + 1;                      // increment the read cycle number at each turn     

    for (int i=0; i< (numberC); i++) {              
      setMultiplexer(i);                            /////// (channels 0 to 15 of the multiplexer are used)
      int channel = i+1;                            //channel being measured
      if(sensors[i]=='T'){        //if sensor on channel is a thermoresistor
        struct STRUCT1 valeurs = thermistor(arrayA[i], arrayB[i], arrayC[i],channel);   //call 'thermistor' function and store results in a structure
        arrayV[i] = valeurs.t;                        // storing temperature to array
        arrayR[i] = valeurs.o;                        // storing resistances (ohm) to array       
            }
      if(sensors[i]=='P'){          //if sensor on channel is a photoresistor
        struct STRUCT1 lux1 = illuminance2(channel);
        arrayV[i] = lux1.t;           // storing illuminance to array of values
        //if(lux1.o=='inf'){
        //  lux1.o= 999999;   //to avoid printing 'inf' instead of value
        //}
        arrayR[i] = lux1.o;           // storing resistances (ohm) to array
    }   
    }
    setMultiplexer(15);                             // set multiplexer to empty channel to avoid self-heating effect of the last thermistor called
    runRTC();                                       // display timestamp
    Serial.print(readCycle2);
    spacing(readCycle2, 12);
    for (int i=0; i< (numberC); i++) {               // print all probes temperature with a loop
      spacing(arrayV[i], 12);
      Serial.print(arrayV[i],2);                     // print value from array with 2 decimals  
    }

    if (ohmDisplay == 1){
      spacing2("*",12);
      Serial.print("*");          
          for (int i=0; i< (numberC); i++) {
            spacing(arrayR[i], 14);
            Serial.print(arrayR[i],0);                      // print all probes resistance with a loop (optionnal)
    }}

    if (humDisplay == 1){
      Serial.print(F("  "));   
      Serial.print(F("*"));   
      for (int i=0; i<4; i++){
       //Serial.println();    ///////// test //////////// 
       //Serial.println(humidities[i]);     ////// test ////////////
       //Serial.println();    ///////// test ////////////
       //Serial.println(sortedHum[i]);     ////// test ////////////
      ///int sortedHum[]={5,1,0,0,0,0,0,0}; // test ////////////////
      int db_channel=sortedHum[2*i];
      int wb_channel=sortedHum[2*i+1];
      arrayH[i] = 65;   /////////// temporary test
      if (db_channel!=0){                                   //if there is a humidity probe defined by the user, then calculate the relative humidity
         arrayH[i]=relhum(arrayV[db_channel],arrayV[wb_channel],1013, units);      //reactivate this line after test
         //arrayH[i]=65;               //temporary test
      }
    }
      for (int i=0; i<4; i++){
      Serial.print(F( "    ")); 
      Serial.print(arrayH[i]);         //print relative humidity.
    }
    }
    Serial.println();
}

//----------------------------------------------------------------
//  Watching for incoming commands from serial port

while (Serial.available() > 0) {                   // evaluate if there is content stored in the serial monitor memory of the arduino (incoming data)
    delay(10);                                     // allow a small delay to read content
    char data = Serial.read();                     // The read() function reads characters one at a time from serial buffer
    str = str + String(data);                      // convert new char into string and add that string piece to the rest
    str.toUpperCase();
}
    if(str != ""){        // if str is not an empty string
        int temp1 = commands2();  // rsun the appropriate command based on the incoming text  
    }                             

str="";                     // reinitialize string str with empty string. str holds commands incoming from serial monitor. Without this line, buffer is never empty.  ///////////// TEMP

}  //end of main loop()

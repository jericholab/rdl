
//  ------------------------------
// This program is used on the production line right after soldering the board together
// 1. erase all EEPROM
// 2. things to write on EEPROM:
//   units CELCIUS  (EEPROM address = 0)
//   interval 1000 [ms]  (EEPROM address = 4)
//   quantities: 8 [probes] (EEPROM address = 8)
//   sensors: TTTTTTTT  (EEPROM address = 20)
//   humidities A1B2C3D4  (EEPROM address = 50)
//   ohmDisplay  1 (EEPROM address = 100)
// 3. the end
//  ------------------------------

#include <EEPROM.h>                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)

void setup() {

  Serial.begin(57600);                           // initialize serial monitor at the specified baud rate (e.g. 9600) 
  
  for (int i=0; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);   //start fresh by putting 0s everywhere
  }

EEPROM.put(0, 0);   // Units are celcius

long readInterval = 1000;  //interval of measurements
EEPROM.put(4, readInterval);

int numberC=8;   //number of sensors
EEPROM.put(8, numberC);

char sensors[17]="TTTTTTTTTTTTTTTT";            // define array of X elements to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . factory default.
EEPROM.put(20, sensors);

char humidities[9]="ABCD1234";         // define array of 8 elements to indicate the type of sensor in each channel  (T=thermistor, P=photoresistor) . factory default.
EEPROM.put(50, humidities);

int ohmDisplay=1;   //activate/deactivate the display of resistance values on the serial monitor
EEPROM.put(100, ohmDisplay);  

Serial.println("All done") ; 
}

void loop() {
  // put your main code here, to run repeatedly:

}

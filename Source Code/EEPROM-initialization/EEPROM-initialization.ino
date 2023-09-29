
//  ------------------------------
// This program is used on the production line.
// 1. erase all EEPROM
// 2. things to write on EEPROM:
//   units CELCIUS  (EEPROM address = 0)
//   interval 1000 [ms]  (EEPROM address = 4)
//   quantities: 8 [probes] (EEPROM address = 8)
//   sensors: TTTTTTTTTTTTTTTT  (EEPROM address = 20) (Not yet implemented)
//   humidities A100 0000 0000 0000  (EEPROM address = 30) (Not yet implemented)
// 3. the end
//  ------------------------------

#include <EEPROM.h>                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)

void setup() {

  Serial.begin(57600);                           // initialize serial monitor at the specified baud rate 
  
  for (int i=0; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);   //start fresh by putting 0s everywhere
  }

EEPROM.put(0, 0);   // Units are celcius
long readInterval = 1000;  //interval of measurements
EEPROM.put(4, readInterval);
int numberC=8;   //number of sensors
EEPROM.put(8, numberC); 
Serial.println("All done") ; 
}

void loop() {
  // put your main code here, to run repeatedly:

}

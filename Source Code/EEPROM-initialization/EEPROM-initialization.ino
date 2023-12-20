
//  ------------------------------
// This program is used on the production line.
// 1. erase all EEPROM
// 2. at next main program upload, it will run default values found on the flash memory.
// 3. signal that the program has finished
//  ------------------------------

#include <EEPROM.h>                    // library required to read and write on the EEPROM memory (library size = 8.3 kB)

void setup() {

  Serial.begin(57600);                           // initialize serial monitor at the specified baud rate 
  
  for (int i=0; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);   //start fresh by putting 0s everywhere
  }


Serial.println("All done") ; 
}

void loop() {
  // put your main code here, to run repeatedly:

}

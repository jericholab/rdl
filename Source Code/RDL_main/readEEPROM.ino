//-------------------------------------------------------------------
// FONCTION: readEEPROM
// PURPOSE: Read RDL parameters from the EEPROM memory, if possible
// INPUT: none
// OUTPUT: none

void readEEPROM(){

    units_T =  EEPROM.read(0);                          // read EEPROM in case, temperature units were previously defined. EEPROM.read() will read a single byte.
    long readInterval_ROM;                            // define readInterval_ROM before using it to store data extracted from EEPROM, if any
    EEPROM.get(4, readInterval_ROM);                  // Read EEPROM address that could contain readInterval and store to temporary variable. EEPROM.get() can read variable size object.
    
    if (readInterval_ROM !=0){                        // If readInterval present ...
      readInterval = readInterval_ROM;}               // ... use that stored value.

    int numberC_ROM = EEPROM.read(8);
    if (numberC_ROM !=0){                              // If numberC present ...
      numberC = numberC_ROM;}                         // ... use that stored value.

    int numberV_ROM = EEPROM.read(9);
    if (numberV_ROM !=0){                              // If numberC present ...
      numberV = numberV_ROM;}                         // ... use that stored value.

 //- - - - -       
    int ohmDisplay_ROM;                              //initialize variable
    EEPROM.get(100, ohmDisplay_ROM);                      // Read EEPROM address that could contain ohmDisplay and store to temporary variable
 
         if (ohmDisplay_ROM=0){
          int ohmDisplay=0;  
         }
}

// -----------------------------------------

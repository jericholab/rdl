//-------------------------------------------------------------------
// FONCTION: readEEPROM
// PURPOSE: Read RDL parameters from the EEPROM memory, if possible
// INPUT: none
// OUTPUT: none

void readEEPROM(){

    units =  EEPROM.read(0);                          // read EEPROM in case, temperature units were previously defined
    long readInterval_ROM;                            // define readInterval_ROM before using it to store data extracted from EEPROM, if any
    EEPROM.get(4, readInterval_ROM);                  // Read EEPROM address that could contain readInterval and store to temporary variable
    
    if (readInterval_ROM !=0){                        // If readInterval present ...
      readInterval = readInterval_ROM;}               // ... use that stored value.

    int numberC_ROM = EEPROM.read(8);
    if (numberC_ROM !=0){                              // If numberC present ...
      numberC = numberC_ROM;}                         // ... use that stored value.

    int numberV_ROM = EEPROM.read(9);
    if (numberV_ROM !=0){                              // If numberC present ...
      numberV = numberV_ROM;}                         // ... use that stored value.

//- - - - -      
    char sensors_ROM[9];                            // Initialize variable
    EEPROM.get(20, sensors_ROM);                      // Read EEPROM address that could contain readInterval and store to temporary variable
    for(int i=0; i<8; i++)    
      {
          if (sensors_ROM[i]!=0){                     // if the content of the variable is different then 0,
             sensors_present=1;                      // then at least one sensor is probably defined
          }
      }
    if (sensors_present==1){
      for(int i=0; i<(9); i++){
        sensors[i] = sensors_ROM[i];                 //In the Arduino language, you must substitute character by character the array
      }
    }

 //- - - - -       
    int ohmDisplay_ROM;                              //initialize variable
    EEPROM.get(100, ohmDisplay_ROM);                      // Read EEPROM address that could contain ohmDisplay and store to temporary variable
 
         if (ohmDisplay_ROM=0){
          int ohmDisplay=0;  
         }
      
  //- - - - - 
//  char humidities_ROM[9];                              //initialize variable
//  EEPROM.get(50, humidities_ROM);                      // Read EEPROM address that could contain humidities and store to temporary variable
//        for(int i=0; i<8; i++)
//      {
//         if (humidities_ROM[i]!=0){
//          humidities_present=1;        
//         }
//      }
//    if (humidities_present==1){
//          for(int i=0; i<8; i++){
//      {
//         humidities[i] = humidities_ROM[i];                 //In the Arduino language, you must substitute character by character the array
//      }
//    }
//    }
}

  //- - - - - 

// -----------------------------------------

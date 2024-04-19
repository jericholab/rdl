
//-------------------------------------------------------------------
// FONCTION NAME: currentNAU7802
// PURPOSE: Obtain a measurement from the TAMURA current sensor by using the 24-bit ADC of the strain gauge load cell
// INPUT: none
// OUTPUT: none

void currentNAU7802() {

  float val = -1.00;            // define a default value.
  
  strainDevice = 1;             // TEMPORARY STATEMENT TO FORCE READING.
  
  if(strainDevice == 1){        // if sensor found by strain_init()
    nau.begin();                // The begin() statement is necessary at each power cycle. Calibration is NOT necessary at each power cycle.
    
    val = nau.getReading();     // Read sensor
   
    Serial.print(F("*"));
    spacing2(F("*"),12); 
    Serial.print(val);
    spacing1(val,12); 
    
  }
  }

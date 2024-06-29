
//-------------------------------------------------------------------
// FONCTION NAME: strainFunc
// PURPOSE: Obtain a measurement from the selected strain gauge load cell
// INPUT: channel
// OUTPUT: none

void strainFunc() {

  float val = -1.00;            // define a default value.
  float b = 20000;              // DUMMY VALUE. Calibration value. ADC value when load cell has no load.
  float a = 1000;               // DUMMY VALUE. Calibration value. Load cell ratio (Newton/ADC) measured experimentally.
  
  strainDevice = 1;             // TEMPORARY STATEMENT TO FORCE READING.
  
  if(strainDevice == 1){        // If sensor found by strain_init()
    //nau.begin();              // Includes a full reset. // The begin() statement is necessary at each power cycle. Calibration is NOT necessary at each power cycle.
    nau.begin(Wire, false);     // TEST to avoid full reset
    val = nau.getReading();     // Read sensor
   
    Serial.print(F("*"));
    spacing2(F("*"),12); 
    Serial.print(val);
    spacing1(val,12); 
    
    float force = (val-b)/a;    //[N] Force applied on load cell. Linear equation convert ADC to force based on calibration values.
    Serial.print(force);
    spacing1(force,12); 
  }
  }

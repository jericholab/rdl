
//-------------------------------------------------------------------
// FONCTION NAME: strainFunc
// PURPOSE: Obtain a measurement from the selected strain gauge load cell
// INPUT: calibration coefficients (a,b)
// OUTPUT: none

void strainFunc(float a, float b) {

  float val = -1.00;            // define a default value.
  float ds = 0.04;              // (meters) TAL220 = 40mm // distance in between two holes (gauge cells). Enables to calculate the moment [N-m]  

  if (strain_initiated<qty_strain){
    if (!nau_ada.begin()) {       //The begin() statement contains instance creation.
      //Serial.print("Failed to find NAU7802");
    }
    else{ 
      strain_present=1;   // the sensor is considered present
      strain_initiated++;   //increment by one the number of strain sensors having been initiated
    } 
  }
  if(strain_present == 1){                // If sensor found 
        nau_ada.enable(true);             // Prescribe the sensor to power up.
            // Take 10 readings to flush out readings
            for (uint8_t i=0; i<10; i++) {
              while (! nau_ada.available()) delay(1);
              nau_ada.read();
            }
        val= nau_ada.read();            // Read sensor  //Adafruit library only
        Serial.print(F("*"));
        spacing2(F("*"),12); 
        Serial.print(val,0);
        spacing1(val,15); //extra two spaces because we removed two decimals.
        float force = (val-b)/a;    //[N] Force applied on load cell. Linear equation convert ADC to force based on calibration values.
        Serial.print(force);
        spacing1(force,12); 
        float moment = force *ds;   //[N-m] Moment applied on load cell.
        Serial.print(moment);
        spacing1(moment,12); 
        nau_ada.enable(false);   // power off the sensor before cutting power, so we are able to power up at the next measurement
  }
  else{    
      Serial.print(F("*"));
      spacing2(F("*"),12); 
      Serial.print(F("0.00"));                               //print the temperature
      spacing2(F("0.00"),12); 
      Serial.print(F("0.00"));                               //print the relative humidity
      spacing2(F("0.00"),12);
    }

  }

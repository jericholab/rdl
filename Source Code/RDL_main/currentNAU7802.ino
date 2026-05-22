//-------------------------------------------------------------------
// FONCTION NAME: currentNAU7802
// PURPOSE: Obtain a measurement from the TAMURA current sensor by using the 24-bit ADC of the strain gauge load cell. Only works with DC current for now.
// INPUT: none
// OUTPUT: none

void currentNAU7802(uint8_t t_channel, float zeroValue, float T_ref) {

  //Watchdog.enable(4000);        // Start the 4000ms counter of the watchdog. If watchdog.reset() is not sent within 4000ms, the watchdog resets the Arduino.
  float offset = 26700;         // offset for conversion of adc to vols (temporary approximation based on early experimental measurements)
  float slope = 1662407;        // offset for conversion of adc to vols (temporary approximation based on early experimental measurements)
  //float zeroValue = 2.4805;                      // TAMURA sensor output value when null current
  int n = 2;   //20                               // size of the sample to be collected
  int discarded = 0;                             // number of samples discarded
  int i;                                         // integer for loop iteration
  float raw_value = 0;                           // initialize raw value
  float val_sum = 0;                             // initialize average value
  float volts;                                   // initialize variable
  float val_a = -1.00;                           // define a default value.
  float val_b = -1.00;                           // define a default value.
  float val2 = -1.00;                            // define a default value.
  float val3 = -1.00;                            // define a default value.  
  float offsetTdrift = 0;                        // initialize variable to zero
  float T_comp = 0;                              // initialize variable to zero
  float hallRatio = 33.33333;                    // Hall effect sensor ratio (Amps/Volt) for the TAMURA L01Z050S05 (50/1.5 = 33.33333)

  if (current_initiated < 1) {
    if (!nau_current.beginCurrent()) {                     // //The beginCurrent() statement contains instance creation. It is a modified copy of begin().
      Serial.print("N/A");
      delay(1000);
    }
    else {    //if begin() doesn't fail then the sensor is considered present
      //Serial.print("BeginCurrent() ran    ");
      current_present = 1; // the sensor is considered present
      current_initiated++;   //increment by one the number of current sensors having been initiated ////// This will eventually reach the limit and reset to zero, causing a begin() call.
    }
  }

  //******* THE CONDITION BELOW IS WEAK. What if we have two active sensors and one unplugged?
  // We would then launch begin() twice on the same sensor and later try to enable() a second sensor - who's just been hotplugged - without any instantiation.
  // This kind of behavior can only be temporary.
  //  if (current_initiated >= 1){   // TEST. Maybe if at least one sensor has been initiated, we don't need to initiate them at the next loop
  //    //if (current_initiated >= qty_current){   //if all sensors have been initiated once, we don't need to initiate them at the next loop
  //      Serial.print(current_initiated);
  //      Serial.print("  ");
  //      Serial.print(qty_current);
  //      Serial.print("  ");
  //
  //      //nau_current.enableCurrent(true);   //contains beginCurrent() except the instantiation
  //    }

  if (current_present == 1){
    nau_current.enable(true);
    nau_current.enableCurrent2(); 
    nau_current.setRate(NAU7802_RATE_10SPS);
    delay(100);
    nau_current.setLDO(NAU7802_EXTERNAL);
    delay(100);
    nau_current.calibrate(NAU7802_CALMOD_INTERNAL);    //Re-cal analog front end when we change gain, sample rate, or NAU7802 channel (Recalibration must be done after changes to register)
    delay(500);  //1000

    //nau_current.enable(false);
    //nau_current.enable(true);
    //nau_current.enableCurrent(true);         // Prescribe the sensor to power up.
    delay(100);
    
    if (nau_current.available()) {    // Verify if the sensor has data available
      //for (i = 0; i < n; i++) {
      //  val = nau_current.read();
      //  val_sum = val_sum + val;
      //}
      for (i = 0; i < n; i++) {
        val_a = nau_current.read();
        delay(100);                    // We must space the two readings enough to avoid double bad readings.
        val_b = nau_current.read();
        if (abs(val_a - val_b) < 5000) { //threshold for value rejection is 5000 ADC.
          val_sum = val_sum + val_a;
        }
        else {
          val_a = -222;            //// test //// lets try to use a different signal for rejection than non-comm.
          discarded = +1;       //if we discard a measurement, the sample size is reduced
        }
      }
    }

    val_sum = val_sum / float(n - discarded); //arithmetic average

    nau_current.enable(false); 

  // TEMPERATURE COMPENSATION
   T_comp = arrayV[t_channel - 1];                // current sensor temperature
  if (currentTComp == 1) {
    float slope = -0.001136;                   // slope for offset temperature drift compensation [mv/C] based on exp 2025-05-08
    offsetTdrift = (T_comp - T_ref) * slope;   //offset temperature drift compensation [mV] (array indexed to 0, not 1)  
  }

  // CONVERT VOLTAGE TO AMPS
  if (val_sum>0){
    val2 = (val_sum - offset) / slope; //convert the ADC to volts  
    float V_offset = zeroValue + offsetTdrift;       //[mV] offset value (no load) to calibrate the sensor
    val3 = (val2 - V_offset) * hallRatio;      // Finalize conversion to instantaneous amps
  }    

    
  } //end of if (current_present = 1)

 // PRINT OUT RESULTS

  Serial.print(F("*"));
  spacing2(F("*"), 12);

  Serial.print(T_comp, 2);
  spacing1(T_comp, 12);

  Serial.print(offsetTdrift, 5);
  spacing1(offsetTdrift, 9);                          //12 spaces - 3 extra decimals (total 5) = 9 spaces

  Serial.print(val_a, 0);                           // raw value (single read) 
  spacing1(val_a, 15);
  Serial.print(val2, 4);                            // sensor voltage output
  spacing1(val2, 11);                                //12 spaces - 1 extra decimals (total 5) =  11 spaces

  Serial.print(val3, 3);                           // Print out the value you read. Test with 3 decimals
  spacing1(val3, 11);                             // Since a bonus decimal is printed, the spacing requirement is reduced by one unit.



}

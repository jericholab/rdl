//-------------------------------------------------------------------
// FONCTION NAME: currentNAU7802
// PURPOSE: Obtain a measurement from the TAMURA current sensor by using the 24-bit ADC of the strain gauge load cell. Only works with DC current for now.
// INPUT: none
// OUTPUT: none
//
//********************** CAREFUL ******************************** STILL SOME DUMMY VALUES IN THIS FUNCTION ****************************
//********************** CAREFUL ******************************** TEMPERATURE COMPENSATION INACTIVE FOR NOW ****************************

void currentNAU7802(uint8_t t_channel) {

  //Watchdog.enable(4000);        // Start the 4000ms counter of the watchdog. If watchdog.reset() is not sent within 4000ms, the watchdog resets the Arduino. 
  float offset = 26700;         // offset for conversion of adc to vols (temporary approximation based on early experimental measurements)
  float slope= 1662407;         // offset for conversion of adc to vols (temporary approximation based on early experimental measurements)
  float zeroValue = 2.4585;                      // sensor output value when null current //TEMPORARY DUMMY VALUE
  int n = 20;                                    // size of the sample to be collected
  int i;                                         // integer for loop iteration
  float raw_value = 0;                           // initialize raw value
  float val_sum = 0;                           // initialize average value
  float volts;                                   // initialize variable 
  float val = -1.00;            // define a default value.
  float val2 = -1.00;           // define a default value.
  float offsetTdrift = 0;                        // initialize variable to zero
  float T_comp =0;                               // initialize variable to zero
  float hallRatio = 33.33333;                    // Hall effect sensor ratio (Amps/Volt) for the TAMURA L01Z050S05 (50/1.5 = 33.33333)
  
  if((currentDisplay == 1)&(current_initiated<qty_current)){  

    if (!nau_current.begin()) {                // //The begin() statement contains instance creation.
//      //Serial.print("Failed to find NAU7802");
//      //delay(1000);
        //these configurations run only at the initialization, not at every power up.
        nau_current.setRate(NAU7802_RATE_80SPS);   //I must eventually test if these function calls return true (1) ......................................
        nau_current.setLDO(NAU7802_EXTERNAL);  
        nau_current.calibrate(NAU7802_CALMOD_INTERNAL);    //Re-cal analog front end when we change gain, sample rate, or NAU7802 channel (Recalibration must be done after changes to register)
        nau_current.calibrate(NAU7802_CALMOD_OFFSET);  ///// JUST A TEST. I'm not sure I want that.
        // common mode input is activated inside the jericho_adafruit_nau7802 version. (Requires PGA bypass mode set) )
        // ADD HERE PGA BYPASS? IMPOSSIBLE INTERNAL METHOD. HAS TO BE INSIDE THE LIBRARY   ////////////////////////
          
    }
    else{ 
      current_present=1;   // the sensor is considered present
      current_initiated++;   //increment by one the number of current sensors having been initiated
    }
    }
  Wire.setClock(clockSpeed);                         // clockSpeed must be prescribed after library begins because it overrides the parameter by reinitializing the Wire library.


/////////////////////

//    TEMPORARY COMMENT ALL THE SPARKFUN CONFIGURATION THAT IS NOT REQUIRED TO TEST THE MULTIPLEXING
//
//    nau_current.setSampleRate(NAU7802_SPS_320); //Increase to max sample rate    *********** MAX SAMPLE RATE NOT REQUIRED FOR DC CURRENTS (INCREASED NOISE, REDUCED ACCURACY)
//    nau_current.setBit(NAU7802_PGA_BYPASS_EN, NAU7802_PGA);              //Set the NAU7802 register bit that controls the PGA bypass and enable it (just a first test)
//    //INFO: This is the format : bool setBit(uint8_t bitNumber, uint8_t registerAddress) - Mask & set a given bit within a register
//    nau_current.setChannel(NAU7802_CHANNEL_1);   //With NAU7802-revB1, the channel dedicated to current measurements is 1 (A).
//    //nau_current.setChannel(NAU7802_CHANNEL_2);   //With NAU7802-revB1, the channel dedicated to strain measurements is 2 (B).
//
//    nau_current.setBit(3,NAU7802_ADC);     //ACTIVATE THE INPUT COMMON MODE (RANGE CLOSE TO REFN)(Requires PGA bypass mode set)
//    nau_current.clearBit(7,NAU7802_PU_CTRL);   //Clear bit 7 from register NAU7802_PU_CTRL (This will select AVDD pin as AVDD source )
//    nau_current.calibrateAFE();                //Re-cal analog front end when we change gain, sample rate, or NAU7802 channel (Recalibration must be done after changes to register)
//    delay(1000);

  if(current_present == 1){

    nau_current.enable(true);             // Prescribe the sensor to power up.
    if (nau_current.available()){     // Then verify if the sensor has data available
        for (i=0; i< n; i++){
          val = nau_current.read(); 
          val_sum= val_sum + val;
        } 
      }     
      val_sum = val_sum/float(n);   //arithmetic average
      val2=(val_sum-offset)/slope;  //convert the ADC to volts
      nau_current.enable(false);   // power off the sensor before cutting power, so we are able to power up at the next measurement
  }
    Serial.print(F("*"));
    spacing2(F("*"),12); 
     
    // TEMPERATURE COMPENSATION
    T_comp = arrayV[t_channel-1];                  // current sensor temperature 
    Serial.print(T_comp,2);   
    spacing1(T_comp,12);                       
    if (currentTComp == 1){
        float slope = 0; //-0.0001122;                  // slope for offset temperature drift compensation [mv/C] NULL VALUE FOR NOW
        float T_ref = 21;                               // Reference temperature for the temperature compensation [C]
        offsetTdrift = (arrayV[t_channel-1]-21)*slope;  //offset temperature drift compensation [mV] (array indexed to 0, not 1)  
    } 
    Serial.print(offsetTdrift,5);   
    spacing1(offsetTdrift,9);                           //12 spaces - 3 extra decimals (total 5) = 9 spaces

    Serial.print(val,0);  // raw value
    spacing1(val,15); 
    Serial.print(val2,4);  // raw value
    spacing1(val2,11);                                 //12 spaces - 1 extra decimals (total 5) =  11 spaces

    // CONVERT VOLTAGE TO AMPS
    float V_offset = zeroValue + offsetTdrift;       //[mV] offset value (no load) to calibrate the sensor
    float val3 = (val2 - V_offset) * hallRatio;      // Finalize conversion to instantaneous amps  (Removing V_offset after RMS allow negative currents)
    Serial.print(val3,3);                           // Print out the value you read. Test with 3 decimals
    spacing1(val3,11);                              // Since a bonus decimal is printed, the spacing requirement is reduced by one unit.
    
//    Watchdog.reset();                               //  If watchdog.reset() is not sent within 4000ms, the watchdog resets the Arduino. 
//    Watchdog.disable();                             // If the code executed completely, we can disable the watchdog until the next call to the function.
  }
  

//-------------------------------------------------------------------
// FONCTION: initRTC
// PURPOSE: initialize the Real-Time-Clock on the RDL PCB.
// INPUT: none
// OUTPUT: none

void initRTC(){

    if (! rtc.begin()) {       //if unable to start the rtc, then print out a warning to the user
      Serial.println();
      Serial.println(F("Couldn't find RTC"));
      Serial.flush();
    }

    if (rtc.lostPower()) {
      Serial.println("RTC is NOT running, let's set the time!");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // When time needs to be set on a new device, or after a power loss, the following line sets the RTC to the date & time this sketch was compiled.
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); // This line sets the RTC with an explicit date & time, for example to set January 21, 2014 at 3am you would call:
  }
  
    
    // When time needs to be re-set on a previously configured device, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));  
    // When the RTC was stopped and stays connected to the battery, it has
    // to be restarted by clearing the STOP bit. Let's do this to ensure
    // the RTC is running.

}




//-------------------------------------------------------------------

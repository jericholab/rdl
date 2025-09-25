//-------------------------------------------------------------------
// FONCTION: setTime
// PURPOSE: apply last compile time to the RTC (Real-Time Clock)
// INPUT: none
// OUTPUT: none
void setTime(){
  
    DateTime now = DateTime(F(__DATE__), F(__TIME__));
    if (isDST(now) && (dstRegion == 1)) {  // Check if we are currently in DST and adjust time if necessary
      DateTime dstAdjustedTime = now - TimeSpan(0, 1, 0, 0); // Remove 1 hour to obtain non-DST
      rtc.adjust(dstAdjustedTime);
    } else {
      rtc.adjust(now); // Use standard time if not in DST
    }
  
}
//-------------------------------------------------------------------

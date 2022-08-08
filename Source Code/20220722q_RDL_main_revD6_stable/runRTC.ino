//-------------------------------------------------------------------
// FONCTION NAME: runRTC
// INPUT: None.
// OUTPUT: None.

int runRTC(){

   DateTime now = rtc.now();

  //buffer can be defined using following combinations:
  //hh - the hour with a leading zero (00 to 23)
  //mm - the minute with a leading zero (00 to 59)
  //ss - the whole second with a leading zero where applicable (00 to 59)
  //YYYY - the year as four digit number
  //YY - the year as two digit number (00-99)
  //MM - the month as number with a leading zero (01-12)
  //MMM - the abbreviated English month name ('Jan' to 'Dec')
  //DD - the day as number with a leading zero (01 to 31)
  //DDD - the abbreviated English day name ('Mon' to 'Sun')

   char buf1[] = "YYYY/MM/DD";
   Serial.print(now.toString(buf1));
   spacing2(buf1,12);
   
   char buf2[] = "hh:mm:ss"; 
   Serial.print(now.toString(buf2));
   spacing2(buf2,12);

//Alternative ways of printing RTC data:
//    DateTime now = rtc.now();
//
//    Serial.print(now.timestamp(DateTime::TIMESTAMP_FULL));
//    
//    Serial.print(now.year(), DEC);
//    Serial.print(F("/"));
//    Serial.print(now.month(), DEC);
//    Serial.print(F("/"));
//    Serial.print(now.day(), DEC);
//    //Serial.print(";");          //add one semi-colon for csv purposes
//    Serial.print(F("  "));
//    Serial.print(now.hour(), DEC);
//    Serial.print(F(":"));
//    Serial.print(now.minute(), DEC);
//    Serial.print(F(":"));
//    Serial.print(now.second(), DEC);

  }

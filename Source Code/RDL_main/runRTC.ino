//-------------------------------------------------------------------
// FONCTION NAME: runRTC
// PURPOSE: ask the Real-Time Clock chip to provide the present time
// INPUT: none
// OUTPUT: none

void runRTC(){

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
  }

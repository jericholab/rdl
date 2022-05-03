//-------------------------------------------------------------------
// FONCTION: spacing2
// INPUT: item (item to display), space(number of characters of the area in total)
// OUTPUT: none
int spacing2(String item, int space)
{          
      String temp10= String(item);
      int temp11 = temp10.length();
      int temp12 = space-temp11;  //required number of spaces
      for (int i=0; i< (temp12-1); i++){
         Serial.print(F(" "));
      }
}

//----------------------------------------------------------------

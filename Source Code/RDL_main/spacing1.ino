//-------------------------------------------------------------------
// FONCTION: spacing1 (for float variables)
// PURPOSE: add the correct amount of space after a float to keep the columns aligned
// INPUT: item (item to display), space(number of characters of the area in total)
// OUTPUT: none

void spacing1(float item, int space)
{          
      String temp10= String(item);   //the String() function will keep two decimals from the float by default. Be careful if you print more or less than 2 decimals.
      int temp11 = temp10.length();
      int temp12 = space-temp11;  //required number of spaces
      //Serial.print(";");          //add one semi-colon for csv purposes
      for (int i=0; i< (temp12-1); i++){
         Serial.print(F(" "));
      }
}
//-------------------------------------------------------------------

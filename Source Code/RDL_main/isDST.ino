//-------------------------------------------------------------------
// FONCTION: isDHT
// PURPOSE: //function checks if the current date falls within the DST period for North America
// INPUT: date time
// OUTPUT: true, false

bool isDST(DateTime dt) {
  int month = dt.month();
  int day = dt.day();
  int weekday = dt.dayOfTheWeek(); // Sunday is 0, Monday is 1, etc.

  // DST starts on the second Sunday in March
  if (month > 3 && month < 11) return true; // Between March and November, DST is active
  if (month < 3 || month > 11) return false; // Outside of March to November, DST is inactive

  // For March and November, we need to check the specific day
  if (month == 3) {
    // DST starts on the second Sunday in March
    return (day - weekday >= 8); // Returns true if it's the second Sunday or later
  }
  if (month == 11) {
    // DST ends on the first Sunday in November
    return (day < (8 - weekday)); // Returns false if it's the first Sunday or earlier in November
  }
  return false; // Fallback just in case
}

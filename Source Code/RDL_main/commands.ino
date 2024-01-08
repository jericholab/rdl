//-------------------------------------------------------------------
// FONCTION: commands
// PURPOSE: execute the command required by the user input
// INPUT: none
// OUTPUT: none

void commands(){

  char text1[]="Switching temperature units to";
  char text2[]="What new definition do you want ?  (You have 30 seconds)";  
  char text3[]="New definition:   ";

if (str == F("RESET\r")){          
    blink(200,2);
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //restart the Arduino
}
if (str == F("CELCIUS\r")){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units_T = 0;
    EEPROM.put(0, units_T);                // writes the chosen unit to EEPROM address "1".
    delay(1000);                         // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc();                         //restart the Arduino
}

if (str == F("FAHRENHEIT\r")){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units_T = 1;  
    EEPROM.put(0, units_T);                      // writes the chosen unit to EEPROM address "1".
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}

if (str == F("KELVIN\r")){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units_T = 2;  
    EEPROM.put(0, units_T);                      // writes the chosen unit to EEPROM address "1".
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}

    if (str == F("HELP\r")){
    Serial.println();
    Serial.println(F("Possible commands:")); 
    Serial.println(F("CELCIUS, FAHRENHEIT, KELVIN, RESET, EEPROM-ERASE, INTERVAL, QTY-T, QTY-V"));
    Serial.println();
    delay(2000);
    }        

if (str == F("EEPROM-ERASE\r")){
    blink(200,2);
    Serial.println();
    Serial.println(F("Back to factory settings...   "));
  for (int i=0; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  resetFunc();                  //reset the arduino
}


if (str == F("INTERVAL\r")){  //if word "interval" is received, enter a while loop until user sends desired measurement interval.
  Serial.println();
  Serial.print(F("Present rate is "));
  Serial.print(readInterval);
  Serial.println(F(" ms"));
  Serial.println(text2);  
  long timer10 = millis();
  while ((Serial.available() == 0) && ((millis() - timer10)< 30000)){
    readInterval0 = Serial.parseInt();  //Read the data the user has input. If no valid digits are read, function defaults to zero.
  }
  if (readInterval0 > 0){                       // if new value greater than zero... 
    readInterval = readInterval0;                // ... then we can now use that value now
    EEPROM.put(4, readInterval);                 // writes the new rate to EEPROM address "4".
  }
  Serial.print(text3);
  Serial.print(readInterval);
  Serial.println(F(" ms"));
  Serial.println();
  printHeader();
}

if (str == F("QTY-T\r")){  //if word "quantity" is received, enter a while loop until user sends desired quantity of probes.
  Serial.println();
  Serial.print(F("Present qty thermistors: "));
  Serial.println(numberC);
  Serial.println(F("How many probes needed ? (1 to 8) (You have twenty seconds)"));
  long timer10 = millis();
  while ((Serial.available() == 0) && ((millis() - timer10)< 30000)){
    numberC10 = Serial.parseInt();  //Read the data the user has input. If no valid digits are read, function defaults to zero.
  }
  if ((numberC10 > 0)&&(numberC10<=8)){              // if new value between 1 and 8... 
    numberC = numberC10;                             // ... then we can now use that value now
    EEPROM.put(8, numberC);                          // writes the new rate to EEPROM. 
  }
  Serial.print(F("New quantity is "));
  Serial.println(numberC);
  Serial.println();
  delay(1000);
  resetFunc(); //reset the arduino
}

if (str == F("QTY-V\r")){  //if word "quantity" is received, enter a while loop until user sends desired quantity of probes.
  Serial.println();
  Serial.print(F("Present qty voltages: "));
  Serial.println(numberV);
  Serial.println(F("How many probes needed ? (1 to 8) (You have twenty seconds)"));
  long timer10 = millis();
  while ((Serial.available() == 0) && ((millis() - timer10)< 30000)){
    numberV10 = Serial.parseInt();  //Read the data the user has input. If no valid digits are read, function defaults to zero.
  }
  if ((numberV10 > 0)&&(numberC10<=8)){              // if new value between 1 and 8... 
    numberV = numberV10;                             // ... then we can now use that value now
    EEPROM.put(9, numberV);                          // writes the new rate to EEPROM. 
  }
  Serial.print(F("New quantity is "));
  Serial.println(numberV);
  Serial.println();
  delay(1000);
  resetFunc(); //reset the arduino
}

str="";                     // reinitialize string str with empty string. str holds commands incoming from serial monitor. Without this line, buffer is never empty.
}

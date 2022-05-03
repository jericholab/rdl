
int commands2(){
  
  char text1[]="Switching temperature units to";
  char text2[]="What new definition do you want ?  (You have ten seconds to answer)";  
  char text3[]="New definition:   ";

if (str == "RESET\r"){
    blink(200,2);
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}
if (str == "CELCIUS\r"){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units = 0;
    EEPROM.put(0, units);                // writes the chosen unit to EEPROM address "1".
    delay(1000);                         // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}

if (str == "FAHRENHEIT\r"){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units = 1;  
    EEPROM.put(0, units);                      // writes the chosen unit to EEPROM address "1".
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}

if (str == "KELVIN\r"){
    blink(200,2);
    Serial.println();
    Serial.println(text1);
    Serial.println(str);
    units = 2;  
    EEPROM.put(0, units);                      // writes the chosen unit to EEPROM address "1".
    delay(1000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
    resetFunc(); //reset the arduino
}

    if (str == "HELP\r"){
    Serial.println();
    Serial.println(F("Possible commands:")); 
    Serial.println(F("CELCIUS, FAHRENHEIT, KELVIN, RESET, EEPROM-ERASE, COEFF, INTERVAL, QUANTITY, SENSORS, HUMIDITIES"));
    Serial.println();
    delay(2000);
    }        

if (str == "EEPROM-ERASE\r"){
    blink(200,2);
    Serial.println();
    Serial.println(F("Back to factory settings...   "));
  for (int i=0; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  resetFunc(); //reset the arduino
}


//- - - - - - - - - - - 
char buf[9]; 
if (str =="SENSORS\r"){
  Serial.println();
  Serial.println(sensors); 
  Serial.println();
  Serial.println(text2);
  Serial.println();
  long timer10 = millis();
    while ((Serial.available() == 0) && ((millis() - timer10)< 10000)){
      const int BUFFER_SIZE = 9;
      Serial.readBytesUntil('\n', buf , BUFFER_SIZE);  //Read the data the user has input. (Array has 8 characters (8 channels) plus the null character to terminate the array. Total is 9)
      }
bool test_result =0;                         //initialize test result variable as true
  if (sizeof(buf) ==9){                       // if new string has a length of (8 values + null character)

     for(int i=0; i<8; i++){{
         if ((buf[i] != 'T')&&(buf[i] != 'P')){           //if buffer contains something else than 'T' and 'P', then break the loop and test_result value remains zero.
          break;
         }
         test_result=1;               
      }
      if (test_result=1){                    //if buffer contains only good characters and has proper length, then we will update the sensor variable with new content
            for(int i=0; i<8; i++){
              sensors[i] = buf[i];
              }
      }
    }  
    EEPROM.put(20, sensors);                 // writes the new rate to specific EEPROM address (20).
    Serial.print(text3);
    Serial.println(sensors);
    Serial.println();
    delay(1000);
    resetFunc(); //reset the arduino
  }
    Serial.print(F("wrong input"));
}
//- - - - - - - - - - - 

//- - - - - - - - - - - 
char buf2[9]; 
if (str =="HUMIDITIES\r"){
  Serial.println();
  Serial.println(humidities); 
  Serial.println();
  Serial.println(text2);
  Serial.println();
    long timer11 = millis();
    while ((Serial.available() == 0) && ((millis() - timer11)< 10000)){
      const int BUFFER_SIZE = 9;
      Serial.readBytesUntil('\n', buf2 , BUFFER_SIZE);  //Read the data the user has input. (Array has 8 characters (8 channels) plus the null character to terminate the array. Total is 9)
      }
bool test_result =0;                         //initialize test result variable as true
  if (sizeof(buf2) ==9){                       // if new string has a length of (8 values + null character)

     for(int i=0; i<8; i++){{                           //that is harder to implement because we have 0, A, B, C' D, 1, 2, 3, 4....
         if ((buf2[i] != 'A')&&(buf2[i] != 'B')&&(buf2[i] != 'C')&&(buf2[i] != 'D')&&(buf2[i] != '0')&&(buf2[i] != '1')&&(buf2[i] != '2')&&(buf2[i] != '3')&&(buf2[i] != '4')){           
          break;
         }
         test_result=1;               
      }
      if (test_result=1){                    //if buffer contains only good characters and has proper length, then we will update the sensor variable with new content
            for(int i=0; i<8; i++){
              humidities[i] = buf2[i];
              }
      }
    }  
    EEPROM.put(30, humidities);                 // writes the new rate to specific EEPROM address (20).
    Serial.print(text3);
    Serial.println(humidities);
    Serial.println();
    delay(1000);
    resetFunc(); //reset the arduino
  }
    Serial.print(F("wrong input"));
}
//- - - - - - - - - - - 

if (str == "COEFF\r"){
    char space1[]="     ";
    blink(200,2);
    Serial.println();
    Serial.println(F("Thermistors coefficients:"));
    Serial.print(F("#"));
    Serial.print(space1);
    Serial.print(space1);
    Serial.print(F("A"));
    Serial.print(space1);
    Serial.print(F("B"));
    Serial.print(space1);
    Serial.print(F("C"));
    Serial.println(space1);
    for(int i=0; i<8; i++){
          Serial.print(i+1);
          Serial.print(space1);
          Serial.print(space1);
          Serial.print(arrayA[i],20);  //prints the 'A' coefficients with 20 decimals
          Serial.print(space1);
          Serial.print(arrayB[i],20);  //prints the 'A' coefficients with 20 decimals
          Serial.print(space1);
          Serial.print(arrayC[i],20);  //prints the 'A' coefficients with 20 decimals
          Serial.println();
    }
    Serial.println();
    Serial.println();
    delay(2000);                               // after printing out the EEPROM content, wait two seconds before starting measurements again
}


if (str =="INTERVAL\r"){  //if word "interval" is received, enter a while loop until user sends desired measurement interval.
  Serial.println();
  Serial.print(F("Present rate is "));
  Serial.print(readInterval);
  Serial.println(F(" ms"));
  Serial.println(text2);  
  long timer10 = millis();
  while ((Serial.available() == 0) && ((millis() - timer10)< 10000)){
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
}

if (str =="QUANTITY\r"){  //if word "quantity" is received, enter a while loop until user sends desired quantity of probes.
  Serial.println();
  Serial.print("Present quantity: ");
  Serial.println(numberC);
  Serial.println("How many probes do you want to use ? (From 1 to 16) (You have twenty seconds to answer)");  
  long timer10 = millis();
  while ((Serial.available() == 0) && ((millis() - timer10)< 20000)){
    numberC10 = Serial.parseInt();  //Read the data the user has input. If no valid digits are read, function defaults to zero.
  }
  if ((numberC10 > 0)&&(numberC10<=16)){              // if new value between 1 and 16... 
    numberC = numberC10;                             // ... then we can now use that value now
    EEPROM.put(8, numberC);                          // writes the new rate to EEPROM address "6". 
  }
  Serial.print("New quantity is ");
  Serial.println(numberC);
  Serial.println();
  delay(1000);
  resetFunc(); //reset the arduino
}

str="";                     // reinitialize string str with empty string. str holds commands incoming from serial monitor. Without this line, buffer is never empty.
}

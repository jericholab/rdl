//-------------------------------------------------------------------
// FONCTION: watchSerial
// PURPOSE: watch the serial monitor buffer of the microcontroller for possible incoming user command inputs.
// INPUT: none
// OUTPUT: none

void watchSerial(){

while (Serial.available() > 0) {                   // evaluate if there is content stored in the serial monitor memory of the arduino (incoming data)
    delay(10);                                     // allow a small delay to read content
    char data = Serial.read();                     // The read() function reads characters one at a time from serial buffer
    str = str + String(data);                      // convert new char into string and add that string piece to the rest
    str.toUpperCase();
}
    if(str != ""){        // if str is not an empty string
        //int temp1 = commands();  // rsun the appropriate command based on the incoming text  
        commands();  // run the appropriate command based on the incoming text  
    }                             

str="";       // reinitialize string str with empty string. str holds commands incoming from serial monitor. Without this line, buffer is never empty.  ///////////// TEMP

}

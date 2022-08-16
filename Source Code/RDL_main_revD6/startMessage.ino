//-------------------------------------------------------------------
// FONCTION: startMessage
// PURPOSE: Print to serial monitor some informations about the RDL parameters
// INPUT: none
// OUTPUT: none

int startMessage(){

    Serial.println(F("Starting device...Starting live transmission of data...   "));
    Serial.print(F("Temperatures in "));
    if (units == 0){
          Serial.print(F("Celcius"));
    }
    if (units == 1){
      Serial.print(F("Fahrenheit"));
    }
    if (units == 2){
      Serial.print(F("Kelvin"));
    }

    Serial.println(F(". Resistances in Ohms."));
    Serial.print(F("Current interval: " ));
    Serial.print(readInterval);
    Serial.println(F(" ms"));  
    Serial.print(F("Number of probes: "));
    Serial.println(numberC);
    Serial.print(F("Sensors: "));
    Serial.println(sensors);
    Serial.print(F("Humidities: "));
    Serial.println(humidities);
    Serial.println(F("For a list of commands, type 'help'"));
    Serial.print(F("Extension wire for channels 1 to 8 (ohms): "));
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// FONCTION: startMessage
// PURPOSE: Print to serial monitor some informations about the RDL parameters
// INPUT: none
// OUTPUT: none

void startMessage(){

    Serial.println(F("Starting device..."));
    Serial.print(F("Temperatures: "));
    if (units == 0){
          Serial.print(F("°C"));
    }
    if (units == 1){
      Serial.print(F("°F"));
    }
    if (units == 2){
      Serial.print(F("K"));
    }

    Serial.println(F(". Resistances: Ohms."));
    Serial.print(F("Interval target: " ));
    Serial.print(readInterval);
    Serial.println(F(" ms"));  
//    Serial.print(F("Sensors: "));
//    Serial.println(sensors);
//    Serial.print(F("Humidities: "));
//    Serial.println(humidities);
    Serial.println(F("For list of commands, type 'help'"));
    Serial.print(F("Extension wire, channels 1 to 8 (ohms): "));

    if (headerDisplay == 1){
        for(int i=0; i<8; i++){
              Serial.print(R_wire[i],0);
              Serial.print(F(" ,"));
        }
        Serial.println();

    }
}
//-------------------------------------------------------------------

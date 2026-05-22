//-------------------------------------------------------------------
// FONCTION: startMessage
// PURPOSE: Print to serial monitor some informations about the RDL parameters
// INPUT: none
// OUTPUT: none

void startMessage(){

    Serial.print(F("Temperatures: "));
    if (units_T == 0){
          Serial.print(F("°C"));
    }
    if (units_T == 1){
      Serial.print(F("°F"));
    }
    if (units_T == 2){
      Serial.print(F("K"));
    }

    Serial.println(F(". Resistances: Ohms."));
    Serial.print(F("Interval target: " ));
    Serial.print(readInterval);
    Serial.println(F(" ms"));  
    Serial.println(F("For list of commands, type 'help'"));
    Serial.print(F("Extension wire, C1 to C8 (ohms): "));
//    Serial.println(current_offset);
//    Serial.println(current_T_channel);
//    Serial.println(current_T_ref);

    if (headerDisplay == 1){
        for(int i=0; i<8; i++){
              Serial.print(R_wire[i],0);
              Serial.print(F(" ,"));
        }
        Serial.println();

    }
}
//-------------------------------------------------------------------

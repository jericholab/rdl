//-------------------------------------------------------------------
// FONCTION: printHeader
// PURPOSE: Display the title of each active column
// INPUT: none
// OUTPUT: none

int printHeader(){
        if (headerDisplay == 1){
        for(int i=0; i<8; i++){
              Serial.print(R_wire[i],0);
              Serial.print(F(" ,"));
        }
        Serial.println();
        Serial.println();
        }
        
        if (timeDisplay == 1){
          String dateText = F("Date");
          Serial.print(dateText);
          spacing2(dateText,12);
          String timeText = F("Time");
          Serial.print(timeText);
          spacing2(timeText,12);
        }
    
        if (idDisplay ==1){        
          Serial.print(F("#"));
          spacing2("#",12);
        }
        
        if (tDisplay == 1){
            for (int i=1; i<(numberC+1); i++){
              Serial.print(sensors[i-1]);
              if(i<10){
                Serial.print('0');      // T08, T09, T10, etc.
              }
              Serial.print(i);
              spacing2("Tii",12);
            }
        }
        
        if (ohmDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              for (int i=1; i<(numberC+1); i++)
              {
                Serial.print(F("R"));
                if(i<10){
                 Serial.print('0');      // R08, R09, R10, etc.
                }
                Serial.print(i);
                spacing2("Rii",11);          //the large resistance values to display require more spacing (14) than the rest (12)
              }
            }

        if (humDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              for (int i=1; i<(4+1); i++){
                Serial.print(F("H"));
                Serial.print(i);
                spacing2("Ti",12);
              }
            }

        if (i2cDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String i2cText1 = F("i2c_C");
              Serial.print(i2cText1);
              spacing2(i2cText1,12);
              String i2cText2 = F("i2c_RH");
              Serial.print(i2cText2);
              spacing2(i2cText2,12);
            }
        if (WBGTDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String WBGTText = F("WBGT");
              Serial.print(WBGTText);
              spacing2(WBGTText,12);
            }
        if (SoilDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String soilText = F("Soil");
              Serial.print(soilText);
              spacing2(soilText,12);              
            }
        if (VoltDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String voltageText = F("Voltage");
              Serial.print(voltageText);
              spacing2(voltageText,12);
            }
        if (ControlSignal == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String controlText = F("Control");
              Serial.print(controlText);
              spacing2(controlText,12);
            }
            
      Serial.println();
      Serial.println();
     }
        

    

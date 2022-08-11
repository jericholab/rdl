//-------------------------------------------------------------------
// FONCTION: printHeader
// INPUT: none
// OUTPUT: non

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
          Serial.print(F("Date"));
          spacing2("Date",12);
          Serial.print(F("Time"));
          spacing2("Time",12);
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
              Serial.print(F("i2c_C"));
              spacing2("i2c_C",12);
              Serial.print(F("i2c_HR"));
              spacing2("i2c_HR",12);
            }
        if (WBGTDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              Serial.print(F("WBGT"));
              spacing2("WBGT",12);
            }
        if (SoilDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              Serial.print(F("Soil"));
              spacing2("Soil",12);
            }
        if (VoltDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              Serial.print(F("Voltage"));
              spacing2("Voltage",12);
            }
            
      Serial.println();
      Serial.println();
     }
        

    

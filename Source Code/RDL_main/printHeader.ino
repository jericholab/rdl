//-------------------------------------------------------------------
// FONCTION: printHeader
// PURPOSE: Display the title of each active column
// INPUT: none
// OUTPUT: none

int printHeader(){

        Serial.println();
        
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

              Serial.print(F("*"));   //DOUBLING THE COLUMNS FOR THE SECOND SHT40
              spacing2("*",12);
              //String i2cText1 = F("i2c_C");
              Serial.print(i2cText1);
              spacing2(i2cText1,12);
              //String i2cText2 = F("i2c_RH");
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

//        if (voltDisplay == 1){
//              Serial.print(F("*"));
//              spacing2("*",12);
//              String voltageText = F("Voltage");
//              Serial.print(voltageText);
//              spacing2(voltageText,12);
//            }

       if (voltDisplay == 1){
            Serial.print(F("*"));
            spacing2("*",12);
            for (int i=1; i<(numberC+1); i++){
              Serial.print(F("V"));
              if(i<10){
                Serial.print('0');      // T08, T09, T10, etc.
              }
              Serial.print(i);
              spacing2("Vii",12);
            }
        }

        if (currentDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String voltageText = F("Amps");
              Serial.print(voltageText);
              spacing2(voltageText,12);
              //spacing2("0.000",12);
            }

        if (terosDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String terosText1 = F("Teros_mV");
              Serial.print(terosText1);
              spacing2(terosText1,12);
              String terosText2 = F("Teros_VWC");
              Serial.print(terosText2);
              spacing2(terosText2,12);
            }

         if (strainDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String terosText1 = F("Strain");
              Serial.print(terosText1);
              spacing2(terosText1,12);

            }    
         if (pHDisplay == 1){
              Serial.print(F("*"));
              spacing2("*",12);
              String pHText1 = F("pH1");
              Serial.print(pHText1);
              spacing2(pHText1,12);
              String pHText2 = F("pH1_T");
              Serial.print(pHText2);
              spacing2(pHText2,12);
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
        

    

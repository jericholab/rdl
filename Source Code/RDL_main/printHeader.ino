//-------------------------------------------------------------------
// FONCTION: printHeader
// PURPOSE: Display the title of each active column
// INPUT: none
// OUTPUT: none

void printHeader() {

  Serial.println();

  if (timeDisplay == 1) {
    String dateText = F("Date");
    Serial.print(dateText);
    spacing2(dateText, 12);
    String timeText = F("Std_Time");
    Serial.print(timeText);
    spacing2(timeText, 12);
  }

  if (idDisplay == 1) {
    Serial.print(F("#"));
    spacing2(F("#"), 12);
  }

  if (tDisplay == 1) {
    for (int i = 1; i < (numberC + 1); i++) {
      if (i < 10) {
        Serial.print("T0");      // T08, T09, T10, etc.
      }
      Serial.print(i);
      spacing2("Tii", 12);
    }
  }

  if (ohmDisplay == 1) {
    Serial.print(F("*"));
    spacing2("*", 12);
    for (int i = 1; i < (numberC + 1); i++)
    {
      Serial.print(F("R"));
      if (i < 10) {
        Serial.print('0');      // R08, R09, R10, etc.
      }
      Serial.print(i);
      spacing2("Rii", 11);         //the large resistance values to display require more spacing (14) than the rest (12)
    }
  }

  if (SHT40Display == 1) {

    for (int i = 0; i < qty_sht40; i++) {

      Serial.print(F("*"));
      spacing2("*", 12);
      String i2cText1 = F("i2c_C");
      Serial.print(i2cText1);
      spacing2(i2cText1, 12);
      String i2cText2 = F("i2c_RH");
      Serial.print(i2cText2);
      spacing2(i2cText2, 12);

    }
  }

  if (voltDisplay == 1) {
    Serial.print(F("*"));
    spacing2("*", 12);
    for (int i = 1; i < (numberV + 1); i++) {
      Serial.print(F("V"));
      if (i < 10) {
        Serial.print('0');      // T08, T09, T10, etc.
      }
      Serial.print(i);
      spacing2("Vii", 12);
    }
  }

  if (currentDisplay == 1) {
    for (int i = 0; i < qty_current; i++) {
      Serial.print(F("*"));
      spacing2("*", 12);

      String currentText1 = F("T_sensor");
      Serial.print(currentText1);
      spacing2(currentText1, 12);

      String currentText2 = F("T_comp");
      Serial.print(currentText2);
      spacing2(currentText2, 12);

      String currentText3 = F("ADC");
      Serial.print(currentText3);
      spacing2(currentText3, 12);

      String currentText4 = F("Volts");
      Serial.print(currentText4);
      spacing2(currentText4, 12);

      String currentText5 = F("Amps_C");
      Serial.print(currentText5);
      Serial.print(i2cChannels_current[i]);
      spacing2(currentText5, 12);
    }
  }

  if (terosDisplay == 1) {
    for (int i = 0; i < qty_teros; i++) {
      Serial.print(F("*"));
      spacing2("*", 12);
      String terosText1 = F("Teros_mV");
      Serial.print(terosText1);
      spacing2(terosText1, 12);
      String terosText2 = F("VWC_m3/m3");
      Serial.print(terosText2);
      spacing2(terosText2, 12);
      String terosText3 = F("Pascal");
      Serial.print(terosText3);
      spacing2(terosText3, 12);
    }
  }

  if (strainDisplay == 1) {
    for (int i = 0; i < qty_strain; i++) {
      Serial.print(F("*"));
      spacing2("*", 12);
      String terosText1 = F("Strain_ADC");
      Serial.print(terosText1);
      spacing2(terosText1, 12);
      String terosText2 = F("[N]");
      Serial.print(terosText2);
      spacing2(terosText2, 12);
    }
  }

  if (phDisplay == 1) {
    for (int i = 0; i < qty_ph; i++) {
      Serial.print(F("*"));
      spacing2("*", 12);
      String pHText1 = F("pH");
      Serial.print(pHText1);
      spacing2(pHText1, 12);
    }
  }

  if (ControlSignal == 1) {
    Serial.print(F("*"));
    spacing2("*", 12);
    String controlText = F("Control");
    Serial.print(controlText);
    spacing2(controlText, 12);
  }

  Serial.println();
  Serial.println();
}

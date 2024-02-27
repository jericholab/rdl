//-------------------------------------------------------------------
// FONCTION NAME: i2cScan
// PURPOSE: Scan all I2C ports to detect all the I2C devices (permanently connected to the i2c bus or multiplexed).
// INPUT: none
// OUTPUT: none

// DEFAULT ADDRESSES OF RDL SYSTEM COMPONENTS
// 0x20, 0x21 : PCF8574 on the RDL
// 0x22, 0x23 : PCF8574 on the default SHIELD
// 0x24, 0x25 : PCF8574 on a second SHIELD (double stack)
// 0x44 : SHT40 (Air humidity and temperature)
// 0x48 : ADS1115
// 0x68 : DS3231 (Real Time Clock)
// 0x2A : NAU7802 (Strain/ 24-bit ADC device)
// 0x70 : TCA9548 (I2C Multiplexer)


void i2cScan(){

    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<8; t++) {
      pcf3.digitalWrite(t, LOW);  // turn LED on by sinking current to ground
      pcf4.digitalWrite(t, HIGH);  // turn LED on by sinking current to ground
      delay(100);
      
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR) continue;

        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
      }
      pcf3.digitalWrite(t, HIGH); // turn LED off by turning off sinking transistor
      pcf4.digitalWrite(t, LOW); // turn LED off by turning off sinking transistor
    }
      
       Serial.println("\ndone");
}
  
      void tcaselect(uint8_t i) {
      if (i > 7) return;
     
      Wire.beginTransmission(TCAADDR);
      Wire.setClock(clockSpeed);
      Wire.write(1 << i);
      Wire.endTransmission();  
    }

      void tca_init() {              //Attempt to create an initialization function which disconnects all the channels ////////////////  
        Wire.beginTransmission(TCAADDR);
        Wire.setClock(clockSpeed);
        Wire.write(0);    //binary zero is 00000000.
        Wire.endTransmission();  
    }

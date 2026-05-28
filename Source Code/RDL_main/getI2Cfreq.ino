//-------------------------------------------------------------------
// FONCTION NAME: getI2Cfreq
// PURPOSE: Display at startup the clock speed at which the I2C bus is running
// INPUT: none
// OUTPUT: none
uint32_t getI2Cfreq() {
#if defined (ARDUINO_AVR_UNO)
  // Read the prescaler bits from TWSR
  uint8_t prescalerBits = (TWSR & 0x03);  // TWPS1:0
  uint8_t twbrValue     = TWBR;
  // Compute the prescaler from the bits:
  // 00 -> prescaler = 1, 01 -> 4, 10 -> 16, 11 -> 64
  uint8_t prescaler = 1 << (2 * prescalerBits);

  // Apply the formula
  // F_CPU / (16 + 2 * TWBR * prescaler)
  uint32_t freq = F_CPU / (16 + 2 * (uint32_t)twbrValue * prescaler);

  return freq;

# elif defined(__AVR_ATmega4809__)
  uint8_t mbaudValue = TWI0.MBAUD;
  // link for code regarding this equation
  // https://onlinedocs.microchip.com/oxy/GUID-4E9DA219-611B-4772-B5D3-9ED908198864-en-US-16/GUID-18674A55-D327-41FE-9D35-FAB50EAD9B84.html?hl=25.3.2.2.1%2Cclock%2Cgeneration
  uint32_t freq = F_CPU / (10 + (2UL * (uint32_t)mbaudValue));
  return freq;
# else
  return 0;
#endif
}


//-------------------------------------------------------------------
// FONCTION NAME: getI2Cfreq
// PURPOSE: Display at startup the clock speed at which the I2C bus is running
// INPUT: none
// OUTPUT: none


uint32_t getI2Cfreq() {
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
}

**Resistance Data Logger (RDL) Revision E4 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
Document License: CC-BY-SA.  


**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5-12V) supply, but other components of your system might require an electrician. Do NOT install in areas prone to thunder as the system has no protection against thunder. It is recommended to NOT open the main enclosure during bad weather (rain, snow, dust) to minimize the risk of component damage and safety issues.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.

# Table of Contents

1. [GENERAL](#general)
2. [NANO](#nano)
3. [REAL TIME CLOCK (RTC)](#real-time-clock-rtc)
4. [THERMISTOR/RESISTIVE CHANNELS](#thermistorresistive-channels)
5. [I2C COMMUNICATION](#i2c-communication)
6. [ANALOG MEASUREMENT SUBCIRCUIT](#analog-measurement-subcircuit)
7. [CONTROL SIGNAL](#control-signal)
8. [OTHER](#other)


## GENERAL

- This document refers to the Resistance Data Logger (RDL) system associated with the Jericho RDL PCB revision E4. 
- The RDL hardware is released under the MIT open-source license.
- The current board revision only works with the corresponding source code revision.
- Allowable wire gauges are written on the silkscreen (AWG 20-26). This is the ideal size to avoid wires slipping out. The order of the terminals is also printed (i.e. VCC, GND, SIG, VCC, GND, SIG, etc.)
- Starting with revision E2, the objective of maintaining at least 50% of the product cost (material and labor) has been abandoned. This was a requirement for the ‘Made in Canada’ label, which appeared contrary to the goal of maximizing affordability and access. Therefore, outsourcing is maximized, including SMD and through-hole components.
- Long wires (>10m) between the RDL and its sensors will cause significant voltage loss. This means that some devices will require a voltage regulator at the other end to make sure that the chip is supplied with the proper voltage.
- There are holes around the board to help attach the wires and reduce mechanical stress on the wires.

## NANO

- The Nano refers to the Arduino Nano clones that are sold throughout the world by third party manufacturers. ELEGOO is one such manufacturer, which has the benefits of containing the new bootloader (see Arduino IDE). The "old bootloader" tends to provoke errors when uploading the RDL code.
- The Nano clone is inserted in the dedicated female headers and is removable by hand for purposes of replacement or maintenance. This modularity reduces cost and increases product resilience. It allows the user to bring the Nano indoors to upload a new code. It also opens the door to major upgrades, such as the Arduino Nano ESP32, which can run Python and AI Edge but has the same pinout than the Nano. Only the 3.3V supply would be challenging.
- Of course, since the Nano ELEGOO is removable, it can be substituted with any other Nano manufacturer.
- A second row of female header is present to allow temporary connections to all pins via hookup wires. 
- Decoupling capacitors are added to all devices to reduce voltage variations on the power supply. This includes the Nano and the following chips: DS3231, CD74HC4051, PCF8574T, LTC4311, ADS1115. All decoupling capacitors are done with a 0.1uF and 10uF caps. Note that the Nano has internal decoupling capacitors, creating a redundancy.
- It is worth noting that the Nano does not operate at a regulated voltage if connected to a USB port. The USB port itself has some degree of voltage regulation but as the current consumed by the RDL varies, the voltage loss (Ohm law) on the USB cable will vary, resulting in a voltage that varies typically between 4.2 and 4.95V.

## REAL TIME CLOCK (RTC)

- The RTC chip is the DS3231MZ+. The internal oscillator of the clock chip is temperature compensated internally. Operation in cold temperatures should have minimal impact on long-term timestamp accuracy.
- The chip has backup power via the 3V CR1220 battery holder. At extremely low temperature, the voltage of an ordinary CR1220 battery is reduced and can become insufficient for the RTC operation (not tested). The phenomenon is reduced by locating the RDL inside the main enclosure, which benefits from the Pi waste heat.
- The DS3231 communicates via I2C protocol to the Nano. In theory, it only communicates at the standard bus rate of 100Khz. However, tests have shown that it performs well even at 31. Being able to operate all I2C devices on the same bus speed simplifies the product (there is a single I2C bus on the system).
- The positive side of the CR1220 battery is only connected to the RTC clock, and so the I2C bus will not be activated and drawing power from the battery (the RTC chip is a slave I2C device).

## THERMISTOR/RESISTIVE CHANNELS

- The resistive channels are multiplexed on both the high and low sides of the voltage divider. The multiplexing is done via two multiplexers of the CD74HC4051 series. This avoids having a lot of EM noise on the power supply lines (power and ground) that would occur when using 30m lead wires. The CD74 multiplexers are controlled simultaneously via 3 analog pins. This is possible on the RDL and not on the I2C shield because we have easy access to the Nano Shield is only connected to the RDL via the CAT cable (VCC, GND, SDA, SCL).
- The on-resistance of the multiplexers (2) is taken into account in the source code, despite its low value (2 x 70 ohms).
- The two multiplexers are synchronized. They are controlled with the same Nano digital pin. Their channels are controlled with the same digital pins (D2, D3, D4). This simplifies the board wiring, as well as the software. It also leaves more analog pins for other usage.
- The resistor for the voltage divider circuit is a high-accuracy (+/- 0.1%) surface-mounted device (SMD).
- The voltage divider can be measured by two methods. 
  1) The signal can be measured by the Nano analog pin A0. This method has a limited accuracy due to the 10-bit ADC of the Nano and now serves as a backup. 
  2) Second, the voltage divider signal can be measured by the ADS1115 chip. This 16-bit chip has four single-channels. For more information, read the ADS1115 section.
- Neither method (A0, ADS) uses a pulldown resistor. Although this would help display a clean, stable value ("0.0000") when the channel is empty, even a weak pulldown would bias the readings significantly when the thermistor takes a high resistance (near 1 MΩ) value at low temperature.

## I2C COMMUNICATION

- Apart from the resistive and analog sensors, the main method to integrate and communicate with sensors is via the I2C protocol.
- By default, the Nano operates at standard I2C bus clock speed of 100,000 Hz. This speed however is incompatible with very long cables (>10m) due to the high capacitance of cables, which deform the I2C square wave beyond recognition. It is therefore best to reduce the frequency.
- By default, the RDL code operates the I2C bus line at 490Hz. This is achieved by modifying the core parameters of the Wire library before compiling the Arduino code. More precisely, the TWBR and prescalers values of the twi.c file are modified. A ready-to-use modified Wire library is available in the Jericho source code.
- There are two ways to communicate via I2C protocol on this board: the RJ45 connector and the I2C screw terminals. The RJ45 is useful for permanent uses and long wire connections, while the screw terminal is useful for quick tests. The screw terminal can also serve as a temporary location for pull-up resistors on the SDA and/or SCL line.
- The LTC4311 chip is an I2C booster. Together with the pullup resistors and the slow I2C bus clock, it allows communications over long cables. The LTC4311 is located on the RDL board instead of the I2C shield for two reasons: 1) allow long wires even without the use of an I2C shield; 2) avoid having multiple LTC chip on the same I2C bus (conflict) when more than one I2C shield is added.
- The board has holes for the standoffs that allows the I2C shield to be installed beneath the RDL. The installation is best done with the shield beneath the RDL in order to leave an easy access to the Nano pins and buttons. Installation cannot be done above the RDL unless longer standoffs are used than those provide if the the Nano ICSP pins are to be cleared.
- Up to three I2C shields can be stacked, providing 25 I2C connections (3 x 8 + 1 on the RDL). Three is the theoretical limit since the TCA9548 chips have eight I2C addresses possible, and a three-shield stack will use seven of those. The daisy chaining of sensors can be applied to increase that number. For more information, refer to the I2C shield Design Overview document.
- Any subtype of CAT cable will work: CAT5, CAT5e, CAT6, CAT7. Other than the variation on cost, size and weight, these cables have different ability to protect the signal from EM noise. They might also have different capacitance per unit length, which affect the maximum usable cable length.
- The 8-pins wiring of the RJ45 does not follow a standard. The wiring order is:
  - Pin 1 & 2: VCC
  - Pin 3 & 4: GND
  - Pin 5 & 6: SDA
  - Pin 7 & 8: SCL
- This pin order, combined with the internal standard architecture of the CAT cable (either EIA568A or EIA568B) creates a partial EM shielding, since the GND wires are twisted with the VCC and SDA wires. In future versions, improvements will be tested on the wiring order.

## ANALOG MEASUREMENT SUBCIRCUIT

- The RDL has eight (8) multiplexed channels for analog signal (0-5V) measurements. Each channel is made of three (3) pins: Power (VCC), Ground (GND) and Signal (SIG). The power and ground pins are multiplexed via a PCF8574 chip and MOSFETS. The signal pins are multiplexed via a CD74HC4051 chip.
- Using the same logic than the resistive measurement, the analog measurements can also be done via two methods: the analog pin A1 on the Nano (10-bit ADC), and the channel 1 pin on ADS1115 (16-bit ADC).
- The ADS1115 two remaining channels (i.e. 3 & 4) are connected to the 5V and 3.3V pins of the Nano. It is useful to measure the 3.3V pin, only in the case of measuring the voltage divider with the ADS1115. This is because the ADS1115 is not referenced to the same voltage than the Nano. Therefore, the supply voltage of the voltage divider does not cancel itself in the equation as it does when the measurement is done by the Nano ADC, referenced to the same 3.3V. Therefore, the 3.3V must be measured accurately. The 5V measurement is useful to determine the conditions under which the ADS1115 operates, since it cannot measure voltages higher than its own supply voltage.
- According to manufacturer speciications, the ADS1115 has a minimum I2C clock speed requirement of 10 kHz. In theory, this recommendation puts a limit to slowing the clock, although it could be tested lower.
- The same concept of double multiplexing is applied to analog voltage measurements. However, the operation is different for the VCC and GND lines due to the use of transistors. We are forced to use transistors because the CD74 chip is very limited in the current it can transmit (~10-50mA). The Nano can supply as much as 500 mA (USB limit). To be able to supply this amount, MOSFET transistors are used (p-channel (AO3401A) and n-channel (AO3406)). Since the subcircuit is substantially the same than the one for the I2C shield, refer to the I2C shield Design Overview for more information.
- The decoupling capacitors circuit of the ADS1115 is different than those of other chips: it also includes ferrite beads that help reduce the increased noise caused by the ADS1115. This prevents contamination of the entire power buses. A ferrite bead act as an inductor who let pass low-frequency but blocks high frequency signals (i.e. noise).
- The PCF8574 chip is an GPIO (General Purpose Input/Output) expander. It can be thought of as an open drain configuration and has a modifiable I2C address. Since you cannot have two devices with the same I2C address on a given I2C bus, each of the two PCF on the RDL has a different address. This is done via solder jumpers. The PCB layout uses two different addresses to avoid any soldering from the user. There are also 10k resistor to limit the in-rush current to the address pins.

## CONTROL SIGNAL

- For non-critical operations (see the User Guide and General Design disclaimers), the RDL can provide a 0-5V control signal.
- This control signal is most easily produced by the screw terminals via the "D9" identified channel. This channel is connected to pin D9 of the Nano. This pin is ideal due to its ability to have Pulse-Width Modulation (PWM) signals. Only certain pins on the Nano can provide such PWM signals: D3, D5, D6, D9, D10, D11.
- Note that PWM signals perform poorly on long wires, whose high capacitance blurs the PWM exact signal shape. The D9 pin can also provide a binary output (low/high) but it cannot provide a true analog output, since the Nano has no DAC (Digital-to-Analog Converter). For more information on the various types of signal output, refer to the official Arduino Nano documentation.

## OTHER

- The RDL board has no power LED. Only the Nano LED indicates proper power and operation.
- The channels 1 and 8 of the analog voltage measurements both have a power LED to help the user diagnose the proper operation of their code. If the LED of channel 1 does not power on, the sensor connected to channel 1 has no power. The lighting of the LED however does not confirm that the RDL is properly reading the sensor signal though.

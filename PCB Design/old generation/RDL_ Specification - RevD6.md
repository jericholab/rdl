# RESISTANCE DATA LOGGER (RDL) REV D6 SPECIFICATIONS


Table of Contents

[RESISTANCE DATA LOGGER (RDL) REV D6 SPECIFICATIONS 1](#_Toc113303116)

[OVERALL SYSTEM PROPERTIES 1](#_Toc113303117)

[Performance 2](#_Toc113303118)

[A) Temperature measurements <sup>1</sup> 2](#_Toc113303119)

[B) Resistance measurements 2](#_Toc113303120)

[RDL CONTROLLER 3](#_Toc113303121)

[TH-1 PROBE 4](#_Toc113303122)

[TH-2 PROBE 5](#_Toc113303123)

[ANNEX 1: RDL system performance with uncalibrated thermistors for the 0 to 100°C range, based on Octave script 6](#_Toc113303124)

[ANNEX 2: RDL system performance with uncalibrated thermistors for the full range, based on Octave script 7](#_Toc113303125)

## OVERALL SYSTEM PROPERTIES

- Jericho model number: RDL-RevD6
- Temperature measurements: Thermistor only
- Number of channels with temperature measurements: 16
- Number of channels with resistive measurements: 16
- Number of channels with I2C protocol ability: 2
- Number of control signal channels: 1
- Outdoor use: Yes (Weatherproof only)
- USB connection: Male Type B
- USB cable length: 0.9 m
- Timestamp: Yes
- Output format: ASCII (serial communication only)
- Storage: Varies with computer/smartphone. Typical: 1,000,000 temperatures = 28 MB text file.
- Maximum measurement interval: 96 400 000 ms (24 hr)
- Default baud rate: 57 600 bits per sec
- Calibration type: end-to-end 3-point characterization
- ice bath (0°C / 32°F)
- warm bath (typically 37°C/99°F)
- steam point (typically 100°C/212°F)
- For more information about the calibration process, refer to the Jericho calibration procedures.

### Performance

#### A) Temperature measurements <sup>1</sup>

##### 1) Measurement range

- Minimum value: -83°C
- Maximum value: 334°C

##### 2) Measurement resolution

- Maximum resolution in the 0-100°C range: 0.09°C
- Minimum resolution in the 0-100°C range: 0.57°C
- Resolution at 0°C: 0.12°C
- Resolution at 100°C: 0.57°C

##### 3) Overall system uncertainty with uncalibrated thermistors TH-1 or TH-2 <sup>2</sup>

- Overall measurement accuracy in the 0-100°C range: < (± 0.7°C)
- Overall measurement accuracy at 0°C : ± 0.3°C
- Overall measurement accuracy at 100°C : ± 0.7°C

##### 4) Overall system uncertainty with calibrated thermistors TH-1 or TH-2

- \[To be determined\]

Note: For more details about temperature measurements performance, see graphs of Annex 1 and 2.

<sup>1</sup> Specifications only valid for 10 kohm 1% accurate NTC thermistor

<sup>2</sup> Uncertainty specifications do not take into account electromagnetic noise nor the self-heating effect.

#### B) Resistance measurements

##### 1) Measurement range

- Resistance min = 9.8 Ω
- Resistance max = 10 22 0000 Ω

##### 2) Measurement resolution

- Resolution at 0°C: 12 Ω
- Resolution at 100°C: 182 Ω
- Minimum resolution: 9.8 Ω
- Maximum resolution: 5 115 200 Ω

##### 3) Overall system uncertainty

- Minimum uncertainty: \[To be determined\]
- Maximum uncertainty: \[To be determined\]

For more details about the resistance measurements performance, see graphs of Annex 1 and 2.


<figure>
<p align="center">
<img src="../PCB Design/images/1.png" style="width:70%">
</p>


## RDL CONTROLLER

- Outside dimensions (controller): 162 x 94 x 19 mm
- Weight (assembled controller only): ~150g
- Microcontroller: ATMega328P-U-KR (with old bootloader)
- Multiplexer: CD74HC4067 16-channel CMOS
- Real-Time-Clock: DS1307ZN+T&R (No temperature compensation)
- Voltage input: 5V DC (USB)
- Operating temperature (controller): -40°C to 85°C (-40°F to 185°F)
- Maximum operating relative humidity for the controller: 95%
- Analog-to-digital converter (ADC) accuracy: 10-bit
- Tension divider circuit resistor value: 10 kΩ +/- 0.1%
- Microcontroller total memory available (Flash): 30.7 kB
- SRAM memory available: 2 kB
- EEPROM memory available: 1 kB
- Typical maximum acquisition rate for various conditions:

## TH-1 PROBE

- NTC thermistor 10 kΩ, with black epoxy coating
- Probe dimensions: approximately 3.5 x 14 mm
- Probe operating temperature range: -40°C to 125°C (-40°F to 257°F)
- Probe thermal time constant: \[To be determined\]
- Probe pH tolerance: \[To be determined\]
- Wire length: 1m
- Wire temperature range: -30°C to 110°C (-22°F to 230°F)
- Wire properties: 26 AWG, 300V, 105°C. Copper multiple conductors.
- Typical power consumption per probe (continuous measurement, 3.3V circuit): 0.1 W
- Typical power consumption per probe (slow speed (1 S/s), 3.3V circuit): 0.01 W
- Origin: Made in China

## TH-2 PROBE

- NTC thermistor 10kΩ, stainless steel
- Probe dimensions: ~ 0.026 x 0.005 m diameter
- Probe operating temperature range: -40°C to 125°C (-40°F to 257°F)
- Probe thermal time constant: \[To be determined\]
- Probe pH tolerance: \[To be determined\]
- Wire length: 1m
- Wire temperature range: -30°C to 110°C (-22°F to 230°F)
- Wire properties: 26 AWG, 300V, 105°C. Copper multiple conductors.
- Typical power consumption per probe (continuous measurement, 3.3V circuit): 0.1 W
- Typical power consumption per probe (slow speed (1 S/s), 3.3V circuit): 0.01 W
- Origin: Made in China

# ANNEX 1: RDL system performance with uncalibrated thermistors for the 0 to 100°C range, based on Octave script

# ANNEX 2: RDL system performance with uncalibrated thermistors for the full range, based on Octave script

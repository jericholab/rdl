**Strain Sensor Revision A1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  
 

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version, as well as the latest specification sheets of the associated electronic components.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5V) supply, but other components of your system might require an electrician. The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.
 
**Table of Contents**

1. [GENERAL](#general)
2. [APPLICABLE TO THE RDL SUITE](#applicable-to-the-rdl-suite)
3. [NAU7802 CHIP](#nau7802-chip)
   - [NAU7802 CHIP - GENERALITIES](#nau7802-chip---generalities)
   - [NAU7802 CHIP – I2C COMMUNICATION](#nau7802-chip---i2c-communication)
   - [NAU7802 CHIP - MEASUREMENTS](#nau7802-chip---measurements)
4. [STRAIN GAUGE LOAD CELL](#strain-gauge-load-cell)
5. [SOFTWARE](#software)
6. [SENSOR CALIBRATION](#sensor-calibration)
7. [RJ45 CONNECTORS](#rj45-connectors)
8. [OTHER](#other)

## NAU7802 CHIP – I2C COMMUNICATION

## GENERAL

- This document refers to the strain sensor system associated with the Jericho Strain Sensor PCB revision A1.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- The original design of the voltage regulation circuit was done by Sparkfun Industries under the CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- There are holes around the board to help attach the wires and reduce mechanical stress on the wires.
- A copper plane (ground) is poured on the bottom surface of the PCB to reduce EM noise. There is no copper plane on the top surface.

## APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on GitHub. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.
- Unless stated otherwise, all libraries required to run the RDL suite are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

## NAU7802 CHIP

### NAU7802 CHIP - GENERALITIES

- The NAU7802 chip by Nuvoton is a high-accuracy voltage measurement device. It includes a 24-bit ADC and has I2C communication capabilities.
- The NAU7802 has two functions: it provides a regulated excitation voltage and it measures the response signal.
- Very high accuracy ADC is required because the strain gauge, by their nature, creates very weak signals in the order of millivolts.
- The NAU7802 chip makes a differential voltage measurement.
- This chip has two differential measurement channels, but they don’t have the same input capacitance (14pF and 5pF). This confers the two channels different measurement behavior. To avoid any accidental confusion, only one channel is used (i.e. 14pF, channel #1). In the future, it would be possible to evaluate if this level of input capacitance difference is negligible.
- The VDDA and GND are respectively the excitation voltage and ground lines for the activation of the Wheatstone bridge. The A- and A+ pins are the actual measurements of the bridge.
- The NAU7802 chip is equipped with decoupling capacitors at the power supply (0.1uF and 10uF and 22uF). While other RDL boards use only 0.1uF and 10uF, the NAU7802 uses a supplementary 22uF for increased stability.
- In theory, the NAU7802 does not require a precise supply voltage (2.7-5.5V) since it has an internal voltage regulator. However, the input decoupling capacitors, by stabilizing the input voltage, ease the work of the voltage regulator and improve performance by removing noise and other voltage fluctuations. A future version could include a voltage regulation circuit, similar to the current sensor revA1, since multiple users of the similar Sparkfun NAU7802 board report high sensitivity of readings to voltage supply.
- Note that the NAU7802 can accept various voltage supply values but the reading voltage is limited by the supply voltage (“AVDD should not exceed DVDD supply voltage”).
- When used with the RDL revision E2 and after, the PCB is only supplied in power when a measurement is required by the Nano. This means that over the course of its life, the sensor will be powered up thousands of times. The NAU7802 chip does not require a delay between power up and reading: it will deal with the necessary delays autonomously.

### NAU7802 CHIP - I2C COMMUNICATION

- The NAU7802 chip has a single permanent I2C address: 0x2A. Therefore, one cannot daisy-chain two strain boards, it can only daisy chain a different sensor. Using two strain sensors on a given system requires two separate channels.
- Like all sensors from the RDL suite, the NAU7802 board has been designed for long wire operation (30m). However, the NAU7802 chip appears to have a weaker native signal and achieves shorter cable lengths. When combined with I2C shield revA1 and RDL RevE2, with a CAT5 cable and low EM noise environment, the maximum cable length for continuous communication is currently 30 m.
- Apart from Sparkfun, there is another popular board design based on the NAU7802, by Adafruit. When comparing the two schematics, the stronger pullup resistors on the SDA/SCL lines (2.2kohm) seem to be the reason why longer cables are possible with Sparkfun than Adafruit (10kohm). On the Jericho design, as well as Sparkfun, these pullup resistors are in series with solder junctions (normally on) that can be cut with a knife if the user wants to disconnect them.
- NAU7802 is designed to operate at 100kHz or 400kHz (high-speed I2C bus). However, it has shown no difficulties at operating at low bus frequency, down to 31kHz (Jericho default on hardware-based I2C protocol).
- The presence of two RJ45 connectors on the board allows to daisy chain I2C devices. For example, the cabling cost can be reduced by using a single long cable to reach the strain sensor PCB and, from there, only add a short CAT cable to connect to the SHT40 PCB. This is possible because the two PCBs do not have the I2C address.

### NAU7802 CHIP - MEASUREMENTS

- The measurements can be done at various speed: 10, 20, 40, 80, 320 SPS (Samples Per Second). To reduce sampling time, RDL runs at 320 SPS by default.
- DVDD is the digital power supply input (2.7 - 5.5V). It is external (e.g. RDL/Nano).
- VDDA is the analog power supply input (2.7 - 5.5V) It comes from NAU7802. The default value is 3.3V.
- The PGA (Programmable Gain Amplifier) can be configured to vary the gain applicable (1, 2, 4, 8, 16, 32, 64, 128). It also affects the voltage range applicable. The default value is 128.This gain could be reduced if the load cell output measurement was saturated by the NAU7802 chip.
- The Wheatstone bridge operates at the default 3.3V. It is within the allowable excitation voltage range of the TAL220 (3-10V) and it maximize the measurement range by minimizing the sensitivity (V/N).
- The measurement output by the NAU7802 is the average of a large sample. This is configured within the Arduino code. The ADC voltage range is also modified within the code. For more information, read the RDL source code and the RDL code documentation.
- The ADC output follow this equation: “ADC Output Value = Gain_Calibration\* (ADC measurement - Offset_Calibration)”.

## STRAIN GAUGE LOAD CELL

- A strain sensor board is not of much use without a strain gauge load cell. This section details the relationship of the sensor with the required load cell.
- The J3 screw terminal allows the PCB to connect with the strain gauge load cell. The load cell should be a full Wheatstone bridge. The wire colors are an indication only and might differ on your specific load cell. In case of contradiction, the wire function (VDDA, GND, A-, A+) has priority over color.
- A Wheatstone bridge is an electrical circuit used to precisely measure an unknown electrical resistance by balancing two legs of a bridge circuit, one leg of which includes the unknown component. It is commonly used in sensor applications to convert changes in physical phenomena (like temperature, strain, or pressure) into changes in resistance, which can then be measured with high accuracy.
- As a general rule of thumb, the wire length between the NAU7802 and the strain gauge must be minimized and be kept under 1 m. This helps keep the signal-to-noise ratio at a sufficient level.
- For general use, we recommend the following load cell: TAL220 (micro parallel beam) by HTC-sensor (China). For more information, consult the TAL220 specification sheet. You can buy the TAL220 on Sparkfun.com or on the manufacturer website (htc-sensor.com). The manufacturer has more production options (e.g. load capacity from 1kg to 50kg, outdoor jacket).
- The installation procedure for strain gauges goes beyond the scope of this document but is a crucial part of the process.
- Note: Since strain gauge load cell wires are usually quite small, this PCB design uses smaller crew terminals: 3.5mm pitch instead of the typical 5mm pitch. Too small gauge causes the wire to slip out of the terminal.
- By their nature, strain gauges do not tolerate well long-term static loads (> 1 day). It causes measurement drift for multiple reasons (gauge deformation, adhesive breakdown). For precise long-term measurements, periodic recalibration and the use of multiple gauges for redundancy may also be necessary.
- For outdoor operation, Jericho recommends weatherproofed strain gauge load cells (with conformal coating or other) and weather resistant wires. These options are available on the TAL220 if you order directly from the manufacturer.

## SOFTWARE

- The native code of the RDL (revE2 and beyond) can operate the strain sensor. The number of allowable strain sensors is only limited by the number of I2C channels.

## SENSOR CALIBRATION

- When measuring strain with a NAU7802, there are three types of calibration: internal, external and at the system level. Internal (or external) calibration makes sure that the strain gauge is accurately measured by the NAU7802 ADC. The system calibration ensures that the strain gauge resistance is accurately converted into a force or strain.
- According to the NAU7802 chip manufacturer, the calibration (either internal or external) is recommended after each of the following events: initial power-up, power-up after long-duration register mediated power-down conditions, PGA gain changes, supply changes, significant temperature changes (can be measured using built-in thermal sensing feature), Sample rate changes, Channel select changes. This list excludes the frequent powerups that occur due to a potential multiplexer (i.e. RDL).
- For the RDL, internal calibration is done automatically by a function from the NAU7802 library (calibrateAFE()). It is called at power up and at a regular interval. The algorithm is still under development.
- External calibration has to be done for each specific load cell. If the load cell is damaged and replaced, calibration must be done. External calibration can be done via the source code only. It currently cannot be done via a live command.
- Since the strain gauges are highly linear devices, only a two-point calibration is required.

## RJ45 CONNECTORS

- There are two RJ45 connectors on this board, which allow I2C communication. They are not compatible with Ethernet protocol. They are interchangeable.
- Each connector follows the following wiring connection:
  - Pin 1 & 2: VCC
  - Pin 3 & 4: GND
  - Pin 5 & 6: SDA
  - Pin 7 & 8: SCL
- This wiring order, combined with the internal architecture of the CAT cable (standard) creates a partial shielding, since the GND wires are twisted with the VCC and SDA wires. In future versions, improvements could be made on wiring order.
- The main modifications with the Sparkfun design are the additions of RJ45 connectors.
- The NAU7802 chip itself has some sensitivity to temperature. There is an embedded temperature compensation mechanism inside the NAU7802 chip. However, this compensation is done at calibration time only (calculateZeroOffset()). The temperature data is not exposed to the I2C interface. This means that if the chip temperature changes, chip calibration must be redone.
- Strain gauge load cells are very sensitive to temperature variation. There are multiple components to this relationship (e.g. load cell thermal expansion, strain gauge film expansion). Load cell temperature compensation is specific to each installation setup and must be addressed separately than the chip temperature compensation.

## OTHER

- A LED is added to the PCB to indicate that the sensor powered.
- The board has 3.5mm diameter holes in each corner for installation purposes.
- There is a supplementary 6-pin male header (2.54mm spacing) for quick connections and testing: GND, 5V, INT, SDA, SCL, VDDA.
- There are two STEMMA (aka QWIIC) connectors on this board. They contain the same pins than the RJ45 connectors. They are a redundant form of connecting the boards. There are two units for the same daisy chain reason than RJ45.
- Warning: Contrarily to the original Sparkfun design, this design is not compatible with a standard Qwiic bus due to the 5V operation of the I2C bus instead of 3.3V.

## TEMPORARY COMMENTS

1) UPDATE: "Thin film heaters" have supposedly replaced PTC resistors

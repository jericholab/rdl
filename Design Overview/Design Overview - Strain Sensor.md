**NAU7802 Board For Strain and Current Revision B1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
License: CC-BY-SA.  
 

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version, as well as the latest specification sheets of the associated electronic components.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5V) supply, but other components of your system might require an electrician. The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.
 

*** OH WAIT **** DOES THE NAU7802 OPERATE IN SIMILAR WAY? i THINK NOT BECAUSE STRAIN IS DIFFERENTIAL AND CURRENT IS UNIPOLAR.

## Table of Contents  (UPDATE **********)
- [INTRODUCTION](#introduction)
- [NAU7802 CHIP](#nau7802-chip)
  - [NAU7802 CHIP - GENERALITIES](#nau7802-chip---generalities)
  - [NAU7802 CHIP - I2C COMMUNICATION](#nau7802-chip---i2c-communication)
  - [NAU7802 CHIP - MEASUREMENTS](#nau7802-chip---measurements)
- [STRAIN GAUGE LOAD CELL](#strain-gauge-load-cell)
- [SOFTWARE](#software)
- [SENSOR CALIBRATION](#sensor-calibration)
  - [INTERNAL CALIBRATION](#internal-calibration)
  - [EXTERNAL CALIBRATION](#external-calibration)
- [RJ45 CONNECTORS](#rj45-connectors)
- [OTHER](#other)
- [CURRENT SENSOR (L01Z050S05) GENERALITIES AND INSTALLATION](#current-sensor-l01z050s05-generalities-and-installation)
  - [SENSOR OPERATION](#sensor-operation)
  - [ANALOG OPERATION MODE](#analog-operation-mode)
  - [DIGITAL OPERATION MODE](#digital-operation-mode)
- [VOLTAGE REGULATOR TPS630701](#voltage-regulator-tps630701)
- [REFERENCES](#references)

************ ADD SECTION ABOUT THE 3 ALGORITHMS (True RMS, Sine RMS (Work in dev), Average DC)


## INTRODUCTION

- The NAU7802 board is a dual sensor PCB. A single design allows both electrical AC/DC current measurements (Hall Effect) and strain/force measurements with a gauge cell. This reduces the number of active designs at Jericho.
- Note however that the TAMURA sensor is not installed on the PCB. You will notice on the strain sensor that the TAMURA space is present, but the sensor absent. Therefore, the same raw PCB is used for two separate Jericho products:
  - Jericho NAU7802 Strain Board;
  - Jericho NAU7802 Current Board;
- It is in theory possible to use the Current board to make strain measurements. However, this has not been tested and the magnetic field of the cable current could induce noise and/or bias on the strain measurements.
- The current measurements can be done via analog or digital mode, while the strain measurements can only be done via digital mode.
- For general information about PCB designs of Jericho sensors, please refer to the 'Design Overview - General information' document.  
- The original design of this board was provided by Sparkfun (CC-BY-SA).
- The license for the Jericho improvements of the hardware is also CC-BY-SA.


## NAU7802 CHIP (COMMON SECTION)

- This section describes the details of the Analog-to-Digital NAU7802 chip. The information is relevant to both current and strain measurements.

  ## NAU7802 CHIP - GENERALITIES  
- The NAU7802 chip by Nuvoton is a high-accuracy voltage measurement device. It includes a 24-bit ADC (Analog-to-Digital Converter) and has I2C communication.
- The NAU7802 has two main capabilities: it can provide a regulated voltage  and it measures the analog signals from sensors with two channels. The regulated voltage is typically used to excite a Wheatstone bridge (not used in this product).
- Very high accuracy ADC is required because the strain gauge, by their nature, creates very weak signals in the order of millivolts. The current sensor also needs the accuracy as it distributes a -50A/+50A input range on a 3V range output (1.0-4.0V).
- The NAU7802 chip makes a differential voltage measurement by default. It can also be configured for single-end measurement (i.e. signal-to-ground).
- The VDDA and GND are respectively the excitation voltage and ground lines for the activation of the Wheatstone bridge. The A- and A+ pins are the actual measurements of the bridge.
- The NAU7802 chip is equipped with decoupling capacitors at the power supply (0.1uF, 10uF and 22uF). While other Jericho boards use only 0.1uF and 10uF, the NAU7802 uses a supplementary 22uF for increased stability.
- In theory, the NAU7802 does not require a precise supply voltage (2.7-5.5V) since it has an internal voltage regulator. However, multiple users of the similar Sparkfun NAU7802 board reported (on forums) a high sensitivity of readings to voltage supply, hence, a voltage regulator circuit was added.
Similarly, the input decoupling capacitors, by stabilizing the input voltage, ease the work of the NAU7802 voltage regulator and improve performance by further reducing noise and other voltage fluctuations.
- Note that the NAU7802 can accept various voltage supply values but the reading voltage range will be limited by the supply voltage value (“AVDD should not exceed DVDD supply voltage”).
- When used with the RDL, the NAU7802 PCB is only supplied in power when a measurement is required by the RDL. This means that over the course of its life, the sensor will be powered up thousands of times. The NAU7802 chip does not require a delay between power up and reading; it deals with the necessary delays autonomously.

  ### NAU7802 CHIP - I2C COMMUNICATION

- Like all sensors from the RDL suite, the NAU7802 board has been designed for long wire operation (30m). However, the NAU7802 chip appears to have a weaker native signal and achieves shorter cable lengths for a given I2C bus frequency. When combined with I2C shield, RDL, a CAT5 cable and low EM noise environment, the maximum cable length for continuous communication is currently 30 m.
- Apart from Sparkfun, there is another popular board design based on the NAU7802, by Adafruit. When comparing the two schematics, the stronger pullup resistors on the SDA/SCL lines (2.2kohm) seem to be the reason why longer cables are possible with Sparkfun than Adafruit (10kohm). On the Jericho design, as well as Sparkfun, these pullup resistors are in series with solder junctions (normally ON) that can be cut with a knife if the user wants to disconnect them.
- NAU7802 is designed to operate at 100kHz or 400kHz (high-speed I2C bus). However, it has shown no difficulties at operating at low bus frequency, down to 31kHz (Jericho present default on hardware-based I2C protocol).
- The presence of two RJ45 connectors on the board allows to daisy chain I2C devices. For example, the cabling cost can be reduced by using a single long cable to reach the strain sensor PCB and, from there, only add a short CAT cable to connect to the SHT40 PCB. This is possible because the two PCBs do not have the I2C address.
- The NAU7802 chip has a single permanent I2C address: 0x2A. Therefore, one cannot daisy-chain two strain boards, it can only daisy chain a different sensor. Using two strain sensors on a given system requires two separate channels.

  ### NAU7802 CHIP - MEASUREMENTS

- Although the strain and current measurements both use the same chip, NAU7802, they use it differently.
  - STRAIN: Differential mode
  - CURRENT: Unipolar mode

******* IS THIS THE ONLY DIFFERENCE BETWEEN THE TWO? *********

- The measurements can be done at various speed: 10, 20, 40, 80, 320 SPS (Samples Per Second). To reduce sampling time, RDL runs at 320 SPS by default.
- DVDD is the digital power supply input (2.7 - 5.5V). It is externally provided by the on-board regulating circuit (5V).
- VDDA is the analog power supply input (2.7 - 5.5V), used for example to excite the Wheatstone bridge. The default manufacturer value is 3.3V, supplied by NAU7802 internal circuit. This default mode is overriden and instead the DVDD signal is used (5V). It is within the allowable excitation voltage range of the TAL220 (3-10V) and it maximize the measurement range by minimizing the sensitivity (V/N). Accordingly, the ADC voltage range is also modified within the code. For more information, read the RDL source code and the RDL code documentation.
- The PGA (Programmable Gain Amplifier) can be configured to vary the gain applicable (1, 2, 4, 8, 16, 32, 64, 128). It also affects the voltage range applicable. The default value is 128. This gain could be reduced if the load cell output measurement was saturated by the NAU7802 chip.
- The measurement output by the NAU7802 is the average of a large sample. This is configured within the Arduino code. 
- The ADC output follows this equation: “ADC Output Value = Gain_Calibration\* (ADC measurement - Offset_Calibration)”.

  ## STRAIN GAUGE LOAD CELL

- To operate, a strain sensor board requires a separate strain gauge load cell. This section details the relationship of the sensor with the required load cell.
- The J3 screw terminal allows the PCB to connect with the strain gauge load cell. The load cell should be a full Wheatstone bridge. The wire colors are an indication only and might differ on your specific load cell. In case of contradiction, the wire function (VDDA, GND, A-, A+) has priority over color.
- A Wheatstone bridge is an electrical circuit used to precisely measure an unknown electrical resistance by balancing two legs of a bridge circuit, one leg of which includes the unknown component. It is commonly used in sensor applications to convert changes in physical phenomena (like temperature, strain, or pressure) into changes in resistance, which can then be measured with high accuracy.
- As a general rule of thumb, the wire length between the NAU7802 and the strain gauge must be minimized and be kept under 1 m. This helps keep the signal-to-noise ratio at a sufficient level.
- For general use, we recommend the following load cell: TAL220 (micro parallel beam) by HTC-sensor (China). For more information, consult the TAL220 specification sheet. You can buy the TAL220 on Sparkfun.com or on the manufacturer website (htc-sensor.com). The manufacturer has more production options (e.g. load capacity from 1kg to 50kg, outdoor jacket). It has IP65 rating.
- The installation procedure for strain gauges goes beyond the scope of this document but is a crucial part of the process.
- Since strain gauge load cell wires are usually quite small, this PCB design uses smaller crew terminals: 3.5mm pitch instead of the typical 5mm pitch. The small gauge wire can slip out of the 5mm terminal.
- By their nature, strain gauges do not tolerate well long-term static loads (> 1 day). It causes measurement drift for multiple reasons (gauge deformation, adhesive breakdown). For precise long-term measurements, periodic recalibration and the use of multiple gauges for redundancy may also be necessary.

  ## SOFTWARE

- The standard RDL code can operate the strain sensor. The number of allowable strain sensors is only limited by the number of I2C channels.

  ## STRAIN SENSOR CALIBRATION

- When measuring strain with a NAU7802, there are two types of calibration: internal, external. The internal calibration makes sure that the strain gauge is accurately measured by the NAU7802 ADC. The external calibration ensures that the strain gauge resistance is accurately converted into a force or strain.

  ## INTERNAL CALIBRATION
- According to the NAU7802 manufacturer, the calibration (**either internal or external**???????) is recommended after each of the following events:
  1) initial power-up
  2) power-up after long-duration register mediated power-down conditions
  3) PGA gain value change
  4) power supply change
  5) significant temperature changes (can be measured using built-in thermal sensing feature)
  6) sample rate change 
  7) channel select change. 

  This list excludes the frequent powerups that occur due to a potential multiplexer (i.e. RDL).
- For the RDL, internal calibration is done automatically by a function from the NAU7802 library (calibrateAFE()). It is called at powerup and at a regular interval. The algorithm is still under development for the regular interval.

  ## EXTERNAL CALIBRATION
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




## CURRENT SENSOR (L01Z050S05)  
This section describes the current measurement section of the PCB.  

  ## GENERALITIES AND INSTALLATION  
- The core component of the board is the L01Z050S05 current sensor module manufactured by TAMURA. The L01Z module, based on the Hall effect, can measure both DC and AC (up to 100kHz) current up to 50A DC. The maximum frequency readable by the Jericho board however is much less, limited by the sampling speed of the processors. The LZ01 series offers module with a capacity up to 600A DC.
- The L01Z component was selected because it can be used with DC current, while as induction-based sensors are only compatible with AC current.
- The TAMURA component is readily available at global suppliers like DigiKey or Mouser. PCB manufacturers like JLCPCB can source from those suppliers for their SMD and through-hole assembly line.
- The TAMURA module was designed for indoor use and is not weatherproof. Therefore, the sensor MUST be installed in a weatherproof enclosure to avoid any damage or safety risk.
- The TAMURA is a through-hole component soldered on the PCB. Two soldered mechanical pins reduce the strain on the electronic pins.
- Jericho recommend the use of two adequate size cable glands (inlet, outlet) on the main cable to avoid any water entry in the enclosure.
- Jericho recommends the addition of silica gel packet inside the enclosure to reduce humidity.
- The NAU7802 board is able to operate in two modes: analog and digital.

  ## SENSOR OPERATION

- To make a measurement, a single conductor must pass through the core. If both the supply and return conductors pass through, the sensor will measure a value near zero, since the two electrical fields will cancel each other.
- The TAMURA design is NOT a clamp. The cable has to be securely disconnected from the source and passed through the core.
- The maximum size of wire gauge that can fit into the TAMURA core is limited. The cable – with its insulation – must fit into an 8mm x 15mm rectangular opening.
- The module can work from -20 to 80°C. Therefore, in most cold climates, there is no need to add a heating module. The rest of the components such as the voltage regulator can also tolerate those temperatures. In the near future, the module accuracy will be tested at -40°C. It is expected that the sensor will function properly but potentially with a reduced accuracy.
- According to L01Z specifications, the sensor accuracy at nominal current (i.e., 50A DC) and nominal temperature is ±1%. However, this is dependent on a high accuracy voltage supply: 5V ± 2%. For this reason, a voltage regulator was added to the board.
- The L01Z module has 3 pins: voltage (VCC), ground (GND), signal (SIG). The signal data is an analog 0-5V signal. This signal can be read by the analog channels of the RDL RevE2. The sensor can read positive and negative DC currents. Positive currents go from the reference voltage (V_ref) to 5V. Negative currents go from the reference voltage to 0V.
- The TAMURA consumes up to 15mA, which can cause a voltage drop on longer power supply cables (Ohm's law). This is the second reason - beside accuracy - why the voltage regulator subcircuit is essential. For the signal cable, the current is much reduced, reducing significantly the voltage drop. The RDL can therefore measure the signal directly with its ADS1115 chip, if desired.
- Due to its two RJ45 connectors, the NAU7802 board is compatible with daisy-chain, if there is no I2C addresses conflict.

  ## ANALOG OPERATION MODE

- The analog mode consist of taking direct measurements of the TAMURA sensor output (0-5V) with the RDL ADS1115 chip.
- This mode is less precise due to: 
    1) reduced ADC resolution (NAU7802 has 24-bit, while the ADS1115 has 16-bit)
    2) analog signal is sensitive to E.M. noise and voltage loss  
- The analog mode is only accessible via the screw terminal (VCC, GND, DATA). It is not available via the RJ45 connectors.
- The analog mode is therefore not recommended if the digital mode is available.


  ## DIGITAL OPERATION MODE

- The digital mode builds upon the analog mode. A high-accuracy ADC chip, NAU7802, measures the analog signal and converts it to a digital I2C signal that is transmitted to the data logger.
- The NAU7802 defaults to differential measurements (A+, A-) but for the current measurements, it operates in unipolar mode (A+, GND). The PGA is also deactivated to increase the measurement range to a full 0-5V.
- The Jericho NAU7802 board has dual purpose: current measurement and strain measurements. This is made possible by the dual-channel NAU7802. Channel A (A+,A-) is dedicated to current measurement, while Channel B (B+,B-) is dedicated to strain measurements (i.e. Wheatstone bridge). 
- Two types of calibration are possible on the NAU7802:  
    a) ADC calibration  
    b) Output calibration (offset & slope)


  ## VOLTAGE REGULATOR (TPS630701)

- To supply a high accuracy 5V line to the current sensor, the TPS630701 chip (buck-boost converter with switch current) is used.
- The circuitry around the TPS630701 is based on the manufacturer recommendation presented in the specification sheet.
- Four (4) decoupling capacitors are added on the input and output of the TPS630701 to improve the performance and stability.
- This chip has two operation modes: PFM mode (Pulse Frequency Modulation) and PWM (Pulse Width Modulation). One mode is more efficient, the other is more accurate. The PWM mode has a +1/-3% accuracy, which is insufficient for the need of the TAMURA sensor. The PFM mode achieves a +/-1% accuracy, which is the minimum requirement for the TAMURA sensor. To activate the PFM mode, the pin ‘PS/SYNC’ is pulled high.
- A male header is added to give access to some of the TPS63070 pins, but in normal operations they are not required. These pins are: VOUT, PG, GND, PS, GND, EN, VIN.
- Note: A heat sink of dimension 0.19x0.25x0.30" is optional but generally recommended for the TPS630701 chip. No heat sink is added for the current sensor since the power consumption is so low (15mA) compared with the nominal capacity (2A).
- TPS630701 is the fixed output version (5V) of the TPS63070 (adjustable output 2.5 - 9V). Contrarily to the Sparkfun original design, this circuit uses the fixed 5V output version. It has no feedback resistor to adjust the output between 2.5 and 9V. Instead, it has a feedback resistor inside the chip. The feedback resistor has an effect on the accuracy of the output, and so the accuracy (unknown) of the inner resistor probably limits the maximum accuracy achievable (i.e. 1%). Using the fixed 5V output has the advantage of avoiding any confusion that could occur with the variable voltage version.
- A LED is added to the PCB to indicate that the sensor is powered on. If the voltage regulator circuit is out of service, the LED will not turn on. However, the LED turning on does not confirm that the regulation is within specs, as the LED can turn on at lower voltages than 5V.
- You will notice a high-frequency noise while the ADS1115 operates. You will also notice a ticking sound at power startup, due to the coil being energized. These two sounds are considered normal with this design.
- The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply. On the measurement side, a sudden spike in current can produce an unexpectedly strong magnetic field, which could lead to erroneous readings or potentially damage the sensor if it exceeds the sensor's maximum current rating.

  ## SOFTWARE

- The standard RDL code can operate the current sensor in both the digital mode (I2C) and analog mode.
- In digital mode, the number of current sensors is only limited by the number of available I2C channels (max 8). In analog mode, it is limited by the number of available analog channels (max 8)

## OTHER

- A LED is added to the PCB to indicate that the sensor powered.
- The board has 3.5mm diameter holes in each corner for installation purposes.
- There is a supplementary 6-pin male header (2.54mm spacing) for quick connections and testing: GND, 5V, SDA, SCL, INT, VCC.

## REFERENCES

xxxxxxxxxxx 
NAU7802 specsheet

TAMURA Specsheet

TAL220 Specsheet
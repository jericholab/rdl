**NAU7802 Board For Strain and Current Revision B1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
Document license: CC-BY-SA.  
 

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version, as well as the latest specification sheets of the associated electronic components.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5V) supply, but other components of your system might require an electrician. The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.


**Table of Contents** 

1. [INTRODUCTION](#introduction)
2. [ADC SUBCIRCUIT (NAU7802)](#adc-subcircuit-nau7802)
   - 2.1 [GENERALITIES](#generalities)
   - 2.2 [I2C COMMUNICATION](#i2c-communication)
   - 2.3 [MEASUREMENTS](#measurements)
3. [VOLTAGE REGULATOR SUBCIRCUIT (TPS630701)](#voltage-regulator-subcircuit-tps630701)
4. [STRAIN & FORCE MEASUREMENTS](#strain--force-measurements)
   - 4.1 [GENERALITIES AND INSTALLATION](#generalities-and-installation)
   - 4.2 [STRAIN GAUGE LOAD CELL (TAL220)](#strain-gauge-load-cell-tal220)
   - 4.3 [SOFTWARE](#software)
   - 4.4 [STRAIN SENSOR CALIBRATION](#strain-sensor-calibration)
       - 4.4.1 [INTERNAL CALIBRATION](#internal-calibration)
       - 4.4.2 [EXTERNAL CALIBRATION](#external-calibration)
   - 4.5 [RJ45 CONNECTORS](#rj45-connectors)
5. [ELECTRICAL CURRENT MEASUREMENTS](#electrical-current-measurements)
   - 5.1 [TAMURA L01Z050S05 SENSOR DESCRIPTION](#tamura-l01z050s05-sensor-description)
   - 5.2 [SENSOR OPERATION](#sensor-operation)
   - 5.3 [ANALOG OPERATION MODE](#analog-operation-mode)
   - 5.4 [DIGITAL OPERATION MODE](#digital-operation-mode)
   - 5.5 [ALGORITHMS (DC & RMS)](#algorithms-dc--rms)
       - 5.5.1 [DC AVERAGE](#dc-average)
       - 5.5.2 [SINE RMS](#sine-rms)
       - 5.5.3 [TRUE RMS](#true-rms)
6. [OTHER](#other)
7. [REFERENCES](#references)




## INTRODUCTION

- The NAU7802 board is a dual sensor PCB. A single design allows both electrical AC/DC current measurements (Hall Effect) and strain/force measurements with a gauge cell. This reduces the number of active designs at Jericho. 
-  Therefore, the same raw PCB is used for two separate Jericho products:
    - Jericho NAU7802 Strain Board;
    - Jericho NAU7802 Current Board;
- You will notice on the Strain Board that the TAMURA sensor absent, to reduce cost.
- It is in theory possible to use the Current board to make both times of measurements simultaneously (i.e. strain and current). However, this has not been tested yet and the magnetic field of the cable current is likely to induce noise and/or bias on the strain measurements.
- The current measurements can be done via the analog or digital mode, while the strain measurements can only be done via the digital mode.
- For general information about PCB designs of Jericho sensors, please refer to the 'Design Overview - General information' document.  
- The original design of this board was provided by Sparkfun (CC-BY-SA).
- The license for the Jericho improvements of the hardware is also CC-BY-SA.


## ADC SUBCIRCUIT (NAU7802)

- This section describes the details of the Analog-to-Digital (ADC) NAU7802 chip. The information is relevant to both current and strain measurements.

  ## GENERALITIES  
- The NAU7802 chip by Nuvoton is a high-accuracy voltage measurement device. It includes a 24-bit ADC (Analog-to-Digital Converter) and provides I2C communication.
- The NAU7802 has two main capabilities: it can provide a regulated voltage  and it has two channels to measure analog signals from sensors. The regulated voltage is typically used to excite a Wheatstone bridge (not used in this product).
- A very high accuracy ADC is required because the strain gauges, by their nature, create very weak signals, in the order of millivolts. The current sensor also needs the accuracy as it distributes a -50A/+50A input range on a 3V output range (+1.0V/+4.0V).
- The NAU7802 chip makes a differential voltage measurement by default. It can also be configured for single-end measurement (i.e. signal-to-ground).
- The VDDA and GND are respectively the excitation voltage and ground lines for the activation of the Wheatstone bridge. The A- and A+ pins are the actual measurements of the bridge.
- The NAU7802 chip is equipped with decoupling capacitors at the power supply (0.1uF, 10uF and 22uF). While other Jericho boards use only 0.1uF and 10uF, the NAU7802 uses a supplementary 22uF for increased stability.
- In theory, the NAU7802 does not require a precise supply voltage (2.7-5.5V) since it has an internal voltage regulator. However, multiple users of the similar Sparkfun NAU7802 board have reported on forums a high sensitivity of readings to voltage supply; hence, a voltage regulator circuit was added.
Similarly, the input decoupling capacitors, by stabilizing the input voltage, ease the work of the NAU7802 voltage regulator and improve performance by further reducing noise and other voltage fluctuations.
- Note that the NAU7802 can accept various voltage supply values but the reading voltage range will be limited by the supply voltage value (“AVDD should not exceed DVDD supply voltage”).
- When used with the RDL, the NAU7802 PCB is only supplied in power when a measurement is required by the RDL. This means that over the course of its life, the sensor will be powered up thousands of times. The NAU7802 chip does not require a delay between power up and reading; it deals with the necessary delays autonomously.

  ### I2C COMMUNICATION

- Like all sensors from the RDL suite, the NAU7802 board has been designed for long wire operation (30m). However, the NAU7802 chip appears to have a weaker native signal and achieves shorter cable lengths for a given I2C bus frequency. When combined with I2C shield, RDL, a CAT5 cable and low EM noise environment, the maximum cable length for continuous communication is currently 30 m.
- Apart from Sparkfun, there is another popular board design based on the NAU7802, by Adafruit. When comparing the two schematics, the stronger pullup resistors on the SDA/SCL lines (2.2kohm) seem to be the reason why longer cables are possible with Sparkfun than Adafruit (10kohm). On the Jericho design, as well as Sparkfun, these pullup resistors are in series with solder junctions (normally ON) that can be cut with a knife if the user wants to disconnect them.
- NAU7802 is designed to operate at 100kHz or 400kHz (high-speed I2C bus). However, it has shown no difficulties at operating at low bus frequency, down to 31kHz (Jericho present default on hardware-based I2C protocol).
- The presence of two RJ45 connectors on the board allows to daisy chain I2C devices. For example, the cabling cost can be reduced by using a single long cable to reach the strain sensor PCB and, from there, only add a short CAT cable to connect to the SHT40 PCB. This is possible because the two PCBs do not have the I2C address.
- The NAU7802 chip has a single permanent I2C address: 0x2A. Therefore, one cannot daisy-chain two strain boards, it can only daisy chain a different sensor. Using two strain sensors on a given system requires two separate channels.
- There is a supplementary 6-pin male header (2.54mm spacing) for quick connections and testing: GND, 5V, SDA, SCL, INT, VCC.

  ### MEASUREMENTS

- Although the strain and current measurements both use the same chip, NAU7802, they use it differently.
  - STRAIN: Differential mode
  - CURRENT: Unipolar mode

- The measurements can be done at various speed: 10, 20, 40, 80, 320 SPS (Samples Per Second). To reduce sampling time, the RDL runs at 320 SPS by default.
- The DVDD pin is the digital power supply input (2.7 - 5.5V). It is externally provided by the on-board regulating circuit (5V).
- The VDDA pin is the analog power supply input (2.7 - 5.5V), used to excite the Wheatstone bridge. The default manufacturer value is 3.3V, supplied by NAU7802 internal circuit. In the present case, this default mode is overriden (via NAU7802 registers) and instead the DVDD signal is used (5V). It is within the allowable excitation voltage range of the TAL220 (3-10V) and it maximize the measurement range by maximizing the sensitivity (V/N). Accordingly, the ADC voltage range is also modified within the code. For more information, read the RDL source code and the RDL code documentation.
- The PGA (Programmable Gain Amplifier) can be configured to vary the gain applicable (1, 2, 4, 8, 16, 32, 64, 128). It also affects the voltage range applicable. The default value is 128. This gain could be reduced if the load cell output measurement was saturated by the NAU7802 chip. The PGA must be deactivated for unipolar mode (current measurements).
- The measurement output by the NAU7802 is the average of a large sample. This is configured within the Arduino code. 
- The ADC output follows this general equation: “ADC Output Value = Gain_Calibration\* (ADC measurement - Offset_Calibration)”.

## VOLTAGE REGULATOR SUBCIRCUIT (TPS630701)

- This section describes the details of the voltage regulation subcircuit. The information is relevant to both current and strain measurements.

- To supply a high accuracy 5V line to the current sensor, the TPS630701 chip (buck-boost converter with switch current) is used.
- The circuitry around the TPS630701 is based on the manufacturer recommendation presented in the specification sheet.
- Four (4) decoupling capacitors are added on the input and output of the TPS630701 to improve the performance and stability.
- This chip has two operation modes: PWM (Pulse Width Modulation) and PFM mode (Pulse Frequency Modulation) . The first is more efficient, the second is more accurate. The PWM mode has a +1/-3% accuracy, which is insufficient for the need of the TAMURA sensor. The PFM mode achieves a +/-1% accuracy, which is the minimum requirement for the TAMURA sensor. To activate the PFM mode, the pin ‘PS/SYNC’ is pulled high.
- A male header is added to give access to some of the TPS63070 pins, but in normal operations they are not required. These pins are: VOUT, PG, GND, PS, GND, EN, VIN.
- A heat sink of dimension 0.19x0.25x0.30" is optional but generally recommended for the TPS630701 chip. No heat sink is added for the NAU7802 board since the power consumption is so low (15mA) compared with the nominal capacity (2A).
- TPS630701 is the fixed output version (5V) of the TPS63070 (adjustable output 2.5 - 9V). Contrarily to the Sparkfun original design, this circuit uses the fixed 5V output version. It has no feedback resistor to adjust the output between 2.5 and 9V. Instead, it has a feedback resistor inside the chip. The feedback resistor has an effect on the accuracy of the output, and so the accuracy (unknown) of the inner resistor is possibly what limits the accuracy achievable according to specsheet (i.e. +/- 1%). Using the fixed 5V output has the advantage of avoiding any confusion that could occur with the variable voltage version.
- A LED is added to the subcircuit to indicate that the sensor is powered on. If the voltage regulator circuit is out of service, the LED will not turn on. However, the LED turning on does not confirm that the regulation is within specs, as the LED can turn on at lower voltages than 5V.
- You will notice a high-frequency noise while the ADS1115 operates. You will also notice a ticking sound at power startup, due to the coil being energized. These two sounds are considered normal with this design.
- The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply. On the measurement side, a sudden spike in current can produce an unexpectedly strong magnetic field, which could lead to erroneous readings or potentially damage the sensor if it exceeds the sensor's maximum current rating.

 ## STRAIN & FORCE MEASUREMENTS

 - This section describes the subcircuit responsible for strain and force measurements.


   ## GENERALITIES AND INSTALLATION  

- To operate, a strain sensor board requires a separate strain gauge load cell. This section details the relationship of the sensor with the required load cell.
- The J3 screw terminal allows the PCB to connect with the strain gauge load cell. The load cell should be a full Wheatstone bridge. The wire colors on a load cell tend to indicate the function but it might differ on your specific load cell. In case of conflict, the wire function (VDDA, GND, A-, A+) has priority over wire color.
- A Wheatstone bridge is an electrical circuit used to precisely measure an unknown electrical resistance by balancing two legs of a bridge circuit, one leg of which includes the unknown component. It is commonly used in sensor applications to convert changes in physical phenomena (like temperature, strain, or pressure) into changes in resistance, which can then be measured with high accuracy.
- As a general rule of thumb, the wire length between the NAU7802 and the strain gauge must be minimized and be kept under 1 m. This helps keep the signal-to-noise ratio at a sufficient level.
- The detailed installation procedure for strain gauges goes beyond the scope of this document but is a crucial part of the process.
- Since strain gauge load cell wires are usually quite small and small gauge wires can slip out of the 5mm terminal, this PCB design uses smaller screw terminals: 3.5mm pitch instead of the typical 5mm pitch. 
- By their nature, strain gauges do not tolerate well long-term static loads (> 1 day). It causes measurement drift for multiple reasons (gauge deformation, adhesive breakdown). For precise long-term measurements, periodic recalibration and the use of multiple gauges for redundancy may also be necessary.

  ## STRAIN GAUGE LOAD CELL (TAL220)  

  - For general use, we recommend the following load cell: TAL220 (micro parallel beam) by HTC-sensor (Chinese manufacturer). For more information, consult the TAL220 specification sheet. You can buy the TAL220 on Sparkfun.com or on the manufacturer website (htc-sensor.com). The manufacturer has more production options (e.g. load capacity from 1kg to 50kg, outdoor jacket, etc). The TAL220 has IP65 rating.

  ## SOFTWARE

- The standard RDL code can operate the strain sensor. The number of allowable strain sensors is only limited by the number of I2C channels.

  ## STRAIN SENSOR CALIBRATION

- When measuring strain with a NAU7802, there are two types of calibration: internal, external. The internal calibration makes sure that the strain gauge is accurately measured by the NAU7802 ADC. The external calibration ensures that the strain gauge resistance is accurately converted into a force or strain.

  ## INTERNAL CALIBRATION
- According to the NAU7802 manufacturer, the internal calibration is recommended after each of the following events:
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
- External calibration has to be done for each specific load cell. If the load cell is damaged and replaced, a calibration must be done. External calibration can be done via the source code only. It currently cannot be done via a live command.
- Since strain gauges are highly linear devices, only a two-point calibration is required.

  ## RJ45 CONNECTORS

- There are two RJ45 connectors on this board, which allow I2C communication. They are not compatible with the Ethernet protocol. They are interchangeable. One can be used for connection to the RDL, the other for daisy-chaining.
- Each connector follows the following wiring connection:
  - Pin 1 & 2: VCC
  - Pin 3 & 4: GND
  - Pin 5 & 6: SDA
  - Pin 7 & 8: SCL
- This wiring order, combined with the internal architecture of the CAT cable (standard) creates a partial shielding, since the GND wires are twisted with the VCC and SDA wires. In future versions, improvements could be made on the wiring order to also shield the SCL line.
- For the strain sub-circuit, the main modifications with the Sparkfun design are: 1) the addition of a voltage regulator circuit; 2) the addition of RJ45 connectors; and 3) the addition of screw terminals.
- The NAU7802 chip itself has some sensitivity to temperature. There are two ways to protect the measurements from temperature bias: 1) internal calibration at a regular interval; 2) on-chip temperature measurement. Due to the complexity of the second method (which is not coded in the Sparkfun library), only the first method is used. The temperature data is not exposed to the I2C interface. 

- Strain gauges are very sensitive to temperature variation. There are multiple components to this relationship (e.g. load cell thermal expansion, strain gauge film expansion). However, some Wheatstone configurations are inherently compensated in temperature. This is the case for the TAL220 (parallel bending cell with full bridge). Therefore, the thermal expansion will affect both strain gauges in the same way and cancel each other out in the voltage output. This technique is effective within a mild temperature range (e.g. -10 to +40C). At extreme temperature, independent external temperature compensation via a separate thermistor probe can be required (not coded).


## ELECTRICAL CURRENT MEASUREMENTS

- This section describes the current measurement section of the PCB.  

  ## SENSOR DESCRIPTION (TAMURA L01Z050S05)

- The core component of the board is the L01Z050S05 current sensor module manufactured by TAMURA Corporation (a global company with head offices in Japan). The L01Z module, based on the Hall effect, can measure both DC and AC (up to 100kHz) current up to 50A DC. The maximum frequency readable by the Jericho board however is much less, limited by the sampling speed of the processors. The LZ01 series offers module with a capacity up to 600A DC.
- The L01Z component was selected because it can be used with AC and DC current, while as induction-based sensors are only compatible with AC current.
- The TAMURA component is readily available at global suppliers like DigiKey or Mouser. PCB manufacturers like JLCPCB can source from those suppliers for their SMD and through-hole assembly line.
- The TAMURA module was designed for indoor use and is not weatherproof. Therefore, the sensor MUST be installed in a weatherproof enclosure to avoid any damage or safety risk.


  ## PCB INTEGRATION

 - The TAMURA is a through-hole component soldered on the PCB. Two soldered mechanical pins reduce the strain on the electronic pins.
 - The analog output is a 0-5V output, but for several reasons, it requires a load resistor (RL):
    - Voltage Division (scale down the voltage to ADC level)  
    - Current limiting
    - Signal conditioning (provide a predicatble load impedance)
    - Interface Matching (Match the input impedance to avoid signal loss)
 - The manufacturer specifications require a 10 kohms load resistor. More information is available in the L01Z Series Application Manual.

  <figure>
  <p align="center">
   <img src="../Design Overview/images/tamura-resistor2.png" style="width:70%"
  </p>
 </figure>
 <p align="center"> Recommended electrical circuit for the L01Z sensor (Copyright TAMURA CORP)

  ## SENSOR OPERATION

- To make a measurement, a single conductor must pass through the core. If both the supply and return conductors pass through, the sensor will measure a value near zero, since the two electrical fields will cancel each other.
- The TAMURA design is NOT a clamp design. The cable has to be securely disconnected from the source and passed through the core.
- The maximum size of wire gauge that can fit into the TAMURA core is limited. The cable – with its insulation – must fit into an 8mm x 15mm rectangular opening.
- The module can work from -20 to 80°C. Therefore, in most cold climates, there is no need to add a heating module. The rest of the components such as the voltage regulator can also tolerate those temperatures. In the near future, the module accuracy will be tested at -40°C. It is expected that the sensor will function properly but potentially with a reduced accuracy.
- According to L01Z specifications, the sensor accuracy at nominal current (i.e., 50A DC) and nominal temperature is ±1%. However, this is dependent on a high accuracy voltage supply: 5V ± 2%. For this reason, a voltage regulator was added to the board.
- The L01Z module has 3 pins: voltage (VCC), ground (GND), signal (SIG). The signal data is an analog 0-5V signal. This signal can be read by the analog channels of the RDL RevE2. The sensor can read positive and negative DC currents. Positive currents go from the reference voltage (V_ref) to 5V. Negative currents go from the reference voltage to 0V.
- The TAMURA consumes up to 15mA, which can cause a voltage drop on longer power supply cables (Ohm's law). This is the second reason - beside accuracy - why the voltage regulator subcircuit is essential. For the signal cable, the current is much reduced, reducing significantly the voltage drop. The RDL can therefore measure the signal directly with its ADS1115 chip, if desired.
- Due to its two RJ45 connectors, the NAU7802 board is compatible with daisy-chain, if there is no I2C addresses conflict.

  ## ANALOG OPERATION MODE

- The analog mode consist of taking direct measurements of the TAMURA sensor output (0-5V) with the RDL ADS1115 chip.
- This mode is less precise due to: 
    1) reduced ADC resolution (NAU7802 has 24-bit, while the ADS1115 has 16-bit resolution)
    2) analog signal is sensitive to E.M. noise and voltage loss  
- The analog mode is only accessible via the screw terminal (VCC, GND, DATA). It is not available via the RJ45 connectors.
- The analog mode is therefore not recommended if the digital mode is available.


  ## DIGITAL OPERATION MODE

- The digital mode builds upon the analog mode. A high-accuracy ADC chip, NAU7802, measures the analog signal and converts it to a digital I2C signal that is transmitted to the data logger.
- The NAU7802 defaults to differential measurements (A+, A-) but for the current measurements, it operates in unipolar mode (A+, GND). The PGA is also deactivated to increase the measurement range to a full 0-5V.
- The Jericho NAU7802 board has dual purpose: current measurement and strain measurements. This is made possible by the dual-channel NAU7802. Channel A (A+, A-) is dedicated to current measurement, while Channel B (B+, B-) is dedicated to strain measurements (i.e. Wheatstone bridge). 

  ## EFFECTIVE CURRENT ALGORITHMS

- The RDL has three algorithms for the measurement of current. The algorithm affects both the sampling method and the data treatment. It does not affect the current sensor itself. For this reason, the detailed description of the algorithms can be found in the SAD (Sofware Architecture Documentation).

    ### DC AVERAGE

  - A simple arithmetic average of a variable-size sample. Useful for DC currents only.

  ### SINE RMS

  - Sine RMS (Root Mean Square) is used for AC measurements where the waveform is predominantly sinusoidal. This method provides an efficient computation by leveraging the properties of a sine wave. It rectifies the signal and applies a correction factor.

  ### TRUE RMS

  -  True RMS calculation provides accurate readings for AC currents regardless of waveform shape, making it essential for electronic applications involving non-linear loads.
  - The True RMS algorithm, and to a lesser extent the Sine RMS, require high-speed data processing. The limited Arduino Nano speed therefore poses a limit to the maximum allowable frequency of AC signal that can be measured.

  ## SOFTWARE

- The standard RDL code can operate the current sensor in both the digital mode (I2C) and analog mode.
- In digital mode, the number of current sensors is limited by the number of available I2C channels (max 8). In analog mode, it is limited by the number of available analog channels (max 8).

## OTHER

- The board has 3.5mm diameter holes in each corner for installation purposes.
- Jericho recommends the use of two adequate size cable glands (inlet, outlet) on the main cable to avoid any water entry in the enclosure.
- Jericho recommends the addition of silica gel packet inside the enclosure to reduce humidity.

## REFERENCES

NAU7802 specsheet

https://www.nuvoton.com/resource-files/NAU7802%20Data%20Sheet%20V1.7.pdf

TAMURA LZ01 Series Specsheet

https://www.tamuracorp.com/clientuploads/pdfs/engineeringdocs/L01ZXXXS05.pdf

L01Z Series Application Manual

https://www.tamuracorp.com/file.jsp?id=18591

HTC-Sensor TAL220 Specsheet

https://www.digikey.com/htmldatasheets/production/2459755/0/0/1/tal220.html


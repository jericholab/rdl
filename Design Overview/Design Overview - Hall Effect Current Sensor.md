**NAU7802 Hall Effect Current Sensor Revision B1- Design Overview**  
=======================================

Copyright: Jericho Laboratory Inc. Document license: CC-BY-SA.  
 

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5V) supply, but other components of your system might require an electrician. The L01Z sensor has no voltage protection against voltage spike or surge. However, the voltage regulator circuit adds some protection against voltage protection that might occur in the power supply.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.

**GENERAL**

- For general information about PCB designs of Jericho sensors, please refer to 'Design Overview - General information.md'.  
- The original design of this board was provided by Sparkfun (CC-BY-SA).
- The license for the Jericho improvements of the hardware is CC-BY-SA.

**CURRENT SENSOR (L01Z050S05) GENERALITIES AND INSTALLATION**

- The core component of the board is the L01Z050S05 current sensor module manufactured by TAMURA. The L01Z module, based on the Hall effect, can measure both DC and AC (up to 100kHz) current up to 50A DC. The maximum frequency readable by the Jericho board however is much less, limited by the sampling speed of the processor. The LZ01 series offers module with a capacity up to 600A DC.
- The L01Z component was selected because it can be used with DC current, while as induction-based sensors are only compatible with AC current.
- The TAMURA component is readily available at global suppliers like DigiKey or Mouser. PCB manufacturers like JLCPCB can source from those suppliers for their SMD and through-hole assembly line.
- The TAMURA module was designed for indoor use and is not weatherproof. Therefore, the sensor MUST be installed in a weatherproof enclosure to avoid any damage or safety risk.
- The TAMURA is a through-hole component soldered on the PCB. Two soldered mechanical pins reduce the strain on the electronic pins.
- Jericho recommend the use of two adequate size cable glands (inlet, outlet) on the main cable to avoid any water entry in the enclosure.
- Jericho recommends the addition of silica gel packet inside the enclosure to reduce humidity.
- The NAU7802 board is able to operate in two modes: analog and digital.

**OPERATION**

- To make a measurement, a single conductor must pass through the core. If both the supply and return conductors pass through, the sensor will measure a value near zero, since the two electrical fields will cancel each other.
- The TAMURA design is NOT a clamp. The cable has to be securely disconnected from the source and passed through the core.
- The maximum size of wire gauge that can fit into the TAMURA core is limited. The cable – with its insulation – must fit into an 8mm x 15mm rectangular opening.
- The module can work from -20 to 80°C. Therefore, in most cold climates, there is no need to add a heating module. The rest of the components such as the voltage regulator can also tolerate those temperatures. In the near future, the module accuracy will be tested at -40°C. It is expected that the sensor will function properly but potentially with a reduced accuracy.
- According to L01Z specifications, the sensor accuracy at nominal current (i.e., 50A DC) and nominal temperature is ±1%. However, this is dependent on a high accuracy voltage supply: 5V ± 2%. For this reason, a voltage regulator was added to the board.
- The L01Z module has 3 pins: voltage (VCC), ground (GND), signal (SIG). The signal data is an analog 0-5V signal. This signal can be read by the analog channels of the RDL RevE2. The sensor can read positive and negative DC currents. Positive currents go from the reference voltage (V_ref) to 5V. Negative currents go from the reference voltage to 0V.
- The TAMURA consumes up to 15mA, which can cause a voltage drop on longer power supply cables (Ohm's law). This is the second reason - beside accuracy - why the voltage regulator subcircuit is essential. For the signal cable, the current is much reduced, reducing significantly the voltage drop. The RDL can therefore measure the signal directly with its ADS1115 chip, if desired.
- Due to its two RJ45 connectors, the NAU7802 board is compatible with daisy-chain, if there is no I2C addresses conflict.


**ANALOG OPERATION MODE**  

- The analog mode consist of taking direct measurements of the TAMURA sensor output (0-5V) with the RDL ADS1115 chip.
- This mode is less precise due to: 
    1) reduced ADC resolution (NAU7802 has 24-bit, while the ADS1115 has 16-bit)
    2) analog signal is sensitive to E.M. noise and voltage loss  
- The analog mode is only accessible via the screw terminal (VCC, GND, DATA). It is not available via the RJ45 connectors.
- The analog mode is therefore not recommended if the digital mode is available.


**DIGITAL OPERATION MODE**

- The digital mode builds upon the analog mode. A high-accuracy ADC chip, NAU7802, measures the analog signal and converts it to a digital I2C signal that is transmitted to the data logger.
- The NAU7802 defaults to differential measurements (A+, A-) but for the current measurements, it operates in unipolar mode (A+, GND). The PGA is also deactivated to increase the measurement range to a full 0-5V.
- The Jericho NAU7802 board has dual purpose: current measurement and strain measurements. This is made possible by the dual-channel NAU7802. Channel A (A+,A-) is dedicated to current measurement, while Channel B (B+,B-) is dedicated to strain measurements (i.e. Wheatstone bridge). 
- Two types of calibration are possible on the NAU7802:  
    a) ADC calibration  
    b) Output calibration (offset & slope)


**VOLTAGE REGULATOR TPS630701**

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

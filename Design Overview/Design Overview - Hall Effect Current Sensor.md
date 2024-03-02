**Hall Effect Current Sensor Revision A1 - Design Overview (DRAFT)**  
=======================================

Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  
Revision: 0.  

Warning: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

Safety warning: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. The current sensor operates with a 5V supply, but the installation of the sensor on the high-voltage circuit requires an electrician.

Warning: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.

GENERAL

- This document refers to the strain sensor system associated with the Jericho Strain Sensor PCB revision A1.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- The original design of the voltage regulation circuit was done by Sparkfun under CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.
- The allowable wire gauges for the PCB screw terminals are AWG 20-26.
- For this product, a “long wire” is defined as 30 m. The device was designed with a target of 30m wire. This applies for both CAT cables and ordinary two-conductor cables.

NOTES APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on Github. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.
- Unless stated otherwise, all libraries required to make the RDL suite run are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

CURRENT SENSOR (L01Z050S05) GENERALITIES AND INSTALLATION

- The core component of the board is the L01Z050S05 current sensor module manufactured by TAMURA. The LZ01 module is based on the Hall effect. It can measure both DC and AC (up to 100kHz) current up to 50A DC. The LZ01 series offers module with a capacity up to 600A DC.
- This component was selected because it can be used with DC current, while as induction-based sensors can also work with AC current.
- The TAMURA component is readily available at global suppliers like DigiKey or Mouser.
- The TAMURA module was designed for indoor use and is not weatherproof. Therefore, the PCB should be installed in a weatherproof enclosure.
- The TAMURA is soldered on the PCB. Two soldered mechanical pins reduce the strain on the electronic pins.
- Jericho recommend the use of two adequate size cable glands (inlet, outlet) on the main cable to avoid any water entry in the enclosure.
- Jericho recommends the addition of silica gel packet inside the enclosure to reduce humidity.

OPERATION

- To make a measurement, a single conductor must pass through the core. If both the supply and return conductors pass through, the sensor will measure a value near zero, since the two electrical fields will cancel each other.
- The TAMURA design is NOT a clamp. The cable has to be securely disconnected from the source and passed through the core.
- The maximum size of wire gauge that can fit into the TAMURA core is limited. The cable – with its insulation – must fit into an 8mm x 15mm rectangular opening.
- The module can work from -20 to 80°C. Therefore, in most cold climates, there is no need to add a heating module. The rest of the components such as the voltage regulator can also tolerate those temperatures. In the near future, the module will be tested at -40°C.
- According to TAMURA specifications, the sensor accuracy at nominal current (i.e., 50A DC) is ±1%. However, this is dependent on a high accuracy voltage supply: 5V ± 2%. For this reason, a voltage regulator must be integrated on-board.
- The TAMURA sensor has 3 pins: voltage (VCC), ground (GND), signal (SIG). The signal data is an analog 0-5V signal. This signal can be read by the analog channels of the RDL RevE2. The sensor can read positive and negative DC currents. Positive currents go from the reference voltage (V_ref) to 5V. Negative currents go from the reference voltage to 0V.
- The TAMURA consumes up to 15mA, which causes a voltage drop on the power supply cable. This is the second reason (beside accuracy) why the voltage regulator subcircuit is essential. For the signal cable, the current is much reduced, reducing significantly the voltage drop. The RDL can therefore measure the signal directly.

VOLTAGE REGULATOR TPS630701

- To supply a high accuracy 5V line to the current sensor, the TPS630701 chip (buck-boost converter with switch current) is used.
- The circuitry around the TPS is based on the manufacturer recommendation presented in the specification sheet.
- A large number of decoupling capacitors are added on the input and output of the TPS63070.
- This chip has two operation modes: PFM mode (Pulse Frequency Modulation) and PWM (Pulse Width Modulation). One mode is more efficient, the other is more accurate. The PWM mode has a +1/-3% accuracy, which is insufficient for the need of the TAMURA sensor. The PFM mode achieves a +/-1% accuracy, which is the minimum requirement for the TAMURA sensor. To activate the PFM mode, the pin ‘PS/SYNC’ is pulled high.
- For TPS63070, the accuracy of the output depends on the accuracy of the feedback resistor.
- A female header is added to give access to some of the TPS63070 pins, but in normal operations they are not required.
- Note: A heat sink of dimension 0.19x0.25x0.30" is optional but generally recommended for the TPS630701 chip. No heat sink is applied for the current sensor revA1 since the power consumption is so low (15mA) compared with the nominal capacity (2A).
- TPS630701 is the fixed output version (5V) of the TPS63070 (adjustable output 2.5 - 9V). Contrarily to the Sparkfun original design, this circuit uses the fixed 5V output version. It has no feedback resistor to adjust the output between 2.5 and 9V. Instead, it has a feedback resistor inside the chip. The feedback resistor has an effect on the accuracy of the output, and so the accuracy (unknown) of the inner resistor probably limits the maximum accuracy achievable (i.e. 1%). Using the fixed 5V output has the advantage of avoiding any confusion that could occur with the variable voltage version.

OTHER

- A LED is added to the PCB to indicate that the sensor is powered on.
- To enable connection between the PCB and the RDL, a 3-pin screw terminal is added (VCC, GND, SIG). There is no RJ45 connector, since this is not an I2C protocol sensor.

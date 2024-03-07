**I2C Shield RevA2 Design Overview**  
=======================================
Jericho Laboratory Inc. Documentation licence: CC-BY-SA.  

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

GENERAL

- This document refers to the Resistance Data Logger (RDL) system associated with the Jericho RDL PCB revision E2. This board is the successor of revision E1 (prototype).
- The RDL rev E2 hardware is released under the MIT open-source license.
- The current board revision only works with the corresponding source code version.
- Allowable wire gauges are written on the silkscreen (AWG 20-26). This interval is the ideal size to avoid wires slipping out. The order of the terminals is also printed (i.e. VCC, GND, SIG, VCC, GND, SIG, etc.)
- Starting with revision E2, the objective of maintaining at least 50% of the product cost (material and labor) has been abandoned. This was a requirement for the ‘Made in Canada’ label, which appeared contrary to the goal of maximizing affordability and access. Therefore, an increased number of manufacturing operations are outsourced.
- In this revision E2, the SMD components are installed at the factory (JLCPCB, China) and THT components are installed in house. The later include headers, screw terminals and RJ45 connectors.
- Long wires (>10m) between the RDL and its sensors will cause significant voltage loss. This means that some devices will require a voltage regulator at the other end to make sure that the chip is supplied with the proper voltage.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.
- There are holes around the board to help attach the wires and reduce mechanical stress on the wires.

NOTES APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on Github. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.
- Unless stated otherwise, all libraries required to run the RDL suite are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

GENERALITIES ABOUT THE I2C SHIELD

- The I2C shield allows the RDL to communicate with eight sensors based on I2C communication.
- Multiplexing is a technical term to describe the ability to communicate with multiple devices one-at-a-time using a single channel. This is a common technique to reduce the hardware requirements in electronics project. It implies that the Arduino will connect to each I2C sensor one after the other.
- With this design, up to three I2C shields can be connected by stacking them below the RDL. They all form a single I2C bus.

I2C COMMUNICATION

- I2C protocol was developed for inter processor communication (1m meter max). However, there are ways to extend this distance. In the present design, the maximum is intended to be about 30m. Depending on the exact setup and environmental conditions, it could be less.
- An I2C protocol is a two-wire protocol: one for the clock (SCL, for signal clock) and one for the data (SDA for signal data).
- There can only be a single device with the same I2C address on a given bus. Otherwise, two or more devices would ‘respond’ at the same time when being ‘talked’ to.
- Some I2C chips are more convenient as they can use more than one address. This is usually done by pulling high/low one or more pins on the chip. Some breakout boards can have solder jumpers cut/soldered to make this address permanent.
- An I2C address has the format 0x_\_. Examples include: 0x44, 0x42, etc.
- Many projects dedicated to I2C multiplexing only affect the SDA and SCL lines. This allows you to communicate with multiple I2C devices, even if they all have the same I2C address. However, these projects do not multiplex the supply lines, which creates problems when using long wires (noisy supply lines). It was therefore necessary to create a different multiplexing solution.

CABLES

- The I2C shield connects to the RDL via RJ45 connectors and an Ethernet (CAT) cable.
- Multiple versions of the CAT cable exist: CAT5, CAT5e, CAT6, CAT7 can all be used. Earlier standards are usually cheaper, but they are progressively phased out of high-volume production.
- Both shielded and unshielded cables can be used. The product design tries to minimize the impact of EMI but shielded cable can be required for best performance in noisy environments.

I2C EXTENDER (LTC4311)

- Long distances bring a few problems: excessive capacitance, excessive inductance and excessive noise.
- The I2C extender circuit is now located on the RDL, instead of the shield. This allows the RDL to communicate with a single I2C sensor at a long distance without the use of an I2C shield. Having the extender chip on the RDL also enables the use of multiple I2C shield. Indeed, the use of three I2C shields would imply having three I2C extender on the I2C bus. This would cause dysfunction of the bus.
- The I2C extender chip used is the LTC4311. It works by providing extra potential to the rising edges of the I2C signal.
- I2C extender works in combination with the pull-up resistors. There are generally pull-up resistors near the master and the slave devices.
- The I2C extender must be close to the Arduino Nano, so that it can operate properly.
- The I2C shield contains two RJ45 connectors. They are interchangeable as they are both connected to the same I2C bus. A first connector is used to connect the shield to the RDL. The second connector can be used to connect to either 1) a second shield; or 2) a supplementary I2C device (no multiplexing).

GPIO I2C EXPANDER (PCF8574)

- PCF8574T is a GPIO (General Purpose Input Output) I2C expander. It means that it can multiplex a signal or power line using I2C communication. In the I2C shield, this chip is used to multiplex the two power lines (VCC and GND). It does so indirectly by activating/deactivating MOSFET transistors.
- The use of transistors is unavoidable because the maximum current output from a Nano VCC pin is 500mA when powered by a USB cable. This is way above the limit of the PCF8674 (80mA), the CD74HC4051MM96EP (25 mA) or a Nano pin directly (20mA). By using transistors, the shield allows any sensor that would have functioned properly if directly connected to the Nano.
- The PCF8574T is preferable to alternatives like the CD74HC because it doesn’t require additional cables to select the channels, which would be impossible with a shield only connected to the Nano via an Ethernet cable.
- The PCF8574 is a bit unusual and is described as “an open-drain output with a 100K resistor pull-up built in”. This mean that the output is inverted: when the channel is inactive, the output is high, and when the channel is active, the output is low. However, the Adafruit library manages this, so that the behavior is more intuitive for the user.

I2C MULTIPLEXER (TCA9548)

- TCA9548APWR is a chip multiplexer for I2C communication. It has 3 address pins (A0, A1, A2), which can be pulled high or low, allowing 8 different I2C addresses.
- The TCA (1 chip) and the PCFs (2 chips) each require 3 solder junctions for permanent I2C addresses. This avoids inner-board conflict between the two PCF chips and inter-board conflicts between TCA/PCF chips on the three shields instances.
- To avoid picking up noise on the power supply lines via 8 cables of up to 30m, the power lines are also multiplexed. They are multiplexed on both the high-side (VCC) and the low-side (GND).

MOSFET TRANSISTORS

- Choice of components:
  - P-channel MOSFET (high-side): AO3401 (max -4.0A)
  - N-channel MOSFET (low-side): AO3406 (max 3.6A)
- High-side transistors, whether in MOSFET (P-channel) or Darlington (PNP) versions, require a low signal (i.e. ground) to be activated. This means that the same signal cannot be used to activate the high-side and low side-multiplexer chips. One solution is to use a separate GPIO multiplexer for each, like the PCF8574T. This implies that a 3-shield stacked system would have 6 PCF8574T with 6 different I2C addresses (out of a possibility of 8). For a given channel, one PCF will send a high signal to the AO3406’S and the other PCF will send a low signal to the AO3401’S. The downside of this strategy is that it adds one more device talking on the I2C bus.
- Note that the PCF8574 has ‘latched outputs’ so all pins can be set simultaneously to HIGH, if needed be.
- High-side and low-side configuration are sometimes called Source and Sink Configuration, respectively.
- On the MOSFET diagram, the body diode has to be oriented so that there is no flow in normal operation. The other internal arrow indicates that the gate is activated by comparison with the voltage at the source (V_GS). With P-channel, we must be at least 2V beneath the source voltage. With N-Channel, we must be at least 2V above the source voltage.
- There is no need to use a gate resistor to limit in-rush current at the gate with a MOSFET. This is because MOSFETs are voltage-driven, while BJT’s are current driven.

OTHER

- A LED is present on the board to indicate that the board is supplied in power.
- Another LED was temporarily added to the VCC of channel 1 to indicate that this MOSFET works correctly. This is useful for troubleshooting.
<figure>
<p align="center">
<img src="../Design Overview/images/I12 shield RevA2.png" style="width:70%">
  </p>
</figure>
<p align="center">
Figure . Temporary diagram for the MOSFETs pairs controlling the sensors power supply
</p>

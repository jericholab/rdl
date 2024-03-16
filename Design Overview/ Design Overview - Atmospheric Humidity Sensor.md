**Atmospheric Humidity Sensor Revision A2 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc. Documentation license: CC-BY-SA.  


Warning: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

GENERAL

- This document refers to the strain sensor system associated with the Jericho Strain Sensor PCB revision A1.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- The original design of the voltage regulation circuit was done by Adafruit under CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- There are holes around the board to help attach the wires and reduce mechanical stress on the wires.
- A copper plane (ground) is poured on the bottom surface of the PCB to reduce EM noise. There is no copper plane on the top surface.

APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 7.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on GitHub. This includes KiCAD project files, Gerber files, BoM and Component Position Placement (CPL) files.
- Design and cost have been partially optimized for JLCPCB manufacturing abilities and components pricing at the time of design, for small batches.
- Unless stated otherwise, all libraries required to run the RDL suite are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

CORE SENSOR - SHT40 CHIP

- The SHT40 is a popular low-cost small form (DFN) sensor that comprises a temperature sensor (thermistor) and a humidity sensor (capacitive). Together, they can produce temperature and relative humidity data.
- The SHT40 is manufactured by Sensirion, a global company with headquarters in Swiss.
- This chip exists in two versions: SHT40- AD1B and SHT40-BD1B. The only difference is the fixed I2C address (0x44 and 0x45, respectfully). The current design only uses one version: SHT40-AD1B-R2.
- This chip operates on a 3.3V voltage supply, which is created from the main supply (5V) with the AP2112K-3.3TRG1 chip.
- The SHT40 tolerates 100%RH and condensation on its surface, although it can accelerate sensor aging. It should not be immersed in water.
- The manufacturer specification regarding accuracy of the SHT40 chip is:
  - Temperature: 0 to +70°C @ ±0.2°C
  - Humidity: 10 to 90%RH @ ±2.0%
- The humidity accuracy is reduced to ± 3.0% in the range extreme (below 10%RH, above 90%RH). However, this level of accuracy remains sufficient to the requirements of the World Meteorological Organization.
- Conformal coating can be applied to the PCB but not directly on the SHT40 chip, as it can cause sensor obstruction and damage.
- Also, the SHT40 chip does NOT tolerate the isopropyl alcohol rinse. Therefore, the board is assembled via No-Clean flux only.

CORE SENSOR - OPERATION MODES

- The SHT40 has three measurement durations: low (1.3 ms), medium (3.7 ms), high (6.9 ms). The repeatability of the measurement increases with duration. With the RDL code, the default is high duration mode (i.e. SHT4X_HIGH_PRECISION).
- The SHT40 also has an internal heater for multiple reasons: removing condensations, sprayed water, and avoid drifting in long term measurements. Application notes on the topic by Sensirion are available.
- The maximum current pulled by the chip heater is 75mA (high level heating).
- At startup, the SHT40 chip is activated in heating by the RDL code. This helps eliminate any potential condensation that might have occurred on the sensor surface. This can be deactivated in the source code. In the seconds that follow the heating, the data output is invalid. There are three levels of heating (low, medium, high). The length can also be modified (1 sec or 100 ms). The heating level and duration can be modified in the source code.
- These options, when combined, give 6 heating options, in addition to the no heating mode:
  - sht4.setHeater(SHT4X_NO_HEATER);
  - sht4.setHeater(SHT4X_HIGH_HEATER_1S);
  - sht4.setHeater(SHT4X_HIGH_HEATER_100MS);
  - sht4.setHeater(SHT4X_MED_HEATER_1S);
  - sht4.setHeater(SHT4X_MED_HEATER_100MS);
  - sht4.setHeater(SHT4X_LOW_HEATER_1S);
  - sht4.setHeater(SHT4X_LOW_HEATER_100MS);

PRINTED CIRCUIT BOARD

- For accurate measurements, the SHT40 is meant to be installed inside a radiation shield.
- The board has been dimensioned to fit inside the UWO 3D printed shield. An OS paper about the design and performance of this shield is available for free \[ref\ https://www.appropedia.org/Design_and_Implementation_of_3-D_Printed_Radiation_Shields_for_Environmental_Sensors].
- There is a M3 hole in each corner of the board. A fifth hole, centered, allows the installation inside the radiation shield.
- There is a board cutout in the middle of the board to improve air circulation around the chip.
- Like other RDL sensor boards, there is a RJ45 connector, with the usual pin order.
- There is a male header 2.54mm spacing giving quick access to some important pins: 5V, 3.3V, GND, SDA, SCL.

LEVEL SHIFTING

- Level shifting is required to allow a 5V I2C bus to speak with a 3.3V I2C chip.
- The principle of operation involves using the BSS138 MOSFET to isolate the lower voltage side from the higher voltage side when the line is high, but allowing both sides to connect when the line is low.

OTHER

- A LED is added to the PCB to indicate that the sensor is powered ON.

COMMENTS

1) Can SHT40 chip survive the isopropyl alcohol washing bath? NO!!! Absolutely not. It will cause permanent damage (drift). No alcohol, no scotch tape (except 3M tape 92 polyimide), and no non-viscous conformal coating. It prescribes no-clean solder paste. I am not even sure I can use my normal solder (flux core).
For more information about how to process SHT40, please refer to: [2] Sensirion, "Handling Instructions for Humidity Sensors," 2020.


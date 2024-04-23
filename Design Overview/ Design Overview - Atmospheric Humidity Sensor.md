**Atmospheric Humidity Sensor (SHT4X Revision A3) - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
Documentation license: CC-BY-SA.  

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.  

**Table of Contents**

1. [GENERAL](#general)
2. [APPLICABLE TO THE RDL SUITE](#applicable-to-the-rdl-suite)
3. [CORE SENSOR - SHT4X CHIP](#core-sensor---SHT4X-chip)
4. [CORE SENSOR - OPERATION MODES](#core-sensor---operation-modes)
5. [PRINTED CIRCUIT BOARD](#printed-circuit-board)
6. [LEVEL SHIFTING](#level-shifting)
7. [OTHER](#other)
8. [REFERENCES](#references)


## CORE SENSOR - SHT4X CHIP

- The SHT4X is a popular series of low-cost small form (DFN) sensor that comprises a temperature sensor (thermistor type) and a humidity sensor (capacitive type). Together, they can produce temperature and relative humidity data.
- The SHT4X is manufactured by Sensirion, a global company with headquarters in Switzerland.
- While this chip exists in multiple versions and generations (SHT40, SHT41, etc.), the Jericho design only uses one version: SHT41I-AD1B-R2 which has a single fixed I2C address (0x44).

  ## Sensor accuracy

- The manufacturer specification regarding accuracy of the SHT41I-AD1B-R2 chip is:
  - Temperature: -40 to +80°C @ ±0.3°C (±2σ accuracy)[1]
  - Humidity: 0 to 100%RH @ ±2.0% (±2σ accuracy)  
- These accuracies meet the requirements of the World Meteorological Organization (±3% max).

- The SHT41I tolerates 100%RH and condensation on its surface, although it can accelerate sensor aging. It should not be immersed in water.

<figure>
<p align="center">
  <img src="../Design Overview/images/img2-sensirion-sht41I-temp.JPG"
  style="width:70%;">
    </p>
</figure>
<p align="center"> Excerpt no.1 from the Sensirion SHT41I Specification Sheet.

<figure>
  <p align="center">
    <img src="../Design Overview/images/img1-sensirion-sht41I-relhum.JPG" style="width:70%;">
  </p>
</figure>
<p align="center"> Excerpt no.2 from the Sensirion SHT41I Specification Sheet.

- In the Sensirion accuracy curves, the typical and maximal accuracy are defined as such:
  - TYPICAL: The accuracy distribution of the ensemble up to μ±2σ is targeted to fit within the typical accuracy limits.[3]  
  - MAXIMAL: The accuracy distribution of the ensemble up to μ±4σ is targeted to fit within the typical accuracy limits.[3]  

- Conformal coating can be applied to the PCB but not directly on the SHT4X chip, as it can cause sensor obstruction and damage. If needed, a polyimide adhesive tape must be used to cover the SHT4X as regular tape (e.g. Scotch tape) can contaminate the sensor [2].
- The SHT4X chip does NOT tolerate rosin flux, nor isopropyl alcohol rinse. Therefore, the board is assembled via No-Clean flux only.

## CORE SENSOR - OPERATION

- The sensor is pre-calibrated at the Sensirion factory and does not require any calibration from Jericho or the final user.
- The SHT4X has three measurement durations: low (1.3 ms), medium (3.7 ms), high (6.9 ms). The repeatability of the measurement increases with duration. With the RDL code, the default is high duration mode (i.e. SHT4X_HIGH_PRECISION).
- The SHT4X also has an internal heater for multiple reasons: removing condensations, sprayed water, and avoid drifting in long term measurements. Application notes on the topic by Sensirion are available.
- The maximum current pulled by the chip heater is 75mA (high level heating).
- At startup, the SHT4X chip is activated in heating by the RDL code. This helps eliminate any potential condensation that might have occurred on the sensor surface. This can be deactivated in the source code. In the seconds that follow the heating, the data output is invalid. There are three levels of heating (low, medium, high). The length can also be modified (1 sec or 100 ms). The heating level and duration can be modified in the source code.
- These options, when combined, give 6 heating options, in addition to the no heating mode:
  - sht4.setHeater(SHT4X_NO_HEATER);
  - sht4.setHeater(SHT4X_HIGH_HEATER_1S)(Jericho default);
  - sht4.setHeater(SHT4X_HIGH_HEATER_100MS);
  - sht4.setHeater(SHT4X_MED_HEATER_1S);
  - sht4.setHeater(SHT4X_MED_HEATER_100MS);
  - sht4.setHeater(SHT4X_LOW_HEATER_1S);
  - sht4.setHeater(SHT4X_LOW_HEATER_100MS);

## PRINTED CIRCUIT BOARD DESIGN

- For accurate outdoor measurements, the SHT4X board is meant to be installed inside a radiation shield. A centered hole allows the installation inside the radiation shield.
- The board has been dimensioned to fit inside the UWO 3D printed shield. An OS paper about the design and performance of this shield is available [5]
- There is a M3 hole in each corner of the board. 
- There is a board cutout in the middle of the board to improve air circulation around the chip [4].
- Like other RDL sensor boards, there is a RJ45 connector, with the standard Jericho pin order.
- There is a male header 2.54mm spacing giving quick access to some important pins: 5V, 3.3V, GND, SDA, SCL.
- A LED is added to the PCB to indicate that the sensor is powered ON.
- The chip operates on a 3.3V voltage supply, which is created from the main supply (5V) with the AP2112K-3.3TRG1 chip. The 3.3V design was mandatory when Jericho used the SHT40 chip, but has become optional with the SHT41 generation which can operate at 5V. The decision was made to continue operating at 3.3V for two reasons:  
  1) Keep the flexibility to go back to SHT40 if sourcing problems appear;
  2) The 3.3V buck converter provides a steady supply at the SHT4X contrary to the raw 5V power line, ensuring the SHT4X operates in the best possible conditions.  

  ## LEVEL SHIFTING

- Level shifting is required to allow a 5V I2C bus to speak with a 3.3V I2C chip.
- The principle of operation involves using the BSS138 MOSFET to isolate the lower voltage side from the higher voltage side when the line is high, but allowing both sides to connect when the line is low.

## REFERENCES

[1] Sensirion Datasheet SHT4xI-Analog, Sensirion, 2023.
https://sensirion.com/media/documents/74DC2069/655379E3/Sensirion_Datasheet_SHT4xI-analog.pdf  
[2] Handling Instructions For SHTxx Humidity and Temperature Sensors, Sensirion, 2020.  https://www.sensirion.com/media/documents/6D95AA80/6374D8C1/Sensirion_Handling_Instructions_SHTxx.pdf  
[3] Sensor Specification Statement and Testing Guide, Sensirion: Understanding and testing the specifications of RHT sensors, Application Note, 2021. https://sensirion.com/media/documents/13FA5FD4/6163F845/Sensirion_AppNotes_Sensors_Specification_Statement.pdf  
[4] SHTxx and STSxx Design Guide: How to design-in a humidity and temperature sensor, Sensirion, 2022. https://sensirion.com/media/documents/FC5BED84/61644655/Sensirion_Temperature_Sensors_Design_Guide_V1.pdf  
[5] J.S. Botero-Valencia, M. Mejia-Herrera, Joshua M. Pearce, Design and Implementation of 3-D Printed Radiation Shields for Environmental Sensors, FAST research group, 2022 https://www.appropedia.org/Design_and_Implementation_of_3-D_Printed_Radiation_Shields_for_Environmental_Sensors    

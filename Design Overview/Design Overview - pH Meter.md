**pH Meter Carrier Board Revision A1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  

SAFETY WARNING: Always protect your skin and eyes when working with chemical products such as acids and bases.

WARNING: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

WARNING: Do not let the pH probe dry. When not in use, store the probe in KCL solution, not water. Do not let pH probe wire leads touch each other; a short circuit will damage the probe.

WARNING: Please read all documentation provided by Atlas Scientific about its EZO-pH, industrial probe before using the product. See references at the end of this document. This expensive equipment can be easily damaged if not used properly.

# Table of Contents

1. [GENERAL](#general)
2. [SOIL MEASUREMENTS](#soil-measurements)
3. [DESIGN GENESIS](#design-genesis)
4. [PROBE](#probe)
5. [PH METER CIRCUIT (EZO-pH by Atlas)](#ph-meter-circuit-ezo-ph-by-atlas)
6. [ANALOG ISOLATOR CIRCUIT](#analog-isolator-circuit)
7. [I2C COMMUNICATION](#i2c-communication)
8. [CALIBRATION OVERVIEW](#calibration-overview)
9. [OTHER](#other)
10. [REFERENCES](#references)

## GENERAL

- The pH meter system described in this document is modular: it is comprised of:
1) a Carrier board, designed by Jericho, 
2) a EZO-pH device, which must be inserted in the female header of the Carrier board.
Together, when connected to the RDL (Resistance Data Logger), they form a reliable pH meter.
- The EZO-pH has a polarity when inserted in the carrier. The drawing on the silkscreen helps the user remember the correct polarity. Powering on a system with an inverted polarity can damage the components. With the wrong polarity, the EZO-pH power LED will not light up.
- Note: The carrier board cannot make any measurement without the EZO-pH being inserted. The EZO-pH must be purchased from Jericho Lab or Scientific Atlas directly.
- The Carrier Board Design is entirely based on the public schematic shared by Atlas Scientific. The PDF schematic was recreated with the open-source software KiCAD, with some modifications and components substitution for improved functionality, availability and/or cost. A PCB layout was subsequently made for production with KiCAD as well.
- pH measurement are among the most common, yet the most difficult measurements. It has wide applications in chemical engineering, pharmaceuticals, laboratory experiments, environmental monitoring, swimming pools, aquariums, hydroponics, fish farming.
- The PCB components have not been tested at low temperature because the pH electrode cannot operate below freezing temperature. The water solution would freeze and expand and break.
- The design was made to be compatible with soil pH measurements and the RDL system.

## SOIL MEASUREMENTS

- Typical pH measurements target solutions, but this design was done with soil measurements in mind. Soil measurements are very useful in the context of agriculture. The user must make sure that the soil is excessively dry, which is why it should remain at a sufficient depth.
-  In the absence of aqueous solutions, the probe membrane will dehydrate and can be permanently damaged. In the event that the probe has dried up, a rehydration can be attempted by leaving the membrane in KCl solution (storage solution) at least 12 hours. 
- Soil mesurements can have variations and might provide inaccurate values in periods where the soil is becoming too dry for a sufficient contact with the membrane. ontrarely to river measuremets, where organic matters will rapidly accumulate through the passage of thousands of liters of water, the probe should not need frequent calibrations, being in relatively static environment.
- The intent of designing for soil measurements explains the choice of an industrial grade pH probe, which has two advantages:
  - an oversized solution reservoir (it will extend the life expectancy of a probe put in an environment that accelerates the consumption of the solution through the membrane)
  - a membrane with an improved resistance to harsh environments (e.g. sand, rocks)
- In the advent that the user is not planning to use the probe in soils, the user could select the other models - more affordable by Atlas, or any other traditional pH electrode. 

## DESIGN GENESIS

- There are very few reliable open-source designs to start from when designing a ph meter. 
  - The digital pH meter from Atlas could not be used as inspiration (US Patent 9571121B2, with equivalents in Canada, Japan, Great Britain, South Korea and WIPO). 
  - The analog pH meter from Atlas could not be used for the same reason (US Patent not found).
  - The DFRobot design could not be used because it appears to copy the one by Atlas Scientific - there is a trademark lawsuit between the US and Chinese companies. Although the trademark does not concern the schematic, it does raise concerns over intellectual property.

It was therefore decided to start with an open-source carrier board for the proprietary EZO-PH and keep the development of the core ph meter PCB for later.
- The goal of creating our own isolation board was to:
  - provide an integrated solution, with RJ45, 
  - provide a ready-to-modify, ready-to-build schematic and PCB layout, which Atlas did not provide.
  - Add a voltage regulator circuit for improved performance in situations where the 5V power supply cannot be guaranteed.
  - Remove the ability to turn off the EZO-pH, which was not useful in a multiplexed context.

## PROBE

- The pH meter revA1 must be used with a traditional pH electrode (combination silver-glass probe). Jericho has mostly experimented with and recommends the industrial probe, generation 3 by Atlas Scientific.
- The use of a shielded cable can be beneficial to the signal integrity of the probe. Cables are generally pre-assembled with the probe, and many will be shielded. In the case of the Atlas Industrial pH probe, the cable is NOT shielded.
- Electrical potentials produced by pH probe are very weak, and for example, one probe could have a range of -200 to +200mV. To limit the possible electrical interference, the cable length between the probe and the meter must be limited to a few meters. The cable provided by Atlas is 3m.
- The PCB connects to the probe via screw terminals (2 pins). If the selected pH probe has a connector (e.g. BNC, SMA), it can be cut or a standard adapter can be added.
- The pH probe wires have a polarity: black wire for ground (GND) and a copper wire for the probe signal (PRB). Make sure to respect this polarity when connecting the probe to the carrier board.
- When not in use, always protect either one of the probe wire leads with silicone tape. This will avoid any short circuit inside the probe, which would damage the probe.

## PH METER CIRCUIT (EZO-pH by Atlas)

- The pH meter subcircuit is the core of the device. It transforms raw electric potential from the probe into an analog signal, measurable by a data logger.
- Traditionally, the main components of a pH meter are an operational amplifier (op amp) and an instrumentation amplifier, but very little is known about the hardware and software of the EZO-pH device. The compiled code is kept in the EZO-pH processor and the user can interact with it via UART or I2C commands.
- Neither the pH meter hardware, nor software, include probe temperature compensation, since the error effect is very small (0.001 pH/°C) compared with the accuracy of the circuit (+/- 0.1 pH). Temperature does affects the pH of all solutions, but it is a real and separate phenomenon that must be captured by the probe.
- For its EZO-pH device, Atlas advertizes a +/- 0.002 pH accuracy, which appears unrealistic outside perfect laboratory environments. Jericho assumes the nominal accuracy of the pH meter in most environments to be no better than +/- 0.1 pH.

## ANALOG ISOLATOR CIRCUIT

- The main components of the Jericho analog isolator are:
  - an isolated power supply (B0505S).
  - a digital signal isolation circuit (ISO1540)
  - a voltage regulation circuit (TPS630701)

- The PCB has a measurement circuit and an isolator circuit. The signal isolator definition is an electrical device which is used to remove any earth loop (also called ground loop) errors which are caused by noise & signal interference problems. The isolator circuit ensures that the measurement is not biased by the nearby electrical fields, such as the one from a conductivity probe or a pump. The effect is more significant in a solution, but can also happen in soil.
- The analog isolator can use a 3.3V or 5.0V power supply. For standardization with the RDL platform, the 5V is selected. A voltage regulator circuit is added to improve the accuracy of the pH meter, since it is sensitive to the power supply fluctuations. It is the same circuit than the Jericho current sensor board. It operates in PFM mode with 1% accuracy on its 5V nominal value. For more information, read the NAU7802 design overview.


## I2C COMMUNICATION

- The EZO-pH can communicate via UART (i.e. Rx/Tx) or I2C protocols.
- By default, Atlas devices ships their EZO-PH in UART mode, which is simpler.
- Jericho ships their EZO-pH by default in I2C mode, to make it compatible with the RDL. EZO-PH is given a default I2C address of 99.
- There are two methods to change the active communication protocol: hardware or software.
  - The hardware methods requires connecting a jumper in between specific pins of the EZO-PH PCB.
  - The software methods consists in sending a UART command ("i2c,99) to switch to I2C, or a I2C command ("baud,9600") to switch to UART.
- Jericho uses the software method and provides two Arduino script to do so - one for each protocol. These are adaptation of public scripts by Atlas.


## CALIBRATION OVERVIEW

- For detailed instructions about the pH meter calibration please refer to the Jericho calibration procedure available on Github.
- For pH measurements, the calibration is done with three buffer solutions that cover a large range of values. The three-point calibration is required because the response of the pH probe is not perfectly linear. The default pH values are 4, 7, 10 for pre-mixed liquid buffer solution. For powders, the pH values most often seen are 4.01, 6.86, 9.18. These powders are mixed with distilled water before use. Buffer powders have different pH values because they do not use the same chemicals. The limited range of the buffer solutions means that accuracy outside this range is unknown. The powders are generally more economic, more practical for transportation and more available. Their accuracy is judged sufficient (+/- 0.01 pH @ 25°C). Once mixed with water however, they have a limited shelf-life (hours to days). 
- The solution temperature must be known at calibration time. And the reference value must be adjusted in the code. For example, if the solution temperature is X Celcius, the nominal pH value of 4.01 is 4.05, and this value must be entered in the code as the reference value for the middle point. 
- The calibration procedure is convenient since the buffer solutions are relatively low risk, with pH values ranging from 4 (vinegar) to 10 (baking soda).
- The calibration results are registered inside the memory of the EZO-pH. There is no interaction with the RDL code. The calibration being specific to a given probe, each EZO-pH and probe form a pair that must not be undone. Otherwise, the calibration must be redone.

## OTHER

- There is no Power LED on the pH Carrier board, only the EZO-pH will indicate that it is powered on.

## REFERENCES

EZO-pH pH meter by Atlas Scientific,
https://atlas-scientific.com/embedded-solutions/ezo-ph-circuit/ 

EZO-pH pH meter by Atlas Scientific (Datasheet),
https://files.atlas-scientific.com/pH_EZO_Datasheet.pdf 

Industrial pH probe, gen 3, no temperature by Atlas Scientific
https://atlas-scientific.com/probes/industrial-gen3-ph-probe-nt/

Electrically Isolated EZO Carrier Board by Atlas Scientific
https://atlas-scientific.com/carrier-boards/electrically-isolated-ezo-carrier-board-gen-2/


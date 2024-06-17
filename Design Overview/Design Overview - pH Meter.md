**pH Meter Revision A1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  
 
WIP – FIRST PASS. MULTIPLE BLANKS. LOTS TO VERIFY. STILL UNCLEAR PICK.

(Temporary note: Go through the ‘Done’ category of the Project Management to find relevant ideas)

(Temporary note: This design is still at the drawing stage; the PCB has not been manufactured.)

Warning: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

**Table of Contents**


  1. [GENERAL](#general)
  2. [NOTES APPLICABLE TO THE RDL SUITE](#notes-applicable-to-the-rdl-suite)
  3. [DESIGN GENESIS AND LICENSES](#design-genesis-and-licenses)
  4. [PROBE](#probe)
  5. [PH METER CIRCUIT](#ph-meter-circuit)
  6. [ANALOG ISOLATOR CIRCUIT](#analog-isolator-circuit)
  7. [I2C COMMUNICATION](#i2c-communication)
  8. [CALIBRATION](#calibration)
  9. [STEP-BY-STEP CALIBRATION PROCEDURE (DRAFT)](#step-by-step-calibration-procedure-draft)
  10. [OTHER](#other)
  11. [COMMENTS](#comments)


## GENERAL

- This document refers to the pH meter system associated with the Jericho pH Meter PCB revision A1.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.
- In the context of this document, a “long cable” is defined as a maximum of twenty (20) meters.
- pH measurements are among the most common, yet the most difficult measurements. It has wide applications in chemical engineering, pharmaceuticals, laboratory experiments, environmental monitoring, swimming pools, aquariums, hydroponics, fish farming.
- The PCB components have not need to be tested at low temperature because by its nature the pH electrode cannot go below freezing. The water solution would freeze and expand and break.
- Typical pH measurements target solutions, but this design was done with soil measurements in mind.
- The design is made to be compatible with the RDL code. The pH measurement of the RDL code use the OS (?) library XXXX by XXXXX.

## NOTES APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on Github. This includes KiCAD project files, Gerber files, BoM and CPL (Component Position Placement) files.
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

## DESIGN GENESIS AND LICENSES

- The Analog Isolator circuit is based on the non-patented design by Atlas Scientific.
- The digital pH meter from Atlas could not be used as inspiration (US Patent 9571121B2, with equivalents in Canada, Japan, Great Britain, South Korea and WIPO). The theoretical basis for the Jericho pH meter is therefore XXXXXXX.
- The analog pH meter from Atlas could not be used for the same reason (US Patent not found yet).
- The DFRobot design could not be used because it ressembles the one by Atlas Scientific (there is a lawsuit between the US and Chinese company)
- The Atlas pH meter EZO could have been used, although over the project budget, but being an I2C sensor, it would have forced the addition of supplementary I2C channels on the I2C shield.
- The original design of the voltage regulation circuit was done by XXX under the CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- Most libraries required to make the RDL suite run are open-source.

## PROBE

- The pH meter revA1 must be used with a traditional pH electrode (combination silver-glass probe). Jericho recommends the industrial probe by Atlas Scientific.
- The use of a shielded cable can be beneficial to the signal integrity of the probe. Cables are generally pre-assembled with the probe, and many will be shielded. In the case of the Atlas Industrial pH probe, the cable is NOT shielded (verify).
- Electrical potentials produced by pH probe are very weak, and for example, one probe could have a range of -200 to +200mV. To limit the possible electrical interference, the cable length between the probe and the meter must be limited to 1-2 meter (verify).
- The PCB connects to the probe via screw terminals (2 pins). If the selected pH probe has a connector (e.g. BNC, SMA), it can be cut or a standard adapter can be added.
- The pH probe wires have a polarity. The black wire is XXX and the copper wire is XXX.
- Why is there a hole beneath the white tape of the pH probe cover? To let pressure out? Air was compressed when screwing the cap. Water leaked out and the next day the cap did not leak.

## PH METER CIRCUIT

- The pH meter subcircuit is the core of the device. It transforms raw electric potential from the probe into an analog signal, measurable by a data logger.
- The main components of a pH meter are an operational amplifier (op amp) and instrumentation amplifier and XXXXX.
- The pH meter circuit requires XX to XXV to function properly. This is compatible with the analog isolator, when the latter is combined with a voltage regulator circuit (verify).
- Analog Isolator, the PWM output from the original design was not kept, since PWM signals do not survive well long cables.
- The pH meter circuit, nor the code, do not include probe temperature compensation, since the effect is too small (0.001 pH/°C) compared with the accuracy of the circuit (+/- 0.2). Temperature affects the pH of all solutions, but it is a real and separate phenomenon that must be captured by the probe.
- The nominal accuracy of the pH meter is +/- 0.2, which meets the design requirements (verify latest TRS).
- The measurement signal output is expressed as a 0-3V signal, which is to be measured by one of the analog channels of the RDL. With the default values, 0.265V means a pH of 14 and 2.745V means a pH of 0.
- The equation for pH conversion from voltage is pH = (-5.6548 \* voltage) + 15.509 (Atlas equation for analog meter).

## ANALOG ISOLATOR CIRCUIT

- The main components of an analog isolator are XXXXXX.
- The PCB has a measurement circuit and an isolator circuit. The signal isolator definition is an electrical device which is used to remove **earth loop** (also called ground loop) errors which are caused by noise & signal interference problems. The isolator circuit ensures that the measurement is not biased by the nearby electrical fields, such as the one from a conductivity probe or a pump. The effect is more significant in a solution, but can also happen in soil.
- The analog isolator requires a 3.3V or 5.0V power supply. For standardization reasons, the 5V is selected. A voltage regulator circuit is added to improve the accuracy of the pH meter, since it is sensitive to the power supply fluctuations. It is the same circuit than the Jericho current sensor board. It operates in PFM mode with 1% accuracy on its 5V nominal value. For more information, consult the design overview for the current sensor.

## I2C COMMUNICATION

- The circuit has a secondary mean of communication, via the digital I2C protocol. This offers an alternative in environments that are too high in EM noise for accurate transmission via a 0-5V analog signal. The final choice between the two means depends on user preference, as well as the available channels. In some installations, the RDL shields might not have a I2C channel left empty.
- The NAU7802 is a 24-bit ADC chip that measures the 0-5V signal produced by the analog circuit. The Sparkfun NAU7802 library is used by the RDL code to decode the signal. It is basically the same strategy than the strain sensor.
- When the I2C communication is chosen, the RJ45 connector must be used, along with a CAT cable.
- A second RJ45 connectors is present to allow daisy chaining.

## CALIBRATION

- For pH measurements, the calibration is done with three buffer solutions that cover a large range of values. The three-point calibration is required because the response of the pH probe is not perfectly linear. The default pH values are 4, 7, 10 for pre-mixed liquid buffer solution. For powders, the pH values most often seen are 4.01, 6.86, 9.18. These powders are mixed with distilled water before use. Buffer powders have different pH values because they do not use the same chemicals. The limited range of the buffer solutions means that accuracy outside this range is unknown. The powders are generally more economic, more practical for transportation and more available. Their accuracy is sufficient (+/- 0.01 pH @ 25C) (Solution temperature must be known at calibration time. And the reference value must be adjusted in the code. For example, if the temperature is 21C, the pH is XXX, and this value must be entered in the code as the reference value for the middle point.). Once mixed with water however, they have a limited shelf-life (how much??). For these reasons, the powder values are the default one in the code.
- The calibration procedure is convenient since the pH solution are low risk, ranging between vinegar and baking soda pH.
- There is a possibility to modify the reference values to accommodate different buffer solution values.
- The calibration does not affect the pH meter itself, but the post-treatment of the raw data only. The pH meter only produces voltages, which are then transformed into pH values.
- How long can we conserve pH buffer solutions? Does it different from powder to liquid to home made?
- Since the output of the pH meter analog isolator is 0-3V, the NAU7802 is set to a reduced range. This in turns increases digital resolution for the 0-3V range. This is great solution for the I2C protocol but the 0-3V makes it hard to achieve target accuracy with the analog channel.
- It is not recommended to use the analog and digital communication simultaneously. Only one type of cable should be connected.
- The NAU7802 must also be calibrated (see strain sensor design overview).

## STEP-BY-STEP CALIBRATION PROCEDURE (DRAFT)

- Required material: Buy the buffer solution powder and room temperature distilled water.
- Verify that the powder is the right values. Otherwise, the regression table will not be accurate.
- Clean four glassware jars. With lid. Clean with soapy water. Rinse.
- Pour 250mL of distilled water into each of the four jars.
- Let each of the three powder

## OTHER

- A LED is added to the PCB to indicate that the sensor is powered ON.

## COMMENTS

1) I really think we are coming back to an I2C EZO-pH based system. See paper scribings.

* If I switch back to the EZO pH, do I have enough I2C channels in all installation to accommodate the required pH meters? And if not, what if we consider daisy chains?
ANSWER: Yes, we can use EZO pH, because we have in all the installations with pH measurement, we have at least 4 empty I2C channels on the I2C shield. Without even using daisy chaining.

2) Explain the choice for the INDUSTRIAL probe (larger reservoirs).

Explain the reasoning behind soil measurement. How is it possible? What are some limitations about installations. Why should you calibrate each season not every week , like in river.

3) Do I want to use DFRobot library? Or the Atlas library? Which is open-source? Did DFRobot steal from Atlas for its library too? Which is more convenient?

4) Switching to an I2C pH is STILL a possibility, if we make use of daisy chain. Double check required.

5) What if we add a NAU7802 chip to the pH meter board? (This chip is a high-accuracy voltage measurement device. It includes a 24-bit ADC and has I2C communication capabilities. )
We can add it in parallel, maybe?
Do I already have a Sparkfun nau7802 board?

6) Now that I am more familiar with the pH EZO, it seems to me we will not integrate the calibration routine into the main RDL code. It is not necessary for now. We can simply temporarily connect the EZO-PH to the main RJ45 of the RDL and upload the Atlas sample code, and send the calibration commands in the serial command window. This code will be in the Github repo. Also, the main_RDL must not use the same EEPROM addresses as the calibration data values storage.

7) No it doesn’t meet. I promised 0.1. (Verified in TRS Nov 30). I think I could rather easily negotiate 0.2C. I would have to bet on repeatability (which is probably much better than 0.2C) and find open source articles that use a 0.2C uncertainty or worse.

8) What is the shelf life of the powders themselves?
Do I avoid the problem of the two-years expiration date of the liquid buffers, incompatible with a 5 yr project?


­JL- P3.2 – Warm Bath Reference Procedure
========================================

Disclaimer: Jericho Laboratory is not responsible for any damage or your safety if you attempt to reproduce this procedure. DO NOT move a vessel filled with fluid. Underneath the lid, Coleman Co. indicates that the jug model 6009 should not be used for hot liquids. Use this jug at your own risk. We advise that you find an alternative product that is designed for hot liquids.

**Technical description**

This procedure allows the creation of a reference temperature for a liquid bath between 35 and 40 °C, with an accuracy of +/- 0.2 °C. This procedure is part of the three-point calibration process for the RDL device. It can be replicated by the user to verify the calibration of probes. The procedure makes uses of a waterproof (IP67) ovulation thermometer (BIOS 16C2). Other brands, such as Fairhaven Health, could possibly work as well, with some verifications.

This procedure is not based on any standard procedure, but it is inspired by the NIST documentation (“Room Temperature Verification”) and ASTM E2488-09 (Standard Guide for the Preparation and Evaluation of Liquid Baths Used for Temperature Calibration by Comparison).

An ovulation thermometer is normally used to monitor the body temperature of women in order to characterize their ovary cycle and enhance pregnancy likelihood. Due to its medical use, the ovulation thermometer is a reliable product, with high resolution (0.01 °C) and good accuracy (+/- 0.1 °C) in a limited temperature range (34 to 42 °C). As the analog-to-digital (ADC) converter is being applied to a narrow range of temperatures, the uncertainty related to numeric conversion is reduced. This is one of the reasons why such a highly accurate thermometer can be acquired at a low price. Being mass produced and consumer grade, these types of thermometers are affordable (around $15-30) and can easily be found in drugstores around the globe.

The overall logic of the procedure is to use the highly-precise ovulation thermometer as a reference thermometer within a liquid bath. The system is not thermally static: it is slowly cooling towards room temperature (exponential curve). However, it can be linearized if we consider a very small section of the curve (<0.1 °C). The water temperature will have changed slightly between the reference measurement and the probe measurement. To compensate that effect, a second reference reading is done at the end \[NIST\]. The two reference readings are averaged to form the final reference value. The final measurement value for the uncalibrated probe is an average of the 30 measurements sequence. This is illustrated in Figure 1, where a set of only 2 (not 30) measurements is considered. One downside of this technique is that, since the reference thermometer is used two times, the instrument uncertainty must be considered twice. For more information, please consider reading about uncertainty propagation. This is why this procedure can provide a reference point with an uncertainty of +/- 0.2 °C.

<figure>
  <p align="center">
    <img src="../Calibration Procedures/images/WARMBATH1.png>
      </p>
</figure>

Figure Main events in the measurement sequence for the warm bath calibration procedure

**Required material**

- 1x Insulated vessel with a lid, non-transparent, with at least a 300 mm in height and 70 mm in diameter.
  - Jericho uses: Coleman jug, model 6009, 1/2 gallon (1.9 L).
- 1x Ovulation thermometer,
  - Jericho uses: BIOS model 16C2
- Custom 3D-printed probe holder
- 1 to 10 temperature probes, uncalibrated, e.g., thermistors.
- Tap water (at least 2L)

**Procedure**

1. Read the instructions of your thermometer.
2. Test your data logger. Make sure that the resistance values are printed out.
3. Start recording the resistance values from the thermistors at 1s interval indefinitely.
4. Clean all equipment with some soapy water. Rinse once with tap water.
5. Position all the uncalibrated probes in the apparatus.
6. Position the apparatus inside the vessel. The wires should go through the lid opening. All probes, including the reference thermometer, should be positioned at the same depth.
7. Fill the vessel with warm water from the sink, leaving space for the lid. The water should be 42-43 °C. You can verify the temperature with your ovulation thermometer.
8. To reduce thermal leaks through the lead wire, we recommend keeping as much lead wire inside the cavity as possible.
9. Put the lid on the vessel for 10 min. This will allow the inner volume to reach spatial thermal equilibrium as much as possible – although the whole system is slowly cooling down towards room temperature. To verify the thermal gradient within the working space, a second identical reference thermometer can be used simultaneously at various locations.
10. Wait until the water temperature cools down to 38 -39°C, which is the most accurate range of this type of thermometer (i.e., body temperature)
11. Open the vessel lid.
12. Measure the water temperature a first time with the reference thermometer. You will hear the beeping sound through the water when it has finished. The BIOS thermometer will retain the highest temperature registered. Do not stir the water during the measurements, as this will increase heat losses, hence uncertainty.
13. Read the final value from the BIOS thermometer (e.g., 37.21 °C) and write it down. This is value “BIOS1”. Also, write down the time displayed by the RDL, to the exact second.
14. Wait around ten seconds then take a second reading from the reference thermometer.
15. Read the temperature registered by the thermometer (e.g., 37.15 °C) and write it down. This is value “BIOS2”. Also, write down the time displayed by the RDL, to the exact second.
16. Calculate the arithmetic average of BIOS1 and BIOS2. (e.g., (37.21 + 37.15)/2 = 37.18 °C). This value is the reference temperature for the procedure.
17. Save all the data from the data logger to a text file. With as spreadsheet, determine the average resistance value of each probe in the period between BIOS1 and BIOS2.
18. Keep your calibration logs for future consultations. Record keeping is an essential component of any calibration program.

**Comments**

1. A non-insulated vessel will give less accurate results due to a less homogeneous bath temperature.
2. Make sure that no bare metal from the probe wire is exposed to water. The electric conductivity would induce an error in the resistance value measured.
3. In theory, the bath could be replaced by an electrically heated bath, equipped with a thermostat. The magnitude and impact of the thermal fluctuations should be evaluated however.
4. If you do not have access to our 3D printed apparatus, you can try to approximate the procedure with a substitute. For example, you could tie the probes and the reference thermometer to a plastic ruler. However, we cannot guarantee the accuracy of such modified procedure.
5. It is not necessary to use distilled water or gloves for this procedure since potential impurities will not affect the temperature evolution of the medium.
6. The thermistor must be immersed deeply enough to avoid perturbation of the temperature by radiation or thermal conduction along the electrical wires. This is why this procedure has a significant water column above the probe.
7. The Joule effect bias is reduced by taking a 100 microseconds measurement \[4\] every 1 second (0.01% of the

time). For a 10 kOhm thermistor connected to a 3.3V tension divider, the average dissipated power is 0.01

microwatts. This value is negligible compared to other sources of error, and is therefore not taken into

account.

1. It is possible to test more than one probe at the same time. However, this will increase the thermal leak through the wires, and could reduce the accuracy and stability of the ice bath temperature. We recommend separating as much as possible the probes from each other. The same should apply to wires. We also suggest using smaller wires to reduce the thermal leak magnitude. Calibrating multiple probes at the same time can increase the time required to stabilize the temperature reading.
2. The test vessel should not be made of glass. Otherwise, the probe could absorb some radiant energy in the visible spectrum. This would bias the temperature measurement.
3. It is normal that during measurements, the probe temperature will oscillate. This is the reason why we average.
4. For even more precision, a plastic structure could be inserted to reduce the convection within the column of liquid, leaving a hole in the center for the probes.
5. Many beverage jugs, such as the Coleman 6009, do not have an insulated lid. This causes an increased overall heat loss as well as increase natural convection, since the cooling occurs on top of the liquid column. To reduce these effects, we add a layer of closed cell foam insulation above the water column.
6. Calibration procedures are delicate procedures and it may take a few tries before you master the procedure. If you are unsure of the results, the procedure should be repeated to see if, at least, you get consistent results.
7. To avoid the ‘stem effect’ during calibration, the company Fluke suggests an immersion depth of 20 times the sum of the probe diameter and the probe length.
8. Extension wires should be as short as possible to minimize the effect of electromagnetic noise.

Electromagnetic noise from the environment should also be minimized. We therefore recommend that the

user does not extend the lead wires during the calibration procedures. All noise filters should also be

disconnected.

Figure Warm bath 3D-printed accessory (thermal equalizing block)

Thermometer BIOS 16C2 specifications  
Storage temperature: -25℃ to +55℃/ 15% to 95% HR  
Operating environment: 10℃ to 40℃/15% to 95% HR  
Measurement Range: 32.00°C to 42.99°C  
Measurement Accuracy: +/- 0.1°C between 34°C and 42°C  
Smallest Display Unit: 0.01°C  
Memory: Stores last measurement  
Battery lifetime: approx. 4500 measurements  
Expected service life: 5 years  
Reference to Standards: IEC 60601-1-11 (Part 1 of norm 60601, edition 2011)

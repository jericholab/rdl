JL- P1.5 - Ice Bath Procedure
=============================

Disclaimer: Jericho Laboratory is not responsible for any damage or your safety if you attempt to reproduce this procedure or any other procedure shared by Jericho Laboratory. DO NOT move a vessel filled with fluid.

Introduction:

The ice bath is the most commonly used fixed point temperature. This procedure will typically produce a reference point of 0.00°C +/- 0.01°C (95% confidence interval) at 101 325 Pa \[NIST reference here\]. This procedure is used to calibrate each of our probes as part of a three-point calibration. It can be replicated by the user to verify the calibration. In order to let the ice solidify and the water cool, this procedure is usually takes two days.

The procedure makes use of a 3D printed accessory designed by Jericho Lab, called the probe holder. The design of the accessory is freely available on our website under the MIT open source license. The accessory can also be purchased from us. The accessory provides a solid and symmetric positionning of up to 16 probes. It is designed to respect the NIST guidelines regarding the minimal distances between the probe and the vessel surfaces. This makes sure that the probe is really exposed to the ice point. Through it mass, the accessory also provides some thermal inertia, hence reducing the fluctuations of the temperature readings during the procedure.

Required material:

- Insulated vessel with an insulated lid, with at least a 300 mm in height and 70 mm in diameter (e.g. beverage cooler)
- Jericho’s probe holder (open-Source 3D printed accessory) (see Figure 3)
- Uncalibrated temperature probe (e.g. Jericho TH-2 probe)
- Distilled water of purity equivalent or better than ASTM Specification D1193
- 1 kg of very small ice cube with maximum size of 1.5 cm, made with distilled water
- Plastic bottle with a cap (500 mL)
- Plastic rod to stir the ice bath
- Powder-free clean plastic gloves
- Tap water

Possibly required:

- Freezer (typically -18°C (0°F)) (to produce ice cubes)
- Refrigerator (typically 4°C (39°F)) (to keep the water cold overnight)
- Ice cube tray, with maximum cube size of 1.5cm (see Figure 2 for an example)
- Aluminum foil sheet of 30 cm (if the vessel has no lid).

Procedure:

Day 1

1. Wash all the equipment (i.e. vessel, lid, trays, rod, apparatus, and probes) with soapy water and rinse three times with tap water, then rinse one time with distilled water.
2. Prepare 500 mL of distilled water chilled to near 0°C in a clean plastic bottle (e.g. refrigerator).
3. Fill the ice cube trays with distilled water, and then put the tray in the freezer.

Day 2

1. Put on the plastic gloves.
2. Connect all the uncalibrated probes to the data logger and activate your RDL data logger. Make sure that the printing of the resistance values is activated. These values will be the basis of the calibration calculations.
3. Position each probe in the probe holder. Weight should be added to the probe holder to avoid floating as the plastic accessory is less dense than water. This can be done with 2-3 bolts tied to the probe holder legs.
4. Position the probe holder in the bottom of the empty vessel.
5. Gently fill the vessel with ice cubes.
6. Shake vigorously the chilled water for 1 minute to aerate, and then add some of the water to the vessel. Leave 1 to 1.5 inch of space at the top with only ice cubes.
7. Ice cube levels should remain one inch above water level at all times during the experiment. If the level is lower than that, add more ice cubes at the top.
8. Stir slowly the water for one minute with the plastic rod. Make sure to not hit the probe holder.
9. To reduce thermal leaks through the lead wire, we recommend keeping as much lead wire inside the cavity as possible – beneath the insulation layer. This will reduce the influence of the room temperature on the probe.
10. Cover the ice bath with an opaque and thermally insulating cover. If this is not possible, at least aluminum foil.
11. Let the water-ice mixture sit for thirty (30) minutes. This allows the ice and water to reach the thermal equilibrium (i.e. 0°C).
12. Once the values are stable (plateau), record 60 values (electrical resistances \[ohms\]) at an interval of 1 sec. Average those values. See Figure 4 for an example of data set.

Comments:

1. According to the NIST, the probe should be at a minimum depth of 20 cm to reduce the amplitude of the thermal leak from the electric wire. The probe must remain at least 5 cm from the bottom and 2 cm from the side walls at all time. See Figure 1 for more details. The probe must sit for one (1) minute before the measurements. This last requirement is easily fulfilled by the procedure since the probes are already in the water during the 30-minutes equilibrium period.
2. A non-insulated vessel gives the same temperature point with less accuracy due to a less homogeneous bath temperature. An insulated vessel also lasts longer (a few hours).
3. Demineralized water can also be used, instead of distilled water.
4. Make sure that no bare metal wire is exposed to water.
5. Do not reuse the gloves for a second experiment.
6. Using city tap water instead of using distilled water will typically give an ice-point of (-0.01°C) to (-0.02°C), depending on the water quality in your area (ASTM-E563-11(2016)). Impurities usually lower the melting point.
7. Slow stirring during measurement increases homogeneity and reduces uncertainty.
8. The effect of barometric pressure on the pure ice point is −74 nK/Pa (−7.5mK/atm). With saturated air in solution, the effect is increased to approximately -0.1 μK/Pa (-10 mK/atm) (ASTM E563-11(2016)). Due to the small magnitude of the effect, the phenomenon is not considered in the procedure.
9. The thermistor must be immersed deeply enough to avoid perturbation of the temperature by radiation or thermal conduction along the electrical wire.
10. Ice coming out of a regular freezer usually has a temperature around -18°C. Hence, time is required for the ice to reach thermal equilibrium with liquid water (0°C).
11. The Joule effect bias is reduced by taking a 100 microseconds measurement \[4\] every 1 second (0.01% of the time). For a 10 kOhm thermistor connected to 3.3V tension divider, the average dissipated power is 0.01 microwatts. This value is negligible compared to other sources of error, and is therefore not taken into account.
12. Testing several probes simultaneously will increase the thermal leak through the wires, and could reduce the accuracy and stability of the ice bath temperature. We recommend separating as much as possible the probes from each other. The same should apply to wires. This was taken into account in the design of the Jericho Probe Holder. We also suggest using smaller wires to reduce the thermal leak magnitude. Calibrating multiple probes at the same time can increase the time required to stabilize the temperature reading.
13. Extension wires should be as short as possible to minimize the effect of electromagnetic noise. Electromagnetic noise from the environment should also be minimized. We therefore recommend that the user does not extend the lead wires during the calibrations procedures. All noise filters should also be disconnected.
14. The test vessel should not be made of glass. Glass is not transparent to the infrared spectrum, but it is transparent to the visible spectrum. Hence, the probe could absorb some radiant energy in the visible spectrum. This energy gain would bias the temperature measurement.
15. The use of larger ice cubes would create a less uniform temperature bath, which is a source of error. The ice cubes will also tend to melt together more easily due to the larger amount of latent energy available to solidify the water in between the cubes.
16. It is normal that during measurements, the probe temperature will fluctuate slightly (see Figure 4). At least two phenomena are involved. First, the temperature equilibrium is not perfect since it is the microscopic temperature differences combined with Brownian movement that drives the phase change. Second, it is possible that the resistance value of the probe falls in between two values on the ADC, due to its limited accuracy. Both electrical and thermal fluctuations will make the reading oscillate between the two values. These two phenomena are dealt with by averaging the data over a sufficient time period.
17. The overall accuracy of a calibrated sensor depends on the accuracy of the reference point but also on the accuracy of the measurement device used for the calibration procedure.
18. The extension wires should be as short as possible to minimize the noise (electromagnetic induction). Electromagnetic noise emanating from the environment should also be minimized, if possible. The use of RC filter is also recommended.
19. If you have insufficient quantities of small cubes, the impact of using larger cubes can be minimized by using small cubes in the bottom of the vessel and larger cubes at the top, further away from the probes. In such a scenario however, the accuracy of the bath could be lower.
20. During the measurements, one option is to let the probe still. Alternatively, some users will keep stiring slowly to make sure that all the water and the ice come into intimate contact. Stir in the center region, avoiding the sides, the top and the bottom, where the temperature is different due to heat losses.
21. If you were to replicate the procedure using shaved ice made of distilled water, the uncertainty would be 0.002°C (ASTM E563-11 (2016)).

References:

1. ASTM E563-11 (2016) Standard Practice for Preparation and Use of an Ice-Point Bath as a Reference Temperature.
2. ASTM Specification D1193 Standard Specification for Reagent Water.
3. NIST, User-Friendly Guidance on the Replacement of Mercury Thermometers, 2010
4. <www.arduino.cc/en/Reference/AnalogRead>

Pictures:
<figure>
<p align="center">
  <img src="../Calibration Procedures/images/ICEBATH1.png" 
    </p>
</figure>
    
<p align="center">Figure 1 Schematic of the distance requirements for the ice bath procedure.


<figure>
<p align="center">
  <img src="../Calibration Procedures/images/ICEBATH2.png" 
    </p>
</figure>
<p align="center"> Figure Example of a silicon mold for small ice cubes


<figure>
<p align="center">
  <img src="../Calibration Procedures/images/ICEBATH3.png" 
    </p>
</figure>

<p align="center">Figure Jericho probe holder for cold ice bath




<figure>
<p align="center">
  <img src="../Calibration Procedures/images/ICEBATH4.png" 
    </p>
</figure>
<p align="center">Figure Typical data for a measurement period of 30  
seconds in an ice bath with a probe holder for 8 probes.

**************************

COMMENTS
1) see ASTM norms taken from ETS here

D:\GDRIVE\Jericho-Lab\12_Litterature\Norms & Standards

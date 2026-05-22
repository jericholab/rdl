JL- P4.0 - pH Probe Calibration Procedure
=============================
Copyright: Jericho Laboratory Inc.  
Document license: CC-BY-NC-SA

**WARNING**: Jericho Laboratory is not responsible for any damage or your safety if you attempt to reproduce this procedure or any other procedure shared by Jericho Laboratory.

**WARNING**: Be careful when manipulating acids and bases. Wear proper protection equipment according to your legislation.

**Table of Contents**

1. [Introduction](#introduction)
2. [Required Material](#required-material)
3. [Introduction to Buffer Solutions](#introduction-to-buffer-solutions)
4. [Procedure](#procedure)
5. [Notes](#notes)
6. [Useful Commands Summary Table](#useful-commands-summary-table)
7. [Others](#others)
8. [References](#references)


**Introduction**
- This is a 3-point calibration. pH meter are quite linear but not perfectly so, hence a 3-point calibration is required (3 reference solutions).
- The procedure is compatible with the Atlas Industrial Probe Gen3 and Jericho pH meter (which incorporates pH-EZO PCB).
- Atlas Scientific provide their own calibration procedure and documentation. This procedure is complementary to theirs. The user is encouraged to read the Atlas procedure which is found in their specification sheet [1].
- The EZO-PH device is ISO 10523 complient (determination of pH) [2]. The Jericho carrier is not certified.
- The EZO-PH is patented, while the Jericho carrier is open-source.
- The calibration results are stored on the EZO-PH internal memory. The procedure requires access to a computer.
- The calibration is specific to each probe. Since the calibration parameters are internally stored in a closed source code, the calibration has to be done with the final pair to be deployed on site.
- The EZO-PH can operate in two modes of communication: UART or I2C. When you receive the material from Jericho, it is already in I2C mode. However, if you buy an EZO-PH directly from Atlas, it will be into UART mode by default. The UART mode has a green light, while the I2C mode has a blue light on.
- Despite using the probe for soil measurements, you can only calibrate the probe with solutions.
- Another related procedure is the drift test. See section below. A drift test with tap water is the most severe drift test.
- The recalibration interval depends on several factors, such as:
  1. Probe quality
  2. Total Dissolved Solids (TDS) in the solution
  3. Accumulation of debris and organic matter on the membrane surface

**Required material**
- pH probe, uncalibrated, any brand
    - Used: Atlas pH meter probe, Industrial Gen 2 or 3
- EZO PH by Atlas Scientific
- pH carrier board revA1
- RDL revE4
- CAT cable (1-2m)
- 4 beakers or mixing vessels with at least 300mL capacity
- Solutions powder kit (low, medium, high)
    - low value: 4.01 (close to lemon)
    - medium value: 6.86 (close to water)
    - high value: 9.18 (close to baking soda)
- 2L of distilled water or deiodized water
- Protection equipment (gloves, eyewear, clothing)
- Computer with Arduino IDE installed and internet access
- Specialized Arduino program (I2C Example)

**Introduction to buffer solutions**  

- A buffer solution is a water-based solution which has a capacity to maintain its nominal pH value, despite the addition of small quantities of acid or base.
- A buffer solution can be pre-mixed or made from powder+water.
- This procedure uses powders instead of pre-mixed solutions for a few reasons:  
  1. more affordable
  2. easier to store and transport
  3. the accuracy of liquid, pre-mixed solutions is excessive compared with the target accuracy of the system
- While there are various online sellers of buffer powders, the products are often the same. It is not recommended to buy buffer products with too many decimals.
- An example of high-quality buffer solution is Omega calibration solution. It has an accuracy of +/-0.01 pH [1]. Low-cost online venders on Amazon claim the same accuracy but this is untested by Jericho Lab. To play safe, we consider the accuracy of these products to be no better than +/- 0.05 pH.
- The shelf life of buffer solutions varies.
- Storage methods vary depending on format (powder vs liquid). Well, do not freeze and do not expose to sun.
- Note that accurate pH meter measurements and calibrations are known to be difficult.
- The shelf life of pre-mixed solution varies but is usually around 3 years.
- The cost is about $1 per pouch ($3 per kit).


<figure>
<p align="center">
  <img src="../Calibration Procedures/images/ph1.jpg" 
    </p>
</figure>
<p align="center">Example of a pH buffer solution powder kit sold on online platforms

**Calibration Procedure**

Day 1

1. Wash all the equipment (i.e. vessel, lid, trays, rod, apparatus, and probes) with soapy water and rinse three times with tap water, then rinse one time with distilled water.
2. Properly identify each buffer solution with a label. Also identify the rinse pot.
3. Pour 250 mL of distilled water in each beaker.
4. Empty the content of each pouch (3) into a beaker. Note that the quantity of powder in each beaker varies.
5. Mix each beaker until most of the powder is dissolved. 
6. Cover the beakers and let rest overnight. The solutions must be used within 24h. The solutions can be kept accurate for some time, but not too long.

Day 2

7. The three solutions should be at room temperature. Measure the temperature of the solutions. Look at the temperature table provided with the buffer solutions to determine the exact pH of the solution.
7.  Connect all the uncalibrated probes to the data logger and activate your RDL data logger. 
8. Load the specialized program onto the RDL.
9. The program will start reading once per second.
9. Let the reading stabilize. Do not exceed one hour when letting the probe adjust to buffer solution.

10. Once the reading is stable, enter the command to modify the reference point in the EZO-pH memory. For example, if you were using the 9.18 pH solution, enter into the serial terminal "'Cal, High'" and follow instructions.
11. Clean the probe in distilled water between each buffer solution.
12. Repeat the other two buffer solutions.
12. To demonstrate repeatability, you should do the calibration twice. The second result should fall within +/- 0.1pH of the target value.


**Notes**
- The measurement accuracy outside the buffer solutions values range is unknown. If you are interested in extreme values (i.e. below 4 and above 10), you will need different buffer solutions.
- Tap water cannot be used for calibrations since the impurities can interac with the buffer chemicals.
- Tap water cannot be used instead of the neutral buffer (7.01) since it has no buffer capabilities. Therefore, any contamination from the previous buffer (a trace left on the probe after rinse) will affect significantly the reading.
- The time required for the probe to reach equilibrium will vary according to the probe (some probes have a less porous membrane) and the ionic strength of a given buffer solution. A less porous membrane may slow down the diffusion of ions into the electrode, thereby extending the time needed to stabilize the reading.
- It takes practice to master the skill of calibration.

**Useful commands sommary table**

- 'R'
- 'Cal, High'
- 'Cal, Low'  
- 'Cal, Med'  

**Others**  

If you have doubts on the accuracy of the reference powders, high-quality pre-mixed solutions can be purchases from Atlas Scientific.

**Reference**   

[1] Atlas Scientific EZO PH Specsheet, pdf. https://files.atlas-scientific.com/pH_EZO_Datasheet.pdf

[2] Pre-mixed pH Calibration Solutions, Omega, https://mx.omega.com/pptst_eng/PHA4_7_10.html
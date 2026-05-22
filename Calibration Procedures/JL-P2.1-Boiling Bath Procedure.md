JL-P2.1 - Boiling Bath (Steam Point) Procedure
=================================
by Jericho Lab

This procedure will produce a steam point close to 100°C (212°F). The exact temperature depends on the atmospheric pressure. The steam point is used to ensure that the temperature measurement reflects the properties of steam rather than the liquid water, as steam provides a more stable reference temperature under constant pressure conditions. Liquid water might be superheated or subject to other thermal phenomena.

The procedure is based on  NIST Special Publication 250-23 (1988) as well as more recent comments from the NIST. This point is also referred as the “steam point”. This method can achieve an uncertainty of 0.1°C (0.2°F) at a 95 % confidence level. The procedure is part of our three-point calibration. The procedure can be replicated by the user to verify the calibration of the system over time.

**WARNING**: This procedure uses boiling water and generates hot steam. DO NOT move a vessel filled with fluid. Protect yourself from burns and scalding. Jericho Laboratory Inc. is not responsible for any damage or your safety if you attempt to reproduce this procedure.

**Required material**

- Stainless steel pot (minimum dimensions: 20 cm dia. x 20 cm (8 x 8 inches))
- One aluminum plate (minimum bottom dimension: 18 cm diameter (7 inches))
- Scissors
- Tap water
- Clean thermistor probe with wire
- Plastic stick
- Third-hand or clothes clamp
- Hot plate (heat source)

**Procedure**

1. Connect all the uncalibrated probes to the data logger and activate your RDL data logger. Make sure that the printing of the resistance values is activated. These values will be the basis of the calibration calculations.
2. Wash the pot and the probe with soapy water and rinse three times with tap water.
3. Attach the probe on the plastic stick and hold the plastic stick with the third-hand.
4. Using the scissors create a hole in the aluminum plate, large enough for the stick.
5. Fill the pot with 10 cm (4 in.) of clean tap water.
6. Put the aluminum lid on and bring water to a strong boil.
7. Once the water boils, lower the heat but boiling should remain strong during measurements.
8. Insert the probe into the pot. The probe should be 2 cm above the water level \[NIST\]. There should be 10 to 15cm (4 to 6 in.) of the thermometer/wire immersed in the space where the steam collects.
9. Determine the atmospheric pressure (barometric pressure) at your position. Be as precise as possible (ex: 1013 hPa). If you use data from a local weather station, the station should be as close as possible from your location and be less than one (1) hour old. For example, the weather station in Montreal (airport) is 13 km from the Jericho lab, a relatively small distance as far as atmospheric pressure is concerned.
10. The probe must be exposed to five (5) minutes of rolling boil before taking measurements \[NIST\].
11. Measure the electrical resistance every second for 30 seconds, one time per second. See Figure 1 for a typical curve.
12. Data treatment: Calculate the atmospheric pressure and average the 30 data points.
13. NIST: The uncertainty of the elevation limits the uncertainty of the steam point. Using the steam point calculator, you can achieve an uncertainty of 0.1 °C (0.2 °F) at a 95 % confidence level. The steam point equation is given by the NIST Excel sheet referenced at the end of this document. Pressure must be between 97.0 and 104.0 kPa for the equation to be valid.
14. Keep your calibration logs for future consultations. Record keeping is an essential component of any calibration program.
15. Calibration procedures are delicate procedures and it may take a few tries before mastering the procedure. If you are unsure of the results, the procedure should be repeated to see if, at least, you get consistent results.
16. To avoid the ‘stem effect’ during calibration, the Fluke company suggests an immersion depth of 20 times the sum of the probe diameter and the probe length.




 <figure>
  <p align="center">
   <img src="../Calibration Procedures/images/JL1.png" style="width:70%"
  </p>
 </figure>
 <p align="center"> Typical data for a measurement period of 30 seconds in a boiling bath with a probe holder for 8 probes.

<p align="center"> 
 Table 1 Frequent values as per the NIST Excel sheet.
 
<figure>
 <p align="center">
   <img src="../Calibration Procedures/images/JL2.png" Style="width:70%"
 </p>
</figure>


**Comments**

1. The lid is absolutely necessary to get accurate results. The steam accumulates within the pot and creates a slight positive pressure. This way no cold surrounding air enters the pot.
2. The NIST recommends using a pot that is at least 8 inch deep.
3. Be careful that no bare metal from the probe is exposed to the steam. It could cause a measurement error by electrical conductivity.
4. To reduce thermal leaks through the lead wire, we recommend keeping as much lead wire inside the cavity as possible.
5. Our data comes from the Montreal Airport, which is at the same altitude as the laboratory. There is therefore no need to correct for altitude. If you reproduce this procedure, you might have to account for elevation (ex: United States Geological Survey website). The building height is taken into account (see calibration certificate for an example).
6. You might need a few tries to figure out what level of heat will maintain a rolling boil. Do not remove the lid during the measurements.
7. There is no need to use distilled water. The steam produced is in itself a small distillation process. For the same reason, gloves are not necessary.
8. At the interface where the water meets the steam, the temperature should theoretically be the same, as both the water and the steam are at the boiling point under given atmospheric conditions. However, placing the probe above the water level ensures that it measures the temperature of the steam exclusively, without the potential interference or variability that might occur if the probe were to touch the water. This method provides a more controlled environment to accurately gauge the steam's temperature.
9. To find recent atmospheric pressure data near you, we suggest the National Weather Service website (USA) or Environment Canada (Canada). NIST recommends using data that is at maximum one hour old.
10. When using a thermistor probe, the Joule effect bias is reduced by taking a 1 mS measurement every 1 second.
11. The overall accuracy of a calibrated sensor depends on the accuracy of the reference point but also on the accuracy of the measurement device used for the calibration procedure. In our lab, the resistance value is measured with the 16-bit accuracy of the ADS1115 (RDL). If you reproduce this experiment at home with the native 10-bit ADC of the RDL, the accuracy of procedure will be lower.
12. It is possible to test more than one probe at the same time. However, this will increase the thermal leak through the wires, and could reduce the accuracy and stability of the ice bath temperature. We recommend separating as much as possible the probes from each other. The same should apply to wires. We also suggest using smaller wires to reduce the thermal leak magnitude. Calibrating multiple probes at the same time can increase the time required to stabilize the temperature reading.
13. The extension wires should be as short as possible to minimize the noise (electromagnetic induction). Electromagnetic noise emanating from the environment should also be minimized, if possible.

**References**  
Certain commercial equipment, instruments or materials are identified in this paper in order to adequately specify the experimental procedure. 

- NIST Special Publication 250-23 (1988)  
https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication250-23.pdf  
- NIST, User-Friendly Guidance on the Replacement of Mercury Thermometers, 2010  https://www.epa.gov/sites/default/files/2015-10/documents/nistuserfriendlyguide.pdf
- Natural Resources Canada (Canada weather data)  
<https://weather.gc.ca/past_conditions/index_e.html?station=yul>
- National Weather Service (USA weather data)  
<https://www.weather.gov/>
- NIST Procedure for steam point:  
<https://www.nist.gov/pml/mercury-thermometer-alternatives/mercury-thermometer-alternatives-verification-methods>




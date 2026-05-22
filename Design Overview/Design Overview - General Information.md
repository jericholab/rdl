**RDL SUITE - GENERAL INFORMATION**
=======================================

**Copyright:** Jericho Laboratory Inc.  
**Documentation License:** CC-BY-SA  

**Warning:** This material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

### Introduction
This document provides general information applicable to all PCB designs (sensors, data loggers, shields) within the RDL suite unless specified otherwise.

### General Design Information
- All boards are 2-layer PCBs with lead-free-HASL and SMD components on the top surface only.
- Copper planes (ground) are on the bottom surface to reduce EM noise.
- Default PCB trace width is 0.25mm for normal traces and 0.5mm for power traces (VCC, GND). 
- Board design are done with KiCAD 7.0 and above.
- Board routing done mostly with Freerouting and some manual traces in KiCAD. Freerouting is used in stand-alone mode (Java package).
- All designs are available on GitHub, including KiCAD project files, Gerber files, BoM, and Component Position Placement files.
- Libraries required for the RDL suite are generally open-source.
- The sensors are designed to support cable lengths up to 30 meters for both CAT cables and two-conductor cables.
- Aimed at optimizing design and cost for JLCPCB's manufacturing capabilities. Efforts were made to use Standard parts (no assembly fee) instead of Extended Parts.

### PCB Manufacturing and Assembly Information

- PCB manufacturing is done at JLCPCB, a low-cost Chinese company.
- Most boards include Surface Mount (SMD) and Through-Hole components. SMD components are soldered via an automated process, while Through-Hole components are placed by hand and soldered with a wave soldering machine.
- Final quality control is done in Canada by Jericho.
- No-rinse flux is used and there is no cleaning done after the soldering.

### RJ45 Connectors

- For RJ45 connectors, the Jericho standard pin order is:  
1- VCC  
2- VCC  
3- GND  
4- GND  
5- SDA  
6- SDA  
7- SCL  
8- SCL  

- Since CAT cables with the 568A/B wiring standard are twisted in pairs (1-2, 3-6, 4-5, 7-8), there is some shielding of the SDA line with the GND line. The SCL line is not protected however (being twisted on itself), so there is improvement potential.

### Silica Gel Bag

- To avoid high humidity in enclosures, it recommended to add one or more silica gel bags in each enclosure. This is especially recommended for enclosure that have multiple cables per cable gland and/or enclosures that have sensitive electronics (e.g. main hub).
- Multiple brands are available worldwide. The ability to see a color change with humidity saturation is an important feature.
- Silica gel bags are replenishable via heat following instructions provided by manufacturer.

### References

- JLCPCB. http://jlcpcb.com
- Freerouting. https://freerouting.org


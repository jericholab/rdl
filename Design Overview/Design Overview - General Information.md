**GENERAL**


GENERAL
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- The original design of the voltage regulation circuit was done by Sparkfun under CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.
- The allowable wire gauges for the PCB screw terminals are AWG 20-26.
- For this product, a “long wire” is defined as 30 m. The device was designed with a target of 30m wire. This applies for both CAT cables and ordinary two-conductor cables.

NOTES APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on Github. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.
- Design and cost have been partially optimized for JLCPCB manufacturing abilities and components pricing at the time of design, for small batches.
- Unless stated otherwise, all libraries required to make the RDL suite run are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.
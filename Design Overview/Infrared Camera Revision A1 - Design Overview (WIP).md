**Infrared Camera Revision A1 - Design Overview (WIP)**  
Copyright: Jericho Laboratory Inc. License: CC-BY-SA-4.0.  
Revision: 1.  

Warning: The following material is for educational purposes only. Always refer to the most recent schematic and PCB layout files associated with your product version.

Safety warning: It is imperative to avoid inhalation of germanium dust due to its potential health hazards. Therefore, meticulous care is required during the handling of these optical components. The utilization of protective gloves is strongly recommended to minimize direct contact. Additionally, adherence to standard operating procedures, including thorough handwashing post-handling, is essential to ensure safety.

GENERAL

- This document refers to the Resistance Data Logger (RDL) system associated with the Jericho RDL PCB revision E2.
- While great efforts have been put into affordability, the IR camera remains the most expensive sensor in the RDL suite. This is partly due to its high-tech nature, but one limiting factor was the high requirements of the WIRED project (i.e. radiometric capability, high resolution). An ultra-low-cost alternative could be the MLX90640 ($C100). However, its image resolution (24x32 pixels) would be of limited use in the context of solar panel monitoring, for example.
- The IR camera board hardware is released under the CC-BY-SA-4.0 open-source license.
- The current board revision only works with the corresponding source code version.
- For the IR camera, a “long” wire or cable is defined as 22m.
- Since October 2023, the objective of maintaining at least 50% of the product cost (material and labor) has been abandoned. This was a requirement for the ‘Made in Canada’ label, which appeared contrary to the goal of maximizing affordability and access. Therefore, an increased number of manufacturing operations are outsourced in China.
- Long wires (>10m) between the RDL and its sensors will cause significant voltage loss. This means that some devices will require a voltage regulator at the other end to make sure that the chip is supplied with the proper voltage.

NOTES APPLICABLE TO THE RDL SUITE

- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.
- The complete PCB design, ready for production, is available on GitHub. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.
- Unless stated otherwise, all libraries required to run the RDL suite are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.
- Generally speaking, most key components of the RDL suite have their datasheet on the Jericho GitHub (e.g. chips).

THERMAL CAMERA MODULE

- To our knowledge, there is no open-source infrared (IR) camera hardware available on the market, as of writing this document. The decision was therefore taken to integrate as best as possible a proprietary device into the open-source framework.
- The main component of the IR module is the C214SPX camera core. It is a long-wave infrared (LWIR) uncooled vanadium oxide microbolometer with a 4.0mm fixed chalcogenide lens, 12µm pixel pitch and a 200 X 150 pixels resolution. Chalcogenide is a class of cost-effective glass that can be molded instead of machined. The pixel pitch describes the pixel density on the camera sensor surface. The higher the density, the more compact the camera core for a given resolution.
- In a micro bolometer, each pixel's electrical signal corresponds to the amount of infrared radiation it has absorbed, which is directly related to the temperature of the part of the scene that pixel is viewing. The surface of each pixel is vanadium oxide, chosen for its highly temperature-dependent electrical resistance.
- This core is manufactured in the U.S. by Seek Thermal Inc., a private U.S. company. It was selected in part due to its open-source python wrapper, that allows easier integration in an open-source project. The SDK (Software Development Kit) is available with Linux, Windows and Mac, allowing operation on the Pi. This was also a decision factor.
- Chalcogenide lenses are more affordable than crystalline lens/windows (e.g. germanium) due to their molding manufacturing process instead of machining. The chalcogenide lens has an anti-reflective (AR) coating with an optimal transmittivity in XXX-XXX um range
- The C214SPX cameras are sold as transition kits. A transition kit is a 10-units pack sold to customers who want to have a small-scale production with improved pricing compared to the Starter Kit, which is sold individually.
- The camera module consists of:
  - a camera core;
  - a camera bracket, 3D printed;
  - a coprocessor (also called an interface board);
  - a USB-C adapter;
  - a support PCB for components integration and auxiliary functions;
  - a weatherproof protective window;
  - a 2W? polyimide film heater;
  - thermal insulation
  - Two USB-over-CAT adapter;
  - a long CAT cable.
- The coprocessor transforms the raw data from the sensor (core). The image processing includes applying algorithms for noise reduction, image enhancement, scaling, or applying color palettes. It can be configured to output different formats (RGB, thermographic array). Whether a camera can produce both RGB and thermographic outputs simultaneously for a single frame would depend on the specific capabilities and configuration of its processing hardware and software.
- Seek manufactures the camera core, the coprocessor and the USB-C adapter. The support PCB is manufactured by Jericho, who also does the general assembly and final quality control.
- The camera core takes pictures, which are then pre-processed by the coprocessor. The USB-C adapter makes it possible to connect the USB-C cable. The Seek Starter Kit (S214SPX) also contains a USB-C connector but this connector is deemed more fragile than the USB-C adapter. Hence, the manufacturer does not recommend permanent setup using the Starter Kit.
- One limitation of the thermal camera is that accuracy is only known when the body camera is 25°C. This is a common limitation of thermal cameras. Accuracy and resolution will decrease as the camera temperature gets further away from this ideal temperature. Systematic tests remain to be done to evaluate accuracy at various body temperature. The simple case heater will limit the phenomenon at low temperature. A possible contingency is to retrofit an autonomous temperature-controlled Peltier heater (with on-board PID controller) inside the enclosure. This would enable hot and cold control.
- The camera magnetic shutter is noisy but not a problem according to discussions with the manufacturer. By default, the shutter action is left to automatic control. This gives a pseudo-random clicking sound, which is increased at startup, when the camera is heating up. The manufacturer has had very few shutter dysfunctions reported over the years.
- The shutter is used to perform what is known as Non-Uniformity Correction (NUC). By periodically closing the shutter, the camera can capture a uniform temperature image (as the shutter is a uniform temperature surface) and use this to calibrate and correct the pixel output.
- The shutter interrupts image capture process, which can be problematic for time sensitive operating like missile guidance thermal videos. However, with a low-speed system dedicated to periodic image capture, there is no added value in a shutterless camera.
- The SV1 filter is a new software option (in the SDK) which can be activated for improved image resolution. Its algorithm improves the image clarity, but its effect on the thermographic data is uncertain at this point.
- Thermographic data is the ability of some higher quality cameras to output arrays of temperature field, with units.
- Note that the field of view (FoV) is not equal in both axes, due to Seek design. The horizontal FoV (35 degrees) is larger than the vertical FoV (26 degrees).
- For more information about the software aspects of the thermal camera, consult the Software Architecture Documentation (SAD).

CUSTOM PCB

- The custom PCB has mostly mechanical functions. Its custom size and holes pattern allow to secure in place the camera core, the coprocessor, the USB-C adapter.
- The PCB size is optimized for the enclosure and is directly screwed into the enclosure pre-drilled holes.
- The camera modularity has the side-benefit of reducing repair cost.
- The heater takes its power supply from the PCB (5V).
- A LED is added to the PCB to indicate that the camera is powered.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.

USB-OVER-CAT ADAPTER

- USB cables are limited in the maximum length they can achieve without an active signal booster. This is due to the higher EM noise sensitivity, higher latency and higher power loss than CAT cables. Conversion from USB to CAT cable is one method to increase cable length. It retains the USB protocol but it removes the problems caused by the USB cable, while also actively maintaining voltage levels.
- This strategy requires two low-cost USB-over-CAT adapters, a transmitter and a receiver, with a CAT cable in between. A conversion is made at each end of the cable.
- This converter is designed for indoor use (not weatherproof) and must be installed in an enclosure.
- Its official rating temperature is 0C to 80°C. The adapter on the RDL side is less concerning, since it will be located in the heated main enclosure. The other adapter will be inside the IR camera enclosure, which will have a temperature around 0C. Jericho tested the adapter at -10°C. Despite the low risk of issues, Jericho will test the converter performance at -40°C in the near term.
- A product disassembly showed that the core component of the USB-over-CAT adapter is a chip with silkscreen inscriptions “CJS1037A AN9MRS.1” and “CJS1037A-D2”, for which no information was found online.
- The chip identity being unknown, the maximum current that can be drawn through the chip is unknown but should be assumed to be very limited. This will have to be tested, but we know that it can supply the thermal camera and its coprocessor (300mW) at the very least. This has implications for the IR camera heater. This might pose a limitation to the power available, which would require us to heat only the camera (not the casing volume) and/or add insulation. A more sophisticated solution would continuously heat the camera at 300mW with a pause each time the camera is turned on.
- The USB-over-CAT has a USB 1.0 rating, which is limited to 15 Mbps. This has not proven to be a problem with the IR camera in picture mode.
- Some users report a very short life (months) for some low-cost USB-over-CAT adapters. This will have to be tested and addresses, if necessary.

FLEX CABLES

- The data transmission inside the enclosure is done by two flexible cables:
  - Sensor flex
  - USB flex (in between the coprocessor and the USB-C adapter)
- These polyimide cables are delicate and should not be folded.
- The PCB, by fixing the components, minimizes movement and the mechanical stress on the flex cables.

THERMAL INSULATION

- Thermal insulation is added to the top and bottom surface of the enclosure. This reduces heat loss in the winter. Assuming a horizontal installation, the top insulation also reduces solar heat gain in the summer.

PROTECTIVE WINDOW

- For harsh environment like a multi-year permanent installation in the Canadian climate, the IR camera manufacturer recommends a supplementary protective window, despite the IP67 rating. The window must be made of material with high transmittivity in the light frequencies of interest. Since the Seek Thermal C214SPX has a detection range of 7.8 to 14 microns, there are only a few materials that can possibly meet the criteria: germanium, chalcogenide and zinc selenide (ZnSe). The manufacturer recommends a 17mm x 1mm lens. There needs to have a minimum diameter, to make sure that the field view is covered (when close enough to the camera). So 17mm or more. The thickness must be as small as possible to reduce the influence of the material, despite the fact that the transmittivity is high for both germanium and ZnSe.
- Germanium is non-toxic, while zinc selenide is mildly toxic.
- Both materials require an anti-reflection coating to transmit light effectively. The transmittivity being high but imperfect (>95%?), the signal loss has to be accounted for in the software.
- The difference between a window and a lens is the absence of focal point. A window is as flat as possible, having no converging/diverging effect.
- There are multiple germanium window suppliers such as ThorLabs, Sunny Optical, Lightpath, Rochester Precision Optics, Knight Optical. The germanium window cost per unit depends on window size, thickness and quantity ordered. The Seek manufacturer recommends a 17mm diameter, 1mm thick germanium window for long term operation in northern climates. This window can cost in the order of 130CAD. Cost is lower for a chalcogenide window.

CAMERA HEATER

- The camera core and the coprocessor do NOT have internal heaters. Like any electronics however, they do consume some amount of electric power, which ultimately is dissipated in the form of heat.
- While the camera can detect temperature surfaces from -40 to +330°C, the camera core can operate from -10°C to XXX. This means that the camera cannot operate on the complete range of weather in Canada. Therefore some heat must be applied.
- The heater type is a 3W (?) polyimide film heater. If the outdoor temperature is below 0°C, the heater is turned on. The heating power has been designed to prevent overheating.
- The heater takes its power from the PCB. The heater power must be limited to avoid drawing too much current on the USB-over-CAT converter.
- In order to optimize heat delivery, the heating film is installed directly on the custom PCB.
- The operating temperature range for the coprocessor is XXXXXXXC. (Is it different than the core? Is it specified?)
- The current consumed by the camera core and the coprocessor are XXXW and XXXW, respectively.

CALIBRATION

- The Seek Mosaic IR camera has automatic inner calibration of its bolometer array, via the shutter. This default operation is maintained. Shutter operation could be put into manual or completely suspended, but the absence of frequent NUC would eventually cause a drift in measured values. Continuous pointing directly at the sun would also have a severe aging effect on the corresponding array pixels.
- The default emissivity parameter is 0.97 (verify). This parameter (0.00 – 1.00) depends on each object and must be adjusted within the SBC Python program. Many daily surfaces have emissivity above 0.9.
- To determine the emissivity of the surface, comparison must be made between a reference thermometer on the object being filmed and the thermography data output for that location.
- Rain and heavy fog will interfere with the image quality of an infrared camera, because is not transparent to IR. Distance will also affect accuracy, since the accuracy is rated for objects at distance of 30cm.

3D PRINTED CAMERA CORE HOLDER

- The camera core holder is a replacement part for the metal holder from the Starter Kit (see image below).
- It is printed with PETG since it is close to humidity (enclosure opening).
- The holder eases the assembly and ensures that the camera core is parallel to the PCB and the enclosure bottom surface. This is a simple way to guarantee that a leveled enclosure will generate leveled images.

ENCLOSURE

- The camera enclosure is based on a low-cost ABS plastic rectangular enclosure. The enclosure is weatherproof, with a IP65 rating.
- Its role is to protect the electronic components, which have no conformal coating. The Seek manufacturer confirms that the board should tolerate both the silicone or acrylic conformal coating, when applied with a brush. Spray coating should not be used due to the risk of sending coating inside the critical components.
- The enclosure holds the protective window, with its sealant.
- An air gap must remain between the camera lens and the enclosure window. This reduces the heat transfer between the outdoor environment and the camera module.
- The drawing of the enclosure is available to ease installation and repair.
- The cable glands are on a single side only. This reduces exposition to water ingress.
- The enclosure should be positioned face up to avoid having all thermal pictures upside down or worse.
- Flexible closed-cell foam is used to help seal the cable gland gap around the cable(s).
- The camera core is aligned with the enclosure bottom with an accuracy of +/- 5deg. An adjustment is possible. We strongly encourage you to test the alignment of pictures before installation.
- The enclosure should NOT be painted as it will absorb too much heat in the summer. The white enclosure limits the heat absorption which will reduce the thermal camera accuracy above 25°C camera body.
- Condensation must be avoided on the thermal camera . (Rating is 10 to 90%HR). This is why the enclosure sealing is important, as it minimizes the humidity ingress. The residual humidity is absorbed by the silica gel bag inside. The gel change of colour tells the user when it is time to replenish the bag.
- The enclosure openings (cable gland, camera core) are drilled in the lab.

OTHER

- The Seek camera hardware is proprietary. This includes the camera core, the coprocessor, and the SDK kit. The Python wrapper provided by Seek Thermal is open-source, however (Apache license 2.0).
- The Software Development Kit (SDK) is a proprietary C/C++ software required to operate the thermal cameras. Despite the copyright, the Seek license gives the permission, free of charge, to use, copy, modify, sell the code examples. The SDK is pre-installed on the Pi computer.
- To help users who would like to add functionalities or troubleshoot something, the free Seek Developer Portal will give you access to: SDKs for app and software development, design documentation for easy integration, pre-built examples to get you up and running faster, access to Seek's developer support team, community forums to share ideas, instructional video tutorials.
- A future area of development is to manufacture the coprocessor, based on the design provided for free by Seek Thermal for customers who want a better product integration. This could reduce the overall cost.

REFERENCES
<figure>
<p align="center">
<img src="../Design Overview/images/1 <figure>
<p align="center">
<img src="../Design Overview/images/1 IR Camera RevA1.png" style="width:70%">
  </p>
</figure>
<p align="center">
*Figure 1. Copyright: Seek Thermal website
  </p>
</figure>

\[INSERT THERMAL CAMERA RGB PICTURE SAMPLE\]

<p align="center">
<img src="../Design Overview/images/2 IR Camera RevA1.png" style="width:70%">
  </p>
</figure>
<p align="center">
<p align="center">
<Figure . Figure 2 An example of Starter Kit (SPX214). Copyright Seek Thermal website
</p>


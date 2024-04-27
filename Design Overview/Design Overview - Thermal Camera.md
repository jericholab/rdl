**Thermal Camera Module Revision A2 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
Document License: CC-BY-SA-4.0.  
 

**Warning**: The following material is for educational purposes only. Always refer to the most recent schematic and PCB layout files associated with your product version.

**Safety warning**: It is imperative to avoid inhalation of germanium dust due to its potential health hazards. Therefore, meticulous care is required during the handling of these optical components. The utilization of protective gloves is strongly recommended to minimize direct contact. Additionally, adherence to standard operating procedures, including thorough handwashing post-handling, is essential to ensure safety.

# Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Thermal Camera Core (C214SPX)](#thermal-camera-core-c214spx)
4. [Camera Core Shutter](#camera-core-shutter)
5. [3D-Printed Camera Adapter (Rev A2)](#3d-printed-camera-adapter-rev-a2)
6. [USB-over-CAT Adapter](#usb-over-cat-adapter)
7. [Flex Cables](#flex-cables)
8. [Custom PCB](#custom-pcb)
9. [3D Printed Camera Core Holder](#3d-printed-camera-core-holder)
10. [Protective Window](#protective-window)
11. [Enclosure](#enclosure)
12. [Calibration](#calibration)
13. [Heater (Work-in-Development)](#heater-work-in-development)
14. [Other](#other)
15. [References](#references)
16. [Comments](#comments)


## INTRODUCTION

- The Jericho Thermal Camera Module consists of:
  - a Seek C214SPX camera core;
  - a Seek coprocessor (also called an interface board);
  - a 3D-printed camera adapter;
  - a USB-C adapter;
  - a support PCB for components integration and auxiliary functions;
  - a weatherproof protective germanium window (optional);
  - 2x USB-over-CAT adapter;
  - a CAT cable (variable length).
  - a ABS enclosure
  - a silica gel bag 

## PREREQUISITES

- Raspberry Pi, pre-configured with:
  - Seek SDK Kit
  - Jericho Python Scripts
  - 1 free USB port
- RDL RevE4 with thermistor(s) (optional, required for emissivity calibration)

*Note: The thermal camera operation is independent from the RDL.

## THERMAL CAMERA CORE (C214SPX)


<figure>
<p align="center">
<img src="../Design Overview/images/1 IR Camera RevA1.png" style="width:70%">
  </p>
<p align="center">
Exploded view of the core and the interface board kit (Copyright Seek Thermal)
  </p>
</figure>

- To our knowledge, there is no open-source thermal camera hardware available on the market, as of writing this document. The decision was therefore taken to integrate as best as possible a proprietary device into an open-source framework. 
- The main component of the IR module is the C214SPX camera core, manufactured in the U.S. by Seek Thermal Inc.. It is a long-wave infrared (LWIR) uncooled vanadium oxide microbolometer with a 4.0mm fixed chalcogenide lens, 12µm pixel pitch and a 200 X 150 pixels resolution. Chalcogenide is a class of cost-effective glass that can be molded instead of machined. The pixel pitch describes the pixel density on the camera sensor surface. The higher the density, the more compact the camera core for a given resolution.
- In a micro bolometer, each pixel's electrical signal corresponds to the amount of infrared radiation it has absorbed, which is directly related to the temperature of the part of the scene that pixel is viewing. The surface of each pixel is made of vanadium oxide, chosen for its highly temperature-dependent electrical resistance.
- This core was selected in part due to its open-source python wrapper, that allows easier integration in an open-source project. The SDK (Software Development Kit) is available with Linux, Windows and Mac, allowing operation on the Raspberry Pi.
- Chalcogenide lenses are more affordable than crystalline lens/windows (e.g. germanium) due to their molding manufacturing process instead of machining. The chalcogenide lens has an anti-reflective (AR) coating with an optimal transmittivity in **XXX-XXX** um range (****** That raises the question: does the seek camera have an inner transmittivity curve?)
- The C214SPX cameras are sold as so-called "transition kits". A transition kit is a 10-units pack sold to customers who want to have a small-scale production with improved pricing compared to the Starter Kit, which is sold individually.
- The coprocessor transforms the raw data from the sensor (core). The image processing includes applying algorithms for noise reduction, image enhancement, scaling, or applying color palettes. It can be configured to output different formats (RGB, thermographic array). 
- Seek manufactures the camera core, the coprocessor and the USB-C adapter. The support PCB is manufactured by Jericho, who also does the general assembly and final system quality control.
- The camera core takes pictures, which are then pre-processed by the coprocessor. The USB-C adapter makes it possible to connect the USB-C cable. The Seek Starter Kit (S214SPX) also contains a USB-C connector but this connector is deemed more fragile than the USB-C adapter. Hence, Seek does not recommend permanent setup using the Starter Kit.
- Thermographic data is the ability of some higher quality cameras to output arrays of temperature field, with units (e.g. celcius). The C214SPX has this ability.
- The camera has the ability to output JPG and CSV, but these are done by distinct Python scripts due to completely different code architectures.
  - The **JPG script** obtains an image directly from the coprocessor/SDK. This image has no temperature scale and has a color scheme chosen from a set of options.
  - The **CSV script** obtains a CSV file, which is converted to PNG by the CSV-to-IMG() function. The resulting image has a title, axis titles and temperature scale.
- The SV1 filter is a software option in the SDK which can be activated for improved image resolution. Its algorithm improves the image clarity, but its effect on the thermographic data is unclear.
- Note that the field of view (FoV) is not equal in both axes, due to the Seek design. The horizontal FoV (35 degrees) is larger than the vertical FoV (26 degrees).
- For more information about the software aspects of the thermal camera, consult the Software Architecture Documentation (SAD).

  ## CAMERA CORE SHUTTER

  - The camera magnetic shutter is noisy but not a problem according to discussions with the manufacturer. By default, the shutter action is left to automatic control. This gives a pseudo-random clicking sound, which is increased at startup, when the camera is heating up (Joule effect). The manufacturer has had very few shutter dysfunctions reported over the years.
  - The shutter is used to perform what is known as Non-Uniformity Correction (NUC). By periodically closing the shutter, the camera can capture a uniform temperature image (as the shutter is a uniform temperature surface) and use this to calibrate and correct the pixel output.
  - The shutter interrupts image capture process, which can be problematic for time sensitive operating like missile guidance thermal videos. However, with a low-speed system dedicated to periodic image capture, there is little added value in a shutterless camera.


## 3D-PRINTED CAMERA ADAPTER (rev A2)

- The camera core needs a 3D-printed adapter which is made out of 2 parts:
  - camera holder
  - camera nut
- The open-source design is available in the Github Jericho repo (/3DCAD folder) in the FreeCAD, Fusion 360 and STL formats.
- The adapter is printed in PETG (weatherproof) as it is exposed to humidity.
- Assembly: The C214SPX core is inserted (with its rubber) in the camera holder, which is then inserted through the enclosure hole. The camera nut locks the assembly in place.

<figure>
<p align="center">
  <img src="../Design Overview/images/camera_holder_v10.JPG"
  style="width:50%;">
    </p>
</figure>
<p align="center"> 3D view of the camera holder (v10)

<figure>
<p align="center">
  <img src="../Design Overview/images/camera_nut_v6.JPG"
  style="width:50%;">
    </p>
</figure>
<p align="center"> 3D view of the camera holder nut (v6)



## USB-OVER-CAT ADAPTER

- USB cables are limited in the maximum length they can achieve without an active signal booster. This is due to the higher EM noise sensitivity, higher latency and higher power loss than CAT cables. Conversion from USB to CAT cable is one method to increase cable length. It retains the USB protocol but it actively maintains the voltage required for USB-protocol and transfers the signal to a CAT cable which is better suited for long distances due to shielding and twisted pairs of wires.
- This strategy requires two low-cost USB-over-CAT adapters - a transmitter and a receiver - with a CAT cable in between. A conversion is made at each end of the cable, providin seamless integration to the system.
- The adapter is designed for indoor use (not weatherproof) and must be installed in the enclosure(s).
- The official rating operating temperature is 0C to 80°C. Jericho successfully tested the adapter at -10°C. Despite the low risk of issues, Jericho will test the converter performance at -40°C in the near future.
- A product disassembly showed that the core component of the USB-over-CAT adapter is a chip with silkscreen inscriptions “CJS1037A AN9MRS.1” and “CJS1037A-D2”, for which no information was found online.
- Despite the adapter being widely available on platform like Amazon, the chip identity is unknown. Therefore, the maximum current that can be drawn through the chip is unknown but should be assumed to be very limited. This will have to be tested, but we know that it can supply the thermal camera and its coprocessor (300mW) at the very least. The exact limit has implications for the IR camera heater.
- The USB-over-CAT has a USB 1.0 rating, which is limited to 15 Mbps. This has proven not to be a problem with the IR camera in picture mode (video not tested).
- Some users report a very short life (months) for some low-cost USB-over-CAT adapters available online. This will have to be tested and addressed, if necessary.

## FLEX CABLES

- The data transmission inside the enclosure is done by two flexible cables:
  - Sensor flex
  - USB flex (in between the coprocessor and the USB-C adapter)
- These polyimide cables are very delicate and should not be folded.
- The PCB, by fixing the components, minimizes movement and the mechanical stress on the flex cables.

(insert image of flex cables, some people don't know what it is)

## CUSTOM PCB

**OHHHHHHHH** This description assumes a mechanical PCB, not the latest PCB idea I had that would include USB, etc.
- The custom PCB has mostly mechanical functions. Its custom size and holes pattern allow to secure in place the camera core, the coprocessor, the USB-C adapter.
- The PCB size is optimized for the enclosure and is directly screwed into the enclosure pre-drilled holes.
- The camera modularity has the side-benefit of reducing repair cost.
- A LED is added to the PCB to indicate that the camera is powered.
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.


## 3D PRINTED CAMERA CORE HOLDER

- The camera adapter eases the assembly and ensures that the camera core is parallel to the PCB and the enclosure bottom surface. This is a simple way to guarantee that a leveled enclosure will generate leveled images.

- One function of the camera adapter is to maintain the camera lens perfectly aligned with the thermal window to avoid any error due to refraction, reflection, absorption or field of view. For the same reason, make sure that the camera core, cushion and gasket are well positioned within the adapter, without any debris. A deviation as small as a degree can compromise the quality of the measurements.

## PROTECTIVE WINDOW

- For harsh environment like a multi-year permanent installation in the Canadian climate, the IR camera manufacturer recommends a supplementary protective window, despite the IP67 rating. The window must be made of material with high transmittivity in the light frequencies of interest. Since the Seek Thermal C214SPX has a detection range of 7.8 to 14 microns, only a few materials can possibly meet the criteria: germanium, chalcogenide and zinc selenide (ZnSe).    
- The manufacturer recommends a window of at least 17mm x 1mm. 
  - There needs to have a minimum diameter, to make sure that the field view is covered (when close enough to the camera) - so 17mm or more is suitable.
  - The thickness is minimized to reduce the transmissio loss of the window.
- Germanium, in its solid form, is non-toxic, while zinc selenide is mildly toxic. Germanium dust is harmful however (see warning).

- Both materials require an anti-reflection coating to transmit light effectively. The overall transmittivity being high but imperfect (90-95%), the signal loss has to be accounted for in the software via emissivity or other parameters.
- The transmittivity would be significantly reduced without an AR coating on each side.
- Note: the difference between a window and a lens is the absence of focal point. A window is as flat as possible, having no converging/diverging effect.
- Multiple germanium window suppliers are available: ThorLabs, Sunny Optical, Lightpath, Rochester Precision Optics, Knight Optical. There are also some affordable unknown-quality Chinese suppliers on Alibaba.com. The germanium window cost per unit depends on window size, thickness, quantity and origin, with a cost typically between 50-150CAD. Cost can be lower for a chalcogenide window.
- Current design uses a Chinese D20mm X 1mm germanium window. The thermal camera adapter is sized for the D20mm window. A gasket is also required on the outside face of the germanium. It is not required on the inside face since the camera rubber acts as a gasket. 

- A chalcogenide can also be used. Despite its reduced hardness, it can be used as a sacrificial component to protect the permanent camera chalcogenide lense.


  <figure>
  <p align="center">
    <img src="../Design Overview/images/Shenyang Wanquan Germanium.JPG"
    style="width:50%;">
      </p>
  </figure>
  <p align="center"> Shenyang germanium window in front of the camera adapter and the enclosure

  <figure>
  <p align="center">
    <img src="../Design Overview/images/Shenyang Wanquan Germanium Transmittivity.png"
    style="width:80%;">
      </p>
  </figure>
  <p align="center"> Window transmittivity for the Shenyang germanium window with AR/AR coating





## ENCLOSURE

- The camera enclosure is based on a low-cost ABS plastic rectangular enclosure. The enclosure is weatherproof, with an IP65 rating.
- Its role is to protect the electronic components, which have no conformal coating. If desired, Seek confirms that the board should tolerate both the silicone or acrylic conformal coating, when applied with a brush. Spray coating should not be used due to the risk of sending coating inside the critical components.
- The enclosure holds the protective window, with its sealant (rubber gasket or silicone seal) Silicone does not react with germanium and any high-temperature outgasing would be have a limited impact on the germanium window as it is only applied on the outer side.
- The cable glands are on a single side only. This reduces exposition to water ingress.
-Note: The enclosure should be positioned face up to avoid having all thermal pictures upside down.
- Flexible closed-cell foam is used to help seal the cable gland gap around the cable(s).
- The camera core is aligned with the enclosure bottom with an accuracy of +/- 5deg. An adjustment is possible. We **STRONGLY** encourage you to test the alignment of pictures before installation.

- Condensation must be avoided on the thermal camera (camera rating is 10 to 90%HR). This is why the enclosure sealing is important, as it minimizes the humidity ingress. The residual humidity is absorbed by the silica gel bag inside. The gel change of colour tells the user when it is time to replenish the bag.
- The enclosure openings (cable gland, camera core) are drilled in the lab.

- Optional thermal insulation can be added to the top and bottom surface of the enclosure. This reduces heat loss in the winter. Assuming a horizontal installation, the top insulation also reduces solar heat gain in the summer.

## CALIBRATION

- By default, the Seek Mosaic thermal camera has automatic inner calibration of its bolometer array, via the shutter. This operation is currently maintained. Shutter operation could be put into manual mode or completely suspended, but the absence of frequent NUC would eventually cause a drift in measured values. Continuous pointing directly at the sun would also have a severe aging effect on the array pixels aligned with the sun.
- The default emissivity parameter is 0.97 [1]. This parameter (0.00 – 1.00) depends on each object and must be adjusted within the SBC Python program. Many daily surfaces have emissivity above 0.9 but varies greatly. This calibration must be done by the final user.
- To determine the emissivity of the surface, comparison must be made between a reference thermometer on the object being filmed and the thermography data output for that location.
- Rain and heavy fog will interfere with the image quality of an thermal camera, because these elements are not transparent to infrared light. Distance will also affect accuracy, since the accuracy is rated for objects at distance of 30cm.

## HEATER (WORK-IN-DEVELOPMENT)

- The camera core and the coprocessor do NOT have internal heaters. Like any electronics however, they do consume a small amount of electric power, which ultimately is dissipated in the form of heat.

- While the camera can detect temperature surfaces from -40 to +330°C, the camera core can operate from -10°C to **XXX**. This means that the camera cannot operate reliably on the complete range of weather in Canada, without more testing.

- Another limitation of the C214SPX camera is that its measurement accuracy is only known when the body camera is 25°C. This information limitation is common for thermal cameras. It is only known that accuracy and resolution will decrease as the camera temperature gets further away from this ideal temperature. Systematic tests remain to be done by Jericho to evaluate accuracy at various body temperature. 

- In order to improve accuracy when the weather temperature is not nominal (25°C), a regulated source of heat is required. This feature is still under development, but the concept consists of a 5V/400mA resistive heater that is regulated at 25°C via a PID controller software on a small processor. To limit the required power, the heat will be applied directly to the camera adapter; the processor and other components not being as sensitive to temperature.

 - An even more advanced concept would use an inexpensive Peltier module instead of resistor. This would enable hot and cold control for a year-round accuracy improvement.

## OTHER

- The Seek camera hardware is proprietary. This includes the camera core, the coprocessor, and the SDK kit. The Python wrapper provided by Seek Thermal is open-source, however (Apache license 2.0).
- The Software Development Kit (SDK) is a proprietary C/C++ software required to operate the thermal cameras. Despite the copyright, the Seek license gives the permission, free of charge, to use, copy, modify, sell the code examples. The SDK is pre-installed on the Pi computer provided by Jericho.
- To help users who would like to add functionalities or troubleshoot something, the free Seek Developer Portal will give you access to: SDKs for app and software development, design documentation for easy integration, pre-built examples to get you up and running faster, access to Seek's developer support team, community forums to share ideas, instructional video tutorials.
- A future area of development is to manufacture the coprocessor, based on the design provided for free by Seek Thermal for customers who want a better product integration.

<figure>
<p align="center">
<img src="../Design Overview/images/2 IR Camera RevA1.png" style="width:70%">
  </p>
</figure>
<p align="center">
Figure 2 An example of Starter Kit (SPX214). (Copyright Seek Thermal)
</p>

## REFERENCES

[1] Seek Mosaic Core Specifications: xxxxxxx.com........


## COMMENTS

If we don't use the camera support angle, how are we gonna make sure that the camera takes pictures that are parallel to the enclosure? (This is the reason I wanted a support angle beside the heat transfer!!)

what is the size of the hole in the enclosure to allow the insertion of the camera adapter? (we can either measure the existing hole OR measure the thread on FreeCAD.)

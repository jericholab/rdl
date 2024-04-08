**Hall Effect Current Sensor Revision A1 (Analog Signal)- Design Overview**  
=======================================

Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  
 

Warning: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

Safety warning: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. The current sensor operates with a 5V supply, but the installation of the sensor on the high-voltage circuit requires an electrician.

Warning: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.

# Table of Contents

## GENERAL
- [Revision A1 Overview](#revision-a1-overview)
- [Board Description](#board-description)
- [Wire Gauges and Lengths](#wire-gauges-and-lengths)

## NOTES APPLICABLE TO THE RDL SUITE
- [Board Routing](#board-routing)
- [PCB Manufacturing](#pcb-manufacturing)
- [PCB Trace Width](#pcb-trace-width)
- [PCB Design Files](#pcb-design-files)
- [Optimization and Cost](#optimization-and-cost)
- [Conformal Coating](#conformal-coating)

## CURRENT SENSOR (L01Z050S05) GENERALITIES AND INSTALLATION
- [Core Component](#core-component)
- [Component Availability](#component-availability)
- [Installation Precautions](#installation-precautions)

## OPERATION
- [Measurement Process](#measurement-process)
- [Temperature Tolerance](#temperature-tolerance)
- [Accuracy Specifications](#accuracy-specifications)
- [Signal Description](#signal-description)

## VOLTAGE REGULATOR TPS630701
- [Component Usage](#component-usage)
- [Operation Modes](#operation-modes)
- [Feedback Resistor](#feedback-resistor)
- [Heat Sink Recommendation](#heat-sink-recommendation)

## OTHER
- [LED Indicator](#led-indicator)
- [Screw Terminal](#screw-terminal)
## COMMENTS
- [ COMMENTS](#comments)



## GENERAL

### Revision A1 Overview
- This document details the revision A1 of the current sensor, which has analog signal output. The revision A2, with the NAU7802 digital output is not covered here.

### Board Description
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL). There are SMD components on the top surface of the PCB only.
- The original design of the voltage regulation circuit was done by Sparkfun under CC-BY-SA-4.0 license. The license for this Jericho hardware is the same.
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise. There is no copper plane on the top surface.
- The allowable wire gauges for the PCB screw terminals are AWG 20-26.
- For this product, a “long wire” is defined as 30 m. The device was designed with a target of 30m wire. This applies for both CAT cables and ordinary two-conductor cables.

## NOTES APPLICABLE TO THE RDL SUITE

### Board Routing
- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.

### PCB Manufacturing
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada (soldering iron and/or solder bath). Final quality control is done in Canada.

### PCB Trace Width
- Default PCB trace width is 0.25mm. For power traces (VCC, GND), the trace width is 0.5mm, with some exceptions (e.g. a power trace connecting to a very compact chip package format). In those cases, the 0.25mm default is applied.

### PCB Design Files
- The complete PCB design, ready for production, is available on Github. This includes KiCAD project files, Gerber files, BoM and Component Position Placement files.

### Optimization and Cost
- Design and cost have been partially optimized for JLCPCB manufacturing abilities and components pricing at the time of design, for small batches.

### Conformal Coating
- Unless stated otherwise, all libraries required to make the RDL suite run are open-source.
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’. Conformal coating on the PCB surface increases durability and reliability.

## CURRENT SENSOR (L01Z050S05) GENERALITIES AND INSTALLATION

### Core Component
- The core component of the board is the L01Z050S05 current sensor module manufactured by TAMURA. The LZ01 module is based on the Hall effect. It can measure both DC and AC (up to 100kHz) current up to 50A DC.

### Component Availability
- The TAMURA component is readily available at global suppliers like DigiKey or Mouser.

### Installation Precautions
- The TAMURA module was designed for indoor use and is not weatherproof. Therefore, the sensor MUST be installed in a weatherproof enclosure to avoid any damage or safety risk.

## OPERATION

### Measurement Process
- To make a measurement, a single conductor must pass through the core.

### Temperature Tolerance
- The module can work from -20 to 80°C.

### Accuracy Specifications
- According to TAMURA specifications, the sensor accuracy at nominal current (i.e., 50A DC) and nominal temperature is ±1%.

### Signal Description
- The TAMURA sensor has 3 pins: voltage (VCC), ground (GND), signal (SIG). The signal data is an analog 0-5V signal.

## VOLTAGE REGULATOR TPS630701

### Component Usage
- To supply a high accuracy 5V line to the current sensor, the TPS630701 chip (buck-boost converter with switch current) is used.

### Operation Modes
- This chip has two operation modes: PFM mode (Pulse Frequency Modulation) and PWM (Pulse Width Modulation).

### Feedback Resistor
- For TPS63070, the accuracy of the output depends on the accuracy of the feedback resistor.

### Heat Sink Recommendation
- Note: A heat sink of dimension 0.19x0.25x0.30" is optional but generally recommended for the TPS630701 chip.

## OTHER

### LED Indicator
- A LED is added to the PCB to indicate that the sensor is powered on.

### Screw Terminal
- To enable connection between the PCB and the RDL, a 3-pin screw terminal is added (VCC, GND, SIG).



## COMMENTS
1) ADD somewhere that the sensor has no voltage protection. (I can add some eventually).

The difference between a voltage spike and a surge is primarily in their duration and sometimes in their cause:
Voltage Spike: A voltage spike is a sudden and brief increase in voltage, typically lasting only a few milliseconds. Spikes are often caused by transient events, such as lightning strikes, power outages, or short circuits. They are characterized by their very high magnitude but short duration.
Voltage Surge: A voltage surge is a longer-lasting increase in voltage, typically lasting for a few microseconds to a few seconds. Surges can be caused by events such as large electrical loads being turned off (like motors or large appliances), faulty wiring, or issues with the utility company's equipment. Surges are generally lower in magnitude compared to spikes but last longer.
In the context of a Hall effect sensor, both spikes and surges can be problematic, but the reasons can vary:
Spike in the Wire Going Through the Sensor: If there is a spike in the current flowing through the wire being measured by the Hall effect sensor, it could potentially affect the sensor's output. Hall effect sensors work by detecting the magnetic field generated by electric current flowing through a conductor. A sudden spike in current can produce an unexpectedly strong magnetic field, which could lead to erroneous readings or potentially damage the sensor if it exceeds the sensor's maximum current rating.
Spike or Surge in the Power Supply to the Sensor: If the spike or surge occurs in the power supply to the Hall effect sensor itself, it could damage the sensor's internal circuitry. Most electronic components, including Hall effect sensors, are designed to operate within a certain voltage range. Exceeding this range, even briefly, can cause irreversible damage to the sensor.
In summary, voltage spikes and surges can affect Hall effect sensors either by causing direct damage to the sensor's circuitry (if they occur in the power supply to the sensor) or by producing abnormal readings (if they occur in the current being measured by the sensor). This is why voltage protection is important in applications where such events are a risk.


**I2C Shield RevA2 Design Overview**  
=======================================
Jericho Laboratory Inc. Documentation licence: CC-BY-SA.  

**Warning**: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version.

# Table of Contents

## GENERAL
- [RDL System Overview](#rdl-system-overview)
- [License and Compatibility](#license-and-compatibility)
- [Wire Gauges and Terminal Order](#wire-gauges-and-terminal-order)
- [Manufacturing and Cost](#manufacturing-and-cost)
- [Board Description](#board-description)
- [Wiring Holes](#wiring-holes)

## NOTES APPLICABLE TO THE RDL SUITE
- [Board Routing](#board-routing)
- [PCB Manufacturing](#pcb-manufacturing)
- [PCB Trace Width](#pcb-trace-width)
- [PCB Design Files](#pcb-design-files)
- [Optimization and Libraries](#optimization-and-libraries)
- [Conformal Coating](#conformal-coating)

## GENERALITIES ABOUT THE I2C SHIELD
- [I2C Shield Functionality](#i2c-shield-functionality)
- [Multiplexing Concept](#multiplexing-concept)
- [Stacking I2C Shields](#stacking-i2c-shields)

## I2C COMMUNICATION
- [I2C Protocol Overview](#i2c-protocol-overview)
- [Two-Wire Protocol](#two-wire-protocol)
- [Device Addressing](#device-addressing)
- [Multiplexing Techniques](#multiplexing-techniques)

## CABLES
- [Cable Types](#cable-types)
- [Shielding Considerations](#shielding-considerations)

## I2C EXTENDER (LTC4311)
- [Functionality and Placement](#functionality-and-placement)
- [Signal Enhancement](#signal-enhancement)
- [Extender Location](#extender-location)

## GPIO I2C EXPANDER (PCF8574)
- [Usage and Multiplexing](#usage-and-multiplexing)
- [PCF8574T Description](#pcf8574t-description)
- [Behavior and Library](#behavior-and-library)

## I2C MULTIPLEXER (TCA9548)
- [Chip Multiplexing](#chip-multiplexing)
- [Addressing Configuration](#addressing-configuration)
- [Power Line Multiplexing](#power-line-multiplexing)

## MOSFET TRANSISTORS
- [Component Selection](#component-selection)
- [High-Side and Low-Side](#high-side-and-low-side)
- [Gate Orientation and Resistor](#gate-orientation-and-resistor)

## OTHER
- [LED Indicators](#led-indicators)

## GENERAL

### RDL System Overview
- This document refers to the Resistance Data Logger (RDL) system associated with the Jericho RDL PCB revision E2.

### License and Compatibility
- The RDL rev E2 hardware is released under the MIT open-source license.
- The current board revision only works with the corresponding source code version.

### Wire Gauges and Terminal Order
- Allowable wire gauges are written on the silkscreen (AWG 20-26).
- Starting with revision E2, the objective of maintaining at least 50% of the product cost (material and labor) has been abandoned.
- Long wires (>10m) between the RDL and its sensors will cause significant voltage loss.

### Manufacturing and Cost
- In this revision E2, the SMD components are installed at the factory (JLCPCB, China) and THT components are installed in-house.

### Board Description
- The board is a simple 2-layer PCB, with no lead content (lead-free-HASL).
- A copper plane (ground) is poured on the bottom surface on the PCB to reduce EM noise.

### Wiring Holes
- There are holes around the board to help attach the wires and reduce mechanical stress on the wires.

## NOTES APPLICABLE TO THE RDL SUITE

### Board Routing
- Board routing is done mostly with Freerouting (stand-alone version), with some traces made manually with KiCAD 6.

### PCB Manufacturing
- For the RDL suite, PCB manufacturing is done mostly in China (SMD and wave soldering), but some through-hole components are installed in Canada.

### PCB Trace Width
- Default PCB trace width is 0.25mm.

### PCB Design Files
- The complete PCB design, ready for production, is available on Github.

### Optimization and Libraries
- Design and cost have been optimized for JLCPCB manufacturing abilities and components pricing at the time of design.

### Conformal Coating
- If conformal coating has been applied to your PCB, the serial number ends with a ‘C’.

## GENERALITIES ABOUT THE I2C SHIELD

### I2C Shield Functionality
- The I2C shield allows the RDL to communicate with eight sensors based on I2C communication.

### Multiplexing Concept
- Multiplexing is a technical term to describe the ability to communicate with multiple devices one-at-a-time using a single channel.

### Stacking I2C Shields
- With this design, up to three I2C shields can be connected by stacking them below the RDL.

## I2C COMMUNICATION

### I2C Protocol Overview
- I2C protocol was developed for inter-processor communication.

### Two-Wire Protocol
- An I2C protocol is a two-wire protocol: one for the clock (SCL) and one for the data (SDA).

### Device Addressing
- There can only be a single device with the same I2C address on a given bus.

### Multiplexing Techniques
- Many projects dedicated to I2C multiplexing only affect the SDA and SCL lines.

## CABLES

### Cable Types
- The I2C shield connects to the RDL via RJ45 connectors and an Ethernet (CAT) cable.

### Shielding Considerations
- Both shielded and unshielded cables can be used.

## I2C EXTENDER (LTC4311)

### Functionality and Placement
- The I2C extender circuit is now located on the RDL, instead of the shield.

### Signal Enhancement
- The I2C extender chip used is the LTC4311.

### Extender Location
- The I2C extender must be close to the Arduino Nano.

## GPIO I2C EXPANDER (PCF8574)

### Usage and Multiplexing
- PCF8574T is a GPIO (General Purpose Input Output) I2C expander.

### PCF8574T Description
- The PCF8574 is described as “an open-drain output with a 100K resistor pull-up built in”.

### Behavior and Library
- The Adafruit library manages the behavior of the PCF8574.

## I2C MULTIPLEXER (TCA9548)

### Chip Multiplexing
- TCA9548APWR is a chip multiplexer for I2C communication.

### Addressing Configuration
- The TCA9548APWR has 3 address pins (A0, A1, A2).

### Power Line Multiplexing
- To avoid picking up noise on the power supply lines via 8 cables of up to 30m, the power lines are also multiplexed.

## MOSFET TRANSISTORS

### Component Selection
- Choice of components: P-channel MOSFET (high-side) and N-channel MOSFET (low-side).

### High-Side and Low-Side
- High-side transistors require a low signal to be activated, while low-side transistors require a high signal.

### Gate Orientation and Resistor
- The body diode has to be oriented so that there is no flow in normal operation.

## OTHER

### LED Indicators
- A LED is present on the board to indicate that the board is supplied in power.

- Another LED was temporarily added to the VCC of channel 1 to indicate that this MOSFET works correctly. This is useful for troubleshooting.
<figure>
<p align="center">
<img src="../Design Overview/images/I12 shield RevA2.png" style="width:70%">
  </p>
</figure>
<p align="center">
Figure . Temporary diagram for the MOSFETs pairs controlling the sensors power supply
</p>

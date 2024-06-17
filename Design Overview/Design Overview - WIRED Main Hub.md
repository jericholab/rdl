**WIRED Main Hub Revision A1 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc.  
Document License: CC-BY-SA.  

**Warning**: The following material is for educational purposes only. Always refer to the specific documents (e.g. schematic) associated with your product version.

**Safety warning**: You are responsible for your own safety. Always consult an accredited electrician before working with high-voltage electricity. This sensor operates with a low-voltage (5V) supply, but other components of your system might require an electrician. Do NOT install in areas prone to thunder as the system has no protection against thunder.

**Warning**: This product is neither intended nor warranted for use in following equipment or devices: Special application (such as for medical devices, transportation equipment, traffic signal control equipment, fire and crime prevention equipment, aeronautics and space devices, nuclear power control, fuel control, in vehicle equipment safety devices, and so on) in which extremely high quality and high reliability is required, or if the malfunction or failures of product could be cause for loss of human life, bodily injury.

******** THE DOCUMENT IS AMBIGUOUS BETWEEN ORANGE PI AND RASPBERRY PI ********


## Table of Contents
1. [General](#general)
2. [Single Board Computer (SBC)](#single-board-computer-sbc)
3. [Resistance Data Logger (RDL)](#resistance-data-logger-rdl)
4. [USB Hub](#usb-hub)
5. [Main Enclosure](#main-enclosure)
6. [Mounting Panels](#mounting-panels)
7. [Power Bar and Power Supplies](#power-bar-and-power-supplies)
    - [Power Bar](#power-bar)
    - [Pi Power Supply (Orange Pi)](#pi-power-supply-orange-pi)
    - [Electrical Certifications](#electrical-certifications)
8. [Cable Glands](#cable-glands)
9. [WIFI IPEX Antenna (Orange Pi only)](#wifi-ipex-antenna-orange-pi-only)
10. [Enclosure Layout](#enclosure-layout)
11. [Silica Gel Pack](#silica-gel-pack)
12. [Supplementary Notes](#supplementary-notes)


## GENERAL

- The main hub is the central point in the WIRED system infrastructure. Each installation (i.e. experiment) has only one main hub.
- The main hub design relies on continuous access to grid electricity and WiFi. Temporary WiFi interruption is of less consequences, as the accumulated local data will be synced later. This design is not for remote areas and/or battery powered systems, without additional components.

- The Main Hub module is comprised of:
  - 1x Main Enclosure
  - 1x Single Board Computer (SBC)
  - 1x SBC power supply
  - 1x Resistance Data Logger (RDL)
  - 1x Main Enclosure Top Mounting Plate (Door)
  - 1x Main Enclosure Bottom Mounting Plate
  - 1x Power bar
  - 1x USB hub
  - 2x USB-over-CAT-adapter
  - 10x Cable glands
  - 1x Switch (optional)
  - 1x Switch power supply (optional)
  - 1x IP camera power supply (sold separately, with IP camera)
  - 1x IPEX antenna (optional, Orange Pi only)
  - 2x Silica gel packs
  - Port plugs

For a detailed list of components, please consult the Bill of Material (BoM) on Github.

## MAIN ENCLOSURE

- The main enclosure is an ABS IP65 white junction box with a hinged door and two snaps. Plastic was selected to reduce cost and weight. It is also easier to drill. The outer dimensions are 15.4"x11.4"x6.3" (391 mm x 290 mm x 160 mm).
- The enclosure contains and protects the equipment against the hardship of the northern climates (-40 to +40°C). With the sun exposure, the enclosure is expected to endure a 100°C temperature range. This waterproof enclosure is tolerant to freeze, direct sunlight (UV) and dust. The door has a black rubber seal.
- For a multi-year project operating with a 100°C temperature range, screws are preferable to a two-face tape, despite the enthusiasm of the 3M company. This ensures that no component will detach from their surface, under the heat.
- There is a row of reinforced holes around the bottom panel. These are used to install the enclosure on a structure.
- The enclosure should be installed vertically, with cable glands pointing downwards. This reduces the risk of water ingress.
- The enclosure has four golden holes in the corners. The mounting panel must be installed with the provided machine screws in these holes.
- The enclosure size is optimized for the current content. If additional components are added to the system, it is recommended to increase the size of the main enclosure.
- It is recommended to NOT open the main enclosure during bad weather (rain, snow, dust) to minimize the risk of component damage and safety issues.

### ENCLOSURE MOUNTING PANELS

- A simple mounting plate is used, to reduce cost. The mounting plate is made of a custom size 2.54mm thick black ABS sheet.
- A similar mounting plate on the enclosure door holds other components.
- Mounting plates reduce the quantity of holes that must be made in the enclosure, which reduces the risk of water ingress. Modules and components are to be assembled on the mounting plate, before installing the mounting plate inside the enclosure with four machine screws. This allows a simpler, faster production and maintenance.
- Several components (e.g. RDL) are installed via nylon standoffs on the main enclosure.
- Cut-outs provide access to the enclosure mounting holes. This way the enclosure can be uninstalled from the wall/structure without removing the bottom mounting panel from the enclosure.

### ENCLOSURE LAYOUT

The exact position of each component on each mounting plate is standardized for improved quality control and productivity. The components installed on the bottom mounting plate were selected based on their size, cost, sensitivity to water and number of cabled connections.

- Bottom Mounting Plate
  - RDL & Shield(s)
  - SBC
  - USB Hub
  - Two silica gel packs
- Top Mounting Plate (Door)
  - Power bar
  - All power supplies
  - Network switch (optional)

## SINGLE BOARD COMPUTER (SBC)

- Due to a global shortage and increased cost, the decision was made in 2023 to use Orange Pi 4 LTE instead of the traditional Raspberry Pi.
- The native OS provided by Orange Pi is used (Ubuntu-based).
- A 3D-printed enclosure allows to install the Pi on the bottom panel with four screws.
- A small fan is added to the SBC enclosure. The fan blows towards the heat sink for improved performance. However, this leaves the back of the fan unprotected. It has a supplementary 3D-printed grille that reduces the risk of an object blocking the blades. This would probably not cause a CPU overheat, but it would reduce the heat transfer to the other components (e.g. RDL) in the winter. This fan is powered via the Pi GPIO pin (POWER +5V).
- When supplying power through the dedicated jack barrel, the power supply of the Pi has to be 4A. With lower current capacity power supplies, the SBC will restart when it has high CPU usage and consumes an increased amount of current, causing a voltage drop.
- The fan also has a role of increasing heat transfer from the Pi to the enclosure, helping to maintain an acceptable temperature inside the enclosure during the winter.
- There is no screen or visual interface to the SBC. The HDMI connector can be used in the lab; in the field, remote access with a laptop is recommended.

## RESISTANCE DATA LOGGER (RDL)

- The RDL includes the optional I2C shield(s), which are stacked under it. The quantity of shields (one or two) depends on the quantity of I2C channels required.
- Inside the main hub, flat CAT cables are favored due to their compact form and increased flexibility, compared with traditional round CAT cables.
- The RDL is installed close to the cable glands to reduce the length of wire inside.

## USB HUB

- The USB hub allows the RDL and the IR camera (1 or 2) to communicate with the SBC. It also provides the 5V power supply.
- The USB hub can only draw a maximum of 500mA on its USB port. This means that it could theoretically pose a limit to the RDL operation under certain circumstances. The power supply multiplexing of course reduces the likelihood, but nonetheless. In that scenario, the RDL USB cable could be directly connected to one of the three USB port of the SBC.
- The USB hub (indoor rated) has been disassembled, coated with a conformal coating for increased protection against oxidation and reassembled.


## POWER BAR AND POWER SUPPLIES

### POWER BAR
- Model: Silkycasters 6-outlets 1000-Joules
- The power bar has six (6) outlets. It is located on the door side.
- It holds with two screws in the mounting plate.
- Weatherproof certification (IPx4).
- There are no permanent high-voltage connections inside the enclosure.
- The power bar is located inside the enclosure, while the outlet is located outside. It has been passed through the cable glands. The original outlet has been cut to pass the cable through the cable gland. An outdoor outlet has been reattached to the cable ends, permanently.

### PI POWER SUPPLY (ORANGE PI)
  - Model: GeeekPi 20W 5V 4A Power Supply
  - The Orange Pi is supplied via the USB-C input.
  - Despite the frequent sale of 3A/5V models, a high-quality 4A/5V power supply is required for reliable performance (e.g. unscheduled reboots). The high-frequency chopper power supplies often used to charge smartphones are not recommended for the same reason. 
  - The cable length should be limited to avoid high capacitance, which can cause a Pi reboot in the eventually of a power surge. A max length of 1m is recommended.

### SWITCH POWER SUPPLY

  - More details can be found in the Ethernet Switch section.

### IP SURVEILLANCE CAMERA POWER SUPPLY

  - More details can be found in the IP Camera section.

### ELECTRICAL CERTIFICATIONS

- The following components operate at 110/120V and have at least one of the recognized electrical certifications (UL, cUL, CSA, ETL):
  - Power bar
  - Reolink power supply
  - Pi power supply
  - Switch power supply

All other components operate at 12V or below and might not have any of these certifications (i.e. low-voltage exception).

### FCC CERTIFICATIONS  (WELL IC (Industry Canada) applies here...)****

- The following components have a FCC approval for EMI: (TO BE VERIFIED)
  - Power bar
  - Reolink power supply (seems to be no certification)
  - Pi power supply (cULus) (no FCC) (VERIFIED)
  - Switch power supply (FCC)
  - Raspberry Pi 4 (FCC/IC/EU) (VERIFIED)

- The following components have a non-FCC radio compliance: 
  - Orange Pi 4 LTS  
    - Certificate of RED compliance, according to Radio Equipment Directive 2014/53/EU.

  The following components/subsystems are low-voltage (5-12V) AND do not have wireless functionalities. They do not require/have an FCC approval: 
  - Jericho RDL
  - Jericho I2C Shield
  - thermal camera based on Seek Thermal C214SPX
  - all Jericho sensors

- Note: The cURus mark indicates that a product meets Canadian and U.S. safety standards.

## CABLE GLANDS

- There are two rows of five (5) cable glands on one of the side panel of the enclosure, facing down.
- A single size of cable gland (M25X1.5, 25mm diameter opening) was selected to reduce cost and complexity (standardization).
- The number of cable glands is standardized, despite the variation in the number of sensors and cables in each system. Cable glands left empty are filled with a piece of closed cell foam to avoid humidity ingress.
- In the WIRED project, up to 30 CAT cables need to go through the enclosure. To save space and reduce cost, up to three CAT cables can fit inside a single cable gland. This is unorthodox since often it is 1 cable per cable gland and you tighten up. The use of multiple cables leaves void between the cables. This can let dust, humidity and insects enter the enclosure. This void is filled with closed cell foam.
- The enclosure holes for the cable glands are done with a hand drill and a 1-in diameter (2.54mm) Forstner drill bit.

## WIFI IPEX ANTENNA  (ORANGE PI ONLY)

- To improve WiFi reception of the Orange Pi, a passive antenna is required outside the enclosure (interference). The original antenna cable is too short to reach outside the enclosure. A replacement antenna is therefore installed on the original IPEX connector. This improved antenna might not be necessary in all setups, depending on WiFi signal strength.
- The antenna is installed on the side of the box to reduce the risk of leaks (compared with the top surface). 
- The external part of the antenna is screwed. It is recommended to remove the antenna for transport to avoid any mechanical .

## POWER BAR

- A waterproof IPX4 power bar with six (6) plugs is installed inside the enclosure.
- The power bar provides electricity for the following power supplies: SBC, ethernet switch, surveillance camera. Other components are indirectly powered via the SBC.
- The IPX4 rating means that it has no dust ingress rating (‘X’) and it has some protection against water splashes (‘4’).
- The electricity enters the enclosure via an extension cord. The extension cord has been selected for its ability to pass through the 1-inch cable gland without disassembly.
- The power bar has surge protection (1000 Joules) and overload protection (15A fuse). It also has a LED light to indicate that power is on.

## SILICA GEL PACK

- Two silica gel packs are installed inside the enclosure to absorb moisture and reduce the long-term air humidity content. The pack changes from purple to orange as it absorbs humidity. The pack should be changed or replenished with the microwave oven when they are saturated (orange). Reducing humidity is important to ensure proper function of all electronic and electric components inside the enclosure (short-circuit, oxidation). The silica gel pack are installed with the transparent side up to allow users to monitor the color evolution.
- The silica gel packs are shipped in a sealed plastic bag and must be installed by the user.

## SUPPLEMENTARY NOTES
- If humidity problems are suspected, a SHT40 board can be installed inside the enclosure to monitor the air humidity. 
- Residual heat from the system, mostly the SBC, helps reduce the relative humidity inside the enclosure by maintaining a constantly warmer temperature than outdoors. This is the same phenomenon that keeps heated houses very dry in the winter time.
- Port plugs: All empty connectors are filled with plastic plugs to avoid oxidation and dust accumulation. This includes RDL and SBC connectors as well as USB and RJ45 ports. This ensures that all connectors are in good state if the need ever comes, over the years.
- Inside the enclosure, cable organization is improved with 3M adhesive devices and tie-wraps.


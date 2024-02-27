**WIRED Main Hub Revision A1 - Design Overview (WIP)**  
=======================================
Copyright: Jericho Laboratory Inc. License: CC-BY-SA.  
Revision: 1.  

Warning: The following material is for educational purposes only. Always refer to the schematic and PCB layout files associated with your product version. For a full list of components, refer to the Bill of Materials (BoM).

GENERAL

- The main hub is the central point in the WIRED system infrastructure. Each installation (i.e. experiment) has only one main hub.
- The main hub design is based on continuous access to grid electricity and WiFi. This design is not for remote areas and/or battery powered systems.
- The components inside the main enclosure are:
  - 1x Single Board Computer (SBC) (Orange Pi)
  - 1x Resistance Data Logger (RDL)
  - 1x Waterproof main enclosure
  - 1x Enclosure top mounting plate
  - 1x Enclosure bottom mounting plate
  - 1x Power bar
  - 1x USB hub
  - 1x USB-over-CAT-adapter
  - 1x Ethernet switch
  - 1x Cable glands
  - 1x IPEX antenna
  - 1x Switch power supply
  - 1x SBC power supply
  - 1x IP camera power supply
  - 2x Silica gel packs
- All empty connectors are filled with plastic plugs to avoid oxidation and dust accumulation. This includes RDL and SBC connectors as well as USB and RJ45 ports. This ensures that all connectors are in good state if the need ever comes, over the years.

SINGLE BOARD COMPUTER (SBC)

- Due to a global shortage and increased cost, the Orange Pi 4 LTE was chosen instead of the traditional Raspberry Pi.
- The native OS provided by Orange Pi is used. It is Ubuntu based.
- A 3D printed enclosure allows to install the Pi on the bottom panel.
- A small fan is added to the SBC enclosure. The fan blows towards the heat sink for improved performance. However, this leaves the back of the fan unprotected. It has a supplementary 3D printed grill that reduces the risk of an object blocking the blades. This would probably not cause a CPU overheat, but it would reduce the heat transfer to the other components (e.g. RDL) in the winter. This fan is powered by the Pi GPIO pins.
- When supplying power through the dedicated jack barrel, the power supply of the Pi has to be 4A. With lower current capacity power supplies, the SBC will restart when it has high CPU usage and consumes an increased amount of current, causing a voltage drop.
- The fan also has a role of increasing heat transfer from the Pi to the enclosure, helping to maintain an acceptable temperature inside the enclosure during the winter.
- There is no screen or visual interface to the SBC. The HDMI connector can be used in the lab; in the field, remote access with a laptop is recommended.

RESISTANCE DATA LOGGER (RDL)

- The RDL is installed on the bottom mounting panel.
- The RDL includes the optional I2C shield(s), which are stacked under it. The quantity of shields (one or two) depends on the quantity of I2C channels required.
- Inside the main hub, flat CAT cables are favored due to their compact form and increased flexibility, compared with traditional round CAT cables.
- The RDL is installed close to the cable glands to reduce the length of wire inside.

USB HUB

- The USB hub allows the RDL and the IR camera (1 or 2) to communicate with the SBC. It also provides the 5V power supply.
- The USB hub can only draw a maximum of 500mA on its USB port. This means that it could theoretically pose a limit to the RDL operation under certain circumstances. The power supply multiplexing of course reduces the likelihood, but nonetheless. In that scenario, the RDL USB cable could be directly connected to one of the three USB port of the SBC.
- The USB hub (indoor rated) has been disassembled, coated with a conformal coating for increased protection against oxidation and reassembled.

MAIN ENCLOSURE

- The main enclosure is an ABS IP65 white junction box with a hinged door and two snaps. Plastic was selected to reduce cost and weight. Plastic is also easier to drill. The outer dimensions are 15.4"x11.4"x6.3" (391 mm x 290 mm x 160 mm).
- The enclosure contains and protects the equipment against the hardship of the northern climates (-40 to +40°C). This waterproof enclosure is tolerant to freeze, direct sunlight (UV) and dust. The door has a black rubber seal.
- A simple mounting plate is used, to reduce cost. The mounting plate is made of a custom size 2.54mm thick white ABS sheet.
- For a multi-year project operating with a 100°C temperature range, screws are preferable to a two-face tape, despite the enthusiasm of the 3M company. This ensures that no component will detach from their surface, under the heat.
- A similar mounting plate on the enclosure door holds other components.
- Mounting plates reduce the quantity of holes that must be made in the enclosure, which reduces the risk of water ingress. Modules and components are to be assembled on the mounting plate, before installing the mounting plate inside the enclosure with four machine screws. This allows a simpler, faster production and maintenance.
- There is a row of reinforced holes around the bottom panel. These are used to install the enclosure on a structure.
- The enclosure should be installed vertically, with cable glands pointing downwards. This reduces the risk of water ingress.
- The enclosure has four golden holes in the corners. The mounting panel must be installed with the provided machine screws in these holes.
- The enclosure size is optimized for the current content. If additional components are added to the system, it is recommended to increase the size of the main enclosure.
- It is recommended to NOT open the main enclosure during bad weather (rain, snow, dust) to minimize the risk of component damage and safety issues.

CABLE GLANDS

- There are five (5) cable glands on one of the side panel of the enclosure.
- A single size of cable gland (M25X1.5, 25mm diameter passage) was selected to reduce cost and complexity (standardization).
- The number of cable glands is also standardized, despite the variation in the number of sensors and cables on each WIRED system. Cable glands left empty are filled with a closed cell foam to avoid humidity ingress.
- In the WIRED project, up to 30? CAT cables need to go through the enclosure. To save space and reduce cost, up to three CAT cables (to be verified) can fit inside a large cable gland (M25). This is unorthodox since usually it is 1 cable per cable gland and you tighten up. The use of multiple cables leaves void between the cables. This can let dust, humidity and insects enter the enclosure. This void is filled with closed cell foam.
- The cable glands are installed on a single row to spread out the cables and reduce the cable density in this region of the enclosure.
- The enclosure holes for the cable glands are done with a hand drill and a 1-in diameter (2.54mm) Forstner drill bit.

WIFI IPEX ANTENNA

- The antenna is installed on the side of the box to reduce the risk of leaks inside (compared with the top surface). This antenna is outside the enclosure to increase range. It might not be necessary in all setups.

POWER BAR

- A waterproof IPX4 power bar with six (6) plugs is installed inside the enclosure.
- The power bar provides electricity for the following power supplies: SBC, ethernet switch, surveillance camera. Other components are indirectly powered via the SBC.
- The IPX4 rating means that it has no dust ingress rating (‘X’) and it has some protection against water splashes (‘4’).
- The electricity enters the enclosure via an extension cord. The extension cord has been selected for its ability to pass through the 1-inch cable gland without disassembly.
- The power bar has surge protection (1000 Joules) and overload protection (15A fuse).
- The power bar has a LED light to indicate that power is on.

ENCLOSURE LAYOUT

The exact position of each component on each mounting plate is standardized for improved quality control and production speed. The components installed on the bottom mounting plate were selected based on their size, cost, sensitivity to water and number of cabled connections.

- Bottom Mounting Plate
  - RDL
  - SBC
  - USB Hub
- Door Mounting Plate
  - Network switch
  - Power bar
  - All power supplies
  - Two silica gel pack

OTHERS

- Two silica gel pack are installed inside the enclosure to absorb moisture and reduce the long-term air humidity content. The pack changes from purple to orange as it absorbs humidity. The pack should be changed or replenished via the microwave oven when they are saturated (orange). Reducing humidity is important to ensure proper function of all electronic and electric components inside the enclosure (short-circuit, oxidation). The silica gel pack are installed with the transparent side up to allow users to monitor the color evolution.
- A user could install a SHT40 board inside the enclosure to monitor the air humidity, if humidity problems are suspected.
- The system has no protection against thunder, do not install in areas prone to thunder.
- Residual heat from the system, mostly the SBC, helps reduce the relative humidity inside the enclosure by maintaining a constantly warmer temperature than outdoors. This is the same phenomenon that keeps heated houses very dry in the winter time.
- Inside the enclosure, cable organization is improved with 3M adhesive devices and tie-wraps.

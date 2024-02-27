**IP Camera System - Design Overview (WIP)** 
***********
Jericho Laboratory Inc. Documentation license: CC-BY-SA.  
Revision: 0.  

Warning: The following material is for educational purposes only. Always refer to the product label, if applicable.

GENERAL

- To our knowledge there is no open-source surveillance camera that meets the outdoor requirements of Canadian winter. Therefore, a proprietary surveillance camera was selected, with an open-source integration.
- USB webcams were not considered because, as indoor products, they are not natively weatherproof, despite a similar price than low-cost surveillance cameras.
- The camera can only communicate with the Pi computer, it cannot communicate with the RDL.

CAMERA

- Among the large choice of surveillance camera, the Reolink RLC-520A was chosen for its low-cost, good quality, broad availability and its use of the standard IP protocol.
- The Reolink camera operation is officially limited in low temperature settings. There is no heating element inside the camera, but the electronics inside consume about 3W and release that energy as heat.
- Internet users report that they have run similar models like the RLC-423 without a problem at -45C. The -10C limit is actually the minimal internal temperature. The strategy is to start the camera above -10C and to never shut it off so that it maintains its internal temperature. The strategy proved so efficient that the Reolink design team abandoned the idea of adding a heater. In the case where current is shot however, the camera will have to be brought back to -10C in order to start again. In the context of an outdoor research project that could mean a few days without data until the outdoor temperature reaches -10C again.
- Below 10°C, the camera is not allowed to start operating (software or hardware safety). Tests will have to be done in order to demonstrate if a bypass is possible.
- Note that the Reolink 420LC camera has a fixed fisheye lens, which is typical of surveillance camera aiming at a large field of view.
- The camera has the video capability, but currently, only images are captured by the system.

ETHERNET SWITCH

- The camera can be connected directly into the Pi computer (single camera system) or into the network switch (multiple camera system).
- The network switch is solely dedicated to being an interface between the cameras and the Pi.
- The low-cost network switch (TP-Link TL-SF1005D) chosen does not include a DHCP server. The switch is therefore unable to attribute an IP address to the camera; it must be given manually, beforehand. This default IP address can be modified by the Reolink software (see User Guide).
- In order to have two cameras on the same setup, each camera must be given a different local IP address on the network (e.g. 192.168.0.195 & 192.168.0.196)
- The camera network is independent from the internet network. It doesn’t matter if the Pi is connected to the Internet via WiFi; logging will function. The Pi RJ45 port being connected to the Ethernet card, the Ethernet port cannot be used to access internet while it is used to communicate with the camera(s); WiFi must be used.

REFERENCES


https://reolink.com/blog/security-camera-canada-for-outdoor-extreme-cold/
https://reolink.com/blog/best-cold-weather-ip-security-cameras-systems/

\[To be done\]

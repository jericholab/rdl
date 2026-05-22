**IP Camera System - Design Overview** 
=======================================
Jericho Laboratory Inc.  
Documentation license: CC-BY-SA.  

**Warning**: The following material is for educational purposes only. Always refer to the product label, if applicable.

**Table of Contents**

1. [GENERAL](#general)
2. [CAMERA](#camera)
3. [ETHERNET SWITCH](#ethernet-switch)
4. [REFERENCES](#references)

## GENERAL

- To our knowledge there is no open-source surveillance camera that meets the outdoor requirements of Canadian winter. Therefore, a proprietary surveillance camera was selected, with an open-source integration.
- USB webcams were not considered because, as indoor products, they are not natively weatherproof.
- The camera can only communicate with the Pi computer, it cannot communicate with the RDL.
- Both new and refurbished Reolink cameras are used. The warranty from Reolink, as well as the one from Jericho, are the same in both cases.


<figure>
<p align="center">
<img src="../Design Overview/images/Reolink-rlc-520a.jpg" style="width:70%">
  </p>
</figure>
<p align="center">
Figure 2 Example of RLC-520a installation. (Copyright Reolink)
</p>

## CAMERA

- Among the large choice of surveillance camera, the Reolink RLC-520A was chosen for its low-cost, good quality, weatherproofness (IP66) and its use of the standard IP protocol.
- The Reolink camera must be setup beforehand with the Reolink software on a Windows PC. This allows giving a static IP address to the camera (required) and adjust the image (color, resolution, timestamp display, etc.)
- The Reolink camera operation is officially limited in low temperature settings. There is no heating element inside the camera, but the electronics inside consume about 3W and release that energy as heat.
- The official minimal operating temperature is -10°C. To operate below this limit, the official strategy recommended by Reolink is to start the camera above -10°C and to never shut it off so that it maintains its internal temperature [1] [2]. The strategy proved so efficient that the Reolink design team abandoned the idea of adding a heater. Internet users report that they have run similar models, like the RLC-423, without a problem at -45°C. In theory, below 10°C (internal product temperature), the camera is not allowed to boot (cold start). However, tests by Jericho showed that this is not a problem, at least down to -40°C. 
- Note that the Reolink 520A camera has a fixed fisheye lens, which is typical of surveillance camera aiming at a large field of view. If desired, the fisheye effect can be removed via software.
- The camera has video and sound capability, but currently, only images are captured by the system.

## ETHERNET SWITCH

- The camera can be connected directly into the Pi computer (single camera system) or into the network switch (multiple cameras system).
- The network switch is solely dedicated to being an interface between the cameras and the Pi.
- In order to have two cameras on the same setup, each camera must be given a different local IP address on the network (e.g. 192.168.0.195 & 192.168.0.196)
- The low-cost network switch (TP-Link TL-SF1005D) chosen does not include a DHCP server. The switch is therefore unable to attribute an IP address to the camera; it must be given manually, beforehand. This default IP address can be modified by the Reolink software (see User Guide). This is only required if you need more than one camera on the same hub.
- Each Reolink camera sold by Jericho is pre-configured with the following settings:
  - IP address: 192.168.0.195
  - Colour mode
  - No timestamp
  - No 'Reolink' watermark
- The camera network is independent from the internet network. It doesn’t matter if the Pi is connected to the Internet; logging will function. The Pi RJ45 port being connected to the Ethernet card, the Ethernet port cannot be used to access internet while it is used to communicate with the camera(s); WiFi must be used.
- Pay attention to the orientation of the camera (see "UP" tag) to avoid upside down pictures.

## REFERENCES

Best Security Camera in Canada for Outdoor Extreme Cold, Reolink, 2022. https://reolink.com/blog/security-camera-canada-for-outdoor-extreme-cold/

omplete Guide to Buy Cold Weather IP Security Cameras & Systems in 2024, Reolink, 2023. https://reolink.com/blog/best-cold-weather-ip-security-cameras-systems/

Reolink RLC-520 Specifications, Reolink, 2024. https://home-cdn.reolink.us/files/docs/specs/RLC-520A-IP-Camera-Specifications.pdf?v=1669867641553 




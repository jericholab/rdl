# RTC TIMESTAMP ADJUSTMENT 

To precisely synchronize your Real-Time-Clock (RTC) timestamp with the official time, execute the 
following procedure: 
1. Make sure that your computer clock is synchronized with the official time of your area. 
2. Remove the battery in the battery holder (if any). 
3. Compile and upload the main code to the RDL by using the UPLOAD button in the Arduino IDE 
interface. 
4. Disconnect the USB cable as soon as the upload is complete so that the RTC will experience a power outage.
5. Reconnect the USB cable as soon as possible.
6. The RTC, recognizing that it experienced a power outage, will use the available compile time to update the RTC time.
5. Put in the battery in the battery holder.
6. Time is set.

Note 1: The timestamp error is small (20-30 sec) due to the delay between the start of the compile 
time and the RTC reboot. After that, any reset or upload will not affect the RTC timestamp until the battery is removed or dies. 

Note 2: Make sure that the code is actually recompiled at the time of uploading, so that the code contains the 
current time, and note the time registered at the previous compile. To make sure of that, restart the 
Arduino IDE and change a line of code with a trivial change (like deactivating/activating sensors). 

Note 3: The RTC battery (CR1220) can last years if the RTC experiences very short periods disconnected from the main power (USB cable). However, when in active mode, the RTC drains about 200 uA (micro Amps) on the battery, which will result in a lifetime of a few hundred hours. Therefore, to preserve its energy, the RTC battery should not be left inserted in the RDL when not in use.

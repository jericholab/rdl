INSTALLING A MODIFIED VERSION OF TWI LIBRARY FOR ARDUINO IDE
JerichoLab, 2024-08-16
- - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Introduction
The use of long CAT cables require a slower version of the I2C clock speed than is possible with the native version of the Wire/TWI library. These two libraries work together to generate the I2C signal (SDA/SCL). The Wire library includes the TWI library.
After a fresh install, the Arduino IDE software will create a copy of the TWI library found in /Program Files (x86) and put it in AppData. This becomes the TWI library dedicated to your specific User, and your specific version of the Arduino IDE. In other cases, a library might even be specific to a board (e.g. Arduino Uno). The `AppData\Local\Arduino15` path is where user-specific settings, additional boards, and custom versions of libraries are stored, and it takes precedence over the default installation libraries. This allows users to have multiple versions of the same library for different boards or Arduino cores. The IDE will then proceed to compile that copy. The result is sent to /Temp folder (e.g. twi.c.o). 
In the future, when compiling/uploading an Arduino script, the IDE will in order look to use 1) the precompiled version; 2) the user-specific version, 3) the master version.
If you want to modify the TWI library, and if you are not using a fresh install of the Arduino IDE, then you must delete the precompiled. You can then modify the user-specific version of the library, or you could delete this version too, and modify the master version.


WINDOWS: THREE LOCATIONS

MASTER COPY: C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Wire

USER-CUSTOM: C:\Users\newBlue\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5\libraries\Wire\src\utility

TEMP:  C:\Users\newBlue\AppData\Local\Temp\arduino_build_229642\libraries\Wire\

RASPBERRY OS: TWO LOCATIONS

MASTER: /home/pi/.local/share/arduino-1.8.19/hardware/arduino/avr/libraries/Wire/

TEMP: /tmp/arduino_build_5381/libraries/Wire/


The modifications done by Jericho in the TWI library are small:
1. Comment line: "TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;"
2. Add line for TWBR: "TWBR = 255;"
3. Add line for prescaler bit 0 : "TWSR |= bit (TWPS0);"
4. Add line for prescaler bit 1 : "TWSR |= bit (TWPS1);"

STEP-BY-STEP PROCEDURE (WINDOWS)
1. Delete the Wire folder located at  C:\Users\newBlue\AppData\Local\Temp\arduino_build_229642\libraries\Wire\
2. Copy the new version of twi.c and overwrite the file located at C:\Users\newBlue\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5\libraries\Wire\src\utility\twi
3. Copy the new version of twi.c and overwrite the file located at C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Wiresrc\utility\twi
5. Compile the Arduino script again.

STEP-BY-STEP PROCEDURE (RASPBERRY PI)
1. Delete the Wire folder located at /tmp/arduino_build_5381/libraries/Wire/
2. Copy the new version of twi.c and overwrite the file located at /home/pi/.local/share/arduino-1.8.19/hardware/arduino/avr/libraries/Wire/src/utility/twi
5. Compile the Arduino script again.

STEP-BY-STEP PROCEDURE (RASPBERRY PI)
1.1. Delete the temporary Wire folder at  /tmp/arduino_build_5381/libraries/Wire/
2. Modify and overwrite the twi.c/twi.h files in Wire folder at /home/pi/.local/share/arduino-1.8.19/hardware/arduino/avr/libraries/Wire/
3. Copy the new /Wire folder to: C:\Users\newBlue\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5\libraries\Wire\src\utility\twi
4. Compile the Arduino script again.

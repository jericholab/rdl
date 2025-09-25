**Software Architecture Documentation (SAD) for RDL**  
=======================================
Copyright: Jericho Laboratory Inc.  
Documentation license: CC-BY-SA.  

# Table of Contents

- [Introduction](#introduction)
- [High-Level Flow Diagram](#high-level-flow-diagram)
- [General Ideas](#general-ideas)
- [Fundamental Concepts](#fundamental-concepts)
- [Included Libraries](#included-libraries)
- [Main Code](#main-code)
  - [Declarations](#declarations)
  - [Setup()](#setup)
  - [Loop()](#loop)
- [Main Functions](#main-functions)
  - [ControlFunc()](#controlfunc)
  - [currentNAU7802()](#currentnau7802)
  - [initRTC()](#initrtc)
  - [phFunc()](#phfunc)
  - [printHeader()](#printheader)
  - [runRTC()](#runrtc)
  - [SHT40Func()](#sht40func)
  - [simpleVoltFunc()](#simplevoltfunc)
  - [startMessage()](#startmessage)
  - [strainFunc()](#strainfunc)
  - [terosFunc()](#terosfunc)
  - [thermistor()](#thermistor)
- [Support Functions](#support-functions)
  - [ADS1115.begin()](#ads1115begin)
  - [blink()](#blink)
  - [calculatePhi()](#calculatephi)
  - [commands()](#commands)
  - [getI2Cfreq()](#geti2cfreq)
  - [getVoltFunc()](#getvoltfunc)
  - [i2cScan()](#i2cscan)
  - [I2CSelect()](#i2cselect)
  - [isDST()](#isdst)
  - [pcf1.begin()](#pcf1begin)
  - [readEEPROM()](#readeeprom)
  - [resetFunc()](#resetfunc)
  - [setMultiplexer()](#setmultiplexer)
  - [setTime()](#settime)
  - [spacing1()](#spacing1)
  - [spacing2()](#spacing2)
  - [tca_init()](#tca_init)
  - [tca_select()](#tca_select)
  - [watchSerial()](#watchserial)
- [Standard Functions](#standard-functions)
- [Useful References](#useful-references)



# INTRODUCTION

- The Software Architecture Document (SAD) is a good practice for any software project. It is used to guide developers and maintainers in understanding and working with the software. It provides a comprehensive blueprint of the software structure, which is essential for effective maintenance and scalability of the software over time. The SAD also covers the software development practices, coding standards, and software deployment process. It serves as a reference that captures the rationale behind certain architectural decisions, which might not be immediately apparent from the code itself. Over time, as the collaborators change, having a documented architecture can ensure that the understanding of the system's design persists.
- The document tries to introduce some of the fundamental coding concepts, but it is not exhaustive. It is no substitute to reading the source code, which is heavily commented.
- In the future, the RDL SAD will be converted to the arc42 open-source template. The document might also evolve to a _System_ Architecture Documentation and include hardware architecture. For example, the present document does not include conventions about the products schematics and circuit layouts.
- The present document refers to the last available version of the main code for the latest hardware revision.
- This document is complementary with the Design Overview documents, which focus mostly on the hardware design and overall functionality. The Design Overview latest files are located in the main branch of the Jericho Git Hub repository and include the following files:
  - Design Overview - General Information.md
  - Design Overview - Atmospheric Humidity Sensor.md
  - Design Overview - Resistance Data Logger Revision E4.md
  - Design Overview - IP Camera System.md
  - Design Overview - NAU7802 Strain Current Sensor.md
  - Design Overview - Hall Effect Current Sensor.md
  - Design Overview - I2C Shield.md
  - Design Overview - pH Meter.md
  - Design Overview - Thermal Camera.md
  - Design Overview - WIRED Main Hub.md
  - Design Overview - WIRED Daemons.md
  - Design Overview - WIRED Infrared CSV.md
  - Design Overview - WIRED Python Script RDL.md
  - Design Overview - WIRED Reolink.md
  - Design Overview - WIRED Syncing.md

# HIGH-LEVEL FLOW DIAGRAM


<figure>
<p align="center">
  <img src="../Design Overview/images/flowchart.JPG"
  style="width:50%;">
    </p>
</figure>
<p align="center"> 3D view of the camera holder (v10)



# GENERAL IDEAS

- **Dataflow**: At regular interval, the RDL asks, one by one, each analog/digital sensor to provide data. The RDL collects the data and transmits it to the PC (e.g. Raspberry Pi) via an emulated Serial connection. The PC captures the incoming data from the RDL. RDL dataflow is entirely controlled by the RDL.
- **Simplicity**: The RDL coding style priorities simplicity over efficiency. This allows a greater number of users to understand and modify the code. The code is highly commented and avoids jargon, when possible, for that same purpose. Simplicity will also help early-stage AI agents grasp code more easily, as users progressively transfer coding tasks to AI tools.
- **Measurement printing:** A measurement is only made if displayed, and only displayed if made. This maximizes the measurement speed. Therefore, a single parameter is required to decide on both.
- **Parameters**: Some parameter values can be changed while using the product (e.g. acquisition interval), while others can only be changed in the source code (.ino), before compilation and upload via USB cable (e.g. type of sensors activated).
- **Language**: The programming language is C, with the use of some C/C++ libraries. The use of a procedural language (i.e. C) is deemed simpler than integrating object-oriented language (i.e. C++) into the code. Since the average user is not expected to modify the libraries, the use of C++ libraries does not increase the complexity.
- **Segmentation**: The code is divided into different files which appear as different tabs inside the Arduino IDE.
- **IDE**: We recommend using the Arduino IDE software to read and edit the source code. Since this is the most common popular IDE in the Arduino community, the code was made as compatible as possible with the Arduino IDE. More advanced user can use Visual Studio (PlatformIO), Sublime and other IDEs.
- **Memory use**: Jericho maintains the production code at a maximum of 75% of the Arduino memory. For the ATMega328p, the memory capacity is 32KB (flash), 2KB (volatile memory), 1K (EEPROM, non-volatile memory). It is possible that the user runs out of memory (flash or volatile) when adding functionalities to the RDL. Adding instances of a given sensor also increases memory usage. To solve this problem, the user has some options: 1) Use an Arduino Nano Every instead of an Arduino Nano V3, thereby increasing by 50% the available Flash memory and tripling the SRAM; 2) delete/deactivate unused functions from the code; or 3) add another RDL to the experiment.
- **Github**: The code is stored on GitHub public account of Jericho.
- **Versions**: The date is not included in the source code filename to avoid confusion with GitHub versioning. However, to easily identify the version currently running on your RDL device, the compile timestamp is printed out to the Serial Monitor at boot time. This can give you a clue that you might be running a rather old version of the firmware.
- **Memory optimization**: Multiple methods and conventions are used consistently throughout the code to reduce flash memory use (e.g. use #define, use char arrays instead of String) and SRAM memory use (e.g. send variable to flash memory). Developers must apply those techniques for their pull requests.
- **I2C extender**: The I2C extender (LTC4311) boosts the I2C bus voltage every time it detects a rising edge. This was intended to help preserve the I2C signal shape on buses with high capacitance (impedance). A low-cost oscilloscope (starting from \$60 on Amazon) can be used to evaluate the signal shape in a given setup.
  - ⚠️ **UPDATE:** Testing revealed that the LTC4311 I²C extender often degrades performance when used in combination with the I²C shield and long cables (>5 m). The root cause appears to be impedance mismatch: the LTC4311 sharpens signal edges, which leads to reflections and ringing at the transition between the shield's narrow PCB traces and the external cables. This results in communication instability or corruption.
  - Therefore, **it is recommended to deactivate all LTC4311 chips** by manually cutting the power supply trace (delicate and risky operation). This chip will likely be removed from the next RDL board revision.
- **Analog sensors**: Two types of analog sensors are natively supported by the RDL platform: resistive and analog voltages (0-5V). Each category has a dedicated section of screw terminals. The analog voltage sensor must be referenced to the same ground than the RDL. This is why the terminals provide mandatory VCC, GND and SIG pins.
- **Product evolution**: Ideas and pull requests from users will be accepted on the basis of the first principles attached to the project, as well as the mission and philosophy of the company.
- **ADC Reference**: For the Nano ADC, the 3.3V regulator is used because it produces a cleaner signal (lower level of electromagnetic noise) than the 5V bus from the USB cable (unregulated). The 3.3V bus also has fewer electronic components connected to it. This cleaner signal helps provide a more stable reading of the thermistor probes.
- **EEPROM-Initialization**: This tiny program can be found on our Github and erases the EEPROM. When the main program is subsequently re-uploaded, in the absence of any values on the EEPROM memory, it will use default values found in the Flash memory. This separate Arduino program can be necessary in some rare cases where the EEPROM parameters create such a weird RDL behavior, that the command "EEPROM-ERASE" from the main program cannot be sent or executed successfully.

# FUNDAMENTAL CONCEPTS

- **Bootloader**
  - The bootloader is a tiny program that initializes communication with the microprocessor.
- **Library**
  - A library is a piece of code that has pre-made functionalities. Like any code, a library will take memory space. The library must be installed to the Arduino IDE before being added (#included) to the code.
  - Including a library with #include will make it known to the Arduino IDE compiler, but only the parts of the library that are actually used (referred to in your code) will likely end up in the final executable - and occupy memory space. This is because most modern linkers perform a process called "link-time optimization" or "dead code elimination" where unused code is not included in the final binary.
- **Serial Communication**
  - The Nano CPU emulates a serial communication between the microcontroller and the computer. All data that is transmitted by the RDL is numerical data. Therefore, data might be lost due to noise or else, but the accuracy is not dependent on the cable used or the receiving end (i.e. computer).
- **Local and global variables**
  - A global variable exists throughout the code. It can be seen by every function. A local variable is created inside a given function and is destroyed when exiting the function. It cannot be seen by functions outside the given function.
- **Memory (flash):** Flash memory on an Arduino Nano is non-volatile storage used to hold the device's program code and is retained even when the power is turned off.
- **Memory (volatile):** Volatile memory, commonly referred to as SRAM (Static Random Access Memory) on an Arduino Nano, is used for temporary data storage while the program is running and is lost when the device is powered down or reset.
- **Memory (EEPROM)**: EEPROM (Electrically Erasable Programmable Read-Only Memory) on an Arduino Nano is a form of non-volatile memory used to store small amounts of data that must be saved between sessions, like configuration parameters, that can be read and written during runtime.
- **ADC (Analog-to-digital converter):** This device converts analog signal (voltage potential) into a numerical signal (bits). The quality of the ADC is one of the factors that limits the best accuracy obtainable with a data logger. The Arduino Nano uses a 10-bit ADC. This means that it can translate its voltage range (ex: 0-3.3V) from bit 0 to 1023 (2^10). The ADS1115 is a 16-bit ADC that translates its voltage from bit 0 to 65535 (2^16). This is 64-fold increase in conversion accuracy. Measurements that use the getVoltFunc() have the ADC selection as function input (readMode 1 = ADS1115, readMode = 0 for Nano ADC).
- **Variable types:** A number of common variable types are found in the code. Here are short definitions in the context of 8-bit microcontrollers, like Nano's ATMega328p. The variable types are important since 1) they might have incompatibilities with the certain logical or mathematical operations and 2) might cause waste of memory resources.
  - **char**: A char stores a single byte of data, which can represent a single character in the ASCII encoding scheme. It is typically used to store characters like 'a' or '\$', or control characters like '\\n' (newline).
  - **int**: On the Arduino platform, an integer (int) stores a 16-bit (2-byte) value. This means it can store values between -32,768 and 32,767.
  - **long**: A long stores a 32-bit (4-byte) value. Thus, it can contain values from -2,147,483,648 to 2,147,483,647.
  - **unsigned long**: An unsigned long is a 32-bit (4-byte) value that can hold integers from 0 to 4,294,967,295.
  - **String (upper case 'S')**: This is an object type provided by the Arduino library, representing a string of characters, but with overhead due to dynamic memory allocation and the methods it provides.
  - **string (lower case 's')**: In Arduino programming, the term string typically refers to an array of characters that is used to store text. This is the traditional C-style string, which is a sequence of characters terminated with a null character (\\0). It is a lower-level way of handling strings compared to the String class, and it is generally more memory-efficient, which is appreciated in a resource-constrained environment like the Arduino.
  - **uint8_t**: An unsigned 8-bit integer (1-byte), capable of storing values between 0 and 255. It is often used for raw binary data, byte-level operations, and optimizing memory usage.
  - **float**: On the Arduino, a float is a 32-bit (4-byte) value with a precision of approximately 6-7 decimal digits. It represents a single-precision floating-point number.
  - **struct**: A composite data type that allows grouping of variables of potentially different types under one name, useful for representing complex data structures.
  - **#define**: This is a preprocessor directive, not a variable. It tells the compiler to replace all instances of the defined identifier in the code with the provided value or code snippet, before the actual compilation process begins. This operation happens at compile time.

# INCLUDED LIBRARIES

All libraries below are open-source and can be installed from the Arduino IDE Library Manager or it can be copied from

\\Jericho-github-repo\\rdl\\Source Code\\Arduino-libraries\\libraries  
to  
\\Arduino\\libraries.

An advanced user could remove some libraries to potentially save some memory if he does not plan on using the associated functions.

- EEPROM.h
- RTClib.h
- Wire.h (modified version, 490 Hz instead of 100 kHz)
- Adafruit_SHT4x.h
- Adafruit_ADS1X15.h
- Adafruit_PCF8574.h
- Adafruit_SleepyDog.h
- Jericho_Adafruit_NAU7802.h
- Coeff_gen/coefficients_current.h
- Coeff_gen/current_coefficients.h
- MemoryFree.h

# MAIN CODE

The main code is a separate file which contains the declarations, the setup() and loop() functions.

## DECLARATIONS

- - A number of parameters are declared in the first section of the program, before and outside the setup() and loop() functions. These are global variables.
    - User parameters, include but are not limited to:
      - Activation of each sensor type (e.g. only measure and print strain sensors)
      - Activation of the custom control signal function.
      - Activation of the noise control mechanism.
      - Activate the optional printing of the resistance values.
    - Programmer parameters, include but are not limited to:
      - Establish the reading interval
        - The reading interval applies to all active sensors, without exception.
        - The measurement interval parameter is a target only; it is not enforced. If there are too many operations to be made, the cycle will run but take longer than expected. This strategy ensures that the program will run even if the interval chosen is not realistic given the quantity of sensors selected. The user must always verify the data timestamps to ensure that the target interval is being respected.
      - Establish the default temperature units
      - Temporarily define which channels has which type of sensor (e.g. #define TEROS_PIN A1)
      - Libraries to be included
      - Indicate the series resistor value
      - Provide the Steinhart-Hart coefficients values
      - Create instances of some libraries (e.g. RTC_DS3231 rtc; )
      - Define measurement samples size.

## SETUP()

- - This function exists in every Arduino code.
    - It runs once after any power up or reset of the controller via the reset button or the reset command.
    - Initializes the serial monitor and prints some general information for the benefit of the user.
    - Tells the microcontroller unit to use the external voltage as a reference for the Analog to Digital converter (ADC). In the present case, this voltage is the 3.3V DC signal generated by the Arduino.

## LOOP()

- - This function exists in every Arduino code.
    - This function is continuously repeated as long as the end is reached.
    - Update timers.
    - Take the decision to read the probes if enough time has passed.
    - Listen to the Serial monitor for incoming commands.

# MAIN FUNCTIONS

The measurement functions do the core job of communicating with sensors and producing measurements.

## ControlFunc()

- - This function is a simple example of a control signal that can be generated by the RDL. In the provided example, if voltage for channel 0 is higher than voltage for channel 1 a non-regulated 5V signal is produced at pin D9.

## currentNAU7802()

- - Measures electrical current from a TAMURA Hall-effect sensor (model L01Z050S05) using the NAU7802 24-bit ADC module (normally used for strain gauges). It currently supports DC current only.
    - Initialization & sensor check
      - If the current sensor hasn't been set up yet, it calls beginCurrent() to initialize it.
      - Marks the sensor as present if initialization succeeds.
    - Sensor configuration
      - Enables the NAU7802, sets the sample rate (10 samples/sec), powers it via an external LDO, and runs an internal calibration.
    - Data collection with outlier rejection
      - Reads multiple ADC samples (n=2 by default, but can be larger).
      - For each pair of consecutive reads, it discards any pair with a difference greater than 5000 ADC counts.
      - Averages the accepted readings.
    - Temperature compensation (optional)
      - If currentTComp is enabled, adjusts the offset based on the measured temperature (T_comp) and a known temperature drift slope.
    - Voltage-to-current conversion
      - Converts averaged ADC counts to volts using a predefined slope and offset.
      - Subtracts a calibrated zero-load voltage (zeroValue), applies temperature drift correction, and multiplies by the Hall sensor ratio (A/V) to get amps.
    - Output values
      - Sensor temperature.
      - Temperature offset drift.
      - Last valid raw ADC reading.
      - Calculated sensor voltage.
      - Final calculated current (amps).

## initRTC()

- - Initialize the real-time clock.

## phFunc()

- - Reads the pH sensor that has been selected by the I2C multiplexer function.
    - There is a 2 minutes warm-up delay after powering up the pH sensor in the main loop, before entering the pHFunc per say, and reading the pH probe. This delay is especially essential for industrial-grade pH probe membranes, which are less porous and take more time to reach chemico-electrical equilibrium. Lab-grade probes could stabilize faster.
    - Prints out the sensor value with 3 decimals precision.
    - For more information about the probe calibration, please refer to the pH meter design overview.

## printHeader()

- - Displays the column headers for the sensor data log, based on which sensor types are currently active.
    - This function dynamically prints a title row to the serial monitor, adapting the header to match the configuration of the connected sensors (e.g., temperature, resistance, SHT40, voltage, current, Teros, strain, pH). Each active sensor type is checked via a corresponding display flag (e.g., tDisplay, ohmDisplay, etc.), and only the relevant headers are printed.
    - The formatting aligns each column with consistent spacing using the spacing2() function. This ensures proper visual alignment of sensor readings during serial output. Headers are also prefixed with markers (\*, #, etc.) for readability or parsing purposes.
    - ⚠️ The function is highly modular and assumes global flags (xDisplay) and sensor counts (qty_xx) are set appropriately before calling.

## runRTC()

- - Ask the Real-Time Clock (RTC) chip to provide the current time (standard time, no DST).
    - This data is directly printed out by the function.

## SHT40Func()

- - Checks if the SHT40 humidity/temperature sensor should be displayed and, if not yet detected, attempts initialization. Marks the sensor as present if successful.
    - Sets measurement precision to high (slower but more accurate).
    - On the first run, activates the medium heater for 1 second to remove possible condensation, prints an ampersand (&) to indicate this heating, and disables heating in subsequent runs.
    - If the sensor is present, reads temperature (°C) and relative humidity (%RH) and prints them with formatted spacing; otherwise, prints zeros.

## simpleVoltFunc()

- - This function controls the multiplexer and calls getVoltFunc() the required number of times. The output is in volts.
    - The number of measurements is controlled by QTY-V.

Measurements are always done from channel 1 and onward. This means that if channel 5 is of interest, channel 1 to 5 must be measured and printed.

## startMessage()

Print out the initial message at startup with information like temperature units, reading interval, compile date, thermistor wire resistances considered. It also prints the optional header (i.e. printHeader()).

## strainFunc()

- - The function reads data from a single specific strain sensor (i.e. load cell) connected to the system. The function name, "strain", is a misnomer; the function actually measures force and moment, from which strain values can be calculated by the user during post-treatment.
    - Initializes the NAU7802 load-cell ADC once per channel; marks the strain sensor present and increments an initialization counter when begin() succeeds. Once the counter value is equal to the number of sensors connected to the system, we assume that all NAU7802 chips have been initiated and the initialization is skipped until the next RDL reboot.
    - If present, powers the ADC on, flushes the first 10 samples (waiting for available() each time), then reads a raw ADC value.
    - Computes force \[N\] using the per-sensor calibration slope a and offset b, which are stored in the coefficients.h library (Flash memory). It also computes moment \[N·m\] using the 40 mm gauge spacing.
    - Prints the raw ADC reading (integer-formatted), the computed force, and the computed bending moment, with fixed spacing for aligned columns.
    - Powers the ADC off after the measurement to allow clean power-cycling on the next run.
    - If the sensor is not present, prints zeros for ADC, force, and moment.
    - How the main code calls it (per-channel loop)
      - Iterates over all strain channels; for each, selects the TCA9548A I²C channel, wraps the call with Wire.beginTransmission()/Wire.endTransmission(), and passes that channel's calibration coefficients from strain_matrix\[i\]\[0..1\] into strainFunc(a,b).
      - Turns on/off the sensor via pcf3/pcf4, inserts short delays to avoid bus glitches, and re-initializes the mux with tca_init() after each reading to prevent I²C bus jams.
    - In future developments, to save space on the Flash, strain coefficients could be uploaded to EEPROM memory.
    - For more information about the calibration process, consult the "NAU7802 Strain Current Sensor" Design Overview.

## terosFunc()

- - Reads the TEROS 10 analog sensor that has been selected by the multiplexer function.

Prints out the sensor value in relevant units (Pa, m<sup>3</sup>/m<sup>3</sup>).

## thermistor()

- - Reads a single thermistor probe sensor that has been selected by the multiplexer function.
    - The function inputs are: the channel number, the read mode, and the Steinhart coefficients (A, B, C).
    - If readMode ==0, the Nano ADC is used. If readMode == 1, the ADS1115 ADC is used instead (more accurate).
    - The function returns two outputs in a single structure: the resistance value (Ω) and the temperature value (C/F/K). The function does not print anything to the Serial Terminal.
    - For the coefficients, ten (10) decimals must be entered into the program in order to obtain the nominal accuracy of the device.
    - Some parameter values are stored in the EEPROM (i.e. temperature units, reading interval, QTY-T, QTY-V). The serial command will update the value stored and therefore, after restart, the value is retained.
    - Each thermistor probe has a slightly different temperature-resistance relationship. However, contrarily to early versions of the RDL, there are no custom Steinhart-Hart coefficients. The individual probe calibration process is now used to exclude probes outside the system-level accuracy target (i.e. +/- 0.5°C) (see GNU Octave analysis) . This greatly simplifies the user experience by avoiding the frequent manipulation of 10-decimals probe coefficients, and allowing the interchangeability of probes.
    - The thermistor function takes into account the internal electrical resistance (70 ohms) of the two multiplexers in order to accurately predict the temperature.
    - Beside non-linearity, the thermistor's main weakness is self-heating. This is because current goes through the highly resistive component in order to measure it, causing heat generation via the Joule effect. This effect is largely minimized by measuring the value a small fraction of time. The thermistor multiplexers are only enabled (via a dedicated pin) for the short period where the reading occurs. This beneficial strategy is reduced when doing high-frequency measurements, where a higher fraction of time is under tension. If making 400 measurements per second, this Joule effect becomes noticeable again. The nominal accuracy is calculated for a 1 second measurement interval. The Joule effect is less in water (high specific thermal capacity value) compared with air.
    - In a similar way, the cable resistance must be calculated and added to the code. Otherwise, the error will increase with wire length and gauge number.

# SUPPORT FUNCTIONS

The support functions are those functions doing support tasks for the measurements and control functions. They are presented here in alphabetical order.

## ADS1115.begin()

- - Native function from the ADS1115 library (by Adafruit) to initialize the 16-bit ADC chip for high-accuracy measurements.

## blink()

- - This function is used to blink the LED on the Arduino Board. This function is used to signal some activities to the user.

## calculatePhi()

- - Returns the soil water tension (matric potential) in \[Pa\], computed from the volumetric water content (VWC) input (in \[m³/m³\]) as measured by the analog sensor (i.e. TEROS 10).
    - Soil water tension represents the mechanical energy a plant must exert to extract water from the soil. The lower the soil water content, the higher the mechanical energy required to extract water from the soil. Other factors, such as soil composition, also influence the energy requirement. This relationship between water content and tension is modeled using the common van Genuchten semi-empirical equation, which approximates the soil water retention curve.
    - ⚠️ Note: The current implementation uses a generic sample curve, not calibrated to local soil properties. Therefore, it should not be used for field operations without soil-specific parameterization.

## commands()

- - commands() is a function called by watchSerial(). If the Serial Monitor has received a non-empty string, the commands() function runs the appropriate command based on the incoming text.
    - If the RDL has 20 sensors, once it starts to read the 20 sensors, no command will be able to interrupt the read sequence until it ends, which can take over 10 to 60 seconds. This is why the program verifies any incoming command with watchSerial() at multiple points through the loop().
    - The function contains multiple pseudo-functions (code snippets activated by if() statements):
      - Celsius (Use Celsius as temperature units)
      - Fahrenheit (Use Fahrenheit as temperature units)
      - Kelvin (Use Kelvin as temperature units)
      - Qty-T (Update the number of temperature probes active)
      - Qty-V (Update the number of analog sensors (voltages) active)
      - Interval (Update the time interval for periodic measurements)
      - EEPROM-Erase (Erase the EEPROM, forcing the use of default settings)
      - Help (Print out the available commands)
      - Reset (Reset the microcontroller)

## getI2Cfreq()

- - The RDL operates its I2C bus at an abnormally low clock frequency: 489Hz instead of 100,000Hz. It allows the I2C protocol to operate effectively on very long cables (i.e. 30m). More information can be found in the source code (i.e. twi_readme.txt).
    - The getI2Cfreq() function allows the user to confirm that the I2C bus is truly operating at the expected frequency for long cable communication.
    - The function reads the hardware register values (e.g. TWSR, TWBR) and preprocessor macros (e.g. F_CPU) defined by AVR/io.h to calculate the effective I2C bus frequency and return the result to startMessage() for print out.

## getVoltFunc()

- - This function is called by the simpleVoltFunc() for voltage measurements and also the terosFunc for soil moisture measurements.
    - getVoltFunc() only makes the actual measurement. It does not print out anything.
    - Depending on the selected option, the function will either use the ADS1115 chip or the Nano ADC to make a measurement.

## i2cScan()

- - This function scans the I2C bus for all connected devices, including those on the main I2C bus and any multiplexed sensors attached to the TCA9548 multiplexer. It helps in detecting both the RTC chip and other I2C devices connected to the system.
    - Trigger: The function is executed when the I2CSCAN command is sent via the Serial Monitor. It is called by the commands() function.
    - Multiplexer Handling: The function begins by selecting each I2C channel of the TCA9548 multiplexer one at a time using the tcaselect() function, ensuring that only one channel is active during each scan.
    - Address Scanning: It scans all 128 possible I2C addresses (from 0x00 to 0x7F). The scan skips the address of the multiplexer (TCAADDR) to avoid detecting the multiplexer itself.
    - Device Detection: For each address, the function attempts to communicate using Wire.beginTransmission(addr) and checks for acknowledgment with Wire.endTransmission(). If a response is received, the device at that address is considered active.
    - Output: The detected I2C devices are printed in the Serial Monitor, with the format Found I2C 0xXX, where 0xXX is the address of the device. The output will include any devices connected via the multiplexer (e.g., sensor modules like the ADS1115, PCF8574, etc.) as well as the RTC (DS3231).
    - Limitation: Since the function does not filter out duplicate devices, devices on the full bus, including the RTC chip, may appear multiple times (one for each active multiplexer channel). For example, the RTC might show up multiple times if it is connected to different multiplexer channels.
    - Future Development:
      - Multi-Shield Support: The function may be enhanced to support multiple I2C shields.
      - Duplicate Filtering: Future improvements could include preventing the printing of duplicate devices and refining the output to print devices only once, regardless of the multiplexer channel.
      - Instance Generation: Another potential future feature would be to automatically generate instances for sensors found during the scan.
      - Enhanced Output: Sensor names (e.g., EZO-PH, NAU7802) might be printed alongside their addresses for better clarity in future updates.

## I2CSelect()

- - Allows to select which i2c sensor the Nano communicates with by controlling the TCA9548 multiplexer channel.

## isDST()

- - Determines if the current date falls within the Daylight Saving Time period, as defined in Canada and USA. The function assumes the input (local compile time, "DateTime dt") is already localized. There is no detection of time zone, location, or offset. It also approximates that DST starts at midnight, not 2:00AM.
    - Returns true if we are within the Daylight-Saving Time period, otherwise returns false.

## pcf1.begin()

- - Initializes the PCF8574 I²C GPIO expander using the Adafruit PCF8574 library. This is a native method provided by the library and must be called before interacting with the chip. In this setup, multiple instances of the PCF8574 class are used (e.g., pcf1, pcf2, pcf3, pcf4), each assigned a unique I²C address (0x20, 0x21, etc.). These PCF chips are responsible for switching MOSFETs that control power supply lines: 1) Analog sensor supply (VCC, GND), 2) Digital sensor supply on the I²C shield (VCC, GND). Each PCF device acts as a remote I/O controller, enabling or disabling sensor power through its GPIO outputs.

## readEEPROM()

- - Read the EEPROM memory in search of stored parameters to be retrieved.
    - The table below lists the EEPROM addresses used in the RDL code revE2.
    - If the readEEPROM() function cannot find values for any of these variables, it will use default values. Addresses go from 0 to 1000, since the EEPROM is 1 kB. When you access an EEPROM address, you are reading or writing one byte (8 bits) of data.

| EEPROM ADDRESS | VARIABLE NAME | MEANING | VARIABLE TYPE | SIZE (BYTES) |
| --- | --- | --- | --- | --- |
| 0   | units_T | Temperature units | uint8_t | 1   |
| 4   | readInterval | reading interval | long | 4   |
| 8   | numberC_ROM | Number of channels | uint8_t | 1   |
| 9   | numberV_ROM | Number of channels | uint8_t | 1   |
| 100 | ohmDisplay_ROM | Display Resistance Values | bool | 1   |

## resetFunc()

- - Tiny one-line function that allows a software reset of the Nano without using the physical reset button. By asking the Nano to read the byte 0, it effectively resets the MCU.

## setMultiplexer()

- - Selects the desired input channel (0-7) on a single CD74HC4051 analog multiplexer by setting the appropriate logic levels on the three select pins (S0, S1, S2).
        - Input: channel (integer from 0 to 7)
        - Effect: Routes the chosen input channel of the CD74 multiplexer to the common output (e.g., for sensor reading).
    - Note: This function assumes the ENABLE pin is already active (LOW) and does not activate or disable the multiplexer.

## setTime()

- - Sets the RTC (Real-Time Clock) to the last compile time of the code. This time is used as the base timestamp for logged data.
    - By default, the function applies the non-DST (standard) time, regardless of the compiling computer's time zone or daylight saving setting. To correct for this, the function calls isDST() to check whether the current date falls within the Daylight Saving Time period, and also checks whether the user has indicated that DST is used in the local area.
    - If both conditions are true, the function subtracts 1 hour from the compile time before writing it to the RTC, effectively reverting to standard time.

## spacing1()

- - Tiny function used to add the right number of spaces to keep the columns straight in the Serial Monitor window. Spacing1() concerns the numbers, while spacing2() concerns text.

## spacing2()

- - Tiny function used to add the right number of spaces to keep the columns straight in the Serial Monitor window. Spacing1() concerns the numbers, while spacing2() concerns text.

## tca_init()

- - Initializes the TCA9548A I²C multiplexer located on the optional I2C shield.
    - The TCA9548A is an I²C multiplexer that enables the Arduino microcontroller to communicate with up to 8 separate I²C buses (SDA/SCL pairs), allowing multiple devices with identical I²C addresses to coexist on a single system. Each of the 8 channels can be activated individually to route communication to the desired device.
    - Upon power-up, the internal state of the TCA9548A is undefined, meaning one or more channels could be unintentionally active. This function ensures a clean and deterministic startup by writing 0b00000000 to the control register, thereby disabling all channels.
    - This prevents:
      - Bus contention between devices with shared addresses
      - Noise from floating or uninitialized I²C lines
      - Unintended communication with downstream sensors
    - For more implementation details, refer to the I2C Shield Design Overview document.

## tca_select()

- - Selects a specific channel (0-7) on the TCA9548A I²C multiplexer, allowing communication with one sensor on that channel.
    - The function writes a bitmask to the TCA control register using 1 << i, which shifts a 1 to the bit corresponding to the desired channel. For example:
      - i = 0 → 0b00000001 → enables channel 0
      - i = 3 → 0b00001000 → enables channel 3
    - All other channels are disabled.
    - If i > 7, the function exits without doing anything.

## watchSerial()

- - Small function called at every loop to monitor any potential incoming command from the Serial Monitor.

# STANDARD FUNCTIONS

Here below is a non-exhaustive list of standard functions used by the RDL code. These functions are part of the Arduino native environment or the standard libraries included. More details about these standard functions can be found on the official Arduino website.

- analogRead()
- analogReference()
- delay()
- digitalWrite()
- EEPROM.read()
- EEPROM.write()
- millis()
- pinMode()
- RTC_DS3231()
- Serial.begin()
- Wire.begin()
- Wire.beginTransmission()
- Wire.endTransmission()
- Wire.requestFrom()
- Wire.read()
- Wire.setWireTimeout()
- Wire.write()

# USEFUL REFERENCES

Arduino. (n.d.). Language reference. Retrieved August 8, 2025, from <https://www.arduino.cc/reference>

Working Software. (n.d.). Software architecture documentation: The ultimate guide. Retrieved August 8, 2025, from <https://www.workingsoftware.dev/software-architecture-documentation-the-ultimate-guide/>

Coulombe, F. (2025, August). Annex: Temperature measurements Accuracy [White paper]. Jericho Labs. https://github.com/jericho-lab/rdl

Coulombe, F. (2025, August 31). Octave code for Jericho [Computer code]. GitHub. https://github.com/jericho-lab/rdl

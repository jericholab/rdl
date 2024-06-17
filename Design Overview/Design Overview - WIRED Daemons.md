**WIRED DAEMONS 1.1.0 - Design Overview**  
=======================================
Copyright: Jericho Laboratory Inc. License: CC-BY-SA.

**Table of Contents**


1. [GENERAL](#general)
2. [CONFIGURATION FILES](#configuration-files)
3. [BASH SCRIPTS](#bash-scripts)
4. [How to operate more sensors](#how-to-operate-more-sensors)
5. [Updates](#updates)

## GENERAL

A daemon is the name given to services in the Linux environment and more generally to any background process that runs independently of interactive user interfaces. In this document, the two names "daemons" and "services" are used interchangeably. It is pronounced like "demon" but the Linux programmers decided to use the latin spelling of the word.

RDL data logging can be done via the python scripts but when launched through command windows or Python IDE, there are two inconvenients: 
1) Each script has to be started manually after boot.
2) Each script can be closed accidentally.

The daemon makes the data logging resilient by solving these two problems. Note that the python scripts should not be run independently while the daemon is active. This would cause two instances to call the same USB port, for example.

Various types of daemons exist, but in this sub-project we only use services type.

## CONFIGURATION FILES

Each daemon is controlled by a configuration file with extension file ".service". In the WIRED project, there are 5 configuration files:

1) wired-syncing.service
2) wired-logging-infrared-JPG.service  
3) wired-logging-RDL-USB0.service      
4) wired-logging-reolink1.service
5) wired-logging-infrared-CSV.service 

Each configuration files creates a service for the Python script with the same name.


Here is an example of configuration file content:  

[Unit]<br>
Description=WIRED Infrared CSV<br>
After = network.target<br>
[Service]<br>
ExecStart= sudo -u orangepi python3 /home/orangepi/Desktop/SHELF3/<br>
WIRED-logging-Infrared-CSV.py<br>
Restart = always<br>
RestartSec=60<br>
[Install]<br>
WantedBy=multi-user.target<br>


A configuration file is structured in sections, each denoted by square brackets, containing settings that modify how the service behaves. Here's a brief overview of the parameters in the given example:

    [Unit] Section: General settings applicable at the unit level.
    Description: Briefly describes the purpose or identity of the unit.
    After: Specifies that this unit should start after the listed unit, ensuring proper order of service startup. In this case, it ensures that the network is available first.

    [Service] Section: Specifies how the service should behave and be managed.
    ExecStart: Commands or scripts that are executed when this service starts. Here, the Python script for the infrared camera is started with sudo privilege and the orangepi user.
    Restart: Policy for restarting the service automatically if it stops.
    RestartSec: Time to wait before restarting the service. A 60 seconds delay will avoid triggering the error associated with too many restart in a short period.
    WorkingDirectory: This setting can be used if the working directory should be different than the configuration file location. This is necessary for the syncing script, for example.

    [Install] Section: Controls how the unit is "installed" by enabling it.
    WantedBy: Defines the target that this unit should be started under, influencing when the service starts during the boot process.

## BASH SCRIPTS  
The bash scripts are heavily commented but a short description is given below.

**wired-enable-start-all-daemons.sh**  
After a configuration file has been written, it needs to be enabled. Daemons are managed by systemd and systemctl. Running the script ($ sudo ./wired-enable-start-all-daemons.sh) will add all configurations files found to the list of services, enable the start at boot and will attempt to start immediately.
Running the script twice will not duplicate the service, only overwrite. This script should be run after modifying the configuration file for changes to be effective.

**wired-verify-status-daemons.sh**  
To verify that each python script is running properly, open a terminal in the "/daemons-wired" folder, and execute  "$ sudo ./wired-status-daemons.sh". Use page up and page down to look at all the lines.

**wired-disable-stop-all-daemons.sh**  
To stop the services, run this script once.

## How to operate more sensors
In the advent where you would like to run more than one surveillance camera or one infrared camera or one data logger, you must duplicate the whole system (script, service) and adapt the names and port numbers. There is presently no automatic detection of devices or quantities, but this is a potential future development.

## Updates
The revision number in the title (e.g. 1.1.0) refers to the revision of the set of scripts and configuration files. In the future, there will be independent revisions of the files and of the documentation (whose versions are managed by the Github system).

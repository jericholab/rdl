PYTHON SCRIPTS

The python scripts allow the integration of the surveillance camera, the infrared camera and the RDL Data Logger into the Orange Pi 4 LTS. The Python scripts can be run in various ways:
1) Run a single script within Thonny
2) Run all scripts by executing the shell script "WIRED-runAll.sh"
3) Run them via Daemons (next section)


DAEMONS

A shell script (.sh) will activate permanent services (daemons) via configuration files (.services) which run the usual python scripts (e.g. infrared.py).

1- Stop all the WIRED python scripts, if any were running.

2- Open a new terminal in the "/daemons-wired "folder, and execute  "$ sudo ./wired-enable-start-all-daemons.sh". This will copy a few files into the system, enable the daemons, start the scripts and show status.

3- You can verify the scripts are running by verifying the usual output (/logging-folder).

4- If you only want to verify that each python script is running, open a terminal in the "/daemons-wired "folder, and execute  "$ sudo ./wired-status-daemons.sh". Use page up and page down to look at all the lines.

5- Reboot the computer and verify the scripts are still running (since the daemons have been enable, they will start at boot time)

6- If you want to stop and disable all the scripts, execute  "$ sudo ./wired-disable-stop-all-daemons.sh"

7- If you wish to stop temporarily a given script (e.g. infrared camera), "$ systemctl stop infrared.service"  (It WILL restart at next OS reboot)

8- If you wish to stop permanently a given script (e.g. infrared camera), "$ systemctl disable infrared.service"  (It WILL NOT restart at next OS reboot)

Remember to keep the files associated with daemons in their own subfolder.

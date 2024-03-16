#!/bin/sh -e

#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.


# Emptying the trash to make enough space
printf "Empty the trash...\n"
sudo rm -rf ~/.local/share/Trash/files/*
sudo rm -rf /media/orangepi/SD_CARD1/.Trash-1000/files/*

# Print the IP address
_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  printf "My IP address is/are %s\n" "$_IP"
fi

sleep 5  # 5sec delay  


sudo -u orangepi lxterminal --command="python3 /home/orangepi/SHELF3/WIRED-logging-RDL-USB0.py" &
sudo -u orangepi lxterminal --command="python3 /home/orangepi/SHELF3/WIRED-logging-Reolink1.py" &
sudo -u orangepi lxterminal --command="python3 /home/orangepi/SHELF3/WIRED-logging-Infrared-JPG.py" &
#sudo -u orangepi lxterminal --command="python3 /home/orangepi/SHELF3/WIRED-logging-Infrared-CSV.py" &
lxterminal --command="python3 /home/orangepi/SHELF3/WIRED-syncing.py" &

exit 0

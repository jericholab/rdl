#!/bin/bash

# step 0: Find all .service files in the current directory and store them in the LIST variable
#LIST=$(find . -name "wired-*.service" -exec basename {} \; )  #basename removes the path and keeps the name only

LIST="wired-logging-infrared-JPG.service \
wired-syncing.service \
wired-logging-RDL-USB0.service \
wired-logging-reolink1.service"
# pick one by one the services desired
# wired-logging-infrared-CSV.service \   #removed CSV mode from the list of active services

# step 1 : copy each service file in the current folder into the systemd folder
sudo cp *.service /etc/systemd/system/
echo "Copying each service file into the systemd folder..."

# step 2 : enable the service
sudo systemctl enable $LIST
echo "Enabling the services..."

# step 3 : start the service
sudo systemctl start $LIST
echo "Start the services..."

# step 4: display the status of the service in a new terminal
echo "Display the status of the services..."
lxterminal --command="systemctl status $LIST"

# step 5: offer to reboot
echo "Do you want to reboot the PC now to verify start at boot? (y/N)"
read confirm
if [[ $confirm == [Yy] ]]; then
    echo "Rebooting now..."
    sudo reboot
else
    echo "Reboot canceled."
fi

#!/bin/bash

# step 0: Find all .service files in the current directory and store them in the LIST variable
#LIST=$(find . -name "wired-*.service" -exec basename {} \; )  #basename removes the path and keeps the name only

LIST="wired-logging-infrared-JPG.service \
wired-syncing.service \
wired-logging-RDL-USB0.service \
wired-logging-reolink1.service"
# pick one by one the services desired
# wired-logging-infrared-CSV.service \   #removed CSV mode from the list of active services

# step 1 : copy each service file in the current folder into the systemd folder
sudo cp *.service /etc/systemd/system/
echo "Copying each service file into the systemd folder..."

# step 2 : enable the service
sudo systemctl enable $LIST
echo "Enabling the services..."

# step 3 : start the service
sudo systemctl start $LIST
echo "Start the services..."

# step 4: display the status of the service in a new terminal
echo "Display the status of the services..."
lxterminal --command="systemctl status $LIST"

# step 5: offer to reboot
echo "Do you want to reboot the PC now to verify start at boot? (Y/N)"
read confirm
if [[ $confirm == [Yy] ]]; then
    echo "Rebooting now..."
    sudo reboot
else
    echo "Reboot canceled."
fi


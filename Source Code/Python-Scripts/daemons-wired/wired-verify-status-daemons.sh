#!/bin/bash

# step 0: Find all .service files in the current directory and store them in the LIST variable
#LIST=$(find . -name "wired-*.service" -exec basename {} \; )  #basename removes the path and keeps the name only

LIST="wired-logging-infrared-JPG.service \
wired-syncing.service \
wired-logging-RDL-USB0.service \
wired-logging-reolink1.service"
# pick one by one the services desired
# wired-logging-infrared-CSV.service \   #removed CSV mode from the list of active services


# step 1: display the status of the service in a new terminal
echo "Display the status of the services..."
lxterminal --command="systemctl status $LIST"



#!/bin/bash

# step 0: Find all .service files in the current directory and store them in the LIST variable
LIST=$(find . -name "wired-*.service" -exec basename {} \; )  #basename removes the path and keeps the name only
echo $LIST

# step 1 : Stop the services
sudo systemctl stop $LIST
echo "Stop the WIRED services..."

# step 2 : Disable the service
sudo systemctl disable $LIST
echo "Disabling the WIRED services..."

# step 3: Display the status of the service in a new terminal
echo "Display the status of the services..."
lxterminal --command="systemctl status $LIST"



#!/usr/bin/env bash

# Set version
version="1.8.19"

# Download the Arduino IDE tar.xz file
wget https://downloads.arduino.cc/arduino-$version-linux64.tar.xz

# Extract the downloaded file
tar -xf arduino-$version-linux64.tar.xz

# Move the Arduino IDE directory to /opt
sudo mv arduino-$version /opt

# Navigate to the Arduino directory and run the install script
cd /opt/arduino-$version
./install.sh

# Output success message
echo "Arduino IDE $version has been installed successfully!"

# End of script

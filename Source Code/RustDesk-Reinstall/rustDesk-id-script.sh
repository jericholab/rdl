#!/bin/bash

# Stop RustDesk service
echo "Stopping RustDesk service..."
echo 'raspberry' | sudo -S systemctl stop rustdesk.service

# Kill RustDesk process
echo "Killing RustDesk process..."
echo 'raspberry' | sudo -S pkill rustdesk

# Purge RustDesk
echo "Purging RustDesk..."
echo 'raspberry' | sudo -S apt-get purge rustdesk -y

# Remove RustDesk configuration directory
echo "Removing RustDesk configuration..."
echo 'raspberry' | sudo -S rm -r /home/pi/.config/rustdesk

# Remove machine ID
echo "Removing machine ID..."
echo 'raspberry' | sudo -S rm /etc/machine-id

# Setup new machine ID
echo "Setting up new machine ID..."
echo 'raspberry' | sudo -S systemd-machine-id-setup

# Install RustDesk
echo "Installing RustDesk..."
echo 'raspberry' | sudo -S dpkg -i $HOME/Downloads/rustdesk-1.2.3-2-aarch64.deb

# Start RustDesk
echo "Starting RustDesk..."
rustdesk

#!/bin/bash

NETPLAN_DIR="/etc/netplan"
UDEV_DIR="/etc/udev/rules.d"
SERVICE_DIR="/usr/lib/systemd/system" 

# libusb on mac for flash to work
# brew unlink libusb
# brew install --head libusb

# resize the disk
sudo ./scripts/resizeDisk.sh eMMC

# general update 
sudo apt-get update
sudo apt-get upgrade -y

# install additional tools 
sudo apt-get install i2c-tools -y

# install netplan
sudo cp netplan/* $NETPLAN_DIR
sudo netplan apply

# speedtest
curl -s https://packagecloud.io/install/repositories/ookla/speedtest-cli/script.deb.sh | sudo bash
sudo apt-get install speedtest -y

# vim
cp scripts/vimrc ${HOME}vimrc

# dds config
cp scripts/CycloneDDSConfig.xml ${HOME}

#install udev rules
sudo cp udev/*.rules ${UDEV_DIR}
sudo udevadm control --reload-rules
sudo udevadm trigger


#!/bin/bash
# This installs some thing we need on navq to access the console
INSTALL_DIR=/usr/share/droidz
BIN_DIR=/usr/bin

./scripts/get_depend

# python dependencies
sudo pip3 install pymavlink pyserial
sudo apt install -y tcpdump

# copy the scripts 
sudo mkdir -p  ${INSTALL_DIR}/scripts
sudo cp scripts/px4 ${INSTALL_DIR}/scripts
sudo cp scripts/mavlink_shell.py ${INSTALL_DIR}/scripts
sudo chmod a+x ${INSTALL_DIR}/scripts/px4 

# link the executable 
sudo ln -s ${INSTALL_DIR}/scripts/px4 ${BIN_DIR}/px4 

#!/bin/bash

# manual install
sudo pip install bme680

# install udev rules
sudo cp udev/*.rules /etc/udev/rules.d
sudo udevadm control --reload-rules && sudo udevadm trigger

# full install 
#curl https://get.pimoroni.com/bme680 | bash

# development
# sudo python3 setup.py install


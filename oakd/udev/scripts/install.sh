#!/bin/bash

# fix wifi 
sudo apt install install connman
sudo sed s/nameserver 127.0.0.53/8.8.8.8/ /etc/resolve.conf

# udev rule
sudo cp udev/*.rules /etc/udev/rules.d
sudo udevadm control --reload-rules && sudo udevadm trigger

# install adapter for humble 
sudo apt-get update
sudo apt-get upgrade -y
sudo apt install -y ros-humble-depthai-ros


# directions for how to setup the pipelines on ros2
# https://github.com/luxonis/depthai-ros




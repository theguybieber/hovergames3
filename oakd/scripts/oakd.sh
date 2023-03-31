#!/bin/bash
# TODO customize imagery capture 

pushd depend/depthai-python
    python3 setup.py 
    python3 examples/ColorCamera/rgb_camera_control.py
popd 


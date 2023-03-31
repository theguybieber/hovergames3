#!/bin/bash

#
ros2 launch depthai_examples stereo_inertial_node.launch.py 

# oakd - mobilenet
ros2 launch depthai_examples mobile_publisher.launch.py camera_model:=OAK-D

# oak - mobilenet
ros2 launch depthai_examples mobile_publisher.launch.py camera_model:=OAK-D

# other examples
#rgb_publisher.launch.py
#rgb_stero_node.launch.py
#stereo.launch.py
#stereo_inertial_node.launch.py
#yolo4_publisher.launch.py




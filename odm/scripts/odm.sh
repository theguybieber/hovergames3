#!/bin/bash
# Generates NVDI image based on Drone Data
PROJECT_DIR=$1
IMAGES_DIR=$PROJECT_DIR/images

if [[ -d $PROJECT_DIR  ]] && [[ -d $IMAGES_DIR ]]; then

    # Basic Processing
    ./run.sh $PROJECT_DIR

    # NDVI Processing
    mkdir -p ${PROJECT_DIR}/ndvi
    python ndvi.py ${PROJECT_DIR}/odm_orthophoto/odm_orthophoto.tif 1 2 ${PROJECT_DIR}/ndvi/ndvi.tif
    return 0;

else
    echo "You must specify a project directory that has an images directory"
    echo "with the images to process"
    return 1
fi


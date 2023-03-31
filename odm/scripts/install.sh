#!/bin/bash
# This is a mac only install

scripts/get_depend

pushd depend/ODM
    bash configure_macos.sh install
popd depend/ODM


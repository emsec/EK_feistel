#!/usr/bin/bash

# Get the OS version
OS_VERSION=$(lsb_release -rs)

# Check if the OS version matches Ubuntu 22.04
if [ "$OS_VERSION" != "22.04" ]; then
    echo "This script can only be run on Ubuntu 22.04. Detected version: $OS_VERSION"
    exit 1
fi

sudo apt-get -y install virtualbox-guest-utils virtualbox-guest-x11 plasma-desktop konsole
sudo apt-get -y install qtbase5-dev qt5-qmake git g++
sudo apt-get -y install libqt5svg5-dev qtquickcontrols2-5-dev libqt5quickwidgets5 qtdeclarative5-dev
sudo apt-get -y install qtcreator

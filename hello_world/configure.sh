#!/usr/bin/bash
echo Installing dependencies...
echo

# Install Crosscompiler
dpkg -l | grep gcc-arm-none-eabi &> /dev/null
if [[ $? -eq 0 ]]
then
    echo gcc-arm-none-eabi already installed 
    echo
else
    echo Installting gcc-arm-none-eabi
    sudo apt install gcc-arm-none-eabi
    echo
fi

# Install mkimage to create boot.scr from boot.cmd
dpkg -l | grep u-boot-tools &> /dev/null

if [[ $? -eq 0 ]]
then
    echo u-boot-tools already installed 
    echo
else
    echo Installting u-boot-tools
    sudo apt install u-boot-tools
    echo
fi

# u-boot-tools to generate boot.scr from boot.cmd
#sudo apt install u-boot-tools
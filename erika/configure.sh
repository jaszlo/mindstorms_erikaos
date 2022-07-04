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

# Install qemu for arm system i.e. the versatilepb MCU 
dpkg -l | grep qemu-system-arm &> /dev/null
if [[ $? -eq 0 ]]
then
    echo qemu-system-arm already installed 
    echo
else
    echo Installting qemu-system-arm
    sudo apt install qemu-system-arm
    echo
fi


# Install python3.9 for testcase script helper
dpkg -l | grep "python3.9 " &> /dev/null
if [[ $? -eq 0 ]]
then
    echo python3.9 already installed 
    echo
else
    echo Installting python3.9
    sudo apt install python3.9
    echo
fi

# Install pip3 for python for testcase script helper
dpkg -l | grep "python3-pip" &> /dev/null
if [[ $? -eq 0 ]]
then
    echo python3-pip already installed 
    echo
else
    echo Installting python3-pip and required dependencies
    sudo apt install pip3
    pip install pynput
    echo
fi

# Compiling third-party tools
if [[ -f "./third_party/wermit/wermit" ]]
then
    echo wermit allready installed
    echo
else
    echo Compiling wermit from source
    cd third_party/wermit
    make linux
    echo
fi

#!/bin/sh
#This is an install script for the AFIB module

echo "Starting install script, please remember to launch as sudo."

#Add the boot script to the init.d
#This will make the AFIB software launch on reboot
echo "Creating a boot script."
cp ./Bootscript/AFIBBoot /etc/init.d/AFIBBoot
chmod 755 /etc/init.d/AFIBBoot
update-rc.d AFIBBoot defaults
echo "Done"

#Next install relevant packages
echo "Installing wiring Pi."
apt-get update
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
cd ..
echo "Done"

#Next install the python libraries needed
echo "Installing neccessary packages"
apt-get install python-dev
apt-get install python-numpy python-scipy
echo "Done"

#Next install the AFIB software
echo "Building software package"
cd ./Software
make clean
make
cd ..
echo "Done"

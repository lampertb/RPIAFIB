#!/bin/sh
#This is an install script for the AFIB module

echo "Starting install script, please remember to launch as sudo."

#Add the boot script to the init.d
#This will make the AFIB software launch on reboot
cp ./Bootscript/AFIBBoot /etc/init.d/AFIBBoot
chmod 755 /etc/init.d/AFIBBoot
update-rc.d AFIBBoot defaults

cd ./Software
make clean
make



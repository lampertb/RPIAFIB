#!/bin/sh
#This script launches the program
#It also toggles the LED's to indicate that the board is running

#Launch program
/home/pi/Software/bin/execute_afib_detect &

#Toggle LED at GPIO 0 every second
#Status LED
gpio -g mode 0 out
while [ 1 ]
do
echo "toggling" >> log
gpio -g write 0 1
sleep 1
gpio -g write 0 0
sleep 1
done


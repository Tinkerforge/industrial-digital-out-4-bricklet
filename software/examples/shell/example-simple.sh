#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# Turn pins alternating high/low for 10 times with 100 ms delay
for i in 0 1 2 3 4 5 6 7 8 9; do
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 1
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 2
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 4
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 8
done

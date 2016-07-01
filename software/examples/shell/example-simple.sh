#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

# Turn pins alternating high/low 10 times with 100ms delay
for i in 0 1 2 3 4 5 6 7 8 9; do
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 1 # 1 << 0 = 1
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 2 # 1 << 1 = 2
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 4 # 1 << 2 = 4
	sleep 0.1
	tinkerforge call industrial-digital-out-4-bricklet $uid set-value 8 # 1 << 3 = 8
done

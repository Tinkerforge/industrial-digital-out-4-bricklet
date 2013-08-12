#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# turn pins 0, 3 high and pins 1, 2 low: (1 << 0) | (1 << 3) = 9
tinkerforge call industrial-digital-out-4-bricklet $uid set-value 9

#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "xyz" # Change to your UID

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_industrial_digital_out_4 import IndustrialDigitalOut4

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    ido4 = IndustrialDigitalOut4(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Turn relays alternating on/off for 10 times with 100ms delay
    for i in range(10):
        time.sleep(0.1)
        ido4.set_value(1 << 0)
        time.sleep(0.1)
        ido4.set_value(1 << 1)
        time.sleep(0.1)
        ido4.set_value(1 << 2)
        time.sleep(0.1)
        ido4.set_value(1 << 3)

    raw_input('Press key to exit\n') # Use input() in Python 3

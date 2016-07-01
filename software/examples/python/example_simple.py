#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_industrial_digital_out_4 import BrickletIndustrialDigitalOut4

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    ido4 = BrickletIndustrialDigitalOut4(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Turn pins alternating high/low 10 times with 100ms delay
    for i in range(10):
        time.sleep(0.1)
        ido4.set_value(1 << 0)
        time.sleep(0.1)
        ido4.set_value(1 << 1)
        time.sleep(0.1)
        ido4.set_value(1 << 2)
        time.sleep(0.1)
        ido4.set_value(1 << 3)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()

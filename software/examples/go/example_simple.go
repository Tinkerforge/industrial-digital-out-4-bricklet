package main

import (
	"fmt"
	"time"
	"tinkerforge/industrial_digital_out_4_bricklet"
	"tinkerforge/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ido4, _ := industrial_digital_out_4_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Set pins alternating high/low 10 times with 100ms delay
	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		ido4.SetValue(1 << 0)
		time.Sleep(100 * time.Millisecond)
		ido4.SetValue(1 << 1)
		time.Sleep(100 * time.Millisecond)
		ido4.SetValue(1 << 2)
		time.Sleep(100 * time.Millisecond)
		ido4.SetValue(1 << 3)
	}

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}


#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_out_4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "xyz" // Change to your UID

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalOut4 ido4;
	industrial_digital_out_4_create(&ido4, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Turn pins 0, 3 high and pins 1, 2 low
	industrial_digital_out_4_set_value(&ido4, 1 | 8);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}

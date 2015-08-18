#include <stdio.h>

#define IPCON_EXPOSE_MILLISLEEP

#include "ip_connection.h"
#include "bricklet_industrial_digital_out_4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalOut4 ido4;
	industrial_digital_out_4_create(&ido4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn pins alternating high/low for 10 times with 100 ms delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 0);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 1);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 2);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 3);
	}

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}

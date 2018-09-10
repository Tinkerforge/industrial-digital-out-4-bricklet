import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletIndustrialDigitalOut4;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Industrial Digital Out 4 Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIndustrialDigitalOut4 ido4 =
		  new BrickletIndustrialDigitalOut4(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set pins alternating high/low 10 times with 100ms delay
		for(int i = 0; i < 10; i++) {
			Thread.sleep(100);
			ido4.setValue(1 << 0);
			Thread.sleep(100);
			ido4.setValue(1 << 1);
			Thread.sleep(100);
			ido4.setValue(1 << 2);
			Thread.sleep(100);
			ido4.setValue(1 << 3);
		}

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}

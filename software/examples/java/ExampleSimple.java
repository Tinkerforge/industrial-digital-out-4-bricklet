import com.tinkerforge.BrickletIndustrialDigitalOut4;
import com.tinkerforge.IPConnection;

public class ExampleSimple {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "xyz"; // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		// Create connection to brickd
		IPConnection ipcon = new IPConnection(host, port); // Can throw IOException
		BrickletIndustrialDigitalOut4 ido4 = new BrickletIndustrialDigitalOut4(UID); // Create device object

		// Add device to IP connection
		ipcon.addDevice(ido4); // Can throw IPConnection.TimeoutException
		// Don't use device before it is added to a connection

		// Turn pins alternating high/low for 10 times with 100 ms delay 
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

		System.console().readLine("Press key to exit\n");
		ipcon.destroy();
	}
}

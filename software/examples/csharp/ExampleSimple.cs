using System;
using System.Threading;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIndustrialDigitalOut4 ido4 =
		  new BrickletIndustrialDigitalOut4(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set pins alternating high/low 10 times with 100ms delay
		for(int i = 0; i < 10; i++)
		{
			Thread.Sleep(100);
			ido4.SetValue(1 << 0);
			Thread.Sleep(100);
			ido4.SetValue(1 << 1);
			Thread.Sleep(100);
			ido4.SetValue(1 << 2);
			Thread.Sleep(100);
			ido4.SetValue(1 << 3);
		}

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}

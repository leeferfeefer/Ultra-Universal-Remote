/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;


class UltraUniversalRemote {


	private static boolean isDebugMode;

	private static final String errorRunMsg = "\nTo run, type: \n"
		+ "java -cp bluecove.jar:. UltraUniversalRemote.java -d \n"
		+ "-d = debug mode (optional) \n";


	static {
		print("\nUltra Universal Remote Initiated");
		print(errorRunMsg);
	}
	







	public static void main(String[] args) {
		
		argsChecker(args);

		UURLocalDevice uurLocalDevice = new UURLocalDevice(isDebugMode);
		LocalDevice localDevice = uurLocalDevice.getUURLocalDevice();
		if (localDevice != null) {
			
			UURDiscoveryAgent uurAgent = new UURDiscoveryAgent(isDebugMode);
			uurAgent.discoverDevices(localDevice);


		}


	}

















	/* ------------------------
			    Methods
	-------------------------- */ 

	private static void print(String message) {
		System.out.println(message);
	}
	private static void argsChecker(String[] args) {
		int argsLength = args.length;
		if (argsLength == 1) {
			debugMode();
		}
	}
	private static void debugMode() {
		print("\nDebug Mode Initiated\n");
		isDebugMode = true;
	}




}
/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;
import java.util.Vector;

class UURDiscoveryAgent {

	private boolean isDebugMode; 



	UURDiscoveryAgent(boolean isDebugMode) {
		this.isDebugMode = isDebugMode;
	}




	void discoverDevices(LocalDevice uurLocalDevice) {
		DiscoveryAgent agent = uurLocalDevice.getDiscoveryAgent();

		Object lock = new Object();

		UURDiscoveryListener deviceListener = new UURDiscoveryListener(lock, isDebugMode);

		try {
			if (isDebugMode) {
				print("\nSearching for devices...");
			}
			agent.startInquiry(DiscoveryAgent.GIAC, deviceListener);
		} catch (BluetoothStateException bse) {
			print("Error searching for devices");
			print(bse.getMessage());
		}


		// Pause main thread to search for devices
		try {
			synchronized(lock){
				lock.wait();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		
		Vector deviceList = deviceListener.getDeviceList();
		int deviceCount = deviceList.size();

		if (isDebugMode) {
			print("The device count is " + deviceCount);
		}

		if (deviceCount <= 0) { 
			print("No devices found"); 
		} else { 



			// If found device... connect to it send commands



			// //print bluetooth device addresses and names in the format [ No. address (name) ] 
			// System.out.println("Bluetooth Devices: "); 
			// for (int i = 0; i < deviceCount; i++) { 
			// 	RemoteDevice remoteDevice = (RemoteDevice)deviceList.elementAt(i);

			// 	System.out.println((i+1) + ". " + remoteDevice.getBluetoothAddress()); 
			// 		// + 
			// 			// " (" + remoteDevice.getFriendlyName(true) + ")");
			// 	try {
					 

			// 	} catch (Exception e) {
			// 		print("\nError attempting to get UUR Local Device:");
			// 		print(e.getMessage());
			// 	} 
			// } 
		} 
	}




	/* ------------------------
			    Methods
	-------------------------- */ 

	private void print(String message) {
		System.out.println(message);
	}
	


}
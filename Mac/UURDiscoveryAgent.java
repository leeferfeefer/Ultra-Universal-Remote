/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;
import java.util.Vector;

class UURDiscoveryAgent {

	private boolean isDebugMode; 
	private LocalDevice uurLocalDevice;
	private	DiscoveryAgent agent;


	UURDiscoveryAgent(boolean isDebugMode, LocalDevice uurLocalDevice) {
		this.isDebugMode = isDebugMode;
		this.uurLocalDevice = uurLocalDevice;

		this.agent = uurLocalDevice.getDiscoveryAgent();
	}




	void discoverDevices() {

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

			if (isDebugMode) {

				print("\nBluetooth Devices: "); 
			
				for (int i = 0; i < deviceCount; i++) { 
					RemoteDevice remoteDevice = (RemoteDevice)deviceList.elementAt(i);

					try {
						String deviceName = remoteDevice.getFriendlyName(false);

						print("The device name is: " + deviceName);

						if (deviceName.equals("HC-06")) {
							print("Arduino found");
						}
						
					} catch (Exception e) {
						print("\nError attempting to get UUR Remote Device name");
						print(e.getMessage());
					} 
				} 
			}
		} 
	}




	/* ------------------------
			    Methods
	-------------------------- */ 

	private void print(String message) {
		System.out.println(message);
	}
	
	RemoteDevice[] getDevices() {
		return agent.retrieveDevices(DiscoveryAgent.CACHED);
	}

}
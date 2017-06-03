/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;
import java.util.Vector;



class UURDiscoveryListener implements DiscoveryListener {

	private boolean isDebugMode; 
	private Object lock;


	UURDiscoveryListener(Object lock, boolean isDebugMode) {
		this.lock = lock;
		this.isDebugMode = isDebugMode;
	}


	private static Vector deviceList = new Vector();
	
	public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) { 

		if (isDebugMode) {
			print("Device discovered: " + btDevice.getBluetoothAddress());
		}

		if (!deviceList.contains(btDevice)){ 
			deviceList.addElement(btDevice); 
		} 
	} 

	public void servicesDiscovered(int transID, ServiceRecord[] servRecord) { } 

	public void serviceSearchCompleted(int transID, int respCode) { } 

	
	public void inquiryCompleted(int discType) { 
		synchronized(lock) { 
			lock.notify(); 
		} 

		if (isDebugMode) {
			print("Inquiry Status: ");
			switch (discType) { 
				case DiscoveryListener.INQUIRY_COMPLETED: 
					print("INQUIRY_COMPLETED"); 
					break; 
				case DiscoveryListener.INQUIRY_TERMINATED: 
					print("INQUIRY_TERMINATED"); 
					break; 
				case DiscoveryListener.INQUIRY_ERROR: 
					print("INQUIRY_ERROR"); 
					break; 
				default: 
					print("Unknown Response Code"); 
					break; 
			}
		}
	}







	/* ------------------------
			    Methods
	-------------------------- */ 

	private void print(String message) {
		System.out.println(message);
	}
	
	Vector getDeviceList() {
		return deviceList;
	}
	
}
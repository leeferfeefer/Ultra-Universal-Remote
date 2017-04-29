//
//  ViewController.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "ViewController.h"

#define deviceName @"SH-HC-08"
#define deviceUUID [CBUUID UUIDWithString:@"FFE0"]
#define dataTransferUUID [CBUUID UUIDWithString:@"FFE1"]

@interface ViewController ()

@property (strong, nonatomic) CBCentralManager *centralManager;
@property (strong, nonatomic) CBPeripheral *arduinoPeripheral;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    CBCentralManager *manager = [[CBCentralManager alloc] initWithDelegate:self queue:nil options:nil];
    self.centralManager = manager;
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)startScanning {
    
    NSLog(@"Scanning...");
    
    [self.centralManager scanForPeripheralsWithServices:nil options:nil];
}








- (void)writeWithPeripheral:(CBPeripheral *)peripheral andCharacteristic:(CBCharacteristic *)characteristic{
    
    if (!self.arduinoPeripheral || peripheral != self.arduinoPeripheral) {
        return;
    }
    
    NSLog(@"writing...");
    
    
    
    NSString *one = @"1";
    NSData *data = [one dataUsingEncoding:NSUTF8StringEncoding];
    
    
    
    //[peripheral readValueForCharacteristic:characteristic];
    
    
    
    
    //    int count = 0;
    //    while (count < 100) {
    [self.arduinoPeripheral writeValue:data forCharacteristic:characteristic type:CBCharacteristicWriteWithoutResponse];
    //        count++;
    //    }
    
    
    
}























#pragma mark - CBCentral Manager Delegate Methods

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    
    
    // Validate peripheral information
    if (!peripheral || !peripheral.name || ([peripheral.name isEqualToString:@""])) {
        return;
    }
    
    NSLog(@"Discovered device: %@", peripheral.name);
    
    
    
    
    
    if (peripheral.state == CBPeripheralStateDisconnected) {
        
        if ([peripheral.name isEqualToString:deviceName]) {
            
            NSLog(@"Arduino discovered");
            
            self.arduinoPeripheral = peripheral;
            self.arduinoPeripheral.delegate = self;
            
            [self.centralManager connectPeripheral:peripheral options:nil];
        }
    }
}
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    
    if (!peripheral) {
        return;
    }
    
    NSLog(@"Arduino connected");
    NSLog(@"the UUID is %@", peripheral.identifier);
    
    if (peripheral == self.arduinoPeripheral) {
        [peripheral discoverServices:nil];
    }
    
    
    // Stop scanning for new devices
    [self.centralManager stopScan];
    
    NSLog(@"Scanning for devices stopped");
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    
    NSLog(@"peripheral disconnected");
    
    if (!peripheral) {
        return;
    }
    
    // See if it was our peripheral that disconnected
    if (peripheral == self.arduinoPeripheral) {
        self.arduinoPeripheral = nil;
        //        self.peripheralBLE = nil;
    }
    
    // Start scanning for new devices
    [self startScanning];
}


- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    
    switch (self.centralManager.state) {
        case CBManagerStatePoweredOff:
        {
            //    [self clearDevices];
            NSLog(@"state changed to powered off");
            
            break;
        }
            
        case CBManagerStateUnauthorized:
        {
            // Indicate to user that the iOS device does not support BLE.
            NSLog(@"state changed to unauthorized");
            break;
        }
            
        case CBManagerStateUnknown:
        {
            // Wait for another event
            NSLog(@"state changed to unknown");
            break;
        }
            
        case CBManagerStatePoweredOn:
        {
            NSLog(@"state changed to powered on");
            [self startScanning];
            break;
        }
            
        case CBManagerStateResetting:
        {
            // [self clearDevices];
            NSLog(@"state changed to resetting");
            break;
        }
            
        case CBManagerStateUnsupported:
        {
            NSLog(@"state changed to unsupported");
            break;
        }
            
        default:
            break;
    }
    
}







#pragma mark - CBPeripheral Delegate Methods

-(void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    
    if (error) {
        NSLog(@"error discovering services");
        return;
    }
    
    for (CBService *service in peripheral.services) {
        if ([service.UUID isEqual:deviceUUID]) {
            [peripheral discoverCharacteristics:nil forService:service];
        }
    }
}
-(void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    
    if (error) {
        NSLog(@"error discovering characteristics");
        return;
    }
    
    for (CBCharacteristic *characteristic in service.characteristics) {
        if ([characteristic.UUID isEqual:dataTransferUUID]) {
            //NSLog(@"sending data... ");
            
            [self writeWithPeripheral:peripheral andCharacteristic:characteristic];
        }
    }
}








#pragma mark - Writing and Receiving methods


//when the CBCharacteristicWriteWithResponse type is used.
-(void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error{
    
    if (error) {
        NSLog(@"error writing to peripheral");
        NSLog(@"the error is %@", error);
        return;
    }
}

-(void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    
    if (error) {
        NSLog(@"error");
        return;
    }
    
    
    NSLog(@"received");
    NSLog(@"updated value from arduino");
}



@end

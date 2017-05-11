//
//  devicesTableView.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "devicesTableView.h"


#define arduinoName @"SH-HC-08"


@interface devicesTableView ()

@property (strong, nonatomic) NSMutableArray *deviceList;
@property (strong, nonatomic) NSMutableArray *deviceNames;


@property (strong, nonatomic) CBCentralManager *centralManager;

@property (strong, nonatomic) CBPeripheral *selectedDevice;


@end

@implementation devicesTableView

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.deviceList = [NSMutableArray new];
    self.deviceNames = [NSMutableArray new];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
    CBCentralManager *manager = [[CBCentralManager alloc] initWithDelegate:self queue:nil options:nil];
    self.centralManager = manager;




    if ([WCSession isSupported]) {
        WCSession *session = [WCSession defaultSession];
        session.delegate = self;
        [session activateSession];
        NSLog(@"WCSession is supported");
    }
}
//-(void)viewDidDisappear:(BOOL)animated {
//    [self viewDidDisappear:animated];
//    
//    self.selectedDevice = nil;
//
//    [self.deviceList removeAllObjects];
//}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


















#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.deviceList count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"deviceCell" forIndexPath:indexPath];
    
    CBPeripheral *cellPeripheral = self.deviceList[indexPath.row];
    cell.textLabel.text = cellPeripheral.name;
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    // Try and connect to device
    
    CBPeripheral *selectedDevice = self.deviceList[indexPath.row];

    if ([selectedDevice.name isEqualToString:arduinoName]) {
        
        [self.centralManager stopScan];
        
        self.selectedDevice = selectedDevice;
        
        [self.centralManager connectPeripheral:self.selectedDevice options:nil];


        
    } else {
        
        NSLog(@"unknown way of connecting to device");
        
    }
    
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}
















-(void)startScanning {
    
    NSLog(@"Scanning...");
    
    [self.centralManager scanForPeripheralsWithServices:nil options:nil];
}
-(void)stopScanning {
    
    // Stop scanning for new devices
    [self.centralManager stopScan];
    
    NSLog(@"Scanning for devices stopped");
}
















#pragma mark - CBCentral Manager Delegate Methods

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    
    
    // Validate peripheral information
    if (!peripheral || !peripheral.name || ([peripheral.name isEqualToString:@""])) {
        return;
    }
    
    NSLog(@"Discovered device: %@", peripheral.name);
    
    
    
    [self.deviceList addObject:peripheral];
    
    [self.deviceTableView reloadData];

    [self.deviceNames addObject:peripheral.name];

    [self sendToWatch:@{@"deviceNames" : self.deviceNames}];

    // Send data to watch
//    NSUserDefaults *defaults = [[NSUserDefaults alloc] initWithSuiteName:@"group.com.UUR.sharedData"];
//    [defaults setValue:self.deviceList forKey:@"deviceList"];
//    [defaults synchronize];



    
    /*
    
    
    
    if (peripheral.state == CBPeripheralStateDisconnected) {
        
        if ([peripheral.name isEqualToString:deviceName]) {
            
            NSLog(@"Arduino discovered");
            
            self.arduinoPeripheral = peripheral;
            self.arduinoPeripheral.delegate = self;
            
            [self.centralManager connectPeripheral:peripheral options:nil];
        }
    }
     */
}













- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    
    if (!peripheral) {
        return;
    }
    
    [self stopScanning];

    [self sendToWatch:@{@"connectionStatus" : @"connected"}];

    [self performSegueWithIdentifier:@"showDeviceUI" sender:nil];
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    
    NSLog(@"peripheral disconnected");
    
    if (!peripheral) {
        return;
    }
    
    // See if it was our peripheral that disconnected
    if (peripheral == self.selectedDevice) {
        self.selectedDevice = nil;
    }
    
    // Start scanning for new devices
    [self startScanning];

    [self.navigationController popToRootViewControllerAnimated:YES];
}


- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    
    switch (self.centralManager.state) {
        case CBManagerStatePoweredOff:
        {
            [self clearDevices];
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
             [self clearDevices];
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





















#pragma mark - Segue Methods 

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"showDeviceUI"]) {
        
        deviceRemote *remote = [segue destinationViewController];
        remote.device = self.selectedDevice;
    }
}



-(void)clearDevices {
    [self.deviceNames removeAllObjects];
    [self.deviceList removeAllObjects];

    self.selectedDevice = nil;

    [self.deviceTableView reloadData];
}



#pragma mark - Connectivity Methods

-(void)sendToWatch:(NSDictionary *)message{

    if ([[WCSession defaultSession] isReachable]) {
        //Here is where you will send you data

        NSLog(@"watch reachable");

        [[WCSession defaultSession] sendMessage:message
                                   replyHandler:^(NSDictionary *reply) {
                                       NSLog(@"%@", reply[@"reply"]);
                                   } errorHandler:^(NSError *error) {
                                       NSLog(@"error sending message to watch");
                                   }];


    } else {
        NSLog(@"watch not reachable");
    }
}




#pragma mark - Session Delegate Methods

-(void)session:(WCSession *)session activationDidCompleteWithState:(WCSessionActivationState)activationState error:(NSError *)error {
    NSLog(@"session activated");
}
-(void)sessionDidBecomeInactive:(WCSession *)session {
    NSLog(@"became inactive");
}
-(void)sessionDidDeactivate:(WCSession *)session {
    NSLog(@"session deactivated");
}
-(void)sessionWatchStateDidChange:(WCSession *)session {
    NSLog(@"state changed");
}

-(void)session:(WCSession *)session didReceiveMessage:(NSDictionary<NSString *,id> *)message {
    NSLog(@"message received");
}

-(void)session:(WCSession *)session didReceiveMessage:(NSDictionary<NSString *,id> *)message replyHandler:(void (^)(NSDictionary<NSString *,id> * _Nonnull))replyHandler {
    NSLog(@"message received on iphone");


    NSLog(@"the message is %@", message);

    replyHandler(@{@"reply" : @"Index received"});


    CBPeripheral *selectedDevice = self.deviceList[[message[@"index"] integerValue]];

    if ([selectedDevice.name isEqualToString:arduinoName]) {

        [self.centralManager stopScan];

        self.selectedDevice = selectedDevice;

        [self.centralManager connectPeripheral:self.selectedDevice options:nil];

    } else {

        NSLog(@"unknown way of connecting to device");
        
    }

}

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)refreshButtonPressed:(UIButton *)sender {

    NSLog(@"pressed");

    [self clearDevices];
    [self startScanning];
}
@end

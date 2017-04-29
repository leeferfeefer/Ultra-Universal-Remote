//
//  deviceRemote.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "deviceRemote.h"


// Arduino
#define arduinoUUID [CBUUID UUIDWithString:@"FFE0"]
#define arduinoDataTransferUUID [CBUUID UUIDWithString:@"FFE1"]



@interface deviceRemote ()


@property (nonatomic, strong) CBService *dataService;
@property (nonatomic, strong) CBCharacteristic *dataCharacteristic;


@end

@implementation deviceRemote

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    
    self.device.delegate = self;

    [self.device discoverServices:nil];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}





#pragma mark - CBPeripheral Delegate Methods

-(void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    
    if (error) {
        NSLog(@"error discovering services");
        return;
    }
    
    NSLog(@"discovering services");
    
    for (CBService *service in peripheral.services) {
        if ([service.UUID isEqual:arduinoUUID]) {
            [peripheral discoverCharacteristics:nil forService:service];
        }
    }
}
-(void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    
    NSLog(@"discovering characteristics");
    
    if (error) {
        NSLog(@"error discovering characteristics");
        return;
    }
    
    for (CBCharacteristic *characteristic in service.characteristics) {
        if ([characteristic.UUID isEqual:arduinoDataTransferUUID]) {
         
            self.dataCharacteristic = characteristic;
            self.dataService = service;
            
        }
    }
}
























/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/







- (IBAction)upButtonPressed:(UIButton *)sender {
    
    
    
}

- (IBAction)centerButtonPressed:(UIButton *)sender {
}

- (IBAction)leftButtonPressed:(UIButton *)sender {
}

- (IBAction)downButtonPressed:(UIButton *)sender {
}

- (IBAction)rightButtonPressed:(UIButton *)sender {
}

- (IBAction)playPauseButtonPressed:(UIButton *)sender {
}

- (IBAction)menuButtonPressed:(UIButton *)sender {
}







-(void)sendCommand:(NSString *)command{
    
    
    NSData *data = [command dataUsingEncoding:NSUTF8StringEncoding];
    
    [self.device writeValue:data forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];
    
}








@end

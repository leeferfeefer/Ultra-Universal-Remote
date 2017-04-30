//
//  deviceRemote.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "deviceRemote.h"
#import "codes.h"


// Arduino
#define arduinoUUID [CBUUID UUIDWithString:@"FFE0"]
#define arduinoDataTransferUUID [CBUUID UUIDWithString:@"FFE1"]




@interface deviceRemote ()

@property (nonatomic, strong) codes *codeManager;

@property (nonatomic, strong) CBService *dataService;
@property (nonatomic, strong) CBCharacteristic *dataCharacteristic;

@property BOOL appleTV;
@property BOOL denTV;



@end

@implementation deviceRemote

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    

    self.codeManager = [[codes alloc] initCodes];



    
    self.device.delegate = self;

    [self.device discoverServices:nil];
    
    self.appleTV = YES;
    
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




#pragma mark - Button Methods

- (IBAction)upButtonPressed:(UIButton *)sender {
    [self upAction];
}
- (IBAction)centerButtonPressed:(UIButton *)sender {
    [self selectAction];
}
- (IBAction)leftButtonPressed:(UIButton *)sender {
    [self leftAction];
}
- (IBAction)downButtonPressed:(UIButton *)sender {
    [self downAction];
}
- (IBAction)rightButtonPressed:(UIButton *)sender {
    [self rightAction];
}
- (IBAction)playPauseButtonPressed:(UIButton *)sender {
    [self playPauseAction];
}
- (IBAction)menuButtonPressed:(UIButton *)sender {
    [self menuAction];
}






#pragma mark - Button Method Helpers

-(void)upAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_up];
    } else if (self.denTV) {
        
    }
}
-(void)downAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_down];
    } else if (self.denTV) {

    }
}
-(void)leftAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_left];
    } else if (self.denTV) {

    }
}
-(void)rightAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_right];
    } else if (self.denTV) {

    }
}
-(void)selectAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_select];
    } else if (self.denTV) {

    }
}
-(void)menuAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_menu];
    } else if (self.denTV) {

    }
}
-(void)playPauseAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_play_pause];
    } else if (self.denTV) {

    }
}




-(void)sendCommand:(NSArray *)command{
    
    
//    NSData *data = [command dataUsingEncoding:NSUTF8StringEncoding];

    NSData *data = [NSKeyedArchiver archivedDataWithRootObject:command];


    [self.device writeValue:data forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];
    
}








- (IBAction)segmentControlValueChanged:(UISegmentedControl *)sender {
    self.appleTV = !self.appleTV;
    self.denTV = !self.denTV;
}
@end

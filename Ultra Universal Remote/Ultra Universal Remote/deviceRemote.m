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

#define MAX_BYTES 50


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

            [self.device setNotifyValue:YES forCharacteristic:self.dataCharacteristic];
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

    NSString *returnValue = [[NSString alloc] initWithData:characteristic.value encoding:NSUTF8StringEncoding];

    NSLog(@"Arduino: %@", returnValue);

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
        [self sendCommand:@[self.codeManager.den_tv_vol_down]];
    }
}
-(void)rightAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_right];
    } else if (self.denTV) {
        [self sendCommand:@[self.codeManager.den_tv_vol_up]];
    }
}
-(void)selectAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_select];
    } else if (self.denTV) {
        [self sendCommand:@[self.codeManager.den_tv_power]];
    }
}
-(void)menuAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_menu];
    } else if (self.denTV) {
        [self sendCommand:@[self.codeManager.den_tv_input]];
    }
}
-(void)playPauseAction{
    if (self.appleTV) {
        [self sendCommand:self.codeManager.apple_play_pause];
    } else if (self.denTV) {

    }
}





-(void)sendCommand:(NSArray *)command{

    NSLog(@"Sending command...");

    NSString *commandString;

    if (self.appleTV) {
        [self.device writeValue:[@"AppleTV $" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];

        commandString = [self convertAppleTVCommandToString:command];

    } else if (self.denTV) {
        [self.device writeValue:[@"DenTV $" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];

        commandString = command[0];
    }

    NSLog(@"the command string is %@", commandString);

    NSUInteger bytes = [commandString lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"the total number of bytes is %lu", (unsigned long)bytes);

    if (bytes > MAX_BYTES) {
        [self chunkData:commandString withTotalBytes:bytes];
    } else {
        [self.device writeValue:[@"1 /" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];
        [self.device writeValue:[commandString dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];
        [self.device writeValue:[@"*" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];
    }
}


-(NSString *)convertAppleTVCommandToString:(NSArray *)command {
    NSString *commandString = @"";

    for (int i = 0; i < [command count]/2; i++) {
        commandString = [NSString stringWithFormat:@"%@ %ld", commandString, (long)[command[i] integerValue]];
    }

    // Take the first space out
    commandString = [commandString substringWithRange:NSMakeRange(1, [commandString length]-1)];


    return commandString;
}




-(void)chunkData:(NSString *)commandString withTotalBytes:(NSUInteger )numBytes {

    int chunks = (int)numBytes / MAX_BYTES;
    int remainder = numBytes % MAX_BYTES;

    if (remainder > 0) {
        chunks++;
    }

    // Send number of chunks
    [self.device writeValue:[[NSString stringWithFormat:@"%d /", chunks] dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];

    NSString *chunk = @"";

    // chunk data
    for (int i = 0; i < chunks; i++) {

        int index = i*MAX_BYTES;

        if (index == (int)numBytes - remainder) {
            chunk = [commandString substringWithRange:NSMakeRange(index, remainder)];
        } else {
            chunk = [commandString substringWithRange:NSMakeRange(index, MAX_BYTES)];
        }


        NSLog(@"Sending %@", chunk);

        [self.device writeValue:[chunk dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];

        // delimeter
        [self.device writeValue:[@"*" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.dataCharacteristic type:CBCharacteristicWriteWithoutResponse];


    }
}






- (IBAction)segmentControlValueChanged:(UISegmentedControl *)sender {

    NSLog(@"Device changed");

    self.appleTV = !self.appleTV;
    self.denTV = !self.denTV;


    if (self.appleTV) {
        [self.playPauseButton setHidden:NO];
        [self.menuButton setTitle:@"Menu" forState:UIControlStateNormal];
        [self.centerButton setTitle:@"Select" forState:UIControlStateNormal];
        [self.leftButton setTitle:@"Left" forState:UIControlStateNormal];
        [self.rightButton setTitle:@"Right" forState:UIControlStateNormal];
    } else if (self.denTV) {
        [self.playPauseButton setHidden:YES];
        [self.menuButton setTitle:@"Input" forState:UIControlStateNormal];
        [self.centerButton setTitle:@"Power" forState:UIControlStateNormal];
        [self.leftButton setTitle:@"-" forState:UIControlStateNormal];
        [self.rightButton setTitle:@"+" forState:UIControlStateNormal];
    }
}

@end

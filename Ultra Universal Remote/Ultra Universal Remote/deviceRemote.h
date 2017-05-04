//
//  deviceRemote.h
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>


@interface deviceRemote : UIViewController < CBPeripheralDelegate>


@property (nonatomic, strong) CBPeripheral *device;


@property (strong, nonatomic) IBOutlet UISegmentedControl *segmentedControl;
- (IBAction)segmentControlValueChanged:(UISegmentedControl *)sender;


@property (strong, nonatomic) IBOutlet UIButton *upButton;
@property (strong, nonatomic) IBOutlet UIButton *centerButton;
@property (strong, nonatomic) IBOutlet UIButton *leftButton;
@property (strong, nonatomic) IBOutlet UIButton *downButton;
@property (strong, nonatomic) IBOutlet UIButton *rightButton;
@property (strong, nonatomic) IBOutlet UIButton *playPauseButton;
@property (strong, nonatomic) IBOutlet UIButton *menuButton;


- (IBAction)upButtonPressed:(UIButton *)sender;
- (IBAction)centerButtonPressed:(UIButton *)sender;
- (IBAction)leftButtonPressed:(UIButton *)sender;
- (IBAction)downButtonPressed:(UIButton *)sender;
- (IBAction)rightButtonPressed:(UIButton *)sender;
- (IBAction)playPauseButtonPressed:(UIButton *)sender;
- (IBAction)menuButtonPressed:(UIButton *)sender;




@property (strong, nonatomic) IBOutlet UIButton *inputButton;
- (IBAction)inputButtonPressed:(UIButton *)sender;









@end

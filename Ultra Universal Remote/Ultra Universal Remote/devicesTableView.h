//
//  devicesTableView.h
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/28/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>

#import "deviceRemote.h"

@interface devicesTableView : UITableViewController <CBCentralManagerDelegate>


@property (strong, nonatomic) IBOutlet UITableView *deviceTableView;

@end

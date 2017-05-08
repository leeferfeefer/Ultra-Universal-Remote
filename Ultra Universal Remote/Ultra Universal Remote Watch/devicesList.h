//
//  devicesList.h
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 5/4/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>
#import "devicesRowController.h"
#import <WatchConnectivity/WatchConnectivity.h>

@interface devicesList : WKInterfaceController <WCSessionDelegate>

@property (strong, nonatomic) IBOutlet WKInterfaceLabel *errorLabel;


@property (strong, nonatomic) IBOutlet WKInterfaceTable *devicesTable;


@end

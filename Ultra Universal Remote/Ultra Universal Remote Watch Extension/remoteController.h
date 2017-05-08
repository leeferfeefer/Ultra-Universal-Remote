//
//  remoteController.h
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 5/6/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>

@interface remoteController : WKInterfaceController

- (IBAction)menuItemPressed;

@property (strong, nonatomic) IBOutlet WKInterfaceLabel *deviceLabel;

@end

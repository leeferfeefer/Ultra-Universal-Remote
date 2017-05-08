//
//  remoteController.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 5/6/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "remoteController.h"

@interface remoteController ()

@end

@implementation remoteController

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];
    
    // Configure interface objects here.
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

- (IBAction)menuItemPressed {
}
@end




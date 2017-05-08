//
//  devicesList.m
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 5/4/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import "devicesList.h"

@interface devicesList ()

@property (strong, nonatomic) NSMutableArray *devices;


@end

@implementation devicesList


- (void)awakeWithContext:(id)context {

    [super awakeWithContext:context];
    
    // Configure interface objects here.

//    [self.label setText:@"Yo yo"];

    if ([WCSession isSupported]) {
        WCSession *session = [WCSession defaultSession];
        session.delegate = self;
        [session activateSession];
    }

    [self.errorLabel setText:@"No devices detected. Check iPhone."];
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}


-(void)table:(WKInterfaceTable *)table didSelectRowAtIndex:(NSInteger)rowIndex {

    NSLog(@"selected %ld index", (long)rowIndex);


    [self sendToiPhone:rowIndex];


    [self presentControllerWithName:@"remoteController" context:nil];
}




-(void)loadTableItems {

    [self.devicesTable setNumberOfRows:[self.devices count] withRowType:@"devicesRowController"];

    if ([self.devices count] == 0) {
        [self.errorLabel setHidden:NO];
    } else {
        [self.errorLabel setHidden:YES];
    }


    // Iterate over the rows and set the label and image for each one.
    for (NSInteger i = 0; i < self.devicesTable.numberOfRows; i++) {
        // Set the values for the row controller
        devicesRowController *row = [self.devicesTable rowControllerAtIndex:i];

        [row.label setText:self.devices[i]];

    }
}

-(NSMutableArray *)getDeviceData {
    NSUserDefaults *defaults = [[NSUserDefaults alloc] initWithSuiteName:@"group.com.UUR.sharedData"];
    return [defaults valueForKey:@"devicesList"];
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
    NSLog(@"message received on watch");

    NSDictionary *hi = [NSDictionary dictionaryWithObject:@"hi" forKey:@"message received on watch"];

    replyHandler(hi);

    NSLog(@"the message is %@", message);

    [self loadTableItems];

    self.devices = message[@"deviceNames"];


}


-(void)sendToiPhone:(NSInteger)index {

    if ([[WCSession defaultSession] isReachable]) {
        //Here is where you will send you data

        NSLog(@"reachable");

        [[WCSession defaultSession] sendMessage:[NSDictionary dictionaryWithObject:[NSNumber numberWithInteger:index] forKey:@"index"]
                                   replyHandler:^(NSDictionary *reply) {
                                       //handle reply from iPhone app here


                                   }
                                   errorHandler:^(NSError *error) {
                                       //catch any errors here
                                   }];
        
        
    } else {
        NSLog(@"not reachable");
        
    }
    
}




@end




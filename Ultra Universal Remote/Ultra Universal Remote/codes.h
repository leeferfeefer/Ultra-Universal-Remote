//
//  codes.h
//  Ultra Universal Remote
//
//  Created by Lee Fincher on 4/29/17.
//  Copyright © 2017 Danky Doodle. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface codes : NSObject


-(instancetype)initCodes;


#pragma mark - Apple TV Codes

@property (nonatomic, strong) NSArray *apple_up;
@property (nonatomic, strong) NSArray *apple_down;
@property (nonatomic, strong) NSArray *apple_left;
@property (nonatomic, strong) NSArray *apple_right;
@property (nonatomic, strong) NSArray *apple_select;
@property (nonatomic, strong) NSArray *apple_menu;
@property (nonatomic, strong) NSArray *apple_play_pause;


#pragma mark - Den TV Codes
@property (nonatomic, strong) NSString *den_tv_input;
@property (nonatomic, strong) NSString *den_tv_power;
@property (nonatomic, strong) NSString *den_tv_vol_up;
@property (nonatomic, strong) NSString *den_tv_vol_down;



#pragma mark - Home TV Codes
@property (nonatomic, strong) NSString *home_tv_vol_up;
@property (nonatomic, strong) NSString *home_tv_vol_down;








@end

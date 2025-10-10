//
//  HwWorkoutPoint.h
//  HwBluetoothSDK
//
//  Created by HuaWo on 2022/1/17.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HwWorkoutPoint : NSObject
/**
 millisecond
 */
@property (assign, nonatomic) long time;
@property (assign, nonatomic) long offsetTime;
/**
 step, -255 if none
 */
@property (assign, nonatomic) NSInteger step;
/**
 cal, -255 if none
 */
@property (assign, nonatomic) NSInteger calories;
/**
 meter, -255 if none
 */
@property (assign, nonatomic) NSInteger distance;
/**
 minutes, -255 if none
 */
@property (assign, nonatomic) NSInteger duration;
/**
 heartrate, -255 if none
 */
@property (assign, nonatomic) NSInteger bpm;
/**
 km/hour, -255 if none
 */
@property (assign, nonatomic) NSInteger speed;
/**
 second/km, -255 if none
 */
@property (assign, nonatomic) NSInteger pace;

- (BOOL) isSuspended;
- (BOOL) isSuspendedEnd;

@end

NS_ASSUME_NONNULL_END

//
//  HwGpsStatus.h
//  HwBluetoothSDK
//
//  Created by huawo01 on 2024/5/11.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HwGpsStatus : NSObject

@property (nonatomic, assign) long agpsValidStartTime;

@property (nonatomic, assign) long agpsValidEndTime;

@property (nonatomic, assign) NSString *gpsClipType;

@property (nonatomic, assign) NSString *gpsFirmwareVersion;

@property (nonatomic, assign) NSInteger gpsFirmwareBuild;

@end

NS_ASSUME_NONNULL_END

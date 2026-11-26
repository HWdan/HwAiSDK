//
//  HwDrinkWaterGoal.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 0x9B 喝水设置查询：编号 0 汇总信息（喝水目标数据）。
 字段：0x03 有效总饮水量 / 0x04 总目标 / 0x05 基础生理目标 / 0x06 运动补偿目标，单位 ml。
 */
@interface HwDrinkWaterGoal : NSObject

/** 有效总饮水量，ml。 */
@property(nonatomic, assign) NSInteger totalIntake;
/** 喝水总目标，ml。 */
@property(nonatomic, assign) NSInteger totalGoal;
/** 基础生理目标，ml。 */
@property(nonatomic, assign) NSInteger baseGoal;
/** 运动补偿目标，ml。 */
@property(nonatomic, assign) NSInteger exerciseGoal;

+ (instancetype)goalFromData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END

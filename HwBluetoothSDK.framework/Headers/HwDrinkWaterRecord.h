//
//  HwDrinkWaterRecord.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>
#import "HwDrinkWaterType.h"
#import "HwDrinkWaterGoal.h"

NS_ASSUME_NONNULL_BEGIN

@class HwDrinkWaterRecord;

/** 0x9B 查询全部响应：编号 0 为目标汇总，编号 1~255 为喝水记录。 */
@interface HwDrinkWaterQueryResult : NSObject
@property(nonatomic, strong) HwDrinkWaterGoal *goal;
@property(nonatomic, copy) NSArray<HwDrinkWaterRecord *> *records;
@end

@interface HwDrinkWaterRecord : NSObject

@property(nonatomic, assign) NSInteger recordId;
@property(nonatomic, assign) HwDrinkWaterType drinkType;
@property(nonatomic, assign) NSInteger amount;
@property(nonatomic, assign) NSTimeInterval time;

/** 解析查询全部；编号 0 → goal，1~255 → records。 */
+ (HwDrinkWaterQueryResult *)parseQueryData:(NSData *)data;
/** 解析记录列表；跳过编号 0（汇总信息）。 */
+ (NSArray<HwDrinkWaterRecord *> *)recordsFromData:(NSData *)data;
+ (NSData *)valueUnitBytesForRecord:(HwDrinkWaterRecord *)record;

@end

NS_ASSUME_NONNULL_END

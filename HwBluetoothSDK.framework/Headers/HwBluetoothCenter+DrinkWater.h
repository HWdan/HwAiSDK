//
//  HwBluetoothCenter+DrinkWater.h
//  HwBluetoothSDK
//

#import "HwBluetoothCenter.h"
#import "HwDrinkWaterRecord.h"

NS_ASSUME_NONNULL_BEGIN

/**
 查询全部喝水设置回调。
 goal 来自编号 0 汇总信息；records 来自编号 1~255。
 */
typedef void (^HwDrinkWaterRecordsCallback)(HwDrinkWaterGoal * _Nullable goal,
                                            NSArray<HwDrinkWaterRecord *> * _Nullable records,
                                            NSError * _Nullable error);
typedef void (^HwDrinkWaterRecordIdsCallback)(NSArray<NSNumber *> * _Nullable ids, NSError * _Nullable error);

@interface HwBluetoothCenter (DrinkWater)

- (HwBluetoothTask *)getAvailableDrinkWaterRecordIdsWithCallback:(HwDrinkWaterRecordIdsCallback)callback;
/** 0x9B / 0x70 / 类型 0x00：查询喝水设置（含目标汇总 + 记录）。 */
- (HwBluetoothTask *)getAllDrinkWaterRecordsWithCallback:(HwDrinkWaterRecordsCallback)callback;
- (HwBluetoothTask *)addDrinkWaterRecord:(HwDrinkWaterRecord *)record callback:(HwBoolCallback)callback;
- (HwBluetoothTask *)editDrinkWaterRecord:(HwDrinkWaterRecord *)record callback:(HwBoolCallback)callback;
- (HwBluetoothTask *)deleteDrinkWaterRecordWithId:(NSInteger)recordId callback:(HwBoolCallback)callback;
- (HwBluetoothTask *)deleteAllDrinkWaterRecordsWithCallback:(HwBoolCallback)callback;
- (HwBluetoothTask *)setAllDrinkWaterRecords:(NSArray<HwDrinkWaterRecord *> *)records callback:(HwBoolCallback)callback;

@end

NS_ASSUME_NONNULL_END

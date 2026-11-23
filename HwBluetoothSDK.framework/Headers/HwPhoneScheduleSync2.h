//
//  HwPhoneScheduleSync2.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>
#import "HwPhoneScheduleEvent2.h"
#import "HwScheduleSyncType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 一次 0x75 新协议同步会话，传给 syncPhoneSchedules2。
 Overwrite 只发 events，覆盖设备列表。
 Incremental 将 events 作为增改(0x03)，deleteIds 作为删除(0x04)。
 itemCount 写入开始包“总条数”；覆盖计 events，增量计 events+deleteIds，上限 maxCount。
 */
@interface HwPhoneScheduleSync2 : NSObject

@property(nonatomic, assign) HwScheduleSyncType syncType;
@property(nonatomic, copy) NSArray<HwPhoneScheduleEvent2 *> *events;
@property(nonatomic, copy) NSArray<NSNumber *> *deleteIds;

- (NSInteger)itemCount;

@end

NS_ASSUME_NONNULL_END

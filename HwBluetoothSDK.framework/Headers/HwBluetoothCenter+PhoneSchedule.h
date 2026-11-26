//
//  HwBluetoothCenter+PhoneSchedule.h
//  HwBluetoothSDK
//

#import "HwBluetoothCenter.h"
#import "HwPhoneScheduleEvent.h"
#import "HwPhoneScheduleSync2.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^HwPhoneSchedulesCallback)(NSArray<HwPhoneScheduleEvent2 *> * _Nullable events, NSError * _Nullable error);

@interface HwBluetoothCenter (PhoneSchedule)

- (HwBluetoothTask *)syncPhoneSchedules:(NSArray<HwPhoneScheduleEvent *> *)events callback:(HwBoolCallback)callback;
- (HwBluetoothTask *)syncPhoneSchedules2:(HwPhoneScheduleSync2 *)sync callback:(HwBoolCallback)callback;

/** 0x75 / 0x70 / 0x00：查询日程总个数。 */
- (HwBluetoothTask *)getPhoneScheduleCountWithCallback:(HwBCIntegerCallback)callback;
/** 0x75 / 0x70 / 0x01：按个数拉取全部日程（一帧一条）。 */
- (HwBluetoothTask *)getPhoneSchedulesWithCount:(NSInteger)count callback:(HwPhoneSchedulesCallback)callback;

@end

NS_ASSUME_NONNULL_END

//
//  HwBluetoothCenter+PhoneSchedule.h
//  HwBluetoothSDK
//

#import "HwBluetoothCenter.h"
#import "HwPhoneScheduleEvent.h"
#import "HwPhoneScheduleSync2.h"

NS_ASSUME_NONNULL_BEGIN

@interface HwBluetoothCenter (PhoneSchedule)

- (HwBluetoothTask *)syncPhoneSchedules:(NSArray<HwPhoneScheduleEvent *> *)events callback:(HwBoolCallback)callback;
- (HwBluetoothTask *)syncPhoneSchedules2:(HwPhoneScheduleSync2 *)sync callback:(HwBoolCallback)callback;

@end

NS_ASSUME_NONNULL_END

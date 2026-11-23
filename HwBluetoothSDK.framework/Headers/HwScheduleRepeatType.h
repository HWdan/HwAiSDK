//
//  HwScheduleRepeatType.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 0x75 / 0x03 / 0x08 重复类型。 */
typedef NS_ENUM(NSInteger, HwScheduleRepeatType) {
    HwScheduleRepeatTypeNone = 0x00,
    HwScheduleRepeatTypeDaily = 0x01,
    HwScheduleRepeatTypeWeekly = 0x02,
    HwScheduleRepeatTypeMonthly = 0x03,
    HwScheduleRepeatTypeYearly = 0x04,
    HwScheduleRepeatTypeCustomDaily = 0x05,
    HwScheduleRepeatTypeCustomWeekly = 0x06,
    HwScheduleRepeatTypeCustomMonthly = 0x07,
    HwScheduleRepeatTypeCustomYearly = 0x08,
};

NS_ASSUME_NONNULL_END

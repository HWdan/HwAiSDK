//
//  HwScheduleRepeatLimit.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, HwScheduleRepeatLimitKind) {
    HwScheduleRepeatLimitKindWeekdayMask = 0x00,
    HwScheduleRepeatLimitKindDayMask = 0x01,
    HwScheduleRepeatLimitKindMonthMask = 0x02,
    HwScheduleRepeatLimitKindMonthAndWeekday = 0x03,
};

/**
 0x0A 自定义重复限定。
 星期掩码 bit0–6 = 周日–周六；日掩码 bit1–31 = 1–31 日；月掩码 bit0–11 = 1–12 月。
 月+星期：月掩码(2) + 星期序号(1) + 星期掩码(1)。星期序号 1–5 为第 n 个，6 为倒数第 2 个，7 为最后一个。
 */
@interface HwScheduleRepeatLimit : NSObject

@property(nonatomic, assign, readonly) HwScheduleRepeatLimitKind kind;
@property(nonatomic, assign, readonly) NSInteger weekdayMask;
@property(nonatomic, assign, readonly) NSInteger dayMask;
@property(nonatomic, assign, readonly) NSInteger monthMask;
@property(nonatomic, assign, readonly) NSInteger weekIndex;

+ (instancetype)weekdays:(NSInteger)mask;
+ (instancetype)monthDays:(NSInteger)mask;
+ (instancetype)months:(NSInteger)mask;
+ (instancetype)monthAndWeekdayWithMonthMask:(NSInteger)monthMask
                                   weekIndex:(NSInteger)weekIndex
                                 weekdayMask:(NSInteger)weekdayMask;

- (NSData *)toBytes;

@end

NS_ASSUME_NONNULL_END

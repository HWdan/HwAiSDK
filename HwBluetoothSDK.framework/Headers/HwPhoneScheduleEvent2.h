//
//  HwPhoneScheduleEvent2.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>
#import "HwPhoneScheduleReminder.h"
#import "HwScheduleRepeatType.h"
#import "HwScheduleRepeatLimit.h"
#import "HwScheduleRepeatEnd.h"
#import "HwScheduleException.h"
#import "HwPhoneScheduleDateParts.h"

NS_ASSUME_NONNULL_BEGIN

/**
 0x75 新协议日程项（phase 0x03）。
 id 为 8 字节。重复规则可选；None 只发基础字段。
 最多 MAX_EXCEPTIONS 条例外。标题最多 60 UTF-8 字节，备注最多 180。
 */
@interface HwPhoneScheduleEvent2 : NSObject

/** 单次同步增改条数上限（开始帧总条数 / 增改数，限制 20；删除不计）。 */
+ (NSInteger)maxCount;
/** 单条日程最多例外数。 */
+ (NSInteger)maxExceptions;

@property(nonatomic, assign) long long eventId;
@property(nonatomic, assign) BOOL allDay;
@property(nonatomic, assign) NSInteger startYear;
@property(nonatomic, assign) NSInteger startMonth;
@property(nonatomic, assign) NSInteger startDay;
@property(nonatomic, assign) NSInteger startHour;
@property(nonatomic, assign) NSInteger startMinute;
@property(nonatomic, assign) NSInteger endYear;
@property(nonatomic, assign) NSInteger endMonth;
@property(nonatomic, assign) NSInteger endDay;
@property(nonatomic, assign) NSInteger endHour;
@property(nonatomic, assign) NSInteger endMinute;
@property(nonatomic, assign) BOOL reminderEnabled;
@property(nonatomic, copy, nullable) NSString *title;
@property(nonatomic, copy, nullable) NSString *notes;
@property(nonatomic, assign) HwScheduleRepeatType repeatType;
@property(nonatomic, assign) NSInteger repeatInterval;
@property(nonatomic, strong, nullable) HwScheduleRepeatLimit *repeatLimit;
@property(nonatomic, strong) HwScheduleRepeatEnd *repeatEnd;

- (void)setReminders:(NSArray<HwPhoneScheduleReminder *> *)reminders;
- (NSArray<HwPhoneScheduleReminder *> *)reminders;
- (void)clearReminders;

- (void)setExceptions:(NSArray<HwScheduleException *> *)exceptions;
- (NSArray<HwScheduleException *> *)exceptions;

- (NSArray *)toValueUnits;

/** 0x80 业务数据：一帧一条，直接是 ValueUnit 字段串。 */
+ (NSArray<HwPhoneScheduleEvent2 *> *)listFromData:(NSData *)data;

/** 填充开始时间；全天固定 00:00（UTC 日界）。 */
- (void)applyStartFromTimeInterval:(NSTimeInterval)timeInterval
                            allDay:(BOOL)allDay
                          timeZone:(NSTimeZone * _Nullable)timeZone;
/**
 填充结束时间。
 全天 + exclusiveEnd：按 UTC 回退一天并写 23:59（对齐 Android CalendarContract exclusive END）。
 */
- (void)applyEndFromTimeInterval:(NSTimeInterval)timeInterval
                          allDay:(BOOL)allDay
                    exclusiveEnd:(BOOL)exclusiveEnd
                        timeZone:(NSTimeZone * _Nullable)timeZone;

@end

NS_ASSUME_NONNULL_END

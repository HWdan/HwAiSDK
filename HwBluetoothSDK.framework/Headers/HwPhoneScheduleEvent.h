//
//  HwPhoneScheduleEvent.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>
#import "HwPhoneScheduleReminder.h"
#import "HwPhoneScheduleDateParts.h"

NS_ASSUME_NONNULL_BEGIN

@interface HwPhoneScheduleEvent : NSObject

@property(nonatomic, assign) NSInteger eventId;
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

+ (NSInteger)maxCount;

- (void)setReminders:(NSArray<HwPhoneScheduleReminder *> *)reminders;
- (NSArray<HwPhoneScheduleReminder *> *)reminders;
- (void)clearReminders;

- (NSArray *)toValueUnits;

/** 填充开始时间；全天固定 00:00（UTC 日界）。 */
- (void)applyStartFromTimeInterval:(NSTimeInterval)timeInterval
                            allDay:(BOOL)allDay
                          timeZone:(NSTimeZone * _Nullable)timeZone;
/**
 填充结束时间。
 全天 + exclusiveEnd：按 UTC 回退一天并写 23:59。
 */
- (void)applyEndFromTimeInterval:(NSTimeInterval)timeInterval
                          allDay:(BOOL)allDay
                    exclusiveEnd:(BOOL)exclusiveEnd
                        timeZone:(NSTimeZone * _Nullable)timeZone;

@end

NS_ASSUME_NONNULL_END

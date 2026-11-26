//
//  HwScheduleException.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 0x0C 重复例外。取消 6 字节，改期 18 字节。最多 7 条。 */
@interface HwScheduleException : NSObject

@property(nonatomic, assign, readonly) NSInteger year;
@property(nonatomic, assign, readonly) NSInteger month;
@property(nonatomic, assign, readonly) NSInteger day;
@property(nonatomic, assign, readonly) NSInteger hour;
@property(nonatomic, assign, readonly) NSInteger minute;
@property(nonatomic, assign, readonly) BOOL cancelled;
@property(nonatomic, assign, readonly) NSInteger newStartYear;
@property(nonatomic, assign, readonly) NSInteger newStartMonth;
@property(nonatomic, assign, readonly) NSInteger newStartDay;
@property(nonatomic, assign, readonly) NSInteger newStartHour;
@property(nonatomic, assign, readonly) NSInteger newStartMinute;
@property(nonatomic, assign, readonly) NSInteger newEndYear;
@property(nonatomic, assign, readonly) NSInteger newEndMonth;
@property(nonatomic, assign, readonly) NSInteger newEndDay;
@property(nonatomic, assign, readonly) NSInteger newEndHour;
@property(nonatomic, assign, readonly) NSInteger newEndMinute;

+ (instancetype)cancelWithYear:(NSInteger)year
                         month:(NSInteger)month
                           day:(NSInteger)day
                          hour:(NSInteger)hour
                        minute:(NSInteger)minute;

+ (instancetype)rescheduleWithYear:(NSInteger)year
                             month:(NSInteger)month
                               day:(NSInteger)day
                              hour:(NSInteger)hour
                            minute:(NSInteger)minute
                      newStartYear:(NSInteger)newStartYear
                     newStartMonth:(NSInteger)newStartMonth
                       newStartDay:(NSInteger)newStartDay
                      newStartHour:(NSInteger)newStartHour
                    newStartMinute:(NSInteger)newStartMinute
                        newEndYear:(NSInteger)newEndYear
                       newEndMonth:(NSInteger)newEndMonth
                         newEndDay:(NSInteger)newEndDay
                        newEndHour:(NSInteger)newEndHour
                      newEndMinute:(NSInteger)newEndMinute;

+ (NSData *)dateTimeBytesWithYear:(NSInteger)year
                            month:(NSInteger)month
                              day:(NSInteger)day
                             hour:(NSInteger)hour
                           minute:(NSInteger)minute;

- (NSData *)toBytes;

/** 取消 6 字节，改期 18 字节；否则返回 nil。 */
+ (instancetype _Nullable)exceptionFromBytes:(NSData *)data;

@end

NS_ASSUME_NONNULL_END

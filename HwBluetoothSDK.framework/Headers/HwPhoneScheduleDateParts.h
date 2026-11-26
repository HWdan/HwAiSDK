//
//  HwPhoneScheduleDateParts.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 日程协议用的年月日时分。
 对齐 Android PhoneScheduleV2Mapper.parts / PhoneCalendarLoader.applyDateTime：
 全天按 UTC 日界；exclusiveEnd（次日 00:00 UTC）回退一天后写 23:59，
 避免用本地时区判断 00:00 失败导致只改时分、日期未回退。
 */
@interface HwPhoneScheduleDateParts : NSObject

@property(nonatomic, assign) NSInteger year;
@property(nonatomic, assign) NSInteger month;
@property(nonatomic, assign) NSInteger day;
@property(nonatomic, assign) NSInteger hour;
@property(nonatomic, assign) NSInteger minute;

/**
 @param timeInterval 事件开始/结束时间戳（秒）
 @param allDay 是否全天
 @param exclusiveEnd 是否 exclusive 结束（全天 END 通常为次日 00:00 UTC）
 @param timeZone 非全天使用的时区；nil 表示本地时区。全天忽略此参数，固定 UTC。
 */
+ (instancetype)partsWithTimeInterval:(NSTimeInterval)timeInterval
                               allDay:(BOOL)allDay
                         exclusiveEnd:(BOOL)exclusiveEnd
                             timeZone:(NSTimeZone * _Nullable)timeZone;

@end

NS_ASSUME_NONNULL_END

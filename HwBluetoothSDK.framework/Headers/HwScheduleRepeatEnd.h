//
//  HwScheduleRepeatEnd.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, HwScheduleRepeatEndKind) {
    HwScheduleRepeatEndKindNever = 0x00,
    HwScheduleRepeatEndKindDate = 0x01,
    HwScheduleRepeatEndKindCount = 0x02,
};

/** 0x0B 结束重复。永不 1 字节，日期 5 字节，次数 3 字节。 */
@interface HwScheduleRepeatEnd : NSObject

@property(nonatomic, assign, readonly) HwScheduleRepeatEndKind kind;
@property(nonatomic, assign, readonly) NSInteger year;
@property(nonatomic, assign, readonly) NSInteger month;
@property(nonatomic, assign, readonly) NSInteger day;
@property(nonatomic, assign, readonly) NSInteger count;

+ (instancetype)never;
+ (instancetype)untilYear:(NSInteger)year month:(NSInteger)month day:(NSInteger)day;
+ (instancetype)times:(NSInteger)count;

- (NSData *)toBytes;

@end

NS_ASSUME_NONNULL_END

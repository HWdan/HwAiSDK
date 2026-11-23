//
//  HwScheduleSyncType.h
//  HwBluetoothSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 0x75 新协议同步类型。 */
typedef NS_ENUM(NSInteger, HwScheduleSyncType) {
    /** 覆盖式同步 */
    HwScheduleSyncTypeOverwrite = 0x00,
    /** 增删改式同步 */
    HwScheduleSyncTypeIncremental = 0x01,
};

NS_ASSUME_NONNULL_END

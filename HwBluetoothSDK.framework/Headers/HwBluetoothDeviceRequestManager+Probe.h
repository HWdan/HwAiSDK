//
//  HwBluetoothDeviceRequestManager+Probe.h
//  HwBluetoothSDK
//

#import "HwBluetoothDeviceRequestManager.h"

NS_ASSUME_NONNULL_BEGIN

/// 设备发起的心跳包（0xD8 / 操作码 0x15）。
/// 协议载荷只有操作码，没有时间字段；timestamp 为手机收到该包时的本地时间，单位毫秒。
typedef void (^HwProbeCallback)(NSString *macAddress, long long timestamp);

@interface HwBluetoothDeviceRequestManager (Probe)

- (void)addProbeCallback:(HwProbeCallback)callback;
- (void)removeProbeCallback:(HwProbeCallback)callback;
- (void)removeAllProbeCallbacks;
- (void)notifyProbeReceivedWithMacAddress:(NSString *)macAddress timestamp:(long long)timestamp;

@end

NS_ASSUME_NONNULL_END

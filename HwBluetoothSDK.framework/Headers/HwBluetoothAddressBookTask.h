//
//  HwBluetoothAddressBookTask.h
//  CocoaLumberjack
//
//  Created by sujiang on 2020/4/9.
//

#import "HwBluetoothTaskManager.h"


@interface HwBluetoothAddressBookTask : HwBluetoothTask

+ (HwBluetoothAddressBookTask *) taskWithDataModel:(HwBluetoothData *)dataModel
                                        sendDevice:(HwBluetoothDevice *)sendDevice
                                          callback:(HwBCRequestCallback)callback;

- (HwBluetoothAddressBookTask *) initWithDataModel:(HwBluetoothData *)dataModel
                                        sendDevice:(HwBluetoothDevice *)sendDevice
                                          callback:(HwBCRequestCallback)callback;

@end



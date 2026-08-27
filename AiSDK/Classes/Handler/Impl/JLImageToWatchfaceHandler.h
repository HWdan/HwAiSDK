//
//  JLImageToWatchfaceHandler.h
//  AiSDK
//
//  Created by kingwear on 2026/2/11.
//

#import <Foundation/Foundation.h>
#import "IImageToWatchfaceHandler.h"

NS_ASSUME_NONNULL_BEGIN

@class AiDeviceInfo;
@interface JLImageToWatchfaceHandler : NSObject<IImageToWatchfaceHandler>

- (JLImageToWatchfaceHandler *) initWithImage:(UIImage *_Nonnull)image
                                        deviceInfo:(AiDeviceInfo *_Nonnull)deviceInfo;

@end

NS_ASSUME_NONNULL_END

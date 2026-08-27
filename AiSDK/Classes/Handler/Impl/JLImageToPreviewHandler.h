//
//  JLImageToPreviewHandler.h
//  AiSDK
//
//  Created by kingwear on 2026/2/10.
//

#import <Foundation/Foundation.h>
#import "IImageToPreviewHandler.h"

NS_ASSUME_NONNULL_BEGIN

@class AiDeviceInfo;
@interface JLImageToPreviewHandler : NSObject<IImageToPreviewHandler>

- (JLImageToPreviewHandler *) initWithImage:(UIImage *_Nonnull)image
                                      deviceInfo:(AiDeviceInfo *_Nonnull)deviceInfo
                                needSyncToDevice:(BOOL)needSyncToDevice;
@end

NS_ASSUME_NONNULL_END


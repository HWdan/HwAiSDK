//
//  AiSDK+BmpConverter.h
//  AiSDK
//

#import "AiSDK.h"

NS_ASSUME_NONNULL_BEGIN

/// Converts encoded image data into the bitmap data expected by JieLi devices.
typedef NSData * _Nullable (^AiBmpDataConverter)(NSData *imageData);

@interface AiSDK (BmpConverter)

/// Register at app startup before starting a JieLi preview or watchface transfer.
- (void)setJLBmpDataConverter:(AiBmpDataConverter _Nullable)converter;

@end

NS_ASSUME_NONNULL_END

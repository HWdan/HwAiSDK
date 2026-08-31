//
//  AiSDK+BmpConverterInternal.h
//  AiSDK
//

#import "AiSDK+BmpConverter.h"

NS_ASSUME_NONNULL_BEGIN

@interface AiSDK (BmpConverterInternal)

/// Returns nil when no converter is registered or when conversion fails.
- (nullable NSData *)convertBmpImageData:(NSData *)imageData;

@end

NS_ASSUME_NONNULL_END

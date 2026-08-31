//
//  AiSDK+BmpConverter.m
//  AiSDK
//

#import "AiSDK+BmpConverterInternal.h"

static AiBmpDataConverter _bmpDataConverter;

@implementation AiSDK (BmpConverter)

- (void)setJLBmpDataConverter:(AiBmpDataConverter _Nullable)converter
{
    @synchronized ([AiSDK class]) {
        _bmpDataConverter = [converter copy];
    }
}

@end

@implementation AiSDK (BmpConverterInternal)

- (NSData * _Nullable)convertBmpImageData:(NSData *)imageData
{
    AiBmpDataConverter converter;
    @synchronized ([AiSDK class]) {
        converter = [_bmpDataConverter copy];
    }
    return converter ? converter(imageData) : nil;
}

@end

//
//  AiJieLiDevicePlatformStrategy.m
//  AiSDK
//

#import "AiJieLiDevicePlatformStrategy.h"
#import "AiSDK.h"
#import "JLVoiceToTextHandler.h"
#import "JLImageToWatchfaceHandler.h"
#import "HwBluetoothSDK/HwBluetoothSDK.h"

@implementation AiJieLiDevicePlatformStrategy

- (id<IImageToWatchfaceHandler>)createWatchfaceHandlerWithImage:(UIImage *)image
                                                      deviceInfo:(AiDeviceInfo *)deviceInfo
{
    return [[JLImageToWatchfaceHandler alloc] initWithImage:image deviceInfo:deviceInfo];
}

- (id<IVoiceToText>)createVoiceToTextHandler
{
    return [[JLVoiceToTextHandler alloc] init];
}

- (void)completeTextToImageWithSDK:(AiSDK *)sdk
                              image:(UIImage *)image
                               code:(NSInteger)code
                           errorMsg:(NSString *)errorMsg
{
    [sdk textToImageCompleted_JL:image code:code msg:errorMsg];
}

@end

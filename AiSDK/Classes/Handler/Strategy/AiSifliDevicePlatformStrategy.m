//
//  AiSifliDevicePlatformStrategy.m
//  AiSDK
//

#import "AiSifliDevicePlatformStrategy.h"
#import "AiSDK.h"
#import "SifliVoiceToTextHandler.h"
#import "DefaultImageToWatchfaceHandler.h"
#import "HwBluetoothSDK/HwBluetoothSDK.h"

@implementation AiSifliDevicePlatformStrategy

- (id<IImageToWatchfaceHandler>)createWatchfaceHandlerWithImage:(UIImage *)image
                                                      deviceInfo:(AiDeviceInfo *)deviceInfo
{
    return [[DefaultImageToWatchfaceHandler alloc] initWithImage:image deviceInfo:deviceInfo];
}

- (id<IVoiceToText>)createVoiceToTextHandler
{
    return [[SifliVoiceToTextHandler alloc] init];
}

- (void)completeTextToImageWithSDK:(AiSDK *)sdk
                              image:(UIImage *)image
                               code:(NSInteger)code
                           errorMsg:(NSString *)errorMsg
{
    [sdk textToImageCompleted:image code:code msg:errorMsg];
}

@end

//
//  DefaultTextToImageHandler.m
//  AiSDK
//
//  Created by HuaWo on 2025/1/14.
//

#import "DefaultTextToImageHandler.h"
#import "AiLogger.h"
#import "AiSDK/AiSDK.h"

@implementation DefaultTextToImageHandler

- (void)convertComplete:(UIImage *)image
                   code:(NSInteger)code
               errorMsg:(NSString *)errorMsg
{
    if (self.isCanceled) {
        [AiLogger i:@"TextToImage convertComplete 已取消"];
        return;
    }
    if (code != 0) {
        [AiLogger e:@"Text To Answer Failed: %@, %@", @(code), errorMsg];
    } else {
        [AiLogger i:@"转成图片啦"];
    }
    [[AiSDK sharedInstance] textToImageCompleted:image code:code msg:errorMsg];
}

@end

//
//  JLImageToPreviewHandler.m
//  AiSDK
//
//  Created by kingwear on 2026/2/10.
//

#import "JLImageToPreviewHandler.h"
#import "AiDeviceInfo.h"
#import "AiImageUtils.h"
#import "AiSDK.h"
#import "AiSDK+BmpConverterInternal.h"
#import "AiLogger.h"
#import "AiFileUtils.h"
#import "HwBluetoothSDK.h"
#import "WatchfaceSDK/WatchfaceSDK-Swift.h"

@interface JLImageToPreviewHandler()

@property(nonatomic, assign) BOOL isCanceled;
@property(nonatomic, assign) BOOL needSyncToDevice;
@property(nonatomic, strong) UIImage *source;
@property(nonatomic, strong) UIImage *background;
@property(nonatomic, strong) AiDeviceInfo *deviceInfo;

@end

@implementation JLImageToPreviewHandler

- (void)dealloc
{
    _source = nil;
    _deviceInfo = nil;
    _background = nil;
}

- (JLImageToPreviewHandler *) initWithImage:(UIImage *_Nonnull)image
                                      deviceInfo:(AiDeviceInfo *)deviceInfo
                                needSyncToDevice:(BOOL)needSyncToDevice
{
    self = [super init];
    if (self) {
        self.source = image;
        self.deviceInfo = deviceInfo;
        self.needSyncToDevice = needSyncToDevice;
    }
    return self;
}

- (void)cancel {
    [AiLogger i:@"JLImageToPreviewHandler cancel"];
    self.isCanceled = YES;
}

- (void)makePreviewDone:(UIImage *_Nullable)preview
                   code:(NSInteger)code
               errorMsg:(NSString *_Nullable)errorMsg
{
    if (_isCanceled) {
        [AiLogger i:@"JLImageToPreviewHandler is canceled"];
        return;
    }
    
    [[AiSDK sharedInstance] imageToPreviewCompleted:preview code:code msg:errorMsg];
    if (self.needSyncToDevice) {
        if (code != 0) {
            [self syncToDeviceDone:AiErrorScaleAndCropImageFailed errorMsg:[[AiSDK sharedInstance] errorMsgWithCode:AiErrorScaleAndCropImageFailed]];
            return;
        }
        [self startMakePreviewBin:preview];
    }
}

- (void)start
{
    [AiLogger i:@"preview handler start"];
    self.isCanceled = NO;
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        
        UIImage *image = [AiImageUtils generateJLFitSizePreViewImage:self.source
                                                               width:self.deviceInfo.width
                                                              height:self.deviceInfo.height];
        
        self.background = [AiImageUtils generateFitSizeRoundedImage:image
                                                              width:self.deviceInfo.thumbnailWidth
                                                             height:self.deviceInfo.thumbnailHeight
                                                       cornerRadius:self.deviceInfo.thumbnailCornerRadius
                                                             opaque:true];
        
        if (self.background == nil) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [AiLogger e:@"background is nil"];
                [self makePreviewDone:nil code:AiErrorScaleAndCropImageFailed errorMsg:[[AiSDK sharedInstance] errorMsgWithCode:AiErrorScaleAndCropImageFailed]];
            });
            return;
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [self makePreviewDone:self.background code:0 errorMsg:nil];
        });
    });
}

- (void) startMakePreviewBin:(UIImage *)preview
{
    
    NSMutableArray<HwMultipleFileTransferModel *> *fileModelArr = [NSMutableArray new];
    
    HwMultipleFileTransferModel *trModel = [HwMultipleFileTransferModel new];
    trModel.photoType = MultipleFileTransferPhotoTypeJPG;
    
    UIImage *resizeImage = [AiImageUtils generateFitSizeRoundedImage:preview
                                                          width:self.deviceInfo.thumbnailWidth
                                                         height:self.deviceInfo.thumbnailHeight
                                                   cornerRadius:self.deviceInfo.thumbnailCornerRadius
                                                         opaque:true];
    NSData *imageData = UIImageJPEGRepresentation(resizeImage, 1);
    
    NSData *convertedData = [[AiSDK sharedInstance] convertBmpImageData:imageData];
    if (convertedData == nil) {
        [AiLogger e:@"JieLi bitmap conversion failed. Register the converter on AiSDK before transfer."];
        [self syncToDeviceDone:AiErrorMakeQjsWatchfaceFailed
                      errorMsg:[[AiSDK sharedInstance] errorMsgWithCode:AiErrorMakeQjsWatchfaceFailed]];
        return;
    }
    trModel.fileData = convertedData;
    
    trModel.fileName = @"aipw";
    [fileModelArr addObject:trModel];
    
    [AiLogger e:@"will sync preview to device size: %ld", trModel.fileData.length];
    
    [[HwBluetoothSDK sharedInstance].multipleFileTransferService
        startWithFileModels:fileModelArr
               transferType:MultipleFileTransferTypeAIDialPreview
              readyCallback:^(BOOL b, NSError *error) {
        } progressCallback:^(float f, NSError *error) {
            NSLog(@"jl preview progress: %@", @(f));
        } finishCallback:^(BOOL b, NSError *error) {
            if (!b) {
                [AiLogger e:@"sync preview to device failed: %@", @(b)];
                [self syncToDeviceDone:AiErrorMakeQjsWatchfaceFailed
                              errorMsg:[[AiSDK sharedInstance] errorMsgWithCode:AiErrorMakeQjsWatchfaceFailed]];
                return;
            }
            [self syncToDeviceDone:0 errorMsg:nil];
        }];
}

- (void) syncToDeviceDone:(NSInteger)code
                 errorMsg:(NSString *)errorMsg
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[AiSDK sharedInstance] previewSyncToDeviceCompleted:code
                                                         msg:errorMsg
                                                  isCanceled:self.isCanceled];
    });
    _source = nil;
    _deviceInfo = nil;
    _background = nil;
}

@end

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTNativeOggOpusBridgeResult : NSObject

@property (nonatomic, strong, nullable) NSData *data;
@property (nonatomic, assign) NSInteger sampleRate;
@property (nonatomic, assign) NSInteger channels;
@property (nonatomic, assign) NSInteger bitsPerSample;
@property (nonatomic, copy, nullable) NSString *errorMessage;
@property (nonatomic, assign) BOOL outputLimitExceeded;

@end

@interface OTNativeOggOpusBridge : NSObject

+ (OTNativeOggOpusBridgeResult *)encodePCMToOgg:(NSData *)pcmData
                                    sampleRate:(NSInteger)sampleRate
                                      channels:(NSInteger)channels
                                       bitrate:(NSInteger)bitrate;

+ (OTNativeOggOpusBridgeResult *)decodeOggToPCM:(NSData *)oggData;
+ (OTNativeOggOpusBridgeResult *)decodeOggToPCM:(NSData *)oggData
                                 maxPCMBytes:(NSUInteger)maxPCMBytes NS_SWIFT_NAME(decodeOggToPCM(_:maxPCMBytes:));

+ (OTNativeOggOpusBridgeResult *)decodeOggFile:(NSString *)inputPath
                                     toPCMFile:(NSString *)outputPCMPath NS_SWIFT_NAME(decodeOggFile(_:toPCMFile:));

@end

@interface OTNativeOggOpusFileEncoder : NSObject

- (nullable instancetype)initWithOutputPath:(NSString *)outputPath
                                 sampleRate:(NSInteger)sampleRate
                                   channels:(NSInteger)channels
                                    bitrate:(NSInteger)bitrate
                               errorMessage:(NSString * _Nullable * _Nullable)errorMessage;

- (BOOL)writePCMData:(NSData *)pcmData
        errorMessage:(NSString * _Nullable * _Nullable)errorMessage;

- (BOOL)drainAndCloseWithErrorMessage:(NSString * _Nullable * _Nullable)errorMessage;

@end

NS_ASSUME_NONNULL_END

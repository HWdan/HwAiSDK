@import XCTest;
@import AiSDK;
#import <objc/runtime.h>

@interface DefaultHealthAnalysisResultHandler (TestCompletion)
- (void)analysisCompleted:(NSString *)text code:(NSInteger)code errorMsg:(NSString *)errorMsg;
@end

@interface HealthCallbackCheck : NSObject
@property(nonatomic) NSInteger count;
@property(nonatomic) NSInteger code;
@property(nonatomic, strong) HwHealthAnalysisResult *result;
@end
@implementation HealthCallbackCheck
- (NSString *)errorMsgWithCode:(NSInteger)code { return @"Health analysis failed"; }
- (void)healthAnalysisResultCompleted:(HwHealthAnalysisResult *)result code:(NSInteger)code msg:(NSString *)msg {
    self.count++;
    self.code = code;
    self.result = result;
}
@end

@interface HealthTransportCheck : NSObject
@property(nonatomic) NSInteger count;
@end
@implementation HealthTransportCheck
- (void)setAiHealthAnalysisResultWithResult:(HwHealthAnalysisResult *)result code:(int)code msg:(NSString *)msg {
    self.count++;
}
@end

@interface Tests : XCTestCase
@end
@implementation Tests
- (void)testHealthAnalysisRouting {
    HealthCallbackCheck *callback = [HealthCallbackCheck new];
    HealthTransportCheck *transport = [HealthTransportCheck new];
    Method aiMethod = class_getClassMethod(AiSDK.class, @selector(sharedInstance));
    Method bleMethod = class_getClassMethod(HwBluetoothSDK.class, @selector(sharedInstance));
    IMP aiReplacement = imp_implementationWithBlock(^id(id cls) { return callback; });
    IMP bleReplacement = imp_implementationWithBlock(^id(id cls) { return transport; });
    IMP originalAI = method_setImplementation(aiMethod, aiReplacement);
    IMP originalBLE = method_setImplementation(bleMethod, bleReplacement);
    @try {
        for (NSNumber *appOnly in @[@NO, @YES]) {
            callback.count = transport.count = 0;
            DefaultHealthAnalysisResultHandler *handler = [DefaultHealthAnalysisResultHandler new];
            handler.appOnly = appOnly.boolValue;
            NSString *json = @"{\"HealthDataAnalysisReport\":{\"Conclusion\":\"report\"}}";
            [handler analysisCompleted:json code:0 errorMsg:nil];
            XCTAssertEqual(callback.count, 1);
            XCTAssertEqualObjects(callback.result.summary, @"report");
            XCTAssertEqual(transport.count, appOnly.boolValue ? 0 : 1);
            [handler analysisCompleted:@"" code:0 errorMsg:nil];
            XCTAssertEqual(callback.count, 2);
            XCTAssertEqual(callback.code, AiErrorHealthAnalysisResultNull);
            XCTAssertEqual(transport.count, appOnly.boolValue ? 0 : 2);
            [handler cancel];
            [handler analysisCompleted:json code:0 errorMsg:nil];
            XCTAssertEqual(callback.count, 2);
            XCTAssertEqual(transport.count, appOnly.boolValue ? 0 : 2);
        }
    } @finally {
        method_setImplementation(aiMethod, originalAI);
        method_setImplementation(bleMethod, originalBLE);
        imp_removeBlock(aiReplacement);
        imp_removeBlock(bleReplacement);
    }
}
@end

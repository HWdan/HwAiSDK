//
//  NSData+HwBLE.h
//  HwBluetoothSDK
//
//  Created by HuaWo on 2022/7/16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSData (HwBLE)

- (NSString *)md5String;
- (NSInteger) integerValue;
- (long)dataToLong;

+ (NSData *) dataWithString:(NSString *)str
                  maxLength:(NSInteger)maxLength;

@end

NS_ASSUME_NONNULL_END

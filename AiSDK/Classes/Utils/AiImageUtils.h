//
//  AiImageUtils.h
//  AiSDK
//
//  Created by HuaWo on 2025/1/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AiImageUtils : NSObject

+ (UIImage *) generateFitSizeImage:(UIImage *)source
                             width:(CGFloat)width
                            height:(CGFloat)height;

+ (UIImage *) generateFitSizePreViewImage:(UIImage *)source
                                    width:(CGFloat)width
                                   height:(CGFloat)height;
+ (UIImage *) generateJLFitSizePreViewImage:(UIImage *)source
                                      width:(CGFloat)width
                                     height:(CGFloat)height;
+ (UIImage *) generateFitSizeRoundedImage:(UIImage *)source
                                    width:(CGFloat)width
                                   height:(CGFloat)height
                             cornerRadius:(CGFloat)cornerRadius;
+ (UIImage *) generateFitSizeRoundedImage:(UIImage *)source
                                    width:(CGFloat)width
                                   height:(CGFloat)height
                             cornerRadius:(CGFloat)cornerRadius
                                   opaque:(BOOL)opaque;
+ (NSString *) exportSifliBin:(UIImage *)image
                     fileName:(NSString *)fileName;
+ (UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)size;

@end

NS_ASSUME_NONNULL_END

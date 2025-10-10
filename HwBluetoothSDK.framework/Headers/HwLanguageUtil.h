//
//  HwLanguageUtil.h
//

#import <Foundation/Foundation.h>
#import "HwDeviceDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface HwLanguageUtil : NSObject

/**
 Returns the prefix of multilingual types that can be processed by the SDK. If not, returns English;
 Currently, the types of languages that can be processed are:
 
 @see HwLanguage
 */
+ (NSString *) phoneLanguagePrefix;

/**
 Default is English
 @see HwLanguage
 */
+ (HwLanguage) getPhoneLanguage;

@end

NS_ASSUME_NONNULL_END

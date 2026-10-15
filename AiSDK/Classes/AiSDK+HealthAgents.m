#import <AiSDK/AiSDK-Swift.h>
//
//  AiSDK+HealthAgents.m
//  AiSDK
//

#import "AiSDK+HealthAgents.h"
#import <math.h>

static NSString *const AiHealthAgentsErrorDomain = @"AiHealthAgents";

@implementation AiSDK (HealthAgents)

- (NSError *)healthAgentErrorWithCode:(NSInteger)code message:(NSString *)message
{
    return [NSError errorWithDomain:AiHealthAgentsErrorDomain code:code
                          userInfo:@{NSLocalizedDescriptionKey: message ?: @"Health agent failed"}];
}

- (void)completeHealthAgent:(void (^)(NSDictionary *, NSError *))completion result:(NSDictionary *)result error:(NSError *)error
{
    dispatch_async(dispatch_get_main_queue(), ^{
        completion(result, error);
    });
}

- (NSString *)requiredStringForKey:(NSString *)key inDictionary:(NSDictionary *)json
{
    id value = json[key];
    if (![value isKindOfClass:[NSString class]]) {
        return nil;
    }
    NSString *text = [value stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    return text.length ? text : nil;
}

- (void)addNumber:(NSNumber *)value forKey:(NSString *)key toDictionary:(NSMutableDictionary *)json
{
    json[key] = value.stringValue ?: @"0";
}

- (BOOL)addValues:(NSArray *)values count:(NSUInteger)count separator:(NSString *)separator forKey:(NSString *)key toDictionary:(NSMutableDictionary *)json
{
    if (!values.count) { json[key] = @"0"; return YES; }
    if (count && values.count != count) return NO;
    NSMutableArray *strings = [NSMutableArray array];
    for (id value in values) {
        if ([value isKindOfClass:[NSNumber class]]) {
            if (!isfinite([value doubleValue])) return NO;
            [strings addObject:[value stringValue]];
        } else if ([value isKindOfClass:[NSString class]] && [value length]) {
            [strings addObject:value];
        } else {
            return NO;
        }
    }
    json[key] = [strings componentsJoinedByString:separator];
    return YES;
}

- (NSDictionary *)sleepPayloadWithInput:(AiSleepChronotypeInput *)input
{
    if (!input.date.length || input.period < 0 || input.period > 2 ||
        !input.sleepHours.count || input.sleepHours.count != input.getUpHours.count) return nil;
    if ((input.period == 0 && input.sleepHours.count != 1) ||
        (input.period == 1 && input.sleepHours.count != 7) || input.sleepHours.count > 31) return nil;
    NSString *timePattern = input.use12HourClock ? @"^(0?[1-9]|1[0-2]):[0-5][0-9]:[0-5][0-9] (AM|PM)$" : @"^(([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]|24:00:00)$";
    for (NSString *time in [input.sleepHours arrayByAddingObjectsFromArray:input.getUpHours]) {
        if (![time isKindOfClass:[NSString class]]) return nil;
        if (![time isEqualToString:@"0"] &&
            [time rangeOfString:timePattern options:NSRegularExpressionSearch].location == NSNotFound) return nil;
    }
    return @{@"date": input.date,
             @"sleep_h": [input.sleepHours componentsJoinedByString:@","],
             @"getUp_h": [input.getUpHours componentsJoinedByString:@","]};
}

- (NSDictionary *)exercisePayloadWithInput:(AiExerciseInsightInput *)input
{
    if (!input.date.length) return nil;
    NSMutableDictionary *json = [@{@"date": input.date} mutableCopy];
    [self addNumber:input.stepGoal forKey:@"stepGoal" toDictionary:json];
    [self addNumber:input.activityDurationGoalMinutes forKey:@"activityDurationGoal_min" toDictionary:json];
    [self addNumber:input.calorieGoalKcal forKey:@"activitycalorieGoal_kcal" toDictionary:json];
    [self addNumber:input.sleepQuality forKey:@"sleepQuality" toDictionary:json];
    if (![self addValues:input.steps count:7 separator:@"," forKey:@"steps" toDictionary:json]) return nil;
    if (![self addValues:input.activityDurationMinutes count:7 separator:@"," forKey:@"activityDuration_min" toDictionary:json]) return nil;
    if (![self addValues:input.caloriesKcal count:7 separator:@"," forKey:@"calorieGoal_kcal" toDictionary:json]) return nil;
    for (NSString *mood in input.mood) {
        if (![@[@"0", @"特别低落", @"有点低落", @"心情平和", @"有点愉悦", @"特别愉悦"] containsObject:mood]) return nil;
    }
    if (![self addValues:input.mood count:7 separator:@"," forKey:@"mood" toDictionary:json]) return nil;
    if (![self addValues:input.restingHeartRateBpm count:7 separator:@"," forKey:@"restingheartRate_bpm" toDictionary:json]) return nil;
    if (![self addValues:input.heartRateBpm count:7 separator:@"," forKey:@"heartRate_bpm" toDictionary:json]) return nil;
    if (![self addValues:input.heartRateVariability count:7 separator:@"," forKey:@"heartratevariability(hrv)" toDictionary:json]) return nil;
    if (![self addValues:input.stress count:7 separator:@"," forKey:@"stress" toDictionary:json]) return nil;
    if (![self addValues:input.sleepDurationMinutes count:7 separator:@"," forKey:@"sleepDuration_min" toDictionary:json]) return nil;
    if (![self addValues:input.lightSleepMinutes count:7 separator:@"," forKey:@"lightSleep_min" toDictionary:json]) return nil;
    if (![self addValues:input.deepSleepMinutes count:7 separator:@"," forKey:@"deepSleep_min" toDictionary:json]) return nil;
    return json;
}

- (NSDictionary *)bodyPayloadWithInput:(AiBodyStatusInput *)input
{
    if (!input.date.length) return nil;
    NSMutableDictionary *json = [@{@"date": input.date} mutableCopy];
    [self addNumber:input.stepGoal forKey:@"stepGoal" toDictionary:json];
    [self addNumber:input.steps forKey:@"steps" toDictionary:json];
    [self addNumber:input.activityDurationMinutes forKey:@"activityDuration_min" toDictionary:json];
    [self addNumber:input.caloriesKcal forKey:@"calorieGoal_kcal" toDictionary:json];
    [self addNumber:input.sleepQuality forKey:@"sleepQuality" toDictionary:json];
    if (![self addValues:input.restingHeartRateBpm count:0 separator:@"," forKey:@"restingheartRate_bpm" toDictionary:json]) return nil;
    if (![self addValues:input.heartRateBpm count:0 separator:@"," forKey:@"heartRate_bpm" toDictionary:json]) return nil;
    if (![self addValues:input.heartRateVariability count:0 separator:@"," forKey:@"heartratevariability(hrv)" toDictionary:json]) return nil;
    if (![self addValues:input.stress count:0 separator:@"," forKey:@"stress" toDictionary:json]) return nil;
    if (![self addValues:input.sleepDurationMinutes count:0 separator:@"," forKey:@"sleep" toDictionary:json]) return nil;
    if (![self addValues:input.lightSleepMinutes count:0 separator:@"," forKey:@"lightSleep_min" toDictionary:json]) return nil;
    if (![self addValues:input.deepSleepMinutes count:0 separator:@"," forKey:@"deepSleep_min" toDictionary:json]) return nil;
    return json;
}

- (AiSleepChronotypeResult *)sleepResultWithDictionary:(NSDictionary *)json
{
    NSArray *keys = @[@"best_time", @"best_time_intro", @"adjustment_intro",
                      @"chronotype_intro", @"sleepPlan_start", @"sleepPlan_end"];
    for (NSString *key in keys) {
        if (![self requiredStringForKey:key inDictionary:json]) {
            return nil;
        }
    }
    id chronotype = json[@"chronotype"];
    NSInteger type = 0;
    if ([chronotype isKindOfClass:[NSNumber class]]) {
        type = [chronotype integerValue];
        if ([chronotype doubleValue] != type) return nil;
    } else if ([chronotype isKindOfClass:[NSString class]]) {
        NSScanner *scanner = [NSScanner scannerWithString:chronotype];
        if (![scanner scanInteger:&type] || !scanner.isAtEnd) return nil;
    } else return nil;
    if (type < 1 || type > 6) return nil;
    for (NSString *key in @[@"sleepPlan_start", @"sleepPlan_end"]) {
        NSString *time = [self requiredStringForKey:key inDictionary:json];
        if ([time rangeOfString:@"^((([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]|24:00:00)|(0?[1-9]|1[0-2]):[0-5][0-9]:[0-5][0-9] (AM|PM))$" options:NSRegularExpressionSearch].location == NSNotFound) return nil;
    }
    AiSleepChronotypeResult *result = [[AiSleepChronotypeResult alloc] init];
    result.bestTime = [self requiredStringForKey:@"best_time" inDictionary:json];
    result.bestTimeIntro = [self requiredStringForKey:@"best_time_intro" inDictionary:json];
    result.adjustmentIntro = [self requiredStringForKey:@"adjustment_intro" inDictionary:json];
    result.chronotype = [NSString stringWithFormat:@"%ld", (long)type];
    result.chronotypeIntro = [self requiredStringForKey:@"chronotype_intro" inDictionary:json];
    result.sleepPlanStart = [self requiredStringForKey:@"sleepPlan_start" inDictionary:json];
    result.sleepPlanEnd = [self requiredStringForKey:@"sleepPlan_end" inDictionary:json];
    return result;
}

- (AiExerciseInsightResult *)exerciseResultWithDictionary:(NSDictionary *)json
{
    NSString *title = [self requiredStringForKey:@"title" inDictionary:json];
    NSString *content = [self requiredStringForKey:@"content" inDictionary:json];
    if (!title || !content) {
        return nil;
    }
    id reminder = json[@"remind"];
    NSInteger value = 0;
    if (!reminder || reminder == [NSNull null]) return nil;
    if ([reminder isKindOfClass:[NSNumber class]]) {
        value = [reminder integerValue];
        if ([reminder doubleValue] != value) {
            return nil;
        }
    } else if ([reminder isKindOfClass:[NSString class]] && [reminder length]) {
        NSScanner *scanner = [NSScanner scannerWithString:reminder];
        if (![scanner scanInteger:&value] || !scanner.isAtEnd) {
            return nil;
        }
    } else {
        return nil;
    }
    if (value < 1 || value > 5) {
        return nil;
    }
    AiExerciseInsightResult *result = [[AiExerciseInsightResult alloc] init];
    result.title = title;
    result.content = content;
    result.reminderType = value;
    NSString *mood = [self requiredStringForKey:@"mood" inDictionary:json];
    if (mood && ![mood isEqualToString:@"0"]) {
        if (![@[@"特别低落", @"有点低落", @"心情平和", @"有点愉悦", @"特别愉悦"] containsObject:mood]) return nil;
        result.mood = mood;
    }
    return result;
}

- (AiBodyStatusResult *)bodyResultWithDictionary:(NSDictionary *)json
{
    NSString *title = [self requiredStringForKey:@"title" inDictionary:json];
    NSString *level = [self requiredStringForKey:@"Level" inDictionary:json] ?: [self requiredStringForKey:@"level" inDictionary:json];
    NSString *content = [self requiredStringForKey:@"content" inDictionary:json];
    id rating = json[@"Rating"] ?: json[@"rating"];
    if (!title || !level || !content || ![rating isKindOfClass:[NSNumber class]]) {
        return nil;
    }
    NSInteger score = [rating integerValue];
    if (score < 0 || score > 100 || [rating doubleValue] != score) {
        return nil;
    }
    AiBodyStatusResult *result = [[AiBodyStatusResult alloc] init];
    result.title = title;
    result.level = level;
    result.rating = score;
    result.content = content;
    return result;
}

- (void)requestHealthAgentWithCode:(NSString *)agentCode
                            payload:(NSDictionary *)payload
                          completion:(void (^)(NSDictionary *result, NSError *error))completion
{
    if (!payload || ![NSJSONSerialization isValidJSONObject:payload]) {
        [self completeHealthAgent:completion result:nil error:[self healthAgentErrorWithCode:1 message:@"Invalid health agent input"]];
        return;
    }
    AiDeviceInfo *device = [self getDeviceInfo];
    if (!device.Id.length) {
        [self completeHealthAgent:completion result:nil error:[self healthAgentErrorWithCode:2 message:@"AI device info is missing"]];
        return;
    }
    NSData *data = [NSJSONSerialization dataWithJSONObject:@[payload] options:0 error:nil];
    NSString *text = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    if (!text.length) {
        [self completeHealthAgent:completion result:nil error:[self healthAgentErrorWithCode:1 message:@"Could not encode health agent input"]];
        return;
    }
    NSString *locale = device.currentLocale.length ? device.currentLocale : @"en-US";
    [[AiOASClient shared] requestHealthAgentWithCode:agentCode data:data language:locale completion:^(NSData *answerData, NSString *contextId, NSError *error) {
        if (error) { [self completeHealthAgent:completion result:nil error:error]; return; }
        id json = answerData ? [NSJSONSerialization JSONObjectWithData:answerData options:NSJSONReadingFragmentsAllowed error:nil] : nil;
        if ([json isEqual:@0] || [json isEqual:@"0"]) {
            [self completeHealthAgent:completion result:nil error:[self healthAgentErrorWithCode:4 message:@"No health agent data available"]];
            return;
        }
        if (![json isKindOfClass:[NSDictionary class]]) {
            [self completeHealthAgent:completion result:nil error:[self healthAgentErrorWithCode:3 message:@"Invalid health agent response"]];
            return;
        }
        [self completeHealthAgent:completion result:json error:nil];
    }];
}

- (void)generateSleepChronotype:(AiSleepChronotypeInput *)input
                     completion:(void (^)(AiSleepChronotypeResult *, NSError *))completion
{
    if (input.period < 0 || input.period > 2) {
        [self completeHealthAgent:^(NSDictionary *json, NSError *error) { completion(nil, error); } result:nil error:[self healthAgentErrorWithCode:1 message:@"Invalid sleep report period"]];
        return;
    }
    NSArray *codes = input.use12HourClock ? @[@"swz-12-WZvv8s7Zzg", @"swz-12-D86RHKMdfA", @"swz-12-tgre5yuw4f"] :
        @[@"swz-24-ErtiV9ZWQW", @"swz-24-yoxRkJHouU", @"swz-24-Ki3LgWLpzK"];
    NSString *code = codes[input.period];
    [self requestHealthAgentWithCode:code payload:[self sleepPayloadWithInput:input] completion:^(NSDictionary *json, NSError *error) {
        AiSleepChronotypeResult *result = json ? [self sleepResultWithDictionary:json] : nil;
        completion(result, result || error ? error : [self healthAgentErrorWithCode:3 message:@"Invalid sleep chronotype response"]);
    }];
}

- (void)generateExerciseInsight:(AiExerciseInsightInput *)input
                     completion:(void (^)(AiExerciseInsightResult *, NSError *))completion
{
    [self requestHealthAgentWithCode:@"yddcVTkjCCXgEM" payload:[self exercisePayloadWithInput:input] completion:^(NSDictionary *json, NSError *error) {
        AiExerciseInsightResult *result = json ? [self exerciseResultWithDictionary:json] : nil;
        completion(result, result || error ? error : [self healthAgentErrorWithCode:3 message:@"Invalid exercise insight response"]);
    }];
}

- (void)generateBodyStatus:(AiBodyStatusInput *)input
                completion:(void (^)(AiBodyStatusResult *, NSError *))completion
{
    [self requestHealthAgentWithCode:@"stztu49WdtfBnj" payload:[self bodyPayloadWithInput:input] completion:^(NSDictionary *json, NSError *error) {
        AiBodyStatusResult *result = json ? [self bodyResultWithDictionary:json] : nil;
        completion(result, result || error ? error : [self healthAgentErrorWithCode:3 message:@"Invalid body status response"]);
    }];
}

@end

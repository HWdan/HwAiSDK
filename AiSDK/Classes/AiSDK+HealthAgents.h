//
//  AiSDK+HealthAgents.h
//  AiSDK
//

#import "AiSDK.h"
#import "AiHealthAgentModel.h"

NS_ASSUME_NONNULL_BEGIN

/// App 主动生成报告；与手表语音智能体的回传流程独立。回调始终在主线程执行。
@interface AiSDK (HealthAgents)

- (void)generateSleepChronotype:(AiSleepChronotypeInput *)input
                     completion:(void (^)(AiSleepChronotypeResult * _Nullable result, NSError * _Nullable error))completion;
- (void)generateExerciseInsight:(AiExerciseInsightInput *)input
                     completion:(void (^)(AiExerciseInsightResult * _Nullable result, NSError * _Nullable error))completion;
- (void)generateBodyStatus:(AiBodyStatusInput *)input
                completion:(void (^)(AiBodyStatusResult * _Nullable result, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END

//
//  AiHealthAgentModel.h
//  AiSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 睡眠生物钟输入，缺失日期以字符串 0 占位。
@interface AiSleepChronotypeInput : NSObject

/// 记录日期（请求字段 date），yyyy/MM/dd；多日按结束日期到开始日期排列。
/// 日示例：@"2026/09/22"；周示例：@"2026/09/22-2026/09/16"；月示例：@"2026/09/30-2026/09/01"。
@property (nonatomic, copy) NSString *date;
/// 报告周期：0 日，1 周，2 月；用于选择智能体，不作为 JSON 字段上传。
/// 示例：0（日报告）、1（周报告）、2（月报告）。
@property (nonatomic, assign) NSInteger period;
/// YES 使用 12 小时制智能体及 hh:mm:ss AM/PM；默认 NO 使用 24 小时制。
@property (nonatomic, assign) BOOL use12HourClock;
/// 每日入睡时间（请求字段 sleep_h），HH:mm:ss 或 hh:mm:ss AM/PM，24 小时制允许 24:00:00，保留实际分钟，缺失日期填 @"0"。
/// 日示例：@[@"23:00:00"]；周示例：@[@"23:00:00", @"22:00:00", @"21:00:00", @"22:00:00", @"23:00:00", @"22:00:00", @"19:00:00"]。
/// 日 1 项、周 7 项、月为当月截至请求日的每日记录；均从近到远，上传为逗号分隔字符串。
@property (nonatomic, copy) NSArray<NSString *> *sleepHours;
/// 每日起床时间（请求字段 getUp_h），格式和顺序同 sleepHours，两组数量必须一致。
/// 日示例：@[@"06:00:00"]；周示例：@[@"06:00:00", @"06:00:00", @"06:00:00", @"06:00:00", @"06:00:00", @"06:00:00", @"06:00:00"]。
@property (nonatomic, copy) NSArray<NSString *> *getUpHours;

@end

@interface AiSleepChronotypeResult : NSObject

/// 最佳入睡时间段（返回字段 best_time）。示例：@"23:00:00~24:00:00"。
@property (nonatomic, copy) NSString *bestTime;
/// 最佳入睡时间段说明（返回字段 best_time_intro）。
/// 示例（节选）：@"你本次记录的入睡时间为23:00:00，正好处于该参考窗口的起始点，因此与晚晨型分类相符。"。
@property (nonatomic, copy) NSString *bestTimeIntro;
/// 作息调整建议（返回字段 adjustment_intro）。
/// 示例（节选）：@"按记录估算，你本次睡眠约7小时，接近多数成年人常见的建议范围，但仍需结合白天精神状态判断是否充足。"。
@property (nonatomic, copy) NSString *adjustmentIntro;
/// 睡眠时型（返回字段 chronotype）。数字字符串 1～6，示例：@"3"。
/// 文档分类：日出型、早晨型、晚晨型、中间型、夜间型、深夜型。
@property (nonatomic, copy) NSString *chronotype;
/// 睡眠时型说明（返回字段 chronotype_intro）。
/// 示例（节选）：@"根据本次记录的入睡时间23:00:00，按分类规则归为晚晨型。"。
@property (nonatomic, copy) NSString *chronotypeIntro;
/// 睡眠计划开始时间（返回字段 sleepPlan_start），HH:mm:ss 或 hh:mm:ss AM/PM，24 小时制允许 24:00:00。示例：@"23:00:00"。
@property (nonatomic, copy) NSString *sleepPlanStart;
/// 睡眠计划结束时间（返回字段 sleepPlan_end），HH:mm:ss 或 hh:mm:ss AM/PM，24 小时制允许 24:00:00。示例：@"07:00:00"。
@property (nonatomic, copy) NSString *sleepPlanEnd;

@end

/// 最近七天的运动洞察输入，含当天，所有每日数组为 7 项，按日期从近到远排列，缺失日期填 0。
/// 数组上传为逗号分隔字符串；可选 NSNumber 为 nil、数组为空时，SDK 上传字符串 0。
@interface AiExerciseInsightInput : NSObject

/// 七天日期范围（请求字段 date），含当天，yyyy/MM/dd-yyyy/MM/dd，从近到远。
/// 示例：@"2026/09/22-2026/09/16"。
@property (nonatomic, copy) NSString *date;
/// 目标步数（请求字段 stepGoal），单位：步。示例：@8000。
@property (nonatomic, copy, nullable) NSNumber *stepGoal;
/// 目标活动时长（请求字段 activityDurationGoal_min），单位：分钟。示例：@60。
@property (nonatomic, copy, nullable) NSNumber *activityDurationGoalMinutes;
/// 目标活动热量（请求字段 activitycalorieGoal_kcal），单位：千卡。示例：@350。
@property (nonatomic, copy, nullable) NSNumber *calorieGoalKcal;
/// 七天每日步数（请求字段 steps），单位：步。
/// 示例：@[@5120, @3980, @6100, @6120, @7000, @4500, @4567]。
@property (nonatomic, copy) NSArray<NSNumber *> *steps;
/// 七天每日活动时长（请求字段 activityDuration_min），单位：分钟。
/// 示例：@[@50, @39, @10, @45, @0, @45, @45]。
@property (nonatomic, copy) NSArray<NSNumber *> *activityDurationMinutes;
/// 七天每日实际热量（请求字段 calorieGoal_kcal），单位：千卡；与目标热量字段不同。
/// 示例：@[@350, @351, @352, @356, @345, @362, @340]。
@property (nonatomic, copy) NSArray<NSNumber *> *caloriesKcal;
/// 七天每日情绪（请求字段 mood）；缺失日期填 @"0"。
/// 示例：@[@"有点低落", @"特别低落", @"特别愉悦", @"特别愉悦", @"特别愉悦", @"特别愉悦", @"特别愉悦"]。
/// 有效值：特别低落、有点低落、心情平和、有点愉悦、特别愉悦。
@property (nonatomic, copy) NSArray<NSString *> *mood;
/// 七天每日平均静息心率（请求字段 restingheartRate_bpm），单位：次/分钟；仅统计静息标识数据。
/// 示例：@[@58, @60, @60, @60, @60, @60, @60]。
@property (nonatomic, copy) NSArray<NSNumber *> *restingHeartRateBpm;
/// 七天每日平均心率（请求字段 heartRate_bpm），单位：次/分钟。
/// 示例：@[@45, @56, @56, @56, @56, @45, @45]。
@property (nonatomic, copy) NSArray<NSNumber *> *heartRateBpm;
/// 七天每日平均心率变异性（请求字段 heartratevariability(hrv)），单位：毫秒。
/// 示例：@[@39, @40, @41, @45, @39, @40, @41]。
@property (nonatomic, copy) NSArray<NSNumber *> *heartRateVariability;
/// 七天每日平均压力（请求字段 stress），无单位。
/// 示例：@[@38, @34, @34, @35, @40, @40, @38]。
@property (nonatomic, copy) NSArray<NSNumber *> *stress;
/// 七天每日睡眠时长（请求字段 sleepDuration_min），单位：分钟。
/// 示例：@[@480, @360, @360, @420, @452, @511, @436]。
@property (nonatomic, copy) NSArray<NSNumber *> *sleepDurationMinutes;
/// 七天每日浅睡时长（请求字段 lightSleep_min），单位：分钟。
/// 示例：@[@45, @30, @23, @48, @45, @46, @45]。
@property (nonatomic, copy) NSArray<NSNumber *> *lightSleepMinutes;
/// 七天每日深睡时长（请求字段 deepSleep_min），单位：分钟。
/// 示例：@[@120, @125, @145, @130, @112, @145, @123]。
@property (nonatomic, copy) NSArray<NSNumber *> *deepSleepMinutes;
/// 当天睡眠质量评分（请求字段 sleepQuality），单个数值。示例：@90。
@property (nonatomic, copy, nullable) NSNumber *sleepQuality;

@end

@interface AiExerciseInsightResult : NSObject

/// 运动洞察标题（返回字段 title）。示例：@"拥抱当下的情绪，你的身体依然在温柔地支持你"。
@property (nonatomic, copy) NSString *title;
/// 运动洞察正文（返回字段 content）。
/// 示例（节选）：@"今日步数5120步，活动时长50分钟，卡路里消耗350千卡，睡眠8小时且质量评分90分，整体数据表现良好。"。
@property (nonatomic, copy) NSString *content;
/// 提醒类别（返回字段 remind）：1 睡眠、2 活动、3 生理压力、4 附加、5 正常。示例：4。
/// 整体响应为 0 时，SDK 返回无数据错误，不生成结果 model。
@property (nonatomic, assign) NSInteger reminderType;
/// 可选情绪（返回字段 mood；文档输出 JSON 示例未包含此字段）。示例：@"有点低落"。
/// 有效值：特别低落、有点低落、心情平和、有点愉悦、特别愉悦；未返回或返回 @"0" 时为 nil。
@property (nonatomic, copy, nullable) NSString *mood;

@end

/// 当天身体状态输入，小时数据和睡眠分段数组支持可变数量，上传为逗号分隔字符串。
/// 可选 NSNumber 为 nil、数组为空时，SDK 上传字符串 0。
@interface AiBodyStatusInput : NSObject

/// 记录日期（请求字段 date），yyyy/MM/dd。示例：@"2026/09/22"。
@property (nonatomic, copy) NSString *date;
/// 目标步数（请求字段 stepGoal），单位：步。示例：@8000。
@property (nonatomic, copy, nullable) NSNumber *stepGoal;
/// 当天实际步数（请求字段 steps），单位：步。示例：@5555。
@property (nonatomic, copy, nullable) NSNumber *steps;
/// 当天活动时长（请求字段 activityDuration_min），单位：分钟。示例：@21。
@property (nonatomic, copy, nullable) NSNumber *activityDurationMinutes;
/// 当天实际热量（请求字段 calorieGoal_kcal），单位：千卡。示例：@350。
@property (nonatomic, copy, nullable) NSNumber *caloriesKcal;
/// 按时间顺序排列的小时平均静息心率（请求字段 restingheartRate_bpm），单位：次/分钟。
/// 示例：@[@58, @60, @60, @60, @60, @60]；也支持缺失小时填 0 的完整 24 小时数据。
@property (nonatomic, copy) NSArray<NSNumber *> *restingHeartRateBpm;
/// 按时间顺序排列的小时平均心率（请求字段 heartRate_bpm），单位：次/分钟。
/// 示例：@[@45, @56, @56, @56, @56]。
@property (nonatomic, copy) NSArray<NSNumber *> *heartRateBpm;
/// 按时间顺序排列的小时平均心率变异性（请求字段 heartratevariability(hrv)），单位：毫秒。
/// 示例：@[@39, @40, @41]。
@property (nonatomic, copy) NSArray<NSNumber *> *heartRateVariability;
/// 按时间顺序排列的小时平均压力（请求字段 stress），无单位。示例：@[@38, @34]。
@property (nonatomic, copy) NSArray<NSNumber *> *stress;
/// 当天各段睡眠时长（请求字段 sleep），单位：分钟，按结束时间排列。
/// 示例：@[@268, @158, @66]。
@property (nonatomic, copy) NSArray<NSNumber *> *sleepDurationMinutes;
/// 当天各段浅睡时长（请求字段 lightSleep_min），单位：分钟，顺序与 sleepDurationMinutes 一致。
/// 示例：@[@126, @21, @34]。
@property (nonatomic, copy) NSArray<NSNumber *> *lightSleepMinutes;
/// 当天各段深睡时长（请求字段 deepSleep_min），单位：分钟，顺序与 sleepDurationMinutes 一致。
/// 示例：@[@68, @35, @21]。
@property (nonatomic, copy) NSArray<NSNumber *> *deepSleepMinutes;
/// 主睡眠质量评分（请求字段 sleepQuality），单个数值。示例：@90。
@property (nonatomic, copy, nullable) NSNumber *sleepQuality;

@end

@interface AiBodyStatusResult : NSObject

/// 身体状况标题（返回字段 title）。示例：@"稳步前行，每一次努力都算数"。
@property (nonatomic, copy) NSString *title;
/// 身体状况等级（返回字段 Level，兼容 level）。示例：@"好"，对应评分 72。
/// 文档等级：优秀、良好、好、一般、较差。
@property (nonatomic, copy) NSString *level;
/// 身体状况评分（返回字段 Rating，兼容 rating），范围 0~100。示例：72。
/// 90~100 优秀、80~89 良好、70~79 好、60~69 一般、0~59 较差。
@property (nonatomic, assign) NSInteger rating;
/// 身体状况正文（返回字段 content）。
/// 示例（节选）：@"今日活动量尚有提升空间。实际步数5555步，距离8000步目标略逊一筹，21分钟的活动时长建议适当延长。"。
@property (nonatomic, copy) NSString *content;

@end

NS_ASSUME_NONNULL_END

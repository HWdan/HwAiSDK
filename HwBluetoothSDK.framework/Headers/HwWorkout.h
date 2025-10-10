//
//  HwWorkout.h
//  HwBluetoothSDK
//
//  Created by HuaWo on 2022/1/17.
//

#import <Foundation/Foundation.h>
#import "HwTimeSection.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Workout type enum
 */
typedef NS_ENUM(NSInteger, HwWorkoutType)
{
    HwWorkoutTypeOther = 0,
    HwWorkoutTypeWalk __attribute__((deprecated("Use HwWorkoutTypeOutdoorWalking"))) = 1,
    // 户外健走
    HwWorkoutTypeOutdoorWalking = 1,
    HwWorkoutTypeRun __attribute__((deprecated("Use HwWorkoutTypeOutdoorRunning"))) = 2,
    // 户外跑步
    HwWorkoutTypeOutdoorRunning = 2,
    // 健身操
    HwWorkoutTypeSettingupExercise = 3,
    HwWorkoutTypeSwin __attribute__((deprecated("Use HwWorkoutTypeSwimming"))) = 4,
    // 游泳
    HwWorkoutTypeSwimming = 4,
    // 户外骑行
    HwWorkoutTypeRide __attribute__((deprecated("Use HwWorkoutTypeOutdoorCycling"))) = 5,
    HwWorkoutTypeOutdoorCycling = 5,
    // 爬楼梯
    HwWorkoutTypeClimbStairs __attribute__((deprecated("Use HwWorkoutTypeStairClimbing"))) = 6,
    HwWorkoutTypeStairClimbing = 6,
    // 登山运动
    HwWorkoutTypeClimbMountains __attribute__((deprecated("Use HwWorkoutTypeMoutaineering"))) = 7,
    HwWorkoutTypeMoutaineering = 7,
    // 站立训练
    HwWorkoutTypeStand __attribute__((deprecated("Use HwWorkoutTypeStandingTraining"))) = 8,
    HwWorkoutTypeStandingTraining = 8,
    // 坐姿训练
    HwWorkoutTypeSit __attribute__((deprecated("Use HwWorkoutTypeSittingTraining"))) = 9,
    HwWorkoutTypeSittingTraining = 9,
    
    // 室内骑行
    HwWorkoutTypeRideIndoor __attribute__((deprecated("Use HwWorkoutTypeIndoorCycling"))) = 10,
    HwWorkoutTypeIndoorCycling = 10,
    // 举重训练
    HwWorkoutTypeWeights __attribute__((deprecated("Use HwWorkoutTypeWeightTraining"))) = 11,
    HwWorkoutTypeWeightTraining = 11,
    // 有氧运动
    HwWorkoutTypeAerobics = 12,
    // 室内健走
    HwWorkoutTypeIndoorWalk __attribute__((deprecated("Use HwWorkoutTypeIndoorWalking"))) = 13,
    HwWorkoutTypeIndoorWalking = 13,
    // 室内跑步
    HwWorkoutTypeIndoorRun __attribute__((deprecated("Use HwWorkoutTypeIndoorRunning"))) = 14,
    HwWorkoutTypeIndoorRunning = 14,
    // 瑜伽
    HwWorkoutTypeYoga = 15,
    // 力量训练
    HwWorkoutTypeStrengthTraining = 16,
    // 椭圆机训练
    HwWorkoutTypeEllipticalTraining = 17,
    // 踏步机
    HwWorkoutTypeStairStepper = 18,
    // 跳舞
    HwWorkoutTypeDance = 19,
    // 羽毛球
    HwWorkoutTypeBadminton = 20,
    // 篮球
    HwWorkoutTypeBasketball = 21,
    // 自由训练
    HwWorkoutTypeFreeTraining = 22,
    // 徒步
    HwWorkoutTypeHiking = 23,  // 徒步
    // 越野跑
    HwWorkoutTypeOutdoorRun __attribute__((deprecated("Use HwWorkoutTypeCrossCountry"))) = 24, //野外跑,
    HwWorkoutTypeCrossCountry = 24,
    // 划船机
    HwWorkoutTypeRowingMachine = 25,
    // 攀登
    HwWorkoutTypeClimbing = 26,
    // 需求
    HwWorkoutTypeFootball = 27,
    // 乒乓球
    HwWorkoutTypePingPong = 28,
    // 橄榄球
    HwWorkoutTypeRugby = 29,
    // 网球
    HwWorkoutTypeTennis = 30,
    // 排球
    HwWorkoutTypeVolleyBall = 31,
    // 摔跤
    HwWorkoutTypeWrestling = 32,
    // 拳击
    HwWorkoutTypeBoxing = 33,
    // 普拉提
    HwWorkoutTypePilates = 34,
    // 嘻哈
    HwWorkoutTypeHiphop = 35,
    // 高尔夫
    HwWorkoutTypeGolf = 36,
    // 冲浪
    HwWorkoutTypeSurfing = 37,
    // 皮划艇
    HwWorkoutTypeGanoeing = 38,
    // 滑冰
    HwWorkoutTypeIceSkating = 39,
    // 走步机
    HwWorkoutTypeTreadmill = 40,
    // 打猎
    HwWorkoutTypeHunting = 41,
    // 钓鱼
    HwWorkoutTypeFishing = 42,
    // 玩滑板
    HwWorkoutTypeSkateboarding = 43,
    // 空手道
    HwWorkoutTypeKarate = 44,
    // 跳绳
    HwWorkoutTypeRopeSkipping = 45,
    // 板球
    HwWorkoutTypeCricket = 46,
    // 拉伸
    HwWorkoutTypeStretching = 47,
    // 柔道
    HwWorkoutTypeJudo = 48,
    // 武术
    HwWorkoutTypeMartialArt = 49,
    // 体操
    HwWorkoutTypeGymnastic = 50,
    // 仰卧起坐
    HwWorkoutTypeSitupExercise = 51,
    // 竞走
    HwWorkoutTypeRaceWalking = 52,
    // 马拉松赛跑
    HwWorkoutTypeMarathon = 53,
    // 单车
    HwWorkoutTypeUnicycle = 54,
    // Bmx
    HwWorkoutTypeBmx = 55,
    // 轮滑
    HwWorkoutTypeRollerSkating = 56,
    // 健腹轮
    HwWorkoutTypeAbRoller = 57,
    // 步行机
    HwWorkoutTypeWalkingMachine = 58,
    // 呼拉圈
    HwWorkoutTypeHulaHoop = 59,
    // 飞镖
    HwWorkoutTypeDarts = 60,
    // 棒球运动
    HwWorkoutTypeBaseball = 61,
    // 台球
    HwWorkoutTypeBilliard = 62,
    // 羽毛球
    HwWorkoutTypeShuttlecock = 63,
    // 马球
    HwWorkoutTypePolo = 64,
    // 壁球
    HwWorkoutTypeSquash = 65,
    // 保龄球
    HwWorkoutTypeBowling = 66,
    // 体操
    HwWorkoutTypeGymBall = 67,
    // 曲棍球
    HwWorkoutTypeHockey = 68,
    // 芭蕾
    HwWorkoutTypeBallet = 69,
    // 快步舞
    HwWorkoutTypeQuickstep = 70,
    // 摇摆舞
    HwWorkoutTypeJive = 71,
    // 肚皮舞
    HwWorkoutTypeBellyDance = 72,
    // 探戈
    HwWorkoutTypeTango = 73,
    // 塑造
    HwWorkoutTypeShaping = 74,
    // 钢管舞
    HwWorkoutTypePoleDance = 75,
    // 恰恰舞
    HwWorkoutTypeChaCha = 76,
    // 伦巴
    HwWorkoutTypeRumba = 77,
    HwWorkoutTypeJazz = 78,
    HwWorkoutTypeSamba = 79,
    HwWorkoutTypePasoDoble = 80,
    HwWorkoutTypeWaltz = 81,
    HwWorkoutTypeMuayThai = 82,
    HwWorkoutTypeTaekwondo = 83,
    HwWorkoutTypefreeFight = 84,
    HwWorkoutTypeSanda = 85,
    HwWorkoutTypeJeetKuneDo = 86,
    HwWorkoutTypeMma = 87,
    HwWorkoutTypeKickboxing = 88,
    HwWorkoutTypeTaiChi = 89,
    HwWorkoutTypeSambo = 90,
    HwWorkoutTypeMulanquan = 91,
    HwWorkoutTypeSumo = 92,
    HwWorkoutTypeAikido = 93,
    HwWorkoutTypeFrisbee = 94,
    HwWorkoutTypeGliding = 95,
    HwWorkoutTypeTugOfWar = 96,
    HwWorkoutTypeHotAirBalloon = 97,
    HwWorkoutTypeParkour = 98,
    HwWorkoutTypeCarRace = 99,
    HwWorkoutTypeSailing = 100,
    HwWorkoutTypeMotorcycleRace = 101,
    HwWorkoutTypeExplore = 102,
    HwWorkoutTypeMotorboat = 103,
    HwWorkoutTypeDrift = 104,
    HwWorkoutTypeRowing = 105,
    HwWorkoutTypeBungee = 106,
    HwWorkoutTypeParachuting = 107,
    HwWorkoutTypeHorseRace = 108,
    //高强度间歇训练
    HwWorkoutTypeHIIT = 109,
    //核心训练
    HwWorkoutTypeCORETRAINING = 110,
    //有氧训练
    HwWorkoutTypeAEROBICTRAINING = 111,
    //无氧训练
    HwWorkoutTypeANAEROBICTRAINING = 112,
    //混合有氧
    HwWorkoutTypeMIXEDTRAINING = 113,
    //柔韧训练
    HwWorkoutTypeFLEXIBILITYTRAINING = 114,
    //冥想
    HwWorkoutTypeMEDITATION = 115,
    //室内健身
    HwWorkoutTypeINDOORFITNESS = 116,
    //踏步训练
    HwWorkoutTypeSTEPPING = 117,
    //划船
    HwWorkoutTypeBOATRACING = 118,
    //遛狗
    HwWorkoutTypeDOGWALKING = 119,
    //冰壶
    HwWorkoutTypeCURLING = 120,
    //户外溜冰
    HwWorkoutTypeOUTDOORICESKATING = 121,
    //室内溜冰
    HwWorkoutTypeINDOORICESKATING = 122,
    //滑雪
    HwWorkoutTypeSKIING = 123,
    //冬季两项
    HwWorkoutTypeBIATHLON = 124,
    //手球
    HwWorkoutTypeHANDBALL = 125,
    //垒球
    HwWorkoutTypeSOFTBALL = 126,
    //门球
    HwWorkoutTypeCROQUET = 127,
    //沙滩排球
    HwWorkoutTypeBEACHVOLLEYBALL = 128,
    //躲避球
    HwWorkoutTypeDODGEBALL = 129,
    //美式足球
    HwWorkoutTypeAMERICANFOOTBALL = 130,
    //广场舞
    HwWorkoutTypeSQUAREDANCE = 131,
    //交谊舞
    HwWorkoutTypeBALLROOMDANCE = 132,
    //尊巴
    HwWorkoutTypeZUMBA = 133,
    //迪斯科
    HwWorkoutTypeDISCO = 134,
    //拉丁舞
    HwWorkoutTypeLATIN = 135,
    //踢踏舞
    HwWorkoutTypeTAPDANCE = 136,
    //剑术
    HwWorkoutTypeFENCING = 137,
    //骑马
    HwWorkoutTypeHORSERIDING = 138,
    //射箭
    HwWorkoutTypeARCHERY = 139,
    //障碍赛
    HwWorkoutTypeSTEEPLECHASE = 140,
    //放风筝
    HwWorkoutTypeKITEFLYING = 141,
    //单杠
    HwWorkoutTypeHORIZONTALBAR = 142,
    //双杠
    HwWorkoutTypePARALLELBARS = 143,
    // 爬楼梯
    HwWorkoutTypeSTAIRCLIMBING = 144,
    // 室内游泳
    HwWorkoutTypeIndoorSwimming = 145,
    // 室外游泳
    HwWorkoutTypeOutdoorSwimming = 146,
};


@class HwWorkoutPoint;
@class HwWorkoutGpsPoint;
@interface HwWorkout : NSObject

/*! @brief
 索引[index]
 */
@property(nonatomic, assign) NSUInteger index;


/*! @brief
 时间点（毫秒级时间戳）[interval time, milli seconds]
 */
@property(nonatomic, assign) long startTime;

/*! @brief
 时间点（毫秒级时间戳）[interval time, milli seconds]
 */
@property(nonatomic, assign) long endTime;

/*! @brief
 Record the workout pause period
 */
@property(nonatomic, copy) NSArray *pausedTimeSections;

/*! @brief
 运动类型[workout type]
 */
@property(nonatomic, assign) HwWorkoutType type;

/*! @brief
 步数[step]
 */
@property(nonatomic, assign) NSUInteger step;
/*! @brief
 卡路里[calorie]
 */
@property(nonatomic, assign) NSUInteger calorie;
/*! @brief
 距离[distance]
 */
@property(nonatomic, assign) NSUInteger distance;
/*! @brief
 运动时间[integer duration]
 */
@property(nonatomic, assign) NSUInteger duration;

/*! @brief
 average heartRate bpm for this moment
 */
@property(nonatomic, assign) NSUInteger bpm;

@property(nonatomic, assign) NSUInteger maxBpm;
@property(nonatomic, assign) NSUInteger minBpm;

@property(nonatomic, assign) NSUInteger pace;            // 秒/千米
@property(nonatomic, assign) NSUInteger speed;           // 千米/小时
@property(nonatomic, assign) NSUInteger lapDuration;      // 一圈要多少分钟
@property(nonatomic, assign) NSUInteger cadence;            // 步频，步数/分钟

//多运动
@property(nonatomic, assign) NSUInteger warmUpDuration;   //多运动的
@property(nonatomic, assign) NSUInteger burningDuration;
@property(nonatomic, assign) NSUInteger aerobicDuration;
@property(nonatomic, assign) NSUInteger anaerobicDuration;
@property(nonatomic, assign) NSUInteger limitDuration;
@property(nonatomic, assign) NSUInteger restingDuration;

@property(nonatomic, strong) NSArray<HwWorkoutPoint *> *workoutPoints;
@property(nonatomic, strong) NSArray<HwWorkoutGpsPoint *> *workoutGpsPoints;

- (HwWorkout *) initWithData:(NSData *)data;


@end

NS_ASSUME_NONNULL_END

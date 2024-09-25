#ifndef GUARD_BATTLE_RAID_H
#define GUARD_BATTLE_RAID_H

#include "constants/battle_raid.h"

struct RaidType {
    u16 shield:4;
    u16 shockwave:4;
    u16 rules:4;
    u16 gimmick:4;
};

struct RaidData {
    u8 rank;
    u8 raidType;
    u16 partnerNum;
};

struct RaidPartnerData
{
    u16 trainerNum;
	u16 graphicsId;
};

struct RaidPartner
{
	const struct RaidPartnerData *partnerData;
	u8 numOfPartners;
};


extern const struct RaidType gRaidTypes[NUM_RAID_TYPES];
extern struct RaidData gRaidData;
extern const struct RaidPartner gRaidPartners[];

// Functions
bool32 InitRaidData(void);
bool32 InitCustomRaidData(void);
void InitRaidBattleData(void);
u32 GetRaidBossBattler(void);
bool32 IsRaidBoss(u32 battlerId);
u8 GetRaidBattleTransition(void);
void ApplyRaidHPMultiplier(u32 battlerId, struct Pokemon* mon);
bool32 ShouldRaidKickPlayer(void);
bool32 ShouldMoveDynamaxEnergy(void);
bool32 HandleTeraOrbCharge(void);
bool8 DoesRaidPreventMove(u16 move);
u8 GetRaidRepeatedAttackChance(void);
u8 GetRaidShockwaveChance(void);
u32 GetRaidShockwaveNum(void);
u8 GetRaidBossKOStatIncrease(u8 battlerId);
bool32 UpdateRaidShield(void);
u16 GetShieldDamageRequired(u16 hp, u16 maxHP);
u16 GetShieldDamageReduction(void);
void RaidBarrier_SetVisibilities(u32 healthboxId, bool32 invisible);
void CreateRaidTimerSprites(void);
void DestroyRaidTimerSprites(void);
void RaidTimer_SetVisibilities(u32 healthboxId, bool32 invisible);
void UpdateRaidTimerSprites(void);

void SetRaidBattleFlag(void);
bool8 GetRaidBattleFlag(void);
void ClearRaidBattleFlag(void);
void ClearAllRaidBattleFlags(void);

void GiveRaidBattleRewards(void);
u8 GetRaidRecommendedLevel(void);
u8 GetRaidEggMoveChance(void);
void DetermineRaidPartners(u8* partnerTrainerIndex, u8 maxPartners);
u16 OverrideRaidPartnerTrainerId(u16 trainerId);

#endif

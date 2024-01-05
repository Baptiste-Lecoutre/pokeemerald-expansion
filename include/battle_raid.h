#ifndef GUARD_BATTLE_RAID_H
#define GUARD_BATTLE_RAID_H

#include "constants/battle_raid.h"

struct RaidType {
    u8 shield:1;
    u8 shockwave:1;
    u8 rules:1;
    u8 gimmick;
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
bool32 IsRaidBoss(u16 battlerId);
u8 GetRaidBattleTransition(void);
void ApplyRaidHPMultiplier(u16 battlerId, struct Pokemon* mon);
bool32 ShouldRaidKickPlayer(void);
bool32 ShouldMoveDynamaxEnergy(void);
bool8 DoesRaidPreventMove(u16 move);
u8 GetRaidRepeatedAttackChance(void);
u8 GetRaidShockwaveChance(void);
u8 GetRaidBossKOStatIncrease(u8 battlerId);
bool32 UpdateRaidShield(void);
u16 GetShieldDamageRequired(u16 hp, u16 maxHP);
u16 GetShieldDamageReduction(void);
void RaidBarrier_SetVisibilities(u32 healthboxId, bool32 invisible);

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

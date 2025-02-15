#ifndef GUARD_BATTLE_RAID_H
#define GUARD_BATTLE_RAID_H

#include "constants/battle_raid.h"

struct RaidType {
    u16 shieldType:4;
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
extern u8 gRaidBossBattler; // bitfield for raid boss POSITIONS, used to link the battlers raid boss fields to the setup scripts at the begining of the battle

// Functions
bool32 InitRaidData(void);
bool32 InitCustomRaidData(void);
bool32 InitRaidBattleData(void);

void SetRaidBossBattlers(void);
u32 GetRaidBossBattler(void);
bool32 IsRaidBoss(u32 battlerId);

u32 GetRaidBattleTransition(void);
void ApplyRaidHPMultiplier(struct Pokemon* mon);
bool32 ShouldRaidKickPlayer(void);
bool32 ShouldMoveDynamaxEnergy(void);
bool32 HandleTeraOrbCharge(void);
bool32 DoesRaidPreventMove(u16 move);
void ClearTurnRaidValues(void);

u32 GetRaidRepeatedAttackChance(void);
bool32 TryRaidBossAdditionalMove(u32 battler);

bool32 TryRaidShockwave(void);

u32 GetRaidBossKOStatIncrease(u8 battlerId);
bool32 ApplyRaidBossStatIncrease(u32 faintedBattler, const u8 *nextInstr);

bool32 UpdateRaidShield(void);
void HideRaidAdditionalSprites(void);
u16 GetShieldDamageRequired(u32 battler);
u16 GetShieldDamageReduction(void);
void AdjustRaidBossDamage(u32 attacker, u32 target);
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

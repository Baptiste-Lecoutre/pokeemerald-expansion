#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_interface.h"
#include "battle_raid.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "battle_z_move.h"
#include "data.h"
#include "daycare.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "constants/battle_raid.h"
#include "constants/battle_string_ids.h"
#include "constants/daycare.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"

// Settings for each Raid Type.
const struct RaidType gRaidTypes[NUM_RAID_TYPES] = {
    [RAID_TYPE_MAX] = {
        .shield = RAID_SHIELD_MAX,
        .shockwave = RAID_GEN_8,
        .rules = RAID_RULES_MAX,
        .gimmick = GIMMICK_DYNAMAX,
    },
    [RAID_TYPE_TERA] = {
        .shield = RAID_SHIELD_TERA,
        .shockwave = RAID_GEN_9,
        .rules = RAID_RULES_TERA,
        .gimmick = GIMMICK_TERA,
    },
    [RAID_TYPE_MEGA] = {
        .shield = RAID_SHIELD_MEGA,
        .shockwave = RAID_GEN_8,
        .rules = RAID_RULES_MEGA,
        .gimmick = GIMMICK_MEGA,
    },
    [RAID_TYPE_PRIMAL] = {
        .shield = RAID_SHIELD_MEGA,
        .shockwave = RAID_GEN_8,
        .rules = RAID_RULES_MEGA,
        .gimmick = GIMMICK_PRIMAL,
    },
};

// Rank-based HP Multipliers
static const u16 sGen8RaidHPMultipliers[] = {
    [NO_RAID]     = UQ_4_12(1.0),
    [RAID_RANK_1] = UQ_4_12(1.4),
    [RAID_RANK_2] = UQ_4_12(1.6),
    [RAID_RANK_3] = UQ_4_12(1.9),
    [RAID_RANK_4] = UQ_4_12(2.5),
    [RAID_RANK_5] = UQ_4_12(3.0),
    [RAID_RANK_6] = UQ_4_12(3.0),
    [RAID_RANK_7] = UQ_4_12(3.0),
};

static const u16 sGen9RaidHPMultipliers[] = { // should bave been UQ_4_12() as well, but it's limited to 16...
    [NO_RAID]     = 1,
    [RAID_RANK_1] = 5,
    [RAID_RANK_2] = 5,
    [RAID_RANK_3] = 8,
    [RAID_RANK_4] = 12,
    [RAID_RANK_5] = 20,
    [RAID_RANK_6] = 25,
    [RAID_RANK_7] = 30,
};

const u8 gRaidBattleStarsByBadges[][2] =
{
	[0] = {NO_RAID,         NO_RAID},
	[1] = {RAID_RANK_1, RAID_RANK_1},
	[2] = {RAID_RANK_1, RAID_RANK_2},
	[3] = {RAID_RANK_2, RAID_RANK_2},
	[4] = {RAID_RANK_2, RAID_RANK_3},
	[5] = {RAID_RANK_3, RAID_RANK_3},
	[6] = {RAID_RANK_3, RAID_RANK_4},
	[7] = {RAID_RANK_4, RAID_RANK_4},
	[8] = {RAID_RANK_4, RAID_RANK_5},
	[9] = {RAID_RANK_5, RAID_RANK_6}, //Beat Game
};

const u8 gRaidBattleLevelRanges[MAX_RAID_RANK + 1][2] =
{
	[NO_RAID]     = {1, 2},
    [RAID_RANK_1] = {15, 20},
	[RAID_RANK_2] = {25, 30},
	[RAID_RANK_3] = {35, 40},
	[RAID_RANK_4] = {50, 55},
	[RAID_RANK_5] = {60, 65},
	[RAID_RANK_6] = {75, 90},
    [RAID_RANK_7] = {90, 100},
};

// The chance that each move is replaced with an Egg Move
const u8 gRaidBattleEggMoveChances[MAX_RAID_RANK + 1] =
{
	[NO_RAID]     = 0,
    [RAID_RANK_1] = 0,
	[RAID_RANK_2] = 10,
	[RAID_RANK_3] = 30,
	[RAID_RANK_4] = 50,
	[RAID_RANK_5] = 70,
	[RAID_RANK_6] = 80,
    [RAID_RANK_7] = 90,
};

// The chance that the raid boss has its hidden ability
const u8 gRaidBattleHiddenAbilityChances[MAX_RAID_RANK + 1] =
{
    [NO_RAID]     = 0,
    [RAID_RANK_1] = 0,
	[RAID_RANK_2] = 0,
	[RAID_RANK_3] = 10,
	[RAID_RANK_4] = 20,
	[RAID_RANK_5] = 30,
	[RAID_RANK_6] = 40,
    [RAID_RANK_7] = 50,
};

// The chance that the raid boss to be gigantamax
const u8 gRaidBattleGigantamaxChances[MAX_RAID_RANK + 1] =
{
    [NO_RAID]     = 0,
    [RAID_RANK_1] = 0,
	[RAID_RANK_2] = 0,
	[RAID_RANK_3] = 5,
	[RAID_RANK_4] = 10,
	[RAID_RANK_5] = 50,
	[RAID_RANK_6] = 90,
    [RAID_RANK_7] = 100,
};

// The number of perfect IVs the raid boss is certain to have
const u8 gRaidBattlePerfectIVsNumber[MAX_RAID_RANK + 1] =
{
    [NO_RAID]     = 0,
    [RAID_RANK_1] = 1,
	[RAID_RANK_2] = 2,
	[RAID_RANK_3] = 3,
	[RAID_RANK_4] = 4,
	[RAID_RANK_5] = 5,
	[RAID_RANK_6] = 6,
    [RAID_RANK_7] = 6,
};

static const u8 sRaidBattleDropRates[MAX_RAID_DROPS] =
{	//In percent
	100,
	80,
	80,
	50,
	50,
	30,
	30,
	25,
	25,
	5,
	4,
	1,
};

static const u16 sRaidBattleDropItems_NoRaid[MAX_RAID_DROPS] = {
    ITEM_NONE, //100
    ITEM_NONE, //80
    ITEM_NONE, //80
    ITEM_NONE, //50
    ITEM_NONE, //50
    ITEM_NONE, //30
    ITEM_NONE, //30
    ITEM_NONE, //25
    ITEM_NONE, //25
    ITEM_NONE, //5
    ITEM_NONE, //4
    ITEM_NONE //1
};

static const u16 sRaidBattleDropItems_RaidRank1[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_XS, //100
    ITEM_EXP_CANDY_S, //80
    ITEM_EXP_CANDY_XS, //80
    FIRST_BERRY_INDEX, //50
    ITEM_MASTER_BALL, //50
    ITEM_HEALTH_FEATHER, //30
    ITEM_EXP_CANDY_XS, //30
    ITEM_STRANGE_SOUVENIR, //25
    ITEM_RARE_CANDY, //25
    ITEM_WISHING_PIECE, //5
    ITEM_WISHING_PIECE, //4
    ITEM_WISHING_PIECE //1
};

static const u16 sRaidBattleDropItems_RaidRank2[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_S, //100
    ITEM_EXP_CANDY_M, //80
	ITEM_HEALTH_FEATHER, //80
	FIRST_BERRY_INDEX, //50
	ITEM_MASTER_BALL, //50
	ITEM_HEALTH_FEATHER, //30
	ITEM_STRANGE_SOUVENIR, //30
	ITEM_ABILITY_CAPSULE, //25
	ITEM_RARE_CANDY, //25
	ITEM_WISHING_PIECE, //5
	ITEM_WISHING_PIECE, //4
	ITEM_WISHING_PIECE, //1
};

static const u16 sRaidBattleDropItems_RaidRank3[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_M, //100
    ITEM_EXP_CANDY_L, //80
	ITEM_HEALTH_FEATHER, //80
	FIRST_BERRY_INDEX, //50
	ITEM_MASTER_BALL, //50
	ITEM_HEALTH_FEATHER, //30
	ITEM_STRANGE_SOUVENIR, //30
	ITEM_LONELY_MINT, //25
	ITEM_ABILITY_CAPSULE, //25
	ITEM_HP_UP, //5
	ITEM_HP_UP, //4
	ITEM_HP_UP, //1
};

static const u16 sRaidBattleDropItems_RaidRank4[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_L, //100
    FIRST_BERRY_INDEX, //80
	ITEM_HEALTH_FEATHER, //80
	ITEM_ABILITY_CAPSULE, //50
	ITEM_LONELY_MINT, //50
	ITEM_BOTTLE_CAP, //30
	ITEM_FIRE_STONE, //30
	ITEM_SILK_SCARF, //25
	ITEM_ABILITY_PATCH, //25
	ITEM_HP_UP, //5
	ITEM_HP_UP, //4
	ITEM_HP_UP, //1
};

static const u16 sRaidBattleDropItems_RaidRank5[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_L, //100
    ITEM_BOTTLE_CAP, //80
	ITEM_EXP_CANDY_XL, //80
	ITEM_SILK_SCARF, //50
	ITEM_LONELY_MINT, //50
	ITEM_ABILITY_PATCH, //30
	ITEM_FIRE_STONE, //30
	ITEM_HP_UP, //25
	ITEM_HELIX_FOSSIL, //25
	ITEM_WISHING_PIECE, //5
	ITEM_WISHING_PIECE, //4
	ITEM_WISHING_PIECE, //1
};

static const u16 sRaidBattleDropItems_RaidRank6[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_XL, //100
    ITEM_ABILITY_PATCH, //80
	ITEM_LONELY_MINT, //80
	ITEM_GOLD_BOTTLE_CAP, //50
	ITEM_BOTTLE_CAP, //50
	ITEM_ABILITY_CAPSULE, //30
	ITEM_HELIX_FOSSIL, //30
	ITEM_HP_UP, //25
	ITEM_MASTER_BALL, //25
	ITEM_WISHING_PIECE, //5
	ITEM_WISHING_PIECE, //4
	ITEM_WISHING_PIECE, //1
};

static const u16 sRaidBattleDropItems_RaidRank7[MAX_RAID_DROPS] = {
    ITEM_EXP_CANDY_XL, //100
    ITEM_ABILITY_PATCH, //80
	ITEM_MASTER_BALL, //80
	ITEM_GOLD_BOTTLE_CAP, //50
	ITEM_STRANGE_SOUVENIR, //50
	ITEM_ABILITY_CAPSULE, //30
	ITEM_HELIX_FOSSIL, //30
	ITEM_HP_UP, //25
	ITEM_LONELY_MINT, //25
	ITEM_WISHING_PIECE, //5
	ITEM_WISHING_PIECE, //4
	ITEM_WISHING_PIECE, //1
};
    /*Here is the list of items to refer into the drops list:
    FIRST_BERRY_INDEX - random berry
    ITEM_LONELY_MINT - random mint
    ITEM_HELIX_FOSSIL - random fossil
    ITEM_BUG_TERA_SHARD - random tera shard - unused
    ITEM_HEALTH_FEATHER - random EV feather
    ITEM_HP_UP - random energy drink
    ITEM_FIRE_STONE - random evo item
    ITEM_SILK_SCARF - random held item
    ITEM_STRANGE_SOUVENIR - random treasure*/

static const u16 *const sRaidBattleDropItems[] = 
{
    [NO_RAID] = sRaidBattleDropItems_NoRaid, 
    [RAID_RANK_1] = sRaidBattleDropItems_RaidRank1,
    [RAID_RANK_2] = sRaidBattleDropItems_RaidRank2,
    [RAID_RANK_3] = sRaidBattleDropItems_RaidRank3,
    [RAID_RANK_4] = sRaidBattleDropItems_RaidRank4,
    [RAID_RANK_5] = sRaidBattleDropItems_RaidRank5,
    [RAID_RANK_6] = sRaidBattleDropItems_RaidRank6,
    [RAID_RANK_7] = sRaidBattleDropItems_RaidRank7
};

EWRAM_DATA struct RaidData gRaidData = {0};

// forward declarations
static u8 GetRaidShieldThresholdTotalNumber(void);
static u16 GetNextShieldThreshold(void);
static u16 GetShieldAmount(void);
static u32 CreateRaidBarrierSprite(u8 index);
static void CreateAllRaidBarrierSprites(void);
static void DestroyRaidBarrierSprite(u8 index);
u32 GetRaidRandomNumber(void);

// Sets the data for the Raid being loaded from the map information.
bool32 InitRaidData(void)
{
    u16 numBadges, min, max, species = SPECIES_NONE, preEvoSpecies = SPECIES_NONE, postEvoSpecies = SPECIES_NONE;
	u32 i, randomNum = GetRaidRandomNumber(), numEggMoves;
    u8 raidBossLevel, numPostEvoSpecies = 0, maxIV = MAX_IV_MASK, eggMoveChance = GetRaidEggMoveChance();
    u8 statIDs[NUM_STATS] = {STAT_HP, STAT_ATK, STAT_DEF, STAT_SPEED, STAT_SPATK, STAT_SPDEF};
    u16 eggMoves[EGG_MOVES_ARRAY_COUNT] = {0};
    struct Pokemon* mon = &gEnemyParty[0];
    bool32 boolTrue = TRUE;

    // determine raid type
    if (CheckBagHasItem(ITEM_DYNAMAX_BAND, 1) && CheckBagHasItem(ITEM_TERA_ORB, 1))
        gRaidData.raidType = (randomNum & 1) ? RAID_TYPE_MAX : RAID_TYPE_MAX;//RAID_TYPE_TERA;
    else if (CheckBagHasItem(ITEM_DYNAMAX_BAND, 1))
        gRaidData.raidType = RAID_TYPE_MAX;
    else if (CheckBagHasItem(ITEM_TERA_ORB, 1))
        gRaidData.raidType = RAID_TYPE_TERA;
    else
        gRaidData.raidType = RAID_TYPE_MAX;

    // determine raid rank based on number of badges
    gRaidData.rank = gRaidBattleStarsByBadges[GetNumberOfBadges()][randomNum & 1];
    //numBadges = GetNumberOfBadges();
    //min = gRaidBattleStarsByBadges[numBadges][0];
	//max = gRaidBattleStarsByBadges[numBadges][1];
    //if (min == max)
    //    gRaidData.rank = min;
    //else
    //    gRaidData.rank = (randomNum % ((max + 1) - min)) + min;
    
    // determine raid boss level based on raid rank
    min = gRaidBattleLevelRanges[gRaidData.rank][0];
	max = gRaidBattleLevelRanges[gRaidData.rank][1];

    if (min == max)
        raidBossLevel = min;
    else
        raidBossLevel = (randomNum % ((max + 1) - min)) + min;

    // determine raid species
    do
    {
        species = ((randomNum + species) % SPECIES_VENUSAUR_MEGA) + 1;
    } while (species == SPECIES_NONE || gSpeciesInfo[species].isLegendary || gSpeciesInfo[species].isMythical || gSpeciesInfo[species].isUltraBeast);

    // should check here for legendaries & mythicals. Maybe choose a random form as well
    /*preEvoSpecies = GetPreEvolution(species);
    postEvoSpecies = gEvolutionTable[species][0].targetSpecies;

    // if low rank raid and pre-evolution exists, go for it
    if (preEvoSpecies != SPECIES_NONE && gRaidData.rank < RAID_RANK_3)
    {
        species = preEvoSpecies;
        preEvoSpecies = GetPreEvolution(species);

        // if lowest rank and can find an even lower evolution, go for it
        if (preEvoSpecies != SPECIES_NONE && gRaidData.rank < RAID_RANK_2)
            species = preEvoSpecies;
    }

    // if higher raid rank and post evolution exists, choose a post evolution in a random evo line
    if (postEvoSpecies != SPECIES_NONE && gRaidData.rank > RAID_RANK_2)
    {
        for (i = 0; i < EVOS_PER_MON; i++)
        {
            if (gEvolutionTable[species][i].targetSpecies)
                numPostEvoSpecies++;
        }
        species = gEvolutionTable[species][randomNum % numPostEvoSpecies].targetSpecies;
        postEvoSpecies = gEvolutionTable[species][0].targetSpecies;
        numPostEvoSpecies = 0;
        
        // if even higher raid rank, use last evo stage and choose a random evo line 
        if (postEvoSpecies != SPECIES_NONE && gRaidData.rank > RAID_RANK_4)
        {
            for (i = 0; i < EVOS_PER_MON; i++)
            {
                if (gEvolutionTable[species][i].targetSpecies)
                    numPostEvoSpecies++;
            }
            species = gEvolutionTable[species][randomNum % numPostEvoSpecies].targetSpecies;
        }
    }*/

    // Hidden ability
    if (P_FLAG_FORCE_HIDDEN_ABILITY != 0 && randomNum % 100 < gRaidBattleHiddenAbilityChances[gRaidData.rank])
        FlagSet(P_FLAG_FORCE_HIDDEN_ABILITY);

    // Raid bosses have increased shiny odds: +1% for each rank
    if (P_FLAG_FORCE_SHINY != 0 && randomNum % 100 < gRaidData.rank)
        FlagSet(P_FLAG_FORCE_SHINY);

    // Free previous enemy party in case
    ZeroEnemyPartyMons();

    // Create raid boss
    CreateMon(mon, species, raidBossLevel, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);

    // Set a certain number of perfect IVs
    if (gRaidBattlePerfectIVsNumber[gRaidData.rank])
    {
        ShuffleStatArray(statIDs);
        for (i = 0; i < gRaidBattlePerfectIVsNumber[gRaidData.rank]; i++)
            SetMonData(mon, MON_DATA_HP_IV + statIDs[i], &maxIV);
    }

    // Give egg moves
    numEggMoves = GetEggMovesSpecies(species, eggMoves);
    if (numEggMoves && Random() % 100 < eggMoveChance)
    {
        u16 eggMove = eggMoves[RandRange(0, numEggMoves)];

        if (MonKnowsMove(mon, eggMove))
            eggMove = eggMoves[RandRange(0, numEggMoves)];

        if (!MonKnowsMove(mon, eggMove) && GiveMoveToMon(mon, eggMove) == MON_HAS_MAX_MOVES)
            DeleteFirstMoveAndGiveMoveToMon(mon, eggMove);
    }

    // Gigantamax factor & dynamax level
    if (gRaidTypes[gRaidData.raidType].gimmick == GIMMICK_DYNAMAX)
    {
        postEvoSpecies = GetGMaxTargetSpecies(species);

        if(postEvoSpecies != SPECIES_NONE && randomNum % 100 < gRaidBattleGigantamaxChances[gRaidData.rank])
        {
            SetMonData(mon, MON_DATA_GIGANTAMAX_FACTOR, &boolTrue);
            SetMonData(mon, MON_DATA_SPECIES, &postEvoSpecies);
            SetMonData(mon, MON_DATA_SPECIES_OR_EGG, &postEvoSpecies);
        }

        raidBossLevel = randomNum % 4 + gRaidData.rank;
        SetMonData(mon, MON_DATA_DYNAMAX_LEVEL, &raidBossLevel);
    }

    // Tera type
    if (gRaidTypes[gRaidData.raidType].gimmick == GIMMICK_TERA)
    {
        u32 teraType = randomNum % (NUMBER_OF_MON_TYPES - 2);
        if (teraType >= TYPE_MYSTERY)
            teraType++;
        SetMonData(mon, MON_DATA_TERA_TYPE, &teraType);
    }

    return TRUE;
}

// Sets the data for the Raid being loaded from set variables.
bool32 InitCustomRaidData(void)
{
    u16 item = gSpecialVar_0x8008, species = gSpecialVar_0x8003;
    u8 level = gSpecialVar_0x8007, teraType = gSpecialVar_0x8009;
    gRaidData.raidType = gSpecialVar_0x8001;
    gRaidData.rank = gSpecialVar_0x8002;

    // Free previous enemy party in case
    ZeroEnemyPartyMons();

    // Create raid boss
    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);

    if (item != ITEM_NONE)
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, &item);
    if (teraType != TYPE_NONE)

        SetMonData(&gEnemyParty[0], MON_DATA_TERA_TYPE, &teraType);

    if (gSpeciesInfo[species].isGigantamax)
    {
        bool32 boolTrue = TRUE;
        u8 dynamaxLevel = gRaidData.rank + 3;
        SetMonData(&gEnemyParty[0], MON_DATA_GIGANTAMAX_FACTOR, &boolTrue);
        SetMonData(&gEnemyParty[0], MON_DATA_DYNAMAX_LEVEL, &dynamaxLevel);
    }

    return TRUE;
}

// Sets up the RaidBattleData struct in gBattleStruct, run during battle intro setup after battle transition.
void InitRaidBattleData(void)
{
    u32 i;

    gBattleStruct->raid.shieldsRemaining = GetRaidShieldThresholdTotalNumber();
    gBattleStruct->raid.nextShield = GetNextShieldThreshold();
    gBattleStruct->raid.shield = 0;
    gBattleStruct->raid.state |= RAID_INTRO_COMPLETE;
	gBattleStruct->raid.energy = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);

    // Zeroes sprite IDs for Gen 8-style shield.
    for (i = 0; i < MAX_BARRIER_COUNT; i++)
        gBattleStruct->raid.barrierSpriteIds[i] = MAX_SPRITES;

    // Mega Raids start off with a shield at the beginning.
    if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
    {
        gBattleStruct->raid.shield = GetShieldAmount();
        CreateAllRaidBarrierSprites();
        RaidBarrier_SetVisibilities(gHealthboxSpriteIds[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)], TRUE);

        if (gBattleMons[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].species == SPECIES_RAYQUAZA) // handle the rayquaza wish mega evo special case
            gBattleMons[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].moves[3] = MOVE_DRAGON_ASCENT;
    }

    // Update HP Multiplier.
    RecalcBattlerStats(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), &gEnemyParty[0]);
}

// Returns whether the target is a Raid Boss. Includes battle type flag check.
bool32 IsRaidBoss(u16 battlerId)
{
    return (gBattleTypeFlags & BATTLE_TYPE_RAID) && GetBattlerPosition(battlerId) == B_POSITION_OPPONENT_LEFT;
}

// Returns the battle transition ID for the Raid battle.
u8 GetRaidBattleTransition(void)
{
    if (gRaidData.raidType == RAID_TYPE_TERA)
        return B_TRANSITION_TERA_RAID;
    else if (gRaidTypes[gRaidData.raidType].gimmick == GIMMICK_MEGA
            || gRaidTypes[gRaidData.raidType].gimmick == GIMMICK_PRIMAL)
        return B_TRANSITION_MEGA_RAID;
    else
        return B_TRANSITION_MAX_RAID;
}

// Applies the HP multiplier for Raid Bosses.
// Ideally, I should have used UQ_4_12 all the way, but the possible values are to low for tera multipliers (limited to 16).
// Hence the redundancy in the code below
void ApplyRaidHPMultiplier(u16 battlerId, struct Pokemon* mon)
{
    u16 mult, hp, maxHP;

    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_SHEDINJA)
        return;

    if (gRaidTypes[gRaidData.raidType].rules == RAID_RULES_MAX
        || gRaidTypes[gRaidData.raidType].rules == RAID_RULES_MEGA)
    {
        mult = sGen8RaidHPMultipliers[gRaidData.rank];
        hp = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_HP) * mult) + UQ_4_12_ROUND);
        maxHP = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_MAX_HP) * mult) + UQ_4_12_ROUND);
        SetMonData(mon, MON_DATA_HP, &hp);
        SetMonData(mon, MON_DATA_MAX_HP, &maxHP);
    }
    else if (gRaidTypes[gRaidData.raidType].rules == RAID_RULES_TERA)
    {
        mult = sGen9RaidHPMultipliers[gRaidData.rank];
        hp = GetMonData(mon, MON_DATA_HP) * mult;
        maxHP = GetMonData(mon, MON_DATA_MAX_HP) * mult;
        SetMonData(mon, MON_DATA_HP, &hp);
        SetMonData(mon, MON_DATA_MAX_HP, &maxHP);
    }
}

// Updates Raid Storm state and returns whether battle should end.
bool32 ShouldRaidKickPlayer(void)
{
    // Gen 8-style raids are capped at 10 turns.
    if (gRaidTypes[gRaidData.raidType].rules == RAID_RULES_MAX
        || gRaidTypes[gRaidData.raidType].rules == RAID_RULES_MEGA)
    {
        switch (gBattleResults.battleTurnCounter)
        {
            case RAID_STORM_TURNS_LEVEL_1:
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GETTING_STRONGER;
                BattleScriptExecute(BattleScript_MaxRaidStormBrews);
                break;
            case RAID_STORM_TURNS_LEVEL_2:
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GETTING_STRONGER;
                BattleScriptExecute(BattleScript_MaxRaidStormBrews);
                break;
            case RAID_STORM_TURNS_LEVEL_3:
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GETTING_EVEN_STRONGER;
                BattleScriptExecute(BattleScript_MaxRaidStormBrews);
                break;
            case RAID_STORM_TURNS_MAX:
                gBattleCommunication[MULTIUSE_STATE] = RAID_RULES_MAX;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GETTING_TOO_STRONG;
                BattleScriptExecute(BattleScript_RaidDefeat);
                return TRUE;
        }
    }
    // Gen 9-style raids are capped at 7.5 minutes.
    else if (gBattleStruct->battleTimer >= RAID_STORM_TIMER_MAX)
    {
        gBattleCommunication[MULTIUSE_STATE] = RAID_RULES_TERA;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_PKMN_RELEASED_ENERGY;
        BattleScriptExecute(BattleScript_RaidDefeat);
        return TRUE;
    }
    else if (gBattleStruct->battleTimer >= RAID_STORM_TIMER_WARNING)
    {
        BattleScriptExecute(BattleScript_TeraRaidTimerLow);
    }
    return FALSE;
}

bool32 ShouldMoveDynamaxEnergy(void)
{
    if (gRaidTypes[gRaidData.raidType].rules == RAID_RULES_MAX)
    {
        gBattleStruct->raid.energy ^= BIT_FLANK;
        gBattlerAttacker = gBattleStruct->raid.energy;

        if (CanDynamax(gBattlerAttacker))
            return TRUE;
    }

    return FALSE;
}

bool8 DoesRaidPreventMove(u16 move)
{
    switch(move) // data from Bulbapedia
    {
        case MOVE_BUG_BITE:
        case MOVE_COVET:
        case MOVE_INCINERATE:
        case MOVE_KNOCK_OFF:
        case MOVE_PERISH_SONG:
        case MOVE_PLUCK:
        case MOVE_SELF_DESTRUCT:
        case MOVE_SUPER_FANG:
        case MOVE_THIEF:
        case MOVE_TRICK:
            return TRUE;
    }
    return FALSE;
}

u8 GetRaidRepeatedAttackChance(void)
{
	u8 numStars = gRaidData.rank;
    switch (numStars)
    {
		case NO_RAID ... RAID_RANK_3:
			return 0; //Never
		case RAID_RANK_4:
			return 30; //30 % of the time after KO or Status Move
		case RAID_RANK_5:
			return 50; //50 % of the time after KO or Status Move
		default:
			return 70; //70 % of the time after KO or Status Move
	}
}

u8 GetRaidShockwaveChance(void) // to be adjusted
{
    u8 numStars = gRaidData.rank;

	if (gDisableStructs[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].isFirstTurn)
		return 0; //Don't use first attack with this

    switch (numStars)
    {
		case NO_RAID ... RAID_RANK_2:
			return 0; //Never
		case RAID_RANK_3:
        case RAID_RANK_4:
			return 15; //~20 % chance before each attack
		case RAID_RANK_5:
			return 25; //~35 % chance before each attack: less probable to do 2 attacks 
		default:
			return 25; //~50 % chance before each turn: probably do 2 attacks during the turn
	}
}

u8 GetRaidBossKOStatIncrease(u8 battlerId)
{
    u8 level = gBattleMons[battlerId].level;

    switch (level)
    {
        case 0 ... 19:
            return 0;
        case 20 ... 40:
            return 1;
        case 41 ... 70:
            return 2;
        default: // > 70
            return 3;
    }
}

// Returns the number of shields to produce, or the amount of HP to protect.
static u16 GetShieldAmount(void)
{
    u16 species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
    u8 hp = gSpeciesInfo[species].baseHP;
    u8 def = gSpeciesInfo[species].baseDefense;
    u8 spDef = gSpeciesInfo[species].baseSpDefense;
    u8 retVal;

    if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
    {
        switch (gRaidData.rank)
        {
            case NO_RAID ... RAID_RANK_1:
                retVal = 0;
                break;
            case RAID_RANK_2 ... RAID_RANK_3:
                retVal = 1;
                break;
            case RAID_RANK_4 ... RAID_RANK_5:
                retVal = 2;
                break;
            default: // 6 & 7 stars
                retVal = 3;
                break;
        }
    }
    else
    {
        // Uses the sum of defenses to determine barrier count.
        switch (hp + def + spDef)
        {
            case 0 ... 199:
                retVal = 3;
                break;
            case 200 ... 300:
                retVal = 4;
                break;
            default: // > 300
                retVal = MAX_BARRIER_COUNT;
                break;
        }

        if (gRaidData.rank < RAID_RANK_5)
            retVal -= 1;
    }

    return retVal;
    // only valid for dynamax raids atm
}

static u8 GetRaidShieldThresholdTotalNumber(void)
{
    if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
        return 0;

    switch (gRaidData.rank)
    {
        case RAID_RANK_7:
            return 3;
        case RAID_RANK_5 ... RAID_RANK_6:
            return 2;
        case RAID_RANK_3 ... RAID_RANK_4:
            return 1;
        default:
            return 0;
    }
}

// returns the next shield threshold in health percents
static u16 GetNextShieldThreshold(void)
{
    u8 total = GetRaidShieldThresholdTotalNumber();
    u8 remaining = gBattleStruct->raid.shieldsRemaining;

    if (remaining == 0 || total == 0)
        return 0;
    else
        return (remaining * 100) / (total + 1);
}

// Updates the state of the Raid shield (set up, clearing, or breaking individual barriers).
bool32 UpdateRaidShield(void)
{
    if (gBattleStruct->raid.state & RAID_CREATE_SHIELD)
    {
        gBattleStruct->raid.state &= ~RAID_CREATE_SHIELD;
        gBattlerTarget = B_POSITION_OPPONENT_LEFT;
        gBattleStruct->raid.shieldsRemaining--;

        // Set up shield data.
        gBattleStruct->raid.shield = GetShieldAmount();
        gBattleStruct->raid.nextShield = GetNextShieldThreshold();
        if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MAX
            || gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
            CreateAllRaidBarrierSprites();

        // Play animation and message.
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_RaidShieldAppeared;
        return TRUE;
    }
    else if (gBattleStruct->raid.state & RAID_BREAK_SHIELD && gBattleMoveDamage > 0)
    {
        gBattleStruct->raid.state &= ~RAID_BREAK_SHIELD;
        // Destroy an extra barrier with a Max Move.
        // TODO: Tera STAB moves will probably break 2 barriers, too.
        if (IsZMove(gLastUsedMove) && gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MAX && gBattleStruct->raid.shield > 2)
        {
            gBattleStruct->raid.shield--;
            DestroyRaidBarrierSprite(gBattleStruct->raid.shield);
        }
        if ((IsMaxMove(gLastUsedMove) || IsZMove(gLastUsedMove)) && gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MAX && gBattleStruct->raid.shield > 1)
        {
            gBattleStruct->raid.shield--;
            DestroyRaidBarrierSprite(gBattleStruct->raid.shield);
        }
        if (gBattleStruct->raid.shield > 0)
        {
            gBattleStruct->raid.shield--;
            DestroyRaidBarrierSprite(gBattleStruct->raid.shield);
        }

        if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
        {
            u32 i;
            gBattleMoveDamage = gBattleMons[gBattlerTarget].hp - gBattleMons[gBattlerTarget].maxHP;
            gBattleMons[gBattlerTarget].hp = gBattleMons[gBattlerTarget].maxHP;

            if (gRaidData.rank > RAID_RANK_5)
            {
                for (i = STAT_ATK; i < NUM_STATS; i++)
                {
                    if (gBattleMons[gBattlerTarget].statStages[i] < MAX_STAT_STAGE)
                        ++gBattleMons[gBattlerTarget].statStages[i];
                }
            }
            else if (gRaidData.rank > RAID_RANK_3)
            {
                if (gBattleMons[gBattlerTarget].statStages[STAT_DEF] < MAX_STAT_STAGE)
                    ++gBattleMons[gBattlerTarget].statStages[STAT_DEF];
                if (gBattleMons[gBattlerTarget].statStages[STAT_SPDEF] < MAX_STAT_STAGE)
                    ++gBattleMons[gBattlerTarget].statStages[STAT_SPDEF];
            }
            gBattleCommunication[MULTIUSE_STATE] = RAID_SHIELD_MEGA;
        }

        BattleScriptPushCursor();
        if (gBattleStruct->raid.shield == 0)
            gBattlescriptCurrInstr = BattleScript_RaidShieldDisappeared;
        else
            gBattlescriptCurrInstr = BattleScript_RaidBarrierBroken;
        return TRUE;
    }
    else if (gBattleStruct->raid.state & RAID_RESHOW_SHIELD)
    {
        gBattleStruct->raid.state &= ~RAID_RESHOW_SHIELD;
        if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MAX
            || gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
            CreateAllRaidBarrierSprites();
        return TRUE;
    }
    else if (gBattleStruct->raid.state & RAID_HIDE_SHIELD && gBattleStruct->raid.shield > 0)
    {
        u32 i;
        gBattleStruct->raid.state &= ~RAID_HIDE_SHIELD;
        for (i = 0; i < gBattleStruct->raid.shield; i++)
            DestroyRaidBarrierSprite(i);
        return TRUE;
    }
    return FALSE;
}

// Returns the amount of damage required to make a Raid Boss produce a shield.
u16 GetShieldDamageRequired(u16 hp, u16 maxHP)
{
    u16 threshold = (gBattleStruct->raid.nextShield * maxHP) / 100;
    if (gBattleStruct->raid.nextShield != 0 && hp > threshold)
        return hp - threshold;
    else
        return 0xFFFF; // don't make a shield
}

// Returns the damage reduction applied by a Raid Boss's shield.
u16 GetShieldDamageReduction(void)
{
    // Gen 8-style shields reduce damage by a constant 95%.
    if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MAX
        || gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
    {
        return UQ_4_12(1-0.95);
    }
    else if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_TERA)
    {
        if (IsTerastallized(gBattlerAttacker))
        {
            if (GetBattlerType(gBattlerAttacker, 0, FALSE) == gMovesInfo[gCurrentMove].type)
                return UQ_4_12(0.75); // tera & stab
            else
                return UQ_4_12(0.35); // tera but no stab
        }
        else
        {
            return UQ_4_12(0.2); // not tera
        }
    }
    return UQ_4_12(1);
}

// SHIELD SPRITE DATA:
static const u16 sMaxRaidBarrierGfx[] = INCBIN_U16("graphics/battle_interface/raid_barrier.4bpp");
static const u16 sMaxRaidBarrierPal[] = INCBIN_U16("graphics/battle_interface/misc_indicator.gbapal");
static const u16 sMegaRaidBarrierGfx[] = INCBIN_U16("graphics/battle_interface/mega_shield.4bpp");
static const u16 sMegaRaidBarrierPal[] = INCBIN_U16("graphics/battle_interface/mega_trigger.gbapal");
static const u16 sOmegaRaidBarrierGfx[] = INCBIN_U16("graphics/battle_interface/omega_shield.4bpp");
static const u16 sAlphaRaidBarrierGfx[] = INCBIN_U16("graphics/battle_interface/alpha_shield.4bpp");

static const struct SpriteSheet sSpriteSheet_MaxRaidBarrier =
{
    sMaxRaidBarrierGfx, sizeof(sMaxRaidBarrierGfx), TAG_RAID_BARRIER_TILE
};

static const struct SpriteSheet sSpriteSheet_MegaRaidBarrier =
{
    sMegaRaidBarrierGfx, sizeof(sMegaRaidBarrierGfx), TAG_RAID_BARRIER_TILE
};

static const struct SpriteSheet sSpriteSheet_OmegaRaidBarrier =
{
    sOmegaRaidBarrierGfx, sizeof(sOmegaRaidBarrierGfx), TAG_RAID_BARRIER_TILE
};

static const struct SpriteSheet sSpriteSheet_AlphaRaidBarrier =
{
    sAlphaRaidBarrierGfx, sizeof(sAlphaRaidBarrierGfx), TAG_RAID_BARRIER_TILE
};

// Max Raid Barriers share a palette with the Alpha, Omega, and Dynamax indicators.
static const struct SpritePalette sSpritePalette_MaxRaidBarrier =
{
    sMaxRaidBarrierPal, TAG_MISC_INDICATOR_PAL
};

// Mega Raid Shields share a palette with the Mega trigger.
static const struct SpritePalette sSpritePalette_MegaRaidBarrier =
{
    sMegaRaidBarrierPal, TAG_MEGA_TRIGGER_PAL
};

static const struct OamData sOamData_MaxRaidBarrier =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sOamData_MegaRaidBarrier =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(32x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const s8 sMaxBarrierPosition[2] = {43, 9};
static const s8 sMegaBarrierPosition[2] = {37, 9};

// Sync up barrier sprites with healthbox.
static void SpriteCb_RaidBarrier(struct Sprite *sprite)
{
    u8 healthboxSpriteId = gBattleSpritesDataPtr->battleBars[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].healthboxSpriteId;
    sprite->y2 = gSprites[healthboxSpriteId].y2;
}

static const struct SpriteTemplate sSpriteTemplate_MaxRaidBarrier =
{
    .tileTag = TAG_RAID_BARRIER_TILE,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_MaxRaidBarrier,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_RaidBarrier,
};

static const struct SpriteTemplate sSpriteTemplate_MegaRaidBarrier =
{
    .tileTag = TAG_RAID_BARRIER_TILE,
    .paletteTag = TAG_MEGA_TRIGGER_PAL,
    .oam = &sOamData_MegaRaidBarrier,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_RaidBarrier,
};

static const struct SpriteTemplate sSpriteTemplate_PrimalRaidBarrier =
{
    .tileTag = TAG_RAID_BARRIER_TILE,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_MegaRaidBarrier,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCb_RaidBarrier,
};

#define tBattler    data[0]
#define tHide       data[1]
#define hOther_IndicatorSpriteId data[6]

static u32 CreateRaidBarrierSprite(u8 index)
{
    u32 spriteId, position;
    s16 x, y;
    u16 species = gBattleMons[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].species;

    GetBattlerHealthboxCoords(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), &x, &y);

    if (gRaidTypes[gRaidData.raidType].shield == RAID_SHIELD_MEGA)
    {
        x += sMegaBarrierPosition[0] - (index * 25);
        y += sMegaBarrierPosition[1];

        if (species == SPECIES_GROUDON || species == SPECIES_GROUDON_PRIMAL || species == SPECIES_KYOGRE || species == SPECIES_KYOGRE_PRIMAL)
        {
            LoadSpritePalette(&sSpritePalette_MaxRaidBarrier);
   	        LoadSpriteSheet((species  == SPECIES_GROUDON || species  == SPECIES_GROUDON_PRIMAL) ? &sSpriteSheet_OmegaRaidBarrier : &sSpriteSheet_AlphaRaidBarrier);
            spriteId = CreateSprite(&sSpriteTemplate_PrimalRaidBarrier, x, y, 0);
        }
        else
        {
            LoadSpritePalette(&sSpritePalette_MegaRaidBarrier);
       	    LoadSpriteSheet(&sSpriteSheet_MegaRaidBarrier);
            spriteId = CreateSprite(&sSpriteTemplate_MegaRaidBarrier, x, y, 0);
        }
    }
    else // MAX RAIDS & TERA RAIDS
    {
        x += sMaxBarrierPosition[0] - (index * 10);
        y += sMaxBarrierPosition[1];

   	    LoadSpritePalette(&sSpritePalette_MaxRaidBarrier);
   	    LoadSpriteSheet(&sSpriteSheet_MaxRaidBarrier);
        spriteId = CreateSprite(&sSpriteTemplate_MaxRaidBarrier, x, y, 0);
    }

    gSprites[spriteId].tBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    return spriteId;
}

// Draws all Raid barriers onto the Raid Boss's healthbox.
static void CreateAllRaidBarrierSprites(void)
{
    u8 i;
    for (i = 0; i < gBattleStruct->raid.shield; i++)
    {
        if (gBattleStruct->raid.barrierSpriteIds[i] == MAX_SPRITES)
            gBattleStruct->raid.barrierSpriteIds[i] = CreateRaidBarrierSprite(i);
    }
}

// Destroys one Raid barrier sprite.
static void DestroyRaidBarrierSprite(u8 index)
{
    if (gBattleStruct->raid.barrierSpriteIds[index] != MAX_SPRITES)
    {
        DestroySprite(&gSprites[gBattleStruct->raid.barrierSpriteIds[index]]);
        gBattleStruct->raid.barrierSpriteIds[index] = MAX_SPRITES;
    }

    if (index == 0)
    {
        // Don't free palette because it is shared.
        // FreeSpritePaletteByTag(TAG_MISC_INDICATOR_PAL);
        FreeSpriteTilesByTag(TAG_RAID_BARRIER_TILE);
    }
}

#define hMain_Battler data[6]

void RaidBarrier_SetVisibilities(u32 healthboxId, bool32 invisible)
{
    u32 i;
    for (i = 0; i < gBattleStruct->raid.shield; i++)
    {
        gSprites[gBattleStruct->raid.barrierSpriteIds[i]].invisible = invisible;
    }
}

#undef hMain_Battler

static u8 GetRaidMapSectionId(void)
{
    u8 currRegionMapSecId = GetCurrentRegionMapSectionId();
    return currRegionMapSecId - MAPSEC_ROUTE_101;
}

// battle raid flags
void SetRaidBattleFlag(void)
{
    u8 raidId = GetRaidMapSectionId();
    u8 index = raidId / 8; //get byte in array
    u8 bit = raidId % 8;   //get bit in byte
    u8 mask = 1 << bit;

    gSaveBlock1Ptr->raidAreaFlags[index] |= mask;
    return;
}

bool8 GetRaidBattleFlag(void)
{
    u8 raidId = GetRaidMapSectionId();
    u8 index = raidId / 8; //get byte in array
    u8 bit = raidId % 8;   //get bit in byte
    u8 mask = 1 << bit;

    return ((gSaveBlock1Ptr->raidAreaFlags[index] & mask) != 0);
}

void ClearRaidBattleFlag(void)
{
    u8 raidId = GetRaidMapSectionId();
    u8 index = raidId / 8; //get byte in array
    u8 bit = raidId % 8;   //get bit in byte
    u8 mask = 1 << bit;

    gSaveBlock1Ptr->raidAreaFlags[index] &= ~mask;
    return;
}

void ClearAllRaidBattleFlags(void)
{
    memset(&gSaveBlock1Ptr->raidAreaFlags, 0, sizeof(gSaveBlock1Ptr->raidAreaFlags));
}

u16 GetRaidRewardAmount(u16 item)
{
    if (item == ITEM_MASTER_BALL)
        return 1;
    else if (GetPocketByItemId(item) == POCKET_POKE_BALLS)
		return Random() % 11 + 5; //5 - 15

	if (GetPocketByItemId(item) == POCKET_BERRIES)
		return Random() % 11 + 5; //5 - 15

    if (item >= ITEM_RARE_CANDY && item <= ITEM_EXP_CANDY_XL)
        return Random() % 9 + gRaidData.rank;

    if (item >= ITEM_HELIX_FOSSIL && item <= ITEM_FOSSILIZED_DINO)
        return 1;

    if (item >= ITEM_BOTTLE_CAP && item <= ITEM_STRANGE_SOUVENIR)
        return Random() % 3 + gRaidData.rank;

    if (item >= ITEM_LONELY_MINT && item <= ITEM_SERIOUS_MINT)
        return 1;

    if (item >= ITEM_HEALTH_FEATHER && item <= ITEM_SWIFT_FEATHER)
        return Random() % 21 + 5;

    if (item >= ITEM_HP_UP && item <= ITEM_PP_MAX)
        return Random() % 3 + 1;

    if (item >= ITEM_FIRE_STONE && item <= ITEM_RIBBON_SWEET)
        return 1;

    if (item >= ITEM_SILK_SCARF && item <= ITEM_METAL_COAT)
        return 1;

    if (item >= ITEM_BUG_TERA_SHARD && item <= ITEM_WATER_TERA_SHARD)
        return Random() % 21 + 5;

	// default
	return 1;

}

static u8 TryAlterRaidItemDropRate(u16 item, u8 rate)
{
    u32 i;

	if (FlagGet(FLAG_TEMP_C)) // set if using wishing piece, bumps up the rates to next 10%
    {
        rate = (rate / 10 + 1) * 10;
    }
    
    if (item == ITEM_WISHING_PIECE)
	{
		for (i = 0; i < PARTY_SIZE; i++)
		{
			if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) == SPECIES_JIRACHI)
			{
				if (rate < 20)
					rate = 20; //Bump up to 20%
				break;
			}
		}
	}

    rate += gRaidData.rank;

	return rate;
}

static u16 TryAlterRaidDropItem(u16 item)
{
    if (item == ITEM_NONE) // don't change anything if no item
        return ITEM_NONE;

    if (item == FIRST_BERRY_INDEX) // random berry
        return Random() % (LAST_BERRY_INDEX - FIRST_BERRY_INDEX) + FIRST_BERRY_INDEX;

    if (item == ITEM_MASTER_BALL && gRaidData.rank < RAID_RANK_6) // random ball is master ball for low rank raids
        return Random() % (LAST_BALL - FIRST_BALL + 1) + FIRST_BALL;

    if (item == ITEM_LONELY_MINT) // random mint
        return Random() % (ITEM_SERIOUS_MINT - ITEM_LONELY_MINT + 1) + ITEM_LONELY_MINT;

    if (item == ITEM_HELIX_FOSSIL) // random fossil
        return Random() % (ITEM_FOSSILIZED_DINO - ITEM_HELIX_FOSSIL + 1) + ITEM_HELIX_FOSSIL;
    
    if (item == ITEM_BUG_TERA_SHARD) // random tera shard
        return Random() % (ITEM_WATER_TERA_SHARD - ITEM_BUG_TERA_SHARD + 1) + ITEM_BUG_TERA_SHARD;

    if (item == ITEM_HEALTH_FEATHER) // EV feather
        return Random() % (ITEM_SWIFT_FEATHER - ITEM_HEALTH_FEATHER + 1) + ITEM_HEALTH_FEATHER;
    
    if (item == ITEM_HP_UP) // random energy drink
        return Random() % (ITEM_PP_MAX - ITEM_HP_UP + 1) + ITEM_HP_UP;
    
    if (item == ITEM_FIRE_STONE) // random evolution item
        return Random() % (ITEM_RIBBON_SWEET - ITEM_FIRE_STONE + 1) + ITEM_FIRE_STONE;
    
    if (item == ITEM_SILK_SCARF) // random held item
        return Random() % (ITEM_METAL_COAT - ITEM_SILK_SCARF + 1) + ITEM_SILK_SCARF;

    if (item == ITEM_STRANGE_SOUVENIR) // random treasure
        return Random() % (ITEM_STRANGE_SOUVENIR - ITEM_BOTTLE_CAP + 1) + ITEM_BOTTLE_CAP;
    
    return item;
}

void GiveRaidBattleRewards(void)
{
    u32 i;
	u8 numStars = gRaidData.rank;
	gSpecialVar_0x800B = FALSE; //Not done giving rewards

	for (i = VarGet(VAR_TEMP_A); i < MAX_RAID_DROPS; i++)
    {
        u16 dropItem = sRaidBattleDropItems[numStars][i]; // consider raid rank
        u8 dropRate = sRaidBattleDropRates[i];
        VarSet(VAR_TEMP_A, i+1);

        dropRate = TryAlterRaidItemDropRate(dropItem, dropRate);
        dropItem = TryAlterRaidDropItem(dropItem);

		if (dropItem != ITEM_NONE
			&& (GetRaidRandomNumber() % 100 < dropRate))
	    {
			gSpecialVar_LastTalked = 0xFD; //So no event objects disappear
			gSpecialVar_0x8000 = dropItem;//raid->data[i].drops[(*(GetVarPointer(VAR_TEMP_B)))++];//dropItem;
			gSpecialVar_0x8001 = GetRaidRewardAmount(gSpecialVar_0x8000);
			return;
		}
	}
	gSpecialVar_0x800B = TRUE; //Done giving rewards
}

u32 GetRaidRandomNumber(void)
{
	//Make sure no values are 0
	u8 day = (gLocalTime.days == 0) ? 32 :gLocalTime.days;
    u8 hour = (gLocalTime.hours == 0) ? 24 : gLocalTime.hours;
	u8 lastMapGroup = (gSaveBlock1Ptr->dynamicWarp.mapGroup == 0) ? 0xFF : gSaveBlock1Ptr->dynamicWarp.mapGroup;
	u8 lastMapNum = (gSaveBlock1Ptr->dynamicWarp.mapNum == 0) ? 0xFF : gSaveBlock1Ptr->dynamicWarp.mapNum;
	u8 lastWarpId = (gSaveBlock1Ptr->dynamicWarp.warpId == 0) ? 0xFF : gSaveBlock1Ptr->dynamicWarp.warpId;
	u16 lastPos = (gSaveBlock1Ptr->dynamicWarp.x + gSaveBlock1Ptr->dynamicWarp.y == 0) ? 0xFFFF : (u16) (gSaveBlock1Ptr->dynamicWarp.x + gSaveBlock1Ptr->dynamicWarp.y);
	
    #ifdef VAR_RAID_NUMBER_OFFSET
	u16 offset = VarGet(VAR_RAID_NUMBER_OFFSET); //Setting this var changes all the raid spawns for the current hour (helps with better Wishing Piece)
	#else
	u16 offset = GetRaidMapSectionId();
    if (FlagGet(FLAG_TEMP_C))
        offset <<= 8;
	#endif

	//return ((hour * (day + month) * lastMapGroup * (lastMapNum + lastWarpId + lastPos)) + ((hour * (day + month)) ^ dayOfWeek) + offset) ^ T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    //return ((hour * day * lastMapGroup * (lastMapNum + lastWarpId + lastPos)) + ((hour * day) ^ 8) + offset) ^ T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    return RandomSeeded(hour * day * lastMapGroup * (lastMapNum + lastWarpId + lastPos) + offset, TRUE);
}

u8 GetRaidRecommendedLevel(void)
{
	u8 numStars = gRaidData.rank;
    u8 recommendedLevel = gRaidBattleLevelRanges[numStars][1] + 5; //Max level + 5

    if (recommendedLevel > MAX_LEVEL)
        recommendedLevel = MAX_LEVEL;

	return recommendedLevel; 
}

u8 GetRaidEggMoveChance(void)
{
    return gRaidBattleEggMoveChances[gRaidData.rank];
}

void DetermineRaidPartners(u8* partnerTrainerIndex, u8 maxPartners)
{
    u32 j, n, index, randomNum = GetRaidRandomNumber();

    for (j = 0; j < maxPartners; j++)
        partnerTrainerIndex[j] = j;

    //Shuffle8(partnerTrainerIndex, maxPartners);

    n = maxPartners-1;
    while (n>1) // Shuffle8, but use GetRaidRandomNumber() for randomness reproductibility
    {
        j = (randomNum * (n+1)) >>16;
        SWAP(partnerTrainerIndex[n], partnerTrainerIndex[j], index);
        n--;
    }
}

u16 OverrideRaidPartnerTrainerId(u16 trainerId)
{
    if (trainerId == TRAINER_WALLY_OVERRIDE)
    {
        trainerId = PARTNER_WALLY_PETALBURG;
        if (HasTrainerBeenFought(TRAINER_WALLY_MAUVILLE))
            trainerId = PARTNER_WALLY_MAUVILLE;
        if (HasTrainerBeenFought(TRAINER_WALLY_VR_1))
            trainerId = PARTNER_WALLY_VICTORY_ROAD;
    }
    else if (trainerId == TRAINER_RED_OVERRIDE)
    {
        trainerId = PARTNER_RED_PETALBURG_WOODS;
        if (HasTrainerBeenFought(TRAINER_RED_FALLARBOR))
            trainerId = PARTNER_RED_FALLARBOR;
        if (HasTrainerBeenFought(TRAINER_RED_ROUTE121))
            trainerId = PARTNER_RED_ROUTE121;
        if (HasTrainerBeenFought(TRAINER_RED_VICTORY_ROAD))
            trainerId = PARTNER_RED_VICTORY_ROAD;
    }
    else if (trainerId == TRAINER_RIVAL_OVERRIDE)
    {
        if (VarGet(VAR_STARTER_MON) == 0) // chose treecko
        {
            trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_RUSTBORO_TREECKO : PARTNER_BRENDAN_RUSTBORO_TREECKO;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_110_TREECKO) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_110_TREECKO))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_110_TREECKO : PARTNER_BRENDAN_ROUTE_110_TREECKO;
            if (HasTrainerBeenFought(TRAINER_COURTNEY_METEOR_FALLS))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_TREECKO_METEOR_FALLS : PARTNER_BRENDAN_TREECKO_METEOR_FALLS;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_119_TREECKO) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_119_TREECKO))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_119_TREECKO : PARTNER_BRENDAN_ROUTE_119_TREECKO;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_LILYCOVE_TREECKO) || HasTrainerBeenFought(TRAINER_MAY_LILYCOVE_TREECKO))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_LILYCOVE_TREECKO : PARTNER_BRENDAN_LILYCOVE_TREECKO;
            if (HasTrainerBeenFought(TRAINER_RED_VICTORY_ROAD))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_VICTORY_ROAD_TREECKO : PARTNER_BRENDAN_VICTORY_ROAD_TREECKO;
        }
        else if (VarGet(VAR_STARTER_MON) == 1) // chose torchic
        {
            trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_RUSTBORO_TORCHIC : PARTNER_BRENDAN_RUSTBORO_TORCHIC;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_110_TORCHIC) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_110_TORCHIC))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_110_TORCHIC : PARTNER_BRENDAN_ROUTE_110_TORCHIC;
            if (HasTrainerBeenFought(TRAINER_COURTNEY_METEOR_FALLS))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_TORCHIC_METEOR_FALLS : PARTNER_BRENDAN_TORCHIC_METEOR_FALLS;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_119_TORCHIC) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_119_TORCHIC))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_119_TORCHIC : PARTNER_BRENDAN_ROUTE_119_TORCHIC;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_LILYCOVE_TORCHIC) || HasTrainerBeenFought(TRAINER_MAY_LILYCOVE_TORCHIC))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_LILYCOVE_TORCHIC : PARTNER_BRENDAN_LILYCOVE_TORCHIC;
            if (HasTrainerBeenFought(TRAINER_RED_VICTORY_ROAD))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_VICTORY_ROAD_TORCHIC : PARTNER_BRENDAN_VICTORY_ROAD_TORCHIC;
        }
        else // chose mudkip
        {
            trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_RUSTBORO_MUDKIP : PARTNER_BRENDAN_RUSTBORO_MUDKIP; // must have won against rival in rustboro to do raid battles
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_110_MUDKIP) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_110_MUDKIP))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_110_MUDKIP : PARTNER_BRENDAN_ROUTE_110_MUDKIP;
            if (HasTrainerBeenFought(TRAINER_COURTNEY_METEOR_FALLS))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_MUDKIP_METEOR_FALLS : PARTNER_BRENDAN_MUDKIP_METEOR_FALLS;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_ROUTE_119_MUDKIP) || HasTrainerBeenFought(TRAINER_MAY_ROUTE_119_MUDKIP))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_ROUTE_119_MUDKIP : PARTNER_BRENDAN_ROUTE_119_MUDKIP;
            if (HasTrainerBeenFought(TRAINER_BRENDAN_LILYCOVE_MUDKIP) || HasTrainerBeenFought(TRAINER_MAY_LILYCOVE_MUDKIP))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_LILYCOVE_MUDKIP : PARTNER_BRENDAN_LILYCOVE_MUDKIP;
            if (HasTrainerBeenFought(TRAINER_RED_VICTORY_ROAD))
                trainerId = (gSaveBlock2Ptr->playerGender == MALE) ? PARTNER_MAY_VICTORY_ROAD_MUDKIP : PARTNER_BRENDAN_VICTORY_ROAD_MUDKIP;
        }
    }

    return trainerId;
}

#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_interface.h"
#include "battle_raid.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "data.h"
#include "event_data.h"
#include "item.h"
#include "malloc.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"
#include "sprite.h"
#include "constants/battle_raid.h"
#include "constants/battle_string_ids.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/moves.h"

// TODO:
//  - Switch-in abilities reapplying after Max Mindstorm?
//  - Battle partner fainting and switching breaking after Max Flare?
//  - Raid barrier sprite alignment.
//  - Raid rank disappears in Intro UI after a Raid has occurred.

// Settings for each Raid Type.
const struct RaidType gRaidTypes[NUM_RAID_TYPES] = {
    [RAID_TYPE_MAX] = {
        .shield = RAID_GEN_8,
        .shockwave = RAID_GEN_8,
        .rules = RAID_GEN_8,
        .gimmick = GIMMICK_DYNAMAX,
    },
    [RAID_TYPE_TERA] = {
        .shield = RAID_GEN_9,
        .shockwave = RAID_GEN_9,
        .rules = RAID_GEN_9,
        .gimmick = GIMMICK_TERA,
    },
    [RAID_TYPE_MEGA] = {
        .shield = RAID_GEN_8,
        .shockwave = RAID_GEN_8,
        .rules = RAID_GEN_8,
        .gimmick = GIMMICK_MEGA,
    },
};

// Rank-based HP Multipliers
static const u16 sGen8RaidHPMultipliers[] = {
    [RAID_RANK_1] = UQ_4_12(1.4),
    [RAID_RANK_2] = UQ_4_12(1.6),
    [RAID_RANK_3] = UQ_4_12(1.9),
    [RAID_RANK_4] = UQ_4_12(2.5),
    [RAID_RANK_5] = UQ_4_12(3.0),
    [RAID_RANK_6] = UQ_4_12(3.0),
    [RAID_RANK_7] = UQ_4_12(3.0),
};

static const u16 sGen9RaidHPMultipliers[] = {
    [RAID_RANK_1] = UQ_4_12(5.0),
    [RAID_RANK_2] = UQ_4_12(5.0),
    [RAID_RANK_3] = UQ_4_12(8.0),
    [RAID_RANK_4] = UQ_4_12(12.0),
    [RAID_RANK_5] = UQ_4_12(13.0), //UQ_4_12(20.0),
    [RAID_RANK_6] = UQ_4_12(14.0), //UQ_4_12(25.0),
    [RAID_RANK_7] = UQ_4_12(15.0), //UQ_4_12(30.0),
};

const u8 gRaidBattleStarsByBadges[][2] =
{
//	[0] = {NO_RAID,         NO_RAID},
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
	[RAID_RANK_1]   = {15, 20},
	[RAID_RANK_2]   = {25, 30},
	[RAID_RANK_3] = {35, 40},
	[RAID_RANK_4]  = {50, 55},
	[RAID_RANK_5]  = {60, 65},
	[RAID_RANK_6]   = {75, 90},
    [RAID_RANK_7] = {90, 100},
};

//The chance that each move is replaced with an Egg Move
const u8 gRaidBattleEggMoveChances[MAX_RAID_RANK + 1] =
{
	[RAID_RANK_1] = 0,
	[RAID_RANK_2] = 10,
	[RAID_RANK_3] = 30,
	[RAID_RANK_4] = 50,
	[RAID_RANK_5] = 70,
	[RAID_RANK_6] = 80,
    [RAID_RANK_7] = 90,
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

static const u8 sRaidBattleDropItems[MAX_RAID_DROPS] =
{
	ITEM_MASTER_BALL,
    ITEM_NUGGET,
	ITEM_BOTTLE_CAP,
	ITEM_PEARL,
	ITEM_BIG_PEARL,
	ITEM_WISHING_PIECE,
	ITEM_STARDUST,
	ITEM_COMET_SHARD,
	ITEM_THUNDER_STONE,
	ITEM_WATER_STONE,
	ITEM_LEAF_STONE,
	ITEM_NONE,
};

extern const struct Evolution gEvolutionTable[][EVOS_PER_MON];

EWRAM_DATA struct RaidData gRaidData = {0};

// forward declarations
static u8 GetRaidShieldThresholdTotalNumber(void);
static u16 GetNextShieldThreshold(void);
static u32 CreateRaidBarrierSprite(u8 index);
static void CreateAllRaidBarrierSprites(void);
static void DestroyRaidBarrierSprite(u8 index);
u32 GetRaidRandomNumber(void);

// Sets the data for the Raid being loaded from the map information.
bool32 InitRaidData(void)
{
    u16 numBadges, min, max, species, preEvoSpecies, postEvoSpecies = SPECIES_NONE;
	u32 i, randomNum = GetRaidRandomNumber();
    u8 raidBossLevel, numPostEvoSpecies = 0;;

    // determine raid type
    gRaidData.raidType = RAID_TYPE_MAX;

    // determine raid rank based on number of badges
    numBadges = 0;
    for (i = 0; i < 8; i++)
    {
        if (FlagGet(FLAG_BADGE01_GET + i))
            numBadges++;
    }

    min = gRaidBattleStarsByBadges[numBadges][0];
	max = gRaidBattleStarsByBadges[numBadges][1];

    if (min == max)
        gRaidData.rank = min;
    else
        gRaidData.rank = (randomNum % ((max + 1) - min)) + min;
    
    // determine raid boss level based on raid rank
    min = gRaidBattleLevelRanges[gRaidData.rank][0];
	max = gRaidBattleLevelRanges[gRaidData.rank][1];

    if (min == max)
        raidBossLevel = min;
    else
        raidBossLevel = (randomNum % ((max + 1) - min)) + min;

    // determine raid species
    species = randomNum % FORMS_START + 1;

    // should check here for legendaries & mythicals. Maybe choose a random form as well
    preEvoSpecies = GetPreEvolution(species);
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
    }
    
    // create raid boss
    CreateMon(&gEnemyParty[0], species, raidBossLevel, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);

    return TRUE;
}

// Sets the data for the Raid being loaded from set variables.
bool32 InitCustomRaidData(void)
{
    gRaidData.raidType = gSpecialVar_0x8001;
    gRaidData.rank = gSpecialVar_0x8002;
    CreateMon(&gEnemyParty[0], gSpecialVar_0x8003, gSpecialVar_0x8007, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);

    return TRUE;
}

// Sets up the RaidBattleData struct in gBattleStruct.
void InitRaidBattleData(void)
{
    u8 i;

    gBattleStruct->raid.shieldsRemaining = GetRaidShieldThresholdTotalNumber();
    gBattleStruct->raid.nextShield = GetNextShieldThreshold();
    gBattleStruct->raid.shield = 0;
    gBattleStruct->raid.state |= RAID_INTRO_COMPLETE;
	gBattleStruct->raid.energy = B_POSITION_PLAYER_LEFT;

    // Zeroes sprite IDs for Gen 8-style shield.
    for (i = 0; i < MAX_BARRIER_COUNT; i++)
        gBattleStruct->raid.barrierSpriteIds[i] = MAX_SPRITES;

    // TODO: Some Raids start off with a shield at the beginning.
    // if (should do shield)
    //    do shield.

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
    else
        return B_TRANSITION_MAX_RAID;
}

// Applies the HP multiplier for Raid Bosses.
void ApplyRaidHPMultiplier(u16 battlerId, struct Pokemon* mon)
{
    u16 mult;
    if (gRaidTypes[gRaidData.raidType].shield == RAID_GEN_8)
        mult = sGen8RaidHPMultipliers[gRaidData.rank];
    else
        mult = sGen9RaidHPMultipliers[gRaidData.rank];

    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_SHEDINJA) {
        u16 hp = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_HP) * mult) + UQ_4_12_ROUND);
        u16 maxHP = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_MAX_HP) * mult) + UQ_4_12_ROUND);
        SetMonData(mon, MON_DATA_HP, &hp);
        SetMonData(mon, MON_DATA_MAX_HP, &maxHP);
    }
}

// Updates Raid Storm state and returns whether battle should end.
bool32 ShouldRaidKickPlayer(void)
{
    // Gen 8-style raids are capped at 10 turns.
    if (gRaidTypes[gRaidData.raidType].rules == RAID_GEN_8)
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
                gBattleCommunication[MULTIUSE_STATE] = RAID_GEN_8;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_GETTING_TOO_STRONG;
                BattleScriptExecute(BattleScript_RaidDefeat);
                return TRUE;
        }
    }
    // Gen 9-style raids are capped at 7.5 minutes.
    else if (gBattleStruct->battleTimer >= RAID_STORM_TIMER_MAX)
    {
        gBattleCommunication[MULTIUSE_STATE] = RAID_GEN_9;
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
		case RAID_RANK_1 ... RAID_RANK_3:
			return 0; //Never
		case RAID_RANK_4:
			return 30; //30 % of the time after KO or Status Move
		case RAID_RANK_5:
			return 50; //50 % of the time after KO or Status Move
		default:
			return 70; //70 % of the time after KO or Status Move
	}
}

u8 GetRaidShockwaveChance(void)
{
    u8 numStars = gRaidData.rank;

	if (gDisableStructs[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].isFirstTurn)
		return 0; //Don't use first attack with this

    switch (numStars)
    {
		case RAID_RANK_1 ... RAID_RANK_3:
			return 0; //Never
		case RAID_RANK_4:
			return 20; //20 % chance before each attack
		case RAID_RANK_5:
			return 35; //35 % chance before each attack
		default:
			return 50; //50 % chance before each attack
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

    // Currently uses the sum of defenses to determine barrier count.
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
    return retVal;
    // only valid for dynamax raids atm
}

static u8 GetRaidShieldThresholdTotalNumber(void)
{
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
        if (gRaidTypes[gRaidData.raidType].shield == RAID_GEN_8)
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
        if (IsMaxMove(gLastUsedMove) && gBattleStruct->raid.shield > 1)
        {
            gBattleStruct->raid.shield--;
            DestroyRaidBarrierSprite(gBattleStruct->raid.shield);
        }
        if (gBattleStruct->raid.shield > 0)
        {
            gBattleStruct->raid.shield--;
            DestroyRaidBarrierSprite(gBattleStruct->raid.shield);
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
        if (gRaidTypes[gRaidData.raidType].shield == RAID_GEN_8)
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
    if (gRaidTypes[gRaidData.raidType].shield == RAID_GEN_8)
    {
        return UQ_4_12(1-0.95);
    }
}

// SHIELD SPRITE DATA:
static const u16 sRaidBarrierGfx[] = INCBIN_U16("graphics/battle_interface/raid_barrier.4bpp");
static const u16 sRaidBarrierPal[] = INCBIN_U16("graphics/battle_interface/misc_indicator.gbapal");

static const struct SpriteSheet sSpriteSheet_RaidBarrier =
{
    sRaidBarrierGfx, sizeof(sRaidBarrierGfx), TAG_RAID_BARRIER_TILE
};

// Raid Barriers share a palette with the Alpha, Omega, and Dynamax indicators.
static const struct SpritePalette sSpritePalette_RaidBarrier =
{
    sRaidBarrierPal, TAG_MISC_INDICATOR_PAL
};

static const struct OamData sOamData_RaidBarrier =
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

static const s8 sBarrierPosition[2] = {48, 10};

// Sync up barrier sprites with healthbox.
static void SpriteCb_RaidBarrier(struct Sprite *sprite)
{
    u8 healthboxSpriteId = gBattleSpritesDataPtr->battleBars[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].healthboxSpriteId;
    sprite->y2 = gSprites[healthboxSpriteId].y2;
}

static const struct SpriteTemplate sSpriteTemplate_RaidBarrier =
{
    .tileTag = TAG_RAID_BARRIER_TILE,
    .paletteTag = TAG_MISC_INDICATOR_PAL,
    .oam = &sOamData_RaidBarrier,
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

    GetBattlerHealthboxCoords(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), &x, &y);
    x += sBarrierPosition[0] - (index * 10);
    y += sBarrierPosition[1];

   	LoadSpritePalette(&sSpritePalette_RaidBarrier);
   	LoadSpriteSheet(&sSpriteSheet_RaidBarrier);
    spriteId = CreateSprite(&sSpriteTemplate_RaidBarrier, x, y, 0);

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
    u32 i;
    
    for (i = 0; i < NELEMS(gSaveBlock1Ptr->raidAreaFlags); i++)
        gSaveBlock1Ptr->raidAreaFlags[i] = 0;
}

u16 GetRaidRewardAmount(u16 item)
{
	if (GetPocketByItemId(item) == POCKET_POKE_BALLS)
		return Random() % 11 + 5; //5 - 15

	if (GetPocketByItemId(item) == POCKET_BERRIES)
		return Random() % 11 + 5; //5 - 15

	/*switch (gItemsByType[item]) {
	case ITEM_TYPE_HEALTH_RECOVERY:
	case ITEM_TYPE_STATUS_RECOVERY:
		return Random() % 5 + 1; //1 - 5
	case ITEM_TYPE_PP_RECOVERY:
	case ITEM_TYPE_STAT_BOOST_DRINK:
		return Random() % 3 + 1; //1 - 3
	case ITEM_TYPE_STAT_BOOST_WING:
		return Random() % 21 + 10; //10 - 30
	case ITEM_TYPE_SHARD:
		return Random() % 10 + 1; //1 - 10
	default:*/
		return 1;
	//}
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

	return rate;
}

void GiveRaidBattleRewards(void)
{
    u32 i;
	u8 numStars = gRaidData.rank;
	gSpecialVar_0x800B = FALSE; //Not done giving rewards

	for (i = VarGet(VAR_TEMP_A); i < MAX_RAID_DROPS; i++)
    {
        u16 dropItem = sRaidBattleDropItems[i]; // consider raid rank
        u8 dropRate = sRaidBattleDropRates[i];
        VarSet(VAR_TEMP_A, i+1);

        dropRate = TryAlterRaidItemDropRate(dropItem, dropRate);

		if (dropItem != ITEM_NONE
			&& (Random() % 100 < dropRate))
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
	u16 offset = 0;
	#endif

	//return ((hour * (day + month) * lastMapGroup * (lastMapNum + lastWarpId + lastPos)) + ((hour * (day + month)) ^ dayOfWeek) + offset) ^ T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    //return ((hour * day * lastMapGroup * (lastMapNum + lastWarpId + lastPos)) + ((hour * day) ^ 8) + offset) ^ T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    return RandomSeeded(hour * day * lastMapGroup * (lastMapNum + lastWarpId + lastPos) + offset, TRUE);
}

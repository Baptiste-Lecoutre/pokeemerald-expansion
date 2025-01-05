#ifndef GUARD_DEXNAV_H
#define GUARD_DEXNAV_H

#include "config/dexnav.h"

// GUI Info
#define ROW_WATER       0
#define ROW_LAND_TOP    1
#define ROW_LAND_BOT    2
#define ROW_HIDDEN      3
#define ROWS_COUNT      4

#define ROW_WATER_ICON_X        26
#define ROW_WATER_ICON_Y        45

#define ROW_LAND_ICON_X         20
#define ROW_LAND_TOP_ICON_Y     94//(ROW_WATER_ICON_Y + 28)
#define ROW_LAND_BOT_ICON_Y     (ROW_LAND_TOP_ICON_Y + 24)

#define ROW_HIDDEN_ICON_X       20
#define ROW_HIDDEN_ICON_Y       (ROW_LAND_BOT_ICON_Y + 28)

#define ENCOUNTER_TYPE_LAND     0
#define ENCOUNTER_TYPE_WATER    1
#define ENCOUNTER_TYPE_HIDDEN   2   // Get from species

#define COL_WATER_COUNT         5
#define COL_LAND_COUNT          6
#define COL_HIDDEN_COUNT        6

#define COL_WATER_MAX           (COL_WATER_COUNT - 1)
#define COL_LAND_MAX            (COL_LAND_COUNT - 1)
#define COL_HIDDEN_MAX          (COL_HIDDEN_COUNT - 1)

// SEARCH INFO
#define SCANSTART_X             4 //0
#define SCANSTART_Y             4 //0
#define SCANSIZE_NORMAL              4 //12 // normal
#define SCANSIZE_SMALL              3 //12 // small

#define SPECIES_INFO_Y          4
#define TYPE_ICONS_Y            (SPECIES_INFO_Y + 24)
#define SEARCH_LEVEL_Y          (TYPE_ICONS_Y + 24)
#define CHAIN_BONUS_Y           (SEARCH_LEVEL_Y + 24)
#define HA_INFO_Y               (CHAIN_BONUS_Y + 23) //24


#define MON_LEVEL_NONEXISTENT   255 // If mon not in area GetEncounterLevel returns this to exit the search

// GUI tags
#define ICON_PAL_TAG            56000
#define ICON_GFX_TAG            55130
#define SELECTION_CURSOR_TAG    0x4005
#define CAPTURED_ALL_TAG        0x4002

// Search tags
#define OWNED_ICON_TAG          0x4003
#define HIDDEN_SEARCH_TAG       SELECTION_CURSOR_TAG
#define HIDDEN_MON_ICON_TAG     0x4006
#define LIT_STAR_TILE_TAG       0x4010
#define HELD_ITEM_TAG           0xd750

// DexNav search variable
#define DEXNAV_MASK_SPECIES         0x3FFF  // First 14 bits
#define DEXNAV_MASK_ENVIRONMENT     0xC000  // Last two bit

void EndDexNavSearch(u8 taskId);
void Task_OpenDexNavFromStartMenu(u8 taskId);
void Task_OpenDexNavFromPokenav(u8 taskId);
void Task_OpenDexNavFromPokedex(u8 taskId);
void OpenDexNavFromPokedex(void);
bool8 TryStartDexNavSearch(void);
void TryIncrementSpeciesSearchLevel(u16 dexNum);
void ResetDexNavSearch(void);
bool8 TryFindHiddenPokemon(void);
u32 CalculateDexNavShinyRolls(void);
void IncrementDexNavChain(void);
u32 PokeNavMenuDexNavCallback(void);

//ewram
extern u8 gCurrentDexNavChain;
extern bool8 gDexNavBattle;
extern EWRAM_DATA u16 gDexNavSelectedSpecies;
extern EWRAM_DATA u16 gPokedexSpeciesToLoad;

#endif // GUARD_DEXNAV_H

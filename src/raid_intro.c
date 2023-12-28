#include "global.h"
#include "bg.h"
#include "sprite.h"
#include "main.h"
#include "battle.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item_menu.h"
#include "sound.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "random.h"
#include "palette.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "string_util.h"
#include "trainer_pokemon_sprites.h"
#include "util.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"

#include "data/raid_partners.h"

enum Windows
{
	WIN_RECOMMENDED_LEVEL,
	WIN_CHOOSE_PARTNER,
	WIN_RULES,
	WIN_TYPE_1,
	WIN_TYPE_2,
	WIN_INSTRUCTIONS,
	WIN_PARTNER_NOT_AVAILABLE,
	WINDOW_COUNT,
};

enum
{
	TAG_RAID_BATTLE_STAR = 10001,
	TAG_RAID_BATTLE_CURSOR,
};

struct Partner
{
	u16 id;
	u16 graphicsId;
	u16 team[MAX_TEAM_SIZE];
};

struct RaidBattleIntro
{
	u32* tilemapPtr;
	struct Partner partners[MAX_NUM_PARTNERS];
	u32 personality;
	u16 species;
	u8 selectedTeam;
	u16 monSpriteId;
	u8 outlinedSprite;
	u8 typeIconSpriteIds[2];
};

// const rom data
static const u8 sRaidStarGfx[]          = INCBIN_U8("graphics/misc/raid_battle_star.4bpp");
static const u16 sRaidStarPal[]         = INCBIN_U16("graphics/misc/raid_battle_star.gbapal");
static const u8 sRaidCursorGfx[]        = INCBIN_U8("graphics/misc/raid_battle_cursor.4bpp");
static const u16 sRaidCursorPal[]       = INCBIN_U16("graphics/misc/raid_battle_cursor.gbapal");
static const u32 sRaidIntroBgGfx[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.4bpp.lz");
static const u32 sRaidIntroBgPal[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.gbapal.lz");
static const u32 sRaidIntroBgMap[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.bin.lz");

static const u8 sText_RecommendedLevel[]        = _("Recommended Level: ");
static const u8 sText_RaidIntroSelection[]      = _("{DPAD_UPDOWN}Pick {A_BUTTON}Choose {B_BUTTON}Cancel");
static const u8 sText_RaidIntroSelection2[]      = _("{SELECT_BUTTON}Random {START_BUTTON}Solo");
static const u8 sText_RaidBattleRules[]         = _("Battle ends if:\n 4 Pokemon faint\n 10 turns pass");
static const u8 sText_RaidBattleChoosePartner[] = _("Available Partners");
static const u8 sText_raidPartnerNotAvailable[] = _("Not available");

static const struct WindowTemplate sRaidBattleIntroWinTemplates[WINDOW_COUNT + 1] =
{
	[WIN_RECOMMENDED_LEVEL] =
	{
		.bg = 1,
		.tilemapLeft = 16,
		.tilemapTop = 0,
		.width = 14,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 1,
	},
	[WIN_CHOOSE_PARTNER] =
	{
		.bg = 1,
		.tilemapLeft = 16,
		.tilemapTop = 3,
		.width = 14,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 43,
	},
	[WIN_RULES] =
	{
		.bg = 1,
		.tilemapLeft = 1,
		.tilemapTop = 13,
		.width = 10,
		.height = 6,
		.paletteNum = 15,
		.baseBlock = 71,
	},
	[WIN_TYPE_1] =
	{
		.bg = 1,
		.tilemapLeft = 8,
		.tilemapTop = 0,
		.width = 4,
		.height = 2,
		.paletteNum = 12,
		.baseBlock = 131,
	},
	[WIN_TYPE_2] =
	{
		.bg = 1,
		.tilemapLeft = 12,
		.tilemapTop = 0,
		.width = 4,
		.height = 2,
		.paletteNum = 12,
		.baseBlock = 149,
	},
	[WIN_INSTRUCTIONS] =
	{
		.bg = 1,
		.tilemapLeft = 0,
		.tilemapTop = 18,
		.width = 30,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 167,
	},
	[WIN_PARTNER_NOT_AVAILABLE] = 
	{
		.bg = 1,
		.tilemapLeft = 14,
		.tilemapTop = 6,
		.width = 15,
		.height = 11,
		.paletteNum = 15,
		.baseBlock = 233,
	},
	DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sRaidBattleIntroBgTemplates[] =
{
	{ // Intro Background
		.bg = 2,
		.charBaseIndex = 0,
		.mapBaseIndex = 31,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 2,
		.baseTile = 0,
	},
	{ // Text
		.bg = 1,
		.charBaseIndex = 2,
		.mapBaseIndex = 6,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 1,
		.baseTile = 0,
	},
	{ // Instructions
		.bg = 0,
		.charBaseIndex = 1,
		.mapBaseIndex = 24,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 0,
		.baseTile = 0,
	}
};

static const struct OamData sStarOAM =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(8x8),
	.size = SPRITE_SIZE(8x8),
	.priority = 0, // On BG 2
};

static const struct OamData sOamData_RedArrowCursor =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(32x32),
	.size = SPRITE_SIZE(32x32),
	.priority = 0, // Above everything
};

static const struct SpriteTemplate sRaidBattleStarSpriteTemplate =
{
	.tileTag = TAG_RAID_BATTLE_STAR,
	.paletteTag = TAG_RAID_BATTLE_STAR,
	.oam = &sStarOAM,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCallbackDummy,
};

static void SpriteCB_RaidCursor(struct Sprite* sprite);
static const struct SpriteTemplate sRaidBattleCursorSpriteTemplate =
{
	.tileTag = TAG_RAID_BATTLE_CURSOR,
	.paletteTag = TAG_RAID_BATTLE_CURSOR,
	.oam = &sOamData_RedArrowCursor,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCB_RaidCursor,
};

static const struct SpriteSheet sRaidBattleStarSpriteSheet = {
    sRaidStarGfx, sizeof(sRaidStarGfx), TAG_RAID_BATTLE_STAR
};
static const struct SpritePalette sRaidBattleStarSpritePalette = {
    sRaidStarPal, TAG_RAID_BATTLE_STAR
};
static const struct SpriteSheet sRaidBattleCursorSpriteSheet = {
    sRaidCursorGfx, sizeof(sRaidCursorGfx), TAG_RAID_BATTLE_CURSOR
};
static const struct SpritePalette sRaidBattleCursorSpritePalette = {
    sRaidCursorPal, TAG_RAID_BATTLE_CURSOR
};

// functions
static void PrintInstructions(void);
static void CleanWindows(void);
static void CommitWindows(void);
static void LoadRaidBattleIntroGfx(void);
static void ClearTasksAndGraphicalStructs(void);
static void ClearVramOamPlttRegs(void);
static void Task_RaidBattleIntroFadeOut(u8 taskId);
static void Task_RaidBattleIntroWaitForKeyPress(u8 taskId);
static void Task_RaidBattleIntroFadeIn(u8 taskId);
static void Task_RaidBattleIntroSetUpBattle(u8 taskId);
static void InitRaidBattleIntro(void);
static void ShowStars(void);
static void ShowRaidPokemonSprite(void);
static void ShowRaidPokemonTypes(void);
static void ShowPartnerTeams(void);
static void ShowRaidCursor(void);
static void OutlineMonSprite(u8 spriteId);
static bool32 GetRaidBattleData(void);

EWRAM_DATA static struct RaidBattleIntro *sRaidBattleIntro = NULL;

// code
static void MainCB2_RaidBattleIntro(void)
{
	RunTasks();
	AnimateSprites();
	BuildOamBuffer();
	UpdatePaletteFade();
}

static void VBlankCB_RaidBattleIntro(void)
{
	LoadOam();
	ProcessSpriteCopyRequests();
	TransferPlttBuffer();
}

void CB2_RaidBattleIntro(void)
{
    switch (gMain.state) {
        default:
        case 0:
            SetVBlankCallback(NULL); 
            ClearVramOamPlttRegs();
            gMain.state++;
            break;
        case 1:
            ClearTasksAndGraphicalStructs();
            gMain.state++;
            break;
        case 2:
            sRaidBattleIntro->tilemapPtr = AllocZeroed(BG_SCREEN_SIZE);
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sRaidBattleIntroBgTemplates, 3);
            SetBgTilemapBuffer(2, sRaidBattleIntro->tilemapPtr);
            gMain.state++;
            break;
        case 3:
            LoadRaidBattleIntroGfx();
            gMain.state++;
            break;
        case 4:
            if (IsDma3ManagerBusyWithBgCopy() != TRUE)
            {
                ShowBg(0);
                ShowBg(1);
                ShowBg(2);
                CopyBgTilemapBufferToVram(2);
                gMain.state++;
            }
            break;
        case 5:
            InitWindows(sRaidBattleIntroWinTemplates);
            DeactivateAllTextPrinters();
            gMain.state++;
            break;
        case 6:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gMain.state++;
            break;
        case 7:
            SetVBlankCallback(VBlankCB_RaidBattleIntro);
            InitRaidBattleIntro();
            CreateTask(Task_RaidBattleIntroFadeIn, 0);
            SetMainCallback2(MainCB2_RaidBattleIntro);
            break;
	}
}

static void Task_RaidBattleIntroFadeOut(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        SetMainCallback2(CB2_ReturnToFieldContinueScript);
		Free(sRaidBattleIntro->tilemapPtr);
		Free(sRaidBattleIntro);
        sRaidBattleIntro = NULL;
		FreeAllWindowBuffers();
		DestroyTask(taskId);
	}
}

static void Task_RaidBattleIntroSetUpBattle(u8 taskId)
{
	gBattleTypeFlags |= BATTLE_TYPE_RAID;
	BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
	gTasks[taskId].func = Task_RaidBattleIntroFadeOut;
}

static void Task_RaidBattleIntroWaitForKeyPress(u8 taskId)
{
	u8 i;
	u16 id;
	const u8* name;

	if (gMain.newKeys & A_BUTTON)
	{
        // TODO:
        //  - Set Raid Partner information based on selected trainer.
		PRESSED_A:
		gRaidData.partnerNum = sRaidBattleIntro->partners[sRaidBattleIntro->selectedTeam].id;
		gSpecialVar_Result = 1;
		PlaySE(SE_SUCCESS);
		gTasks[taskId].func = Task_RaidBattleIntroSetUpBattle;
	}
	else if (gMain.newKeys & B_BUTTON)
	{
		PlaySE(SE_FAILURE);
		gSpecialVar_Result = 0;
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
		gTasks[taskId].func = Task_RaidBattleIntroFadeOut;
	}
	else if (gMain.newAndRepeatedKeys & SELECT_BUTTON)
	{
		// TODO:
        //  - Select a random team to partner with.
		/*gRaidData.partnerNum = sRaidBattleIntro->partners[Random()%3].id;
		gSpecialVar_Result = 1;*/
		sRaidBattleIntro->selectedTeam = Random()%3;
		goto PRESSED_A;
	}
	else if (gMain.newAndRepeatedKeys & START_BUTTON)
	{
		// TODO:
        //  - Go alone.
		gRaidData.partnerNum = 0;
		gSpecialVar_Result = 2;
		goto PRESSED_A;
	}
	else if (gMain.newAndRepeatedKeys & DPAD_UP)
	{
		const struct RaidPartner* raidPartners = &gRaidPartners[gRaidData.rank];
		PlaySE(SE_SELECT);
		if (sRaidBattleIntro->selectedTeam == 0)
		{
			for (i = 0; i < MAX_NUM_PARTNERS; ++i)
			{
				if (i < raidPartners->numOfPartners)
					sRaidBattleIntro->selectedTeam++;
				else
					break;
			}

			sRaidBattleIntro->selectedTeam -= 1; // Prevent overflow
		}
		else
			sRaidBattleIntro->selectedTeam--;
	}
	else if (gMain.newAndRepeatedKeys & DPAD_DOWN)
	{
		const struct RaidPartner* raidPartners = &gRaidPartners[gRaidData.rank];
		PlaySE(SE_SELECT);
		sRaidBattleIntro->selectedTeam++;

		if (sRaidBattleIntro->selectedTeam >= MAX_NUM_PARTNERS
		    || sRaidBattleIntro->selectedTeam >= raidPartners->numOfPartners)
			sRaidBattleIntro->selectedTeam = 0;
	}
}

// Makes the sprite move back and forth horizontally.
static void SpriteCB_RaidCursor(struct Sprite* sprite)
{
    sprite->y2 = sRaidBattleIntro->selectedTeam * 33;

	if (sprite->data[1])
	{
		sprite->data[0] -= 1;
		if (sprite->data[0] == 0)
			sprite->data[1] = FALSE;
	}
	else
	{
		sprite->data[0] += 1;
		if (sprite->data[0] == 20)
			sprite->data[1] = TRUE;
	}

	sprite->x2 = 5 - sprite->data[0] / 4;
}

static void Task_RaidBattleIntroFadeIn(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        PlaySE(SE_RG_CARD_OPEN);
		gTasks[taskId].func = Task_RaidBattleIntroWaitForKeyPress;
	}
}

static void PrintInstructions(void)
{
	const u8 partnerColour[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};
	/*{
		.bgColor = 0, // Transparent
		.fgColor = 2, // Dark Gray
		.shadowColor = 3, // Gray
	};*/

	const u8 colour[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
	/*{
		.bgColor = 0, // Transparent
		.fgColor = 1, // White
		.shadowColor = 2, // Dark Gray
	};*/

	AddTextPrinterParameterized3(WIN_RULES, 0, 0, 2, colour, 0, sText_RaidBattleRules);

	StringCopy(gStringVar1, sText_RecommendedLevel);
    ConvertIntToDecimalStringN(gStringVar2, GetRaidRecommendedLevel(), 0, 3); // placeholder
	StringAppend(gStringVar1, gStringVar2);
	AddTextPrinterParameterized3(WIN_RECOMMENDED_LEVEL, 0, 4, 0, colour, 0, gStringVar1);

	AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 2, 4, colour, 0, sText_RaidIntroSelection);
	AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 137, 4, colour, 0, sText_RaidIntroSelection2);

	AddTextPrinterParameterized3(WIN_CHOOSE_PARTNER, 3, 1, 4, partnerColour, 0, sText_RaidBattleChoosePartner);
}

static void ShowStars(void)
{
    u8 i;
    LoadSpriteSheet(&sRaidBattleStarSpriteSheet);
	LoadSpritePalette(&sRaidBattleStarSpritePalette);
	for (i = 0; i < gRaidData.rank; i++)
		CreateSprite(&sRaidBattleStarSpriteTemplate, (gRaidData.rank == RAID_RANK_7 ? 5 : 10) + (9 * i), 8, 0);
}

static void ShowRaidPokemonSprite(void)
{
    u8 i, j;
    u16 species = sRaidBattleIntro->species;
	u32 personality = sRaidBattleIntro->personality;
    u16 paletteOffset;
    u16 spriteId;
	bool8 isShiny = FALSE;

	// Create black silhouette.
	sRaidBattleIntro->monSpriteId = CreateMonPicSprite(species, isShiny, personality, TRUE, 45, 57, 0, species);
    gSprites[sRaidBattleIntro->monSpriteId].oam.priority = 0;

	paletteOffset = IndexOfSpritePaletteTag(species) * 16 + 0x100;
    BlendPalette(paletteOffset, 16, 16, RGB(4, 4, 4));
    CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);

	// Create white outline.
    // TODO: Nicer looking way to do this with fancy VRAM trick, see CFRU.
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            spriteId = CreateMonPicSprite(species, isShiny, personality, TRUE, 44 + i*2, 56 + j*2, gSprites[sRaidBattleIntro->monSpriteId].oam.paletteNum + 1, TAG_NONE);
            gSprites[spriteId].oam.priority = 1;
        }
    }
    paletteOffset += 16;
    FillPalette(RGB_WHITE, paletteOffset, 32);
    CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
}

// different from pokemon_summary_screen
#define TYPE_ICON_PAL_NUM_0     13
#define TYPE_ICON_PAL_NUM_1     14
#define TYPE_ICON_PAL_NUM_2     15
static const u8 sMoveTypeToOamPaletteNum[NUMBER_OF_MON_TYPES] =
{
    [TYPE_NORMAL] = TYPE_ICON_PAL_NUM_0,
    [TYPE_FIGHTING] = TYPE_ICON_PAL_NUM_0,
    [TYPE_FLYING] = TYPE_ICON_PAL_NUM_1,
    [TYPE_POISON] = TYPE_ICON_PAL_NUM_1,
    [TYPE_GROUND] = TYPE_ICON_PAL_NUM_0,
    [TYPE_ROCK] = TYPE_ICON_PAL_NUM_0,
    [TYPE_BUG] = TYPE_ICON_PAL_NUM_2,
    [TYPE_GHOST] = TYPE_ICON_PAL_NUM_1,
    [TYPE_STEEL] = TYPE_ICON_PAL_NUM_0,
    [TYPE_MYSTERY] = TYPE_ICON_PAL_NUM_2,
    [TYPE_FIRE] = TYPE_ICON_PAL_NUM_0,
    [TYPE_WATER] = TYPE_ICON_PAL_NUM_1,
    [TYPE_GRASS] = TYPE_ICON_PAL_NUM_2,
    [TYPE_ELECTRIC] = TYPE_ICON_PAL_NUM_0,
    [TYPE_PSYCHIC] = TYPE_ICON_PAL_NUM_1,
    [TYPE_ICE] = TYPE_ICON_PAL_NUM_1,
    [TYPE_DRAGON] = TYPE_ICON_PAL_NUM_2,
    [TYPE_DARK] = TYPE_ICON_PAL_NUM_0,
    #ifdef TYPE_FAIRY
    [TYPE_FAIRY] = TYPE_ICON_PAL_NUM_1, //based on battle_engine
    #endif
};

static void ShowRaidPokemonTypes(void)
{
	u16 species = sRaidBattleIntro->species;
	u8 type1 = gSpeciesInfo[species].types[0];
	u8 type2 = gSpeciesInfo[species].types[1];
	struct Sprite *sprite;

	/*BlitMenuInfoIcon(WIN_TYPE_1, type1 + 1, 0, 2);
	if (type1 != type2)
		BlitMenuInfoIcon(WIN_TYPE_2, type2 + 1, 0, 2);*/



    LoadCompressedSpriteSheet(&gSpriteSheet_MoveTypes);
    LoadCompressedPalette(gMoveTypes_Pal, 0x1D0, 0x60);

    if (sRaidBattleIntro->typeIconSpriteIds[0] == 0xFF)
    {
		sRaidBattleIntro->typeIconSpriteIds[0] = CreateSprite(&gSpriteTemplate_MoveTypes, 80, 7, 0);

		sprite = &gSprites[sRaidBattleIntro->typeIconSpriteIds[0]];
		StartSpriteAnim(sprite, type1);
		sprite->oam.paletteNum = sMoveTypeToOamPaletteNum[type1];
    }

	if (sRaidBattleIntro->typeIconSpriteIds[1] == 0xFF && type2 != type1)
    {
		sRaidBattleIntro->typeIconSpriteIds[1] = CreateSprite(&gSpriteTemplate_MoveTypes, 112, 7, 0);

		sprite = &gSprites[sRaidBattleIntro->typeIconSpriteIds[1]];
		StartSpriteAnim(sprite, type2);
		sprite->oam.paletteNum = sMoveTypeToOamPaletteNum[type2];
    }
}

static void ShowPartnerTeams(void)
{
	u8 i, j;
	const u8 partnerColour[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};
	const struct RaidPartner* raidPartners = &gRaidPartners[gRaidData.rank];

	for (i = 0; i < MAX_NUM_PARTNERS; ++i)
	{
		//AddTextPrinterParameterized3(WIN_PARTNER_NOT_AVAILABLE, 3, 1+28, 4+4+i*33, partnerColour, 0, sText_raidPartnerNotAvailable);
		if (i < raidPartners->numOfPartners)
		{
            u32 spriteId;

			spriteId = CreateObjectGraphicsSprite(sRaidBattleIntro->partners[i].graphicsId, SpriteCallbackDummy, /*126*/101, 59 + (i * 33), 0);
            gSprites[spriteId].oam.priority = 0;

			for (j = 0; j < MAX_TEAM_SIZE; ++j)
			{
				//if (j < gBattlePartners[sRaidBattleIntro->partners[i].id].partySize)
				{
					u16 species = sRaidBattleIntro->partners[i].team[j];
					if (species != SPECIES_NONE)
					{
						LoadMonIconPalette(species);
						CreateMonIcon(species, SpriteCB_MonIcon, /*158*/120 + (/*32*/21 * j), 59 + (i * 33), 0, 0xFFFFFFFF);
					}
				}
			}
		}
	}
}

static void ShowRaidCursor(void)
{
	LoadSpriteSheet(&sRaidBattleCursorSpriteSheet);
	LoadSpritePalette(&sRaidBattleCursorSpritePalette);
	CreateSprite(&sRaidBattleCursorSpriteTemplate, /*95*/73, 59, 0);
}

static void CleanWindows(void)
{
    u8 i;
	for (i = 0; i < WINDOW_COUNT; i++)
		FillWindowPixelBuffer(i, PIXEL_FILL(0));
}

static void CommitWindows(void)
{
    u8 i;
	for (i = 0; i < WINDOW_COUNT; i++)
	{
		CopyWindowToVram(i, 3);
		PutWindowTilemap(i);
	}
}

static void InitRaidBattleIntro(void)
{
	CleanWindows();
	CommitWindows();

	ShowStars();
    ShowRaidCursor();
    PrintInstructions();
	sRaidBattleIntro->typeIconSpriteIds[0] = 0xFF;
	sRaidBattleIntro->typeIconSpriteIds[1] = 0xFF;
	ShowRaidPokemonTypes();
	ShowPartnerTeams();
	ShowRaidPokemonSprite();

	CommitWindows();
}

static void LoadRaidBattleIntroGfx(void)
{	
    DecompressAndCopyTileDataToVram(2, &sRaidIntroBgGfx, 0, 0, 0);
	LZDecompressWram(sRaidIntroBgMap, sRaidBattleIntro->tilemapPtr);
	LoadCompressedPalette(sRaidIntroBgPal, 0, BG_PLTT_ID(2));
    ListMenuLoadStdPalAt(BG_PLTT_ID(12), 1);
    LoadPalette(&gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
}

static void ClearTasksAndGraphicalStructs(void)
{
	ScanlineEffect_Stop();
	ResetTasks();
	ResetSpriteData();
	ResetTempTileDataBuffers();
	ResetPaletteFade();
	FreeAllSpritePalettes();
}

static void ClearVramOamPlttRegs(void)
{
	DmaFill16(3, 0, VRAM, VRAM_SIZE);
	DmaFill32(3, 0, OAM, OAM_SIZE);
	DmaFill16(3, 0, PLTT, PLTT_SIZE);
	SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
	SetGpuReg(REG_OFFSET_BG3CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0VOFS, DISPCNT_MODE_0);
}

static bool8 HasRaidBattleAlreadyBeenDone(void)
{
    return GetRaidBattleFlag();
}

void IsRaidBattleAvailable(void)
{
	if (!HasRaidBattleAlreadyBeenDone() && GetRaidBattleData())
		gSpecialVar_Result = TRUE;
	else
		gSpecialVar_Result = FALSE;
}

void InitRaidIntro(void)
{
    gSpecialVar_Result = FALSE;
    if (sRaidBattleIntro == NULL)
	    sRaidBattleIntro = AllocZeroed(sizeof(struct RaidBattleIntro));

	if (GetRaidBattleData())
	{
		PlayRainStoppingSoundEffect();
		SetMainCallback2(CB2_RaidBattleIntro);
	}
}

void InitStoryRaid(void)
{
	if (InitCustomRaidData())
	{
		FlagClear(FLAG_SYS_SPECIAL_RAID_BATTLE);
		gSpecialVar_Result = TRUE;
	}
}

static bool32 GetRaidBattleData(void)
{
	bool32 success;
	u32 i,j;

	if (FlagGet(FLAG_SYS_SPECIAL_RAID_BATTLE))
	{
		if (InitCustomRaidData())
			success = TRUE;
	}
	else if (InitRaidData())
		success = TRUE;
	
	if (success)
	{
		const struct RaidPartner* raidPartners = &gRaidPartners[gRaidData.rank];
		u8 partnerTrainerIndex[raidPartners->numOfPartners];
		FlagClear(FLAG_SYS_SPECIAL_RAID_BATTLE);

		sRaidBattleIntro->species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL);
		sRaidBattleIntro->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);

		DetermineRaidPartners(partnerTrainerIndex, NELEMS(partnerTrainerIndex));

		for (i = 0; i < MAX_NUM_PARTNERS; i++)
		{
			struct Partner* partner = &sRaidBattleIntro->partners[i];
			partner->id = OverrideRaidPartnerTrainerId(raidPartners->partnerData[partnerTrainerIndex[i]].trainerNum);

			if (raidPartners->partnerData[partnerTrainerIndex[i]].trainerNum == TRAINER_RIVAL_OVERRIDE)
				partner->graphicsId = (gSaveBlock2Ptr->playerGender == MALE) ? OBJ_EVENT_GFX_MAY_NORMAL : OBJ_EVENT_GFX_BRENDAN_NORMAL;
			else
				partner->graphicsId = raidPartners->partnerData[partnerTrainerIndex[i]].graphicsId;

			for (j = 0; j < MAX_TEAM_SIZE; j++)
				//if (j < gBattlePartners[partner->id].partySize)
					partner->team[j] = gBattlePartners[partner->id].party[j].species;
		}

		return TRUE;
	}
	return FALSE;
}

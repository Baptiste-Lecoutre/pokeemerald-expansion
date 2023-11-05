#include "global.h"
#include "bg.h"
#include "sprite.h"
#include "main.h"
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

enum Windows
{
	WIN_ROUTE,
	WIN_TRAINER_NAME,
	WINDOW_COUNT,
};

struct TrainerRadar
{
    u32* tilemapPtr;
};

// const rom data
static const u32 sTrainerRadarBgGfx[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.4bpp.lz");
static const u32 sTrainerRadarBgPal[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.gbapal.lz");
static const u32 sTrainerRadarBgMap[]      = INCBIN_U32("graphics/misc/raid_battle_intro_bg.bin.lz");

static const struct WindowTemplate sTrainerRadarWinTemplates[WINDOW_COUNT + 1] =
{
    [WIN_ROUTE] =
	{
		.bg = 1,
		.tilemapLeft = 16,
		.tilemapTop = 0,
		.width = 14,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 1,
	},
    [WIN_TRAINER_NAME] = 
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

static const struct BgTemplate sTrainerRadarBgTemplates[] =
{
	{ // UI Background
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

// functions
static void PrintInstructions(void);
static void CleanWindows(void);
static void CommitWindows(void);
static void LoadTrainerRadarGfx(void);
static void ClearTasksAndGraphicalStructs(void);
static void ClearVramOamPlttRegs(void);
static void Task_TrainerRadarFadeOut(u8 taskId);
static void Task_TrainerRadarWaitForKeyPress(u8 taskId);
static void Task_TrainerRadarFadeIn(u8 taskId);
static void InitTrainerRadarScreen(void);

EWRAM_DATA static struct TrainerRadar *sTrainerRadar = NULL;

// code
static void MainCB2_TrainerRadar(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_TrainerRadar(void)
{
	LoadOam();
	ProcessSpriteCopyRequests();
	TransferPlttBuffer();
}

void CB2_TrainerRadar(void)
{
    switch (gMain.state){
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
            sTrainerRadar->tilemapPtr = AllocZeroed(BG_SCREEN_SIZE);
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sTrainerRadarBgTemplates, 3);
            SetBgTilemapBuffer(2, sTrainerRadar->tilemapPtr);
            gMain.state++;
            break;
        case 3:
            LoadTrainerRadarGfx();
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
            InitWindows(sTrainerRadarWinTemplates);
            DeactivateAllTextPrinters();
            gMain.state++;
            break;
        case 6:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gMain.state++;
            break;
        case 7:
            SetVBlankCallback(VBlankCB_TrainerRadar);
            InitTrainerRadarScreen();
            CreateTask(Task_TrainerRadarFadeIn, 0);
            SetMainCallback2(MainCB2_TrainerRadar);
            break;
	}
}

static void Task_TrainerRadarFadeOut(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        SetMainCallback2(CB2_ReturnToFieldContinueScript);
		Free(sTrainerRadar->tilemapPtr);
		Free(sTrainerRadar);
        sTrainerRadar = NULL;
		FreeAllWindowBuffers();
		DestroyTask(taskId);
	}
}

static void Task_TrainerRadarWaitForKeyPress(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarFadeOut;
    }
}

static void Task_TrainerRadarFadeIn(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        PlaySE(SE_RG_CARD_OPEN);
		gTasks[taskId].func = Task_TrainerRadarWaitForKeyPress;
	}
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

static void InitTrainerRadarScreen(void)
{
	CleanWindows();
	CommitWindows();

    // do stuff

	CommitWindows();
}

static void LoadTrainerRadarGfx(void)
{	
    DecompressAndCopyTileDataToVram(2, &sTrainerRadarBgGfx, 0, 0, 0);
	LZDecompressWram(sTrainerRadarBgMap, sTrainerRadar->tilemapPtr);
	LoadCompressedPalette(sTrainerRadarBgPal, 0, BG_PLTT_ID(2));
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

void InitTrainerRadar(void)
{
    if (sTrainerRadar == NULL)
        sTrainerRadar = AllocZeroed(sizeof(struct TrainerRadar));

    PlayRainStoppingSoundEffect();
    SetMainCallback2(CB2_TrainerRadar);
}

#include "global.h"
#include "bg.h"
#include "sprite.h"
#include "main.h"
#include "battle_setup.h"
#include "data.h"
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
#include "palette.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "random.h"
#include "region_map.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "string_util.h"
#include "strings.h"
#include "trainer_pokemon_sprites.h"
#include "trainer_radar.h"
#include "util.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/opponents.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"

enum Windows
{
    WIN_TRAINER_NAME,
	WIN_MAP_NAME,
    WIN_TRAINER_COUNT,
    WIN_TRAINER_LIST,
    WIN_INSTRUCTIONS,
	WINDOW_COUNT,
};

struct TrainerRadar
{
    u32* tilemapPtr;
    u16 trainerId;
    u8 mapsec;
    u8 numOfTrainers;
    u8 visibleCursorPosition;
    u8 absoluteCursorPosition;
    u8 trainerFrontPicSpriteId;
    u8 trainerObjEventSpriteId;
    u8 trainerPartySpriteIds[PARTY_SIZE];
};

#define VISIBLE_CURSOR_MAX_VALUE 5 //6 slots - 1

// const rom data
static const u32 sTrainerRadarBgGfx[]      = INCBIN_U32("graphics/misc/trainer_radar.4bpp.lz");
static const u32 sTrainerRadarBgPal[]      = INCBIN_U32("graphics/misc/trainer_radar.gbapal.lz");
static const u32 sTrainerRadarBgMap[]      = INCBIN_U32("graphics/misc/trainer_radar.bin.lz");

static const u32 sSelectionCursorGfx[] = INCBIN_U32("graphics/misc/trainer_radar_cursor.4bpp.lz");
static const u16 sSelectionCursorPal[] = INCBIN_U16("graphics/misc/trainer_radar_cursor.gbapal");

static const u8 sText_NoData[] = _("No data");
static const u8 sText_unknown[] = _("???");
static const u8 sText_InstructionsArea[] = _("{DPAD_LEFTRIGHT}Area");
static const u8 sText_InstructionsAreaTrainer[] = _("{DPAD_LEFTRIGHT}Area {DPAD_UPDOWN}Trainer");
static const u8 sText_InstructionsExit[] = _("{B_BUTTON}Exit");
static const u8 sText_Defeated[] = _("Defeated: ");

static const struct WindowTemplate sTrainerRadarWinTemplates[WINDOW_COUNT + 1] =
{
    [WIN_TRAINER_NAME] = 
	{
		.bg = 0,
		.tilemapLeft = 1,
		.tilemapTop = 255,
		.width = 10,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 0,
	},
    [WIN_MAP_NAME] =
	{
		.bg = 0,
		.tilemapLeft = 16,
		.tilemapTop = 255,
		.width = 14,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 30,
	},
    [WIN_TRAINER_COUNT]=
    {
        .bg = 0,
		.tilemapLeft = 1,
		.tilemapTop = 3,
		.width = 10,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 72,
    },
    [WIN_TRAINER_LIST] = 
	{
		.bg = 0,
		.tilemapLeft = 1,
		.tilemapTop = 5,
		.width = 10,
		.height = 13,
		.paletteNum = 15,
		.baseBlock = 102,
	},
    [WIN_INSTRUCTIONS] =
	{
		.bg = 0,
		.tilemapLeft = 0,
		.tilemapTop = 18,
		.width = 30,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 232,
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

// gui font
static const u8 sFontColor_White[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sFontColor_Black[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};
static const u8 sFontColor_Red[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED, TEXT_COLOR_LIGHT_RED};

#include "data/trainer_radar.h"

// skeleton functions
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
static void CreateTrainerRadarCursor(void);

// skin functions
static void UpdateTrainerRadarData(void);
static void UpdateTrainerRadarVisualElements(void);
static void PrintTrainerList(void);
static void PrintMapName(void);
static void PrintTrainerClass(void);
static void PrintTrainerPic(void);
static void PrintTrainerOW(void);
static void PrintTrainerParty(void);
static void PrintTrainerCount(void);
static void PrintInstructions(void);
static void TrainerRadar_CursorCallback(struct Sprite *sprite);

EWRAM_DATA static struct TrainerRadar *sTrainerRadar = NULL;

#define SELECTION_CURSOR_TAG    0x4005
static const struct OamData sSelectionCursorOam =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0, // above BG layers
    .paletteNum = 14,
    .affineParam = 0
};

static const struct SpriteTemplate sSelectionCursorSpriteTemplate =
{
    .tileTag = SELECTION_CURSOR_TAG,
    .paletteTag = 0xFFFF,
    .oam = &sSelectionCursorOam,
    .anims =  gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = TrainerRadar_CursorCallback,
};

// code for UI skeleton
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
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarFadeOut;
    }
    else if (JOY_NEW(DPAD_DOWN) && sTrainerRadar->numOfTrainers != 0) // move cursors down
    {
        PlaySE(SE_SELECT);
        if (sTrainerRadar->absoluteCursorPosition < sTrainerRadar->numOfTrainers-1)
        {
            sTrainerRadar->absoluteCursorPosition++;
            if (sTrainerRadar->visibleCursorPosition < VISIBLE_CURSOR_MAX_VALUE)
                sTrainerRadar->visibleCursorPosition++;
        }
        else
            sTrainerRadar->visibleCursorPosition = sTrainerRadar->absoluteCursorPosition = 0;
        
        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }    
    else if (JOY_NEW(DPAD_UP) && sTrainerRadar->numOfTrainers != 0) // move cursors up
    {
        PlaySE(SE_SELECT);
        if (sTrainerRadar->absoluteCursorPosition > 0)
        {
            sTrainerRadar->absoluteCursorPosition--;
            if (sTrainerRadar->visibleCursorPosition > 0)
                sTrainerRadar->visibleCursorPosition--;
        }
        else
        {
            sTrainerRadar->absoluteCursorPosition = sTrainerRadar->numOfTrainers-1;
            sTrainerRadar->visibleCursorPosition = VISIBLE_CURSOR_MAX_VALUE;
            if (sTrainerRadar->numOfTrainers-1 < VISIBLE_CURSOR_MAX_VALUE)
                sTrainerRadar->visibleCursorPosition = sTrainerRadar->numOfTrainers-1;
        }

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        PlaySE(SE_SELECT);
        sTrainerRadar->visibleCursorPosition = sTrainerRadar->absoluteCursorPosition = 0;

        if (sTrainerRadar->mapsec > MAPSEC_LITTLEROOT_TOWN)
            sTrainerRadar->mapsec--;
        else
            sTrainerRadar->mapsec = MAPSEC_NONE-1;
    
        // skip over kanto mapsecs & MAPSEC_SECRET_BASE & MAPSEC_DYNAMIC
        if (sTrainerRadar->mapsec >= MAPSEC_SECRET_BASE && sTrainerRadar->mapsec <= KANTO_MAPSEC_END)
            sTrainerRadar->mapsec = MAPSEC_SECRET_BASE - 1;

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        sTrainerRadar->visibleCursorPosition = sTrainerRadar->absoluteCursorPosition = 0;

        if (sTrainerRadar->mapsec < MAPSEC_NONE-1)
            sTrainerRadar->mapsec++;
        else
            sTrainerRadar->mapsec = MAPSEC_LITTLEROOT_TOWN;

        // skip over kanto mapsecs & MAPSEC_SECRET_BASE & MAPSEC_DYNAMIC
        if (sTrainerRadar->mapsec >= MAPSEC_SECRET_BASE && sTrainerRadar->mapsec <= KANTO_MAPSEC_END)
            sTrainerRadar->mapsec = KANTO_MAPSEC_END + 1;

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
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
    u32 i;
	CleanWindows();
	CommitWindows();

    // do stuff
    sTrainerRadar->mapsec = GetCurrentRegionMapSectionId();
    sTrainerRadar->visibleCursorPosition = 0;
    sTrainerRadar->absoluteCursorPosition = 0;
    sTrainerRadar->trainerFrontPicSpriteId = 0xFF;
    sTrainerRadar->trainerObjEventSpriteId = 0xFF;
    for (i = 0; i < PARTY_SIZE; i++)
        sTrainerRadar->trainerPartySpriteIds[i]=0xFF;
    
    UpdateTrainerRadarData();
    CreateTrainerRadarCursor();

    UpdateTrainerRadarVisualElements();
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

static void CreateTrainerRadarCursor(void)
{
    u8 spriteId;
    struct CompressedSpriteSheet spriteSheet;
    
    spriteSheet.data = sSelectionCursorGfx;
    spriteSheet.size = 0x200;
    spriteSheet.tag = SELECTION_CURSOR_TAG;
    LoadCompressedSpriteSheet(&spriteSheet);
    
    LoadPalette(sSelectionCursorPal, (16 * sSelectionCursorOam.paletteNum) + 0x100, 32);
    
    spriteId = CreateSprite(&sSelectionCursorSpriteTemplate, 11, 52 + sTrainerRadar->visibleCursorPosition * 16, 0);
}

// code for the UI purpose
static void UpdateTrainerRadarData(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];
    
    if (routeTrainersStruct->routeTrainers != NULL)
    {
        sTrainerRadar->trainerId = routeTrainersStruct->routeTrainers[sTrainerRadar->absoluteCursorPosition];
        sTrainerRadar->numOfTrainers = routeTrainersStruct->numTrainers;
    }
    else
    {
        sTrainerRadar->trainerId = TRAINER_NONE;
        sTrainerRadar->numOfTrainers = 0;
    }
}

static void UpdateTrainerRadarVisualElements(void)
{
    CleanWindows();
    PrintTrainerList();
    PrintMapName();
    PrintTrainerClass();
    PrintTrainerPic();
    PrintTrainerOW();
    PrintTrainerParty();
    PrintTrainerCount();
    PrintInstructions();
    CommitWindows();
}

static void PrintTrainerList(void)
{
    u32 i, maxSeen = VISIBLE_CURSOR_MAX_VALUE+1;
    u16 trainerNum;
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
    {
        if (routeTrainersStruct->numTrainers < maxSeen)
            maxSeen = routeTrainersStruct->numTrainers;

        for (i = 0; i < maxSeen; i++)
        {
            trainerNum = routeTrainersStruct->routeTrainers[i+sTrainerRadar->absoluteCursorPosition-sTrainerRadar->visibleCursorPosition];
            if (HasTrainerBeenFought(trainerNum))
                AddTextPrinterParameterized3(WIN_TRAINER_LIST, 1, 8, 4 + i*16, sFontColor_Black, 0, gTrainers[trainerNum].trainerName);
            else
                AddTextPrinterParameterized3(WIN_TRAINER_LIST, 1, 8, 4 + i*16, sFontColor_Red, 0, gTrainers[trainerNum].trainerName);
        }
        CopyWindowToVram(WIN_TRAINER_LIST, 3);
    }
}

static void PrintMapName(void)
{
    GetMapName(gStringVar3, sTrainerRadar->mapsec, 0);
    AddTextPrinterParameterized3(WIN_MAP_NAME, 1, 2, 7, sFontColor_White, 0, gStringVar3);
    CopyWindowToVram(WIN_MAP_NAME, 3);
}

static void PrintTrainerClass(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
    {
        StringCopy(gStringVar1, gTrainerClassNames[gTrainers[sTrainerRadar->trainerId].trainerClass]);
        AddTextPrinterParameterized3(WIN_TRAINER_NAME, 1, 2, 7, sFontColor_White, 0, gStringVar1);
        CopyWindowToVram(WIN_TRAINER_NAME, 3);
    }
}

static void PrintTrainerPic(void)
{
    if (sTrainerRadar->trainerFrontPicSpriteId != 0xFF)
        FreeAndDestroyTrainerPicSprite(sTrainerRadar->trainerFrontPicSpriteId);

    if (sTrainerRadar->trainerId != TRAINER_NONE)
        sTrainerRadar->trainerFrontPicSpriteId = CreateTrainerPicSprite(gTrainers[sTrainerRadar->trainerId].trainerPic, TRUE, 132, 65, 15, TAG_NONE);
    // slot 15 to avoid conflict with mon icon palettes
}

static void PrintTrainerOW(void)
{
    if (sTrainerRadar->trainerObjEventSpriteId != 0xFF)
        DestroySpriteAndFreeResources(&gSprites[sTrainerRadar->trainerObjEventSpriteId]);
    
    if (sTrainerRadar->trainerId != TRAINER_NONE)
        sTrainerRadar->trainerObjEventSpriteId = CreateObjectGraphicsSprite(sTrainerObjEventGfx[sTrainerRadar->trainerId], SpriteCallbackDummy, 140, 124, 0);
}

static void PrintTrainerParty(void)
{
    u32 i;
    u16 species;
    u8 icon_x = 0, icon_y = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sTrainerRadar->trainerPartySpriteIds[i] != 0xFF)
            FreeAndDestroyMonIconSprite(&gSprites[sTrainerRadar->trainerPartySpriteIds[i]]);
    }
    
    FreeMonIconPalettes();

    if (sTrainerRadar->trainerId != TRAINER_NONE)
    {
        LoadMonIconPalettes();

        for (i = 0; i < gTrainers[sTrainerRadar->trainerId].partySize; i++)
        {
            icon_x = 188 + (i%2) * 35;
            icon_y = 43 + (i/2) * 35;

            species = HasTrainerBeenFought(sTrainerRadar->trainerId) ? gTrainers[sTrainerRadar->trainerId].party[i].species : SPECIES_NONE;
            sTrainerRadar->trainerPartySpriteIds[i] = CreateMonIcon(species, SpriteCallbackDummy, icon_x, icon_y, 1, 0xFFFFFFFF);
        }
    }
}

static void PrintTrainerCount(void)
{
    u32 i;
    u8 numTrainers = 0;
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
    {
        for (i = 0; i < routeTrainersStruct->numTrainers; i++)
        {
            if (HasTrainerBeenFought(routeTrainersStruct->routeTrainers[i]))
                numTrainers++;
        }
        
        StringCopy(gStringVar1, sText_Defeated);
        ConvertIntToDecimalStringN(gStringVar2, numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar1,gStringVar2);
        StringAppend(gStringVar1,gText_Slash);
        ConvertIntToDecimalStringN(gStringVar2, routeTrainersStruct->numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar1,gStringVar2);
    }
    else
        StringCopy(gStringVar1, sText_NoData);

    AddTextPrinterParameterized3(WIN_TRAINER_COUNT, 0, 2, 4, sFontColor_White, 0, gStringVar1);
    CopyWindowToVram(WIN_TRAINER_COUNT, 3);
}

static void PrintInstructions(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsAreaTrainer);
    else
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsArea);

    AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 208, 4, sFontColor_White, 0, sText_InstructionsExit);
    CopyWindowToVram(WIN_INSTRUCTIONS, 3);
}

static void TrainerRadar_CursorCallback(struct Sprite *sprite)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadar->mapsec];
    
    if (routeTrainersStruct->routeTrainers != NULL)
        sprite->invisible = FALSE;
    else
        sprite->invisible = TRUE;
        
    sprite->y = 52 + sTrainerRadar->visibleCursorPosition * 16;
}

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
#include "list_menu.h"
#include "sound.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "pokenav.h"
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

enum Page
{
    PAGE_MAIN,
    PAGE_ROUTE,
};

struct TrainerRadar
{
    MainCallback savedCallback;
    u8 state;
    u32* tilemapPtr;
    u8 page;
    u8 listTaskId;
    u8 mainScrollIndicatorsTaskId;
    u8 routeScrollIndicatorsTaskId;
    u16 selectedRowMain;
    u16 scrollOffsetMain;
    u16 selectedRowRoute;
    u16 scrollOffsetRoute;
    u16 trainerId;
    u8 mapsec;
    u8 numOfTrainers;
    u8 visibleCursorPosition;
    u8 absoluteCursorPosition;
    u8 trainerFrontPicSpriteId;
    u8 trainerObjEventSpriteId;
    u8 trainerPartySpriteIds[PARTY_SIZE];
};



// const rom data
static const u32 sTrainerRadarBgPal[]      = INCBIN_U32("graphics/misc/trainer_radar.gbapal.lz");
static const u32 sTrainerRadarMainBgGfx[]      = INCBIN_U32("graphics/misc/trainer_radar_main.4bpp.lz");
static const u32 sTrainerRadarMainBgMap[]      = INCBIN_U32("graphics/misc/trainer_radar_main.bin.lz");
static const u32 sTrainerRadarRouteBgGfx[]      = INCBIN_U32("graphics/misc/trainer_radar_route.4bpp.lz");
static const u32 sTrainerRadarRouteBgMap[]      = INCBIN_U32("graphics/misc/trainer_radar_route.bin.lz");

static const u32 sSelectionCursorGfx[] = INCBIN_U32("graphics/misc/trainer_radar_cursor.4bpp.lz");
static const u16 sSelectionCursorPal[] = INCBIN_U16("graphics/misc/trainer_radar_cursor.gbapal");

static const u8 sText_TrainerDatabase[] = _("Trainer Database");
static const u8 sText_NoData[] = _("No data");
static const u8 sText_unknown[] = _("???");
static const u8 sText_InstructionsAreaMain[] = _("{DPAD_UPDOWN}Area");
static const u8 sText_InstructionsAreaRoute[] = _("{DPAD_LEFTRIGHT}Area");
static const u8 sText_InstructionsAreaTrainer[] = _("{DPAD_LEFTRIGHT}Area  {DPAD_UPDOWN}Trainer");
static const u8 sText_InstructionsBack[] = _("{B_BUTTON}Back");
static const u8 sText_InstructionsSelectExit[] = _("{A_BUTTON}Select  {B_BUTTON}Exit");
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
		.width = 18,
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
		.baseBlock = 336,
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
static const u8 sFontColor_Green[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_GREEN, TEXT_COLOR_LIGHT_GREEN};

#include "data/trainer_radar.h"

static void Task_TrainerRadarMainWaitFadeIn(u8 taskId);
static void Task_TrainerRadarRouteWaitFadeIn(u8 taskId);
static void Task_TrainerRadarFadeAndChangePage(u8 taskId);
static void Task_TrainerRadar_RedoMainGfxSetup(u8 taskId);
static void Task_TrainerRadar_RedoRouteGfxSetup(u8 taskId);

static void TrainerRadarBuildMainListMenuTemplate(void);
static void TrainerRadarMainListMenuMoveCursorFunc(s32 listItem, bool8 onInit, struct ListMenu *list);
static void TrainerRadarMainListMenuItemPrintFunc(u8 windowId, u32 listItem, u8 y);
static void TrainerRadarBuildRouteListMenuTemplate(void);
static void TrainerRadarRouteListMenuMoveCursorFunc(s32 listItem, bool8 onInit, struct ListMenu *list);
static void TrainerRadarRouteListMenuItemPrintFunc(u8 windowId, u32 listItem, u8 y);
static void TrainerRadarAddMainScrollIndicatorArows(void);
static void TrainerRadarAddRouteScrollIndicatorArows(void);
static void TrainerRadarRemoveScrollIndicatorArrows(void);
static bool8 TrainerRadar_ReloadGraphics(void);

static void PrintVisualElements(void);
static void PrintRightHeader(void);
static void PrintLeftHeader(void);
static void PrintInstructions(void);
static void PrintTrainerPic(void);
static void PrintTrainerOW(void);
static void PrintTrainerParty(void);
static void DestroyPartyIcons(void);

static u16 GetTrainerOverride(u16 trainerId);

EWRAM_DATA static struct TrainerRadar *sTrainerRadarPtr = NULL;
EWRAM_DATA static u8 *sBg1TilemapBuffer = NULL;
EWRAM_DATA static struct ListMenuItem *sListMenuItems = NULL;
static EWRAM_DATA u8 (*sItemNames)[MAP_NAME_LENGTH + 2] = {0};

#define VISIBLE_CURSOR_MAX_VALUE 5 //6 slots - 1
#define MAIN_LIST_MENU_NUMBER_OF_ITEMS NELEMS(sTrainerRadarMapsecs)

#define TAG_SCROLL_ARROW   2100

static const struct ListMenuTemplate sTrainerRadarMainMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = TrainerRadarMainListMenuMoveCursorFunc, // change trainer graphics
    .itemPrintFunc = TrainerRadarMainListMenuItemPrintFunc, // print number of trainer defeated per route
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_TRAINER_LIST,
    .header_X = 0,
    .item_X = 10,//8,
    .cursor_X = 0,
    .upText_Y = 4, //1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 7,
    .cursorKind = 0
};

static const struct ListMenuTemplate sTrainerRadarRouteMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = TrainerRadarRouteListMenuMoveCursorFunc, // change trainer graphics
    .itemPrintFunc = NULL,//TrainerRadarRouteListMenuItemPrintFunc,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_TRAINER_LIST,
    .header_X = 0,
    .item_X = 10,
    .cursor_X = 0,
    .upText_Y = 4,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 7,
    .cursorKind = 0
};

// code for UI skeleton
static void TrainerRadar_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void TrainerRadar_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static bool8 TrainerRadar_InitBgs(void)
{
    ResetVramOamAndBgCntRegs();
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    
    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sTrainerRadarBgTemplates, NELEMS(sTrainerRadarBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT , 0);
    ShowBg(0);
    ShowBg(1);
    return TRUE;
}

static bool8 TrainerRadar_LoadGraphics(void)
{
    switch (sTrainerRadarPtr->state)
    {
    case 0:
        ResetTempTileDataBuffers();
        if (sTrainerRadarPtr->page == PAGE_MAIN)
            DecompressAndCopyTileDataToVram(1, sTrainerRadarMainBgGfx, 0, 0, 0);
        else
            DecompressAndCopyTileDataToVram(1, sTrainerRadarRouteBgGfx, 0, 0, 0);
        sTrainerRadarPtr->state++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            if (sTrainerRadarPtr->page == PAGE_MAIN)
                LZDecompressWram(sTrainerRadarMainBgMap, sBg1TilemapBuffer);
            else
                LZDecompressWram(sTrainerRadarRouteBgMap, sBg1TilemapBuffer);
            sTrainerRadarPtr->state++;
        }
        break;
    case 2:
        LoadCompressedPalette(sTrainerRadarBgPal, 0, BG_PLTT_ID(2));
        sTrainerRadarPtr->state++;
        break;
    default:
        sTrainerRadarPtr->state = 0;
        return TRUE;
    }
    
    return FALSE;
}

static void TrainerRadar_InitWindows(void)
{
    InitWindows(sTrainerRadarWinTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
}

static void TrainerRadarGuiFreeResources(void)
{
    Free(sTrainerRadarPtr);
    Free(sBg1TilemapBuffer);
    Free(sListMenuItems);
    Free(sItemNames);
    FreeAllWindowBuffers();
}

static void Task_TrainerRadarFadeAndExit(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        TrainerRadarRemoveScrollIndicatorArrows();
        DestroyListMenuTask(sTrainerRadarPtr->listTaskId, 0, 0);
        FreePokenavResources();
        SetMainCallback2(sTrainerRadarPtr->savedCallback);
        TrainerRadarGuiFreeResources();
        DestroyTask(taskId);
    }
}

static void TrainerRadarFadeAndExit(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_TrainerRadarFadeAndExit, 0);
    SetVBlankCallback(TrainerRadar_VBlankCB);
    SetMainCallback2(TrainerRadar_MainCB);
}

static void Task_TrainerRadarMain(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 listItem;

    if (IsSEPlaying())
        return;

    listItem = ListMenu_ProcessInput(sTrainerRadarPtr->listTaskId);
    ListMenuGetScrollAndRow(sTrainerRadarPtr->listTaskId, &sTrainerRadarPtr->scrollOffsetMain, &sTrainerRadarPtr->selectedRowMain);

    switch (listItem)
    {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_POKENAV_OFF);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            task->func = Task_TrainerRadarFadeAndExit;
            break;
        default:
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            sTrainerRadarPtr->page = PAGE_ROUTE;
            task->func = Task_TrainerRadarFadeAndChangePage;
            break;
    }
}

static void Task_TrainerRadarRoute(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 listItem;

    if (IsSEPlaying())
        return;

    listItem = ListMenu_ProcessInput(sTrainerRadarPtr->listTaskId);
    ListMenuGetScrollAndRow(sTrainerRadarPtr->listTaskId, &sTrainerRadarPtr->scrollOffsetRoute, &sTrainerRadarPtr->selectedRowRoute);

    switch (listItem)
    {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_POKENAV_OFF);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            sTrainerRadarPtr->page = PAGE_MAIN;
            task->func = Task_TrainerRadarFadeAndChangePage;
            break;
    }

    if (JOY_NEW(DPAD_LEFT))
    {
        s32 i;
        for (i = 0; i < MAIN_LIST_MENU_NUMBER_OF_ITEMS; i++)
        {
            if (sTrainerRadarMapsecs[i] == sTrainerRadarPtr->mapsec)
                break;
        }

        if (i-- < 0)
            i = MAIN_LIST_MENU_NUMBER_OF_ITEMS-1;
        
        sTrainerRadarPtr->mapsec = sTrainerRadarMapsecs[i];

        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        task->func = Task_TrainerRadarFadeAndChangePage;
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        s32 i;
        for (i = 0; i < MAIN_LIST_MENU_NUMBER_OF_ITEMS; i++)
        {
            if (sTrainerRadarMapsecs[i] == sTrainerRadarPtr->mapsec)
                break;
        }

        if (i++ > MAIN_LIST_MENU_NUMBER_OF_ITEMS-1)
            i = 0;
        
        sTrainerRadarPtr->mapsec = sTrainerRadarMapsecs[i];

        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        task->func = Task_TrainerRadarFadeAndChangePage;
    }
}

static bool8 TrainerRadar_DoGfxSetup(void)
{
    u8 taskId;

    switch (gMain.state)
    {
        case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 4:
        if (TrainerRadar_InitBgs())
        {
            sTrainerRadarPtr->state = 0;
            gMain.state++;
        }
        else
        {
            TrainerRadarFadeAndExit();
            return TRUE;
        }
        break;
    case 5:
        if (TrainerRadar_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 6:
        TrainerRadarBuildMainListMenuTemplate();
        gMain.state++;
        break;
    case 7:
        TrainerRadar_InitWindows();
        gMain.state++;
        break;
    case 8:
        PrintRightHeader();
        PrintLeftHeader();
        PrintInstructions();
        TrainerRadarAddMainScrollIndicatorArows();
        taskId = CreateTask(Task_TrainerRadarMainWaitFadeIn, 0);
        sTrainerRadarPtr->listTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);
        gMain.state++;
        break;
    case 9:
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 10:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(TrainerRadar_VBlankCB);
        SetMainCallback2(TrainerRadar_MainCB);
        return TRUE;
    }

    return FALSE;
}

static void TrainerRadar_RunSetup(void)
{
    while (!TrainerRadar_DoGfxSetup()) {}
}

static void InitTrainerRadar(MainCallback callback)
{
    u32 i;

    if ((sTrainerRadarPtr = AllocZeroed(sizeof(struct TrainerRadar))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sTrainerRadarPtr->state = 0;
    sTrainerRadarPtr->page = PAGE_MAIN;
    sTrainerRadarPtr->savedCallback = callback;
    sTrainerRadarPtr->mainScrollIndicatorsTaskId = TASK_NONE;
    sTrainerRadarPtr->routeScrollIndicatorsTaskId = TASK_NONE;
    sTrainerRadarPtr->listTaskId = TASK_NONE;
    sTrainerRadarPtr->trainerFrontPicSpriteId = 0xFF;
    sTrainerRadarPtr->trainerObjEventSpriteId = 0xFF;
    for (i = 0; i < PARTY_SIZE; i++)
        sTrainerRadarPtr->trainerPartySpriteIds[i] = 0xFF;

    SetMainCallback2(TrainerRadar_RunSetup);
}

void Task_OpenTrainerRadarFromStartMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitTrainerRadar(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

u32 PokeNavMenuTrainerRadarCallback(void)
{
    gSaveBlock2Ptr->startShortcut = 18; // MENU_ACTION_TRAINER_RADAR
    CreateTask(Task_OpenTrainerRadarFromPokenav, 0);
    return TRUE;
}

void Task_OpenTrainerRadarFromPokenav(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        InitTrainerRadar(CB2_InitPokeNav);
        DestroyTask(taskId);
    }
}

static void Task_TrainerRadarMainWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_TrainerRadarMain;
}

static void Task_TrainerRadarRouteWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_TrainerRadarRoute;
}

static void Task_TrainerRadarFadeAndChangePage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        TrainerRadarRemoveScrollIndicatorArrows();
        if (sTrainerRadarPtr->listTaskId != TASK_NONE)
        {
            if (sTrainerRadarPtr->page == PAGE_MAIN) // changed page in the previous frame, so destroy the other page's list menu
                DestroyListMenuTask(sTrainerRadarPtr->listTaskId, &sTrainerRadarPtr->scrollOffsetRoute, &sTrainerRadarPtr->selectedRowRoute);
            else
                DestroyListMenuTask(sTrainerRadarPtr->listTaskId, &sTrainerRadarPtr->scrollOffsetMain, &sTrainerRadarPtr->selectedRowMain);

            FillWindowPixelBuffer(WIN_TRAINER_LIST, PIXEL_FILL(0));
            FillWindowPixelBuffer(WIN_INSTRUCTIONS, PIXEL_FILL(0));
            FillWindowPixelBuffer(WIN_MAP_NAME, PIXEL_FILL(0));
            FillWindowPixelBuffer(WIN_TRAINER_NAME, PIXEL_FILL(0));
            CopyWindowToVram(WIN_TRAINER_LIST, 3);
            CopyWindowToVram(WIN_INSTRUCTIONS, 3);
            CopyWindowToVram(WIN_MAP_NAME, 3);
            CopyWindowToVram(WIN_TRAINER_NAME, 3);
		    PutWindowTilemap(WIN_TRAINER_LIST);
		    PutWindowTilemap(WIN_INSTRUCTIONS);
            PutWindowTilemap(WIN_MAP_NAME);
            PutWindowTilemap(WIN_TRAINER_NAME);

            sTrainerRadarPtr->listTaskId = TASK_NONE;
            Free(sListMenuItems);
            Free(sItemNames);
        }

        if (TrainerRadar_ReloadGraphics() == TRUE)
        {
            ScheduleBgCopyTilemapToVram(1);

            if (sTrainerRadarPtr->page == PAGE_MAIN)
            {
                DestroyPartyIcons();
                gTasks[taskId].func = Task_TrainerRadar_RedoMainGfxSetup;
            }
            else
            {
                gTasks[taskId].func = Task_TrainerRadar_RedoRouteGfxSetup;
            }
        }
    }
}

static void Task_TrainerRadar_RedoMainGfxSetup(u8 taskId)
{
    switch (sTrainerRadarPtr->state)
    {
        case 0:
            TrainerRadarBuildMainListMenuTemplate();
            sTrainerRadarPtr->state++;
            break;
        case 1:
            PrintRightHeader();
            PrintLeftHeader();
            PrintInstructions();
            sTrainerRadarPtr->state++;
            break;
        case 2:
            TrainerRadarAddMainScrollIndicatorArows();
            sTrainerRadarPtr->listTaskId = ListMenuInit(&gMultiuseListMenuTemplate, sTrainerRadarPtr->scrollOffsetMain, sTrainerRadarPtr->selectedRowMain);
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        case 3:
            PrintTrainerPic();
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        case 4:
            PrintTrainerOW();
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        default:
            sTrainerRadarPtr->state = 0;
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gTasks[taskId].func = Task_TrainerRadarMainWaitFadeIn;
            break;
    }
}

static void Task_TrainerRadar_RedoRouteGfxSetup(u8 taskId)
{
    switch (sTrainerRadarPtr->state)
    {
        case 0:
            sTrainerRadarPtr->scrollOffsetRoute = sTrainerRadarPtr->selectedRowRoute = 0;
            TrainerRadarBuildRouteListMenuTemplate();
            sTrainerRadarPtr->state++;
            break;
        case 1:
            PrintRightHeader();
            PrintLeftHeader();
            PrintInstructions();
            sTrainerRadarPtr->state++;
            break;
        case 2:
            TrainerRadarAddRouteScrollIndicatorArows();
            sTrainerRadarPtr->listTaskId = ListMenuInit(&gMultiuseListMenuTemplate, sTrainerRadarPtr->scrollOffsetRoute, sTrainerRadarPtr->selectedRowRoute);
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        case 3:
            PrintTrainerPic();
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        case 4:
            PrintTrainerOW();
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            sTrainerRadarPtr->state++;
            break;
        default:
            sTrainerRadarPtr->state = 0;
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gTasks[taskId].func = Task_TrainerRadarRouteWaitFadeIn;
            break;
    }
}

static bool8 TrainerRadar_ReloadGraphics(void)
{
    switch (sTrainerRadarPtr->state)
    {
    case 0:
        ResetTempTileDataBuffers();
        if (sTrainerRadarPtr->page == PAGE_MAIN)
            DecompressAndCopyTileDataToVram(1, sTrainerRadarMainBgGfx, 0, 0, 0);
        else
            DecompressAndCopyTileDataToVram(1, sTrainerRadarRouteBgGfx, 0, 0, 0);
        sTrainerRadarPtr->state++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            if (sTrainerRadarPtr->page == PAGE_MAIN)
                LZDecompressWram(sTrainerRadarMainBgMap, sBg1TilemapBuffer);
            else
                LZDecompressWram(sTrainerRadarRouteBgMap, sBg1TilemapBuffer);
            sTrainerRadarPtr->state++;
        }
        break;
    default:
        sTrainerRadarPtr->state = 0;
        return TRUE;
    }
    
    return FALSE;
}






static void TrainerRadarBuildMainListMenuTemplate(void)
{
    u32 i;
    sListMenuItems = Alloc(MAIN_LIST_MENU_NUMBER_OF_ITEMS * sizeof(*sListMenuItems));
    sItemNames = Alloc(MAIN_LIST_MENU_NUMBER_OF_ITEMS * sizeof(*sItemNames));

    for (i = 0; i < MAIN_LIST_MENU_NUMBER_OF_ITEMS; i++)
    {
        GetMapName(sItemNames[i], sTrainerRadarMapsecs[i], 0);
        sListMenuItems[i].name = sItemNames[i];
        sListMenuItems[i].id = sTrainerRadarMapsecs[i];
    }

    gMultiuseListMenuTemplate = sTrainerRadarMainMenuListTemplate;
    gMultiuseListMenuTemplate.items = sListMenuItems;
    gMultiuseListMenuTemplate.totalItems = MAIN_LIST_MENU_NUMBER_OF_ITEMS;

    if (gMultiuseListMenuTemplate.totalItems > 6)
        gMultiuseListMenuTemplate.maxShowed = 6;
    else
        gMultiuseListMenuTemplate.maxShowed = gMultiuseListMenuTemplate.totalItems;
}

static void TrainerRadarMainListMenuMoveCursorFunc(s32 listItem, bool8 onInit, struct ListMenu *list)
{
    const struct RouteTrainers* routeTrainersStruct;
    u16 trainerId;

    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    sTrainerRadarPtr->mapsec = listItem;
    routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];
    if (routeTrainersStruct->routeTrainers != NULL)
    {
        sTrainerRadarPtr->trainerId = GetTrainerOverride(routeTrainersStruct->routeTrainers[routeTrainersStruct->numTrainers - 1]);
        PrintVisualElements();
    }
}

static void TrainerRadarMainListMenuItemPrintFunc(u8 windowId, u32 listItem, u8 y)
{
    s32 x;
    u32 i;
    u8 numTrainers = 0;
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[listItem];

    // print number of defeated trainers on each route
    if (routeTrainersStruct->routeTrainers != NULL)
    {
        for (i = 0; i < routeTrainersStruct->numTrainers; i++)
        {
            if (HasTrainerBeenFought(GetTrainerOverride(routeTrainersStruct->routeTrainers[i])))
                numTrainers++;
        }

        ConvertIntToDecimalStringN(gStringVar1, numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar1,gText_Slash);
        ConvertIntToDecimalStringN(gStringVar2, routeTrainersStruct->numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
        StringAppend(gStringVar1,gStringVar2);
        x = GetStringRightAlignXOffset(7, gStringVar1, 144);

        if (numTrainers == routeTrainersStruct->numTrainers)
            AddTextPrinterParameterized4(windowId, 7, x, y, 0, 0, sFontColor_Green, TEXT_SKIP_DRAW, gStringVar1);
        else
            AddTextPrinterParameterized4(windowId, 7, x, y, 0, 0, sFontColor_Black, TEXT_SKIP_DRAW, gStringVar1);
    }
}

static const u8 sText_ColorRed[] = _("{COLOR_HIGHLIGHT_SHADOW RED TRANSPARENT LIGHT_RED}");
static const u8 sText_Rematch[] = _("{CLEAR_TO 0x0C}Rematch");
static const u8 sText_HiddenTrainer[] = _("???");
static void TrainerRadarBuildRouteListMenuTemplate(void)
{
    u32 i; // build listmenutemplate for the route page -> trainer name + highlight
    s32 rematchTableId;
    u16 trainerId;
    const struct RouteTrainers* routeTrainersStruct= &gRouteTrainers[sTrainerRadarPtr->mapsec];

    sListMenuItems = Alloc(routeTrainersStruct->numTrainers * sizeof(*sListMenuItems));
    sItemNames = Alloc(routeTrainersStruct->numTrainers * sizeof(*sItemNames));

    for (i = 0; i < routeTrainersStruct->numTrainers; i++)
    {
        trainerId = GetTrainerOverride(routeTrainersStruct->routeTrainers[i]);

        if (HasTrainerBeenFought(trainerId))
        {
            rematchTableId = TrainerIdToRematchTableId(gRematchTable, trainerId);
            if (rematchTableId != -1)
            {
                gTrainerBattleOpponent_A = trainerId;
                if (IsTrainerReadyForRematch())
                {
                    if (CountBattledRematchTeams(trainerId) == REMATCHES_COUNT)
                        StringCopy(sItemNames[i], gTrainers[trainerId].trainerName);
                    else
                    {
                        StringCopy(sItemNames[i], sText_ColorRed);
                        StringAppend(sItemNames[i], gTrainers[trainerId].trainerName);
                    }
                    StringAppend(sItemNames[i], sText_Rematch);
                }
                else
                    StringCopy(sItemNames[i], gTrainers[trainerId].trainerName);
            }
            else
                StringCopy(sItemNames[i], gTrainers[trainerId].trainerName);
        }
        else
        {
            StringCopy(sItemNames[i], sText_ColorRed);

            if (!FlagGet(FLAG_SYS_GAME_CLEAR))
                StringAppend(sItemNames[i], sText_HiddenTrainer);
            else if (gTrainers[trainerId].trainerClass == TRAINER_CLASS_RIVAL || gTrainers[trainerId].trainerClass == TRAINER_CLASS_LEADER
                || gTrainers[trainerId].trainerClass == TRAINER_CLASS_ELITE_FOUR || gTrainers[trainerId].trainerClass == TRAINER_CLASS_CHAMPION)
                StringAppend(sItemNames[i], sText_HiddenTrainer);
            else
                StringAppend(sItemNames[i], gTrainers[trainerId].trainerName);
        }
        
        sListMenuItems[i].name = sItemNames[i];
        sListMenuItems[i].id = trainerId;
    }

    gMultiuseListMenuTemplate = sTrainerRadarRouteMenuListTemplate;
    gMultiuseListMenuTemplate.items = sListMenuItems;
    gMultiuseListMenuTemplate.totalItems = routeTrainersStruct->numTrainers;

    if (gMultiuseListMenuTemplate.totalItems > 6)
        gMultiuseListMenuTemplate.maxShowed = 6;
    else
        gMultiuseListMenuTemplate.maxShowed = gMultiuseListMenuTemplate.totalItems;
}

static void TrainerRadarRouteListMenuMoveCursorFunc(s32 listItem, bool8 onInit, struct ListMenu *list)
{
    const struct RouteTrainers* routeTrainersStruct= &gRouteTrainers[sTrainerRadarPtr->mapsec]; // do stuff when moving cursor -> updating graphics

    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    sTrainerRadarPtr->trainerId = GetTrainerOverride(listItem);
    if (routeTrainersStruct->routeTrainers != NULL)
    {
        PrintVisualElements();
        PrintTrainerParty();
    }
}

static void TrainerRadarRouteListMenuItemPrintFunc(u8 windowId, u32 listItem, u8 y)
{
    // print stuff? nothing?
}

static void TrainerRadarAddMainScrollIndicatorArows(void)
{
    if (sTrainerRadarPtr->mainScrollIndicatorsTaskId == TASK_NONE && MAIN_LIST_MENU_NUMBER_OF_ITEMS > 6)
    {
        sTrainerRadarPtr->mainScrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            82,
            42,
            142,
            MAIN_LIST_MENU_NUMBER_OF_ITEMS - 6,
            TAG_SCROLL_ARROW,
            TAG_SCROLL_ARROW,
            &sTrainerRadarPtr->scrollOffsetMain
        );
    }
}

static void TrainerRadarAddRouteScrollIndicatorArows(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];
    
    if (sTrainerRadarPtr->routeScrollIndicatorsTaskId == TASK_NONE && routeTrainersStruct->numTrainers > 6)
    {
        sTrainerRadarPtr->routeScrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            52,
            42,
            142,
            routeTrainersStruct->numTrainers - 6,
            TAG_SCROLL_ARROW,
            TAG_SCROLL_ARROW,
            &sTrainerRadarPtr->scrollOffsetRoute
        );
    }
}

static void TrainerRadarRemoveScrollIndicatorArrows(void)
{
    if (sTrainerRadarPtr->mainScrollIndicatorsTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sTrainerRadarPtr->mainScrollIndicatorsTaskId);
        sTrainerRadarPtr->mainScrollIndicatorsTaskId = TASK_NONE;
    }

    if (sTrainerRadarPtr->routeScrollIndicatorsTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sTrainerRadarPtr->routeScrollIndicatorsTaskId);
        sTrainerRadarPtr->routeScrollIndicatorsTaskId = TASK_NONE;
    }
}

static void PrintVisualElements(void)
{
    PrintTrainerPic();
    PrintTrainerOW();
}

static void PrintTrainerPic(void)
{
    u16 trainerId = sTrainerRadarPtr->trainerId;
    s32 x = 132, y = 65;

    if (sTrainerRadarPtr->trainerFrontPicSpriteId != 0xFF)
        FreeAndDestroyTrainerPicSprite(sTrainerRadarPtr->trainerFrontPicSpriteId);

    if (sTrainerRadarPtr->page == PAGE_MAIN)
        x = 206;

    if (trainerId != TRAINER_NONE)
    {
        sTrainerRadarPtr->trainerFrontPicSpriteId = CreateTrainerPicSprite(gTrainers[trainerId].trainerPic, TRUE, x, y, 15, TAG_NONE);
        // slot 15 to avoid conflict with mon icon palettes

        if (!HasTrainerBeenFought(trainerId))
        {
            u16 paletteOffset = 15 * 16 + 0x100;
            BlendPalette(paletteOffset, 16, 16, RGB(5, 5, 5));
            CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
        }
    }
}

static void PrintTrainerOW(void)
{
    u16 trainerId = sTrainerRadarPtr->trainerId;
    s32 x = 140, y = 124;

    if (sTrainerRadarPtr->trainerObjEventSpriteId != 0xFF)
        DestroySpriteAndFreeResources(&gSprites[sTrainerRadarPtr->trainerObjEventSpriteId]);

    if (sTrainerRadarPtr->page == PAGE_MAIN)
        x = 214;
    
    if (trainerId != TRAINER_NONE)
    {
        sTrainerRadarPtr->trainerObjEventSpriteId = CreateObjectGraphicsSprite(sTrainerObjEventGfx[trainerId], SpriteCallbackDummy, x, y, 0);
        gSprites[sTrainerRadarPtr->trainerObjEventSpriteId].oam.priority = 0;
    
        if (!HasTrainerBeenFought(trainerId))
        {
            u16 paletteOffset = OBJ_PLTT_ID(gSprites[sTrainerRadarPtr->trainerObjEventSpriteId].oam.paletteNum);
            BlendPalette(paletteOffset, 16, 16, RGB(5, 5, 5));
            CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
        }
    }
}

static void PrintTrainerParty(void)
{
    u32 i;
    u16 species, trainerId = sTrainerRadarPtr->trainerId;
    u8 icon_x = 0, icon_y = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sTrainerRadarPtr->trainerPartySpriteIds[i] != 0xFF)
        {
            FreeAndDestroyMonIconSprite(&gSprites[sTrainerRadarPtr->trainerPartySpriteIds[i]]);
            sTrainerRadarPtr->trainerPartySpriteIds[i] = 0xFF;
        }
    }
    
    FreeMonIconPalettes();

    if (trainerId != TRAINER_NONE)
    {
        s32 rematchTableId = TrainerIdToRematchTableId(gRematchTable, trainerId);
        if (rematchTableId != -1)
        {
            gTrainerBattleOpponent_A = trainerId;
            if (IsTrainerReadyForRematch())
                trainerId = GetRematchTrainerIdFromTable(gRematchTable, trainerId);
        }

        LoadMonIconPalettes();
        for (i = 0; i < gTrainers[trainerId].partySize; i++)
        {
            icon_x = 188 + (i%2) * 35;
            icon_y = 43 + (i/2) * 35;

            species = HasTrainerBeenFought(trainerId) ? gTrainers[trainerId].party[i].species : SPECIES_NONE;
            sTrainerRadarPtr->trainerPartySpriteIds[i] = CreateMonIcon(species, SpriteCallbackDummy, icon_x, icon_y, 1, 0xFFFFFFFF);
        }
    }
}

static void DestroyPartyIcons(void)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sTrainerRadarPtr->trainerPartySpriteIds[i] != 0xFF)
        {
            FreeAndDestroyMonIconSprite(&gSprites[sTrainerRadarPtr->trainerPartySpriteIds[i]]);
            sTrainerRadarPtr->trainerPartySpriteIds[i] = 0xFF;
        }
    }
    
    FreeMonIconPalettes();
}

static void PrintRightHeader(void)
{
    if (sTrainerRadarPtr->page == PAGE_MAIN) //if main page, print UI name, else print map name
        StringCopy(gStringVar3, sText_TrainerDatabase);
    else
        GetMapName(gStringVar3, sTrainerRadarPtr->mapsec, 0);
    AddTextPrinterParameterized3(WIN_MAP_NAME, 1, 2, 7, sFontColor_White, 0, gStringVar3);
    CopyWindowToVram(WIN_MAP_NAME, 3);
    PutWindowTilemap(WIN_MAP_NAME);
}

static void PrintLeftHeader(void)
{
    u32 i, j, numTrainers = 0, numTrainersTotal = 0;
    s32 x;
    const struct RouteTrainers* routeTrainersStruct;

    if (sTrainerRadarPtr->page == PAGE_MAIN)
    {
        for (i = 0; i < MAIN_LIST_MENU_NUMBER_OF_ITEMS; i++)
        {
            routeTrainersStruct = &gRouteTrainers[sTrainerRadarMapsecs[i]];

            if (routeTrainersStruct->routeTrainers != NULL)
            {
                for (j = 0; j < routeTrainersStruct->numTrainers; j++)
                {
                    numTrainersTotal++;
                    if (HasTrainerBeenFought(GetTrainerOverride(routeTrainersStruct->routeTrainers[j])))
                        numTrainers++;
                }
            }
        }

        ConvertIntToDecimalStringN(gStringVar1, numTrainers, STR_CONV_MODE_LEADING_ZEROS, 3);
        StringAppend(gStringVar1,gText_Slash);
        ConvertIntToDecimalStringN(gStringVar2, numTrainersTotal, STR_CONV_MODE_LEADING_ZEROS, 3);
        StringAppend(gStringVar1,gStringVar2);
    }
    else
    {
        routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];
        
        if (routeTrainersStruct->routeTrainers != NULL)
        {
            for (i = 0; i < routeTrainersStruct->numTrainers; i++)
            {
                if (HasTrainerBeenFought(GetTrainerOverride(routeTrainersStruct->routeTrainers[i])))
                    numTrainers++;
            }

            ConvertIntToDecimalStringN(gStringVar1, numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
            StringAppend(gStringVar1,gText_Slash);
            ConvertIntToDecimalStringN(gStringVar2, routeTrainersStruct->numTrainers, STR_CONV_MODE_LEADING_ZEROS, 2);
            StringAppend(gStringVar1,gStringVar2);
        }
    }

    x = GetStringRightAlignXOffset(7, gStringVar1, 66);
    AddTextPrinterParameterized3(WIN_TRAINER_NAME, 1, x, 7, sFontColor_White, 0, gStringVar1);
    CopyWindowToVram(WIN_TRAINER_NAME, 3);
    PutWindowTilemap(WIN_TRAINER_NAME);
}

static void PrintInstructions(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];

    if (sTrainerRadarPtr->page == PAGE_MAIN)
    {
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsAreaMain);
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 166, 4, sFontColor_White, 0, sText_InstructionsSelectExit);
    }
    else
    {
        if (routeTrainersStruct->routeTrainers != NULL)
            AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsAreaTrainer);
        else
            AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsAreaRoute);
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 208, 4, sFontColor_White, 0, sText_InstructionsBack);
    }
    CopyWindowToVram(WIN_INSTRUCTIONS, 3);
    PutWindowTilemap(WIN_INSTRUCTIONS);
}

static u16 GetTrainerOverride(u16 trainerId)
{
    if (trainerId == TRAINER_RIVAL_OVERRIDE)
    {
        switch (VarGet(VAR_STARTER_MON))
        {
            case 0: //chose treecko
            {
                if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_103)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_103_TREECKO : TRAINER_BRENDAN_ROUTE_103_TREECKO;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_RUSTBORO_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_RUSTBORO_TREECKO : TRAINER_BRENDAN_RUSTBORO_TREECKO;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_110)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_110_TREECKO : TRAINER_BRENDAN_ROUTE_110_TREECKO;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_119)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_119_TREECKO : TRAINER_BRENDAN_ROUTE_119_TREECKO;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_LILYCOVE_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_LILYCOVE_TREECKO : TRAINER_BRENDAN_LILYCOVE_TREECKO;
            }
            case 1: //chose torchic
            {
                if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_103)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_103_TORCHIC : TRAINER_BRENDAN_ROUTE_103_TORCHIC;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_RUSTBORO_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_RUSTBORO_TORCHIC : TRAINER_BRENDAN_RUSTBORO_TORCHIC;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_110)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_110_TORCHIC : TRAINER_BRENDAN_ROUTE_110_TORCHIC;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_119)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_119_TORCHIC : TRAINER_BRENDAN_ROUTE_119_TORCHIC;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_LILYCOVE_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_LILYCOVE_TORCHIC : TRAINER_BRENDAN_LILYCOVE_TORCHIC;
            }
            case 2: //chose mudkip
            {
                if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_103)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_103_MUDKIP : TRAINER_BRENDAN_ROUTE_103_MUDKIP;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_RUSTBORO_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_RUSTBORO_MUDKIP : TRAINER_BRENDAN_RUSTBORO_MUDKIP;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_110)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_110_MUDKIP : TRAINER_BRENDAN_ROUTE_110_MUDKIP;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_ROUTE_119)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_ROUTE_119_MUDKIP : TRAINER_BRENDAN_ROUTE_119_MUDKIP;
                else if (sTrainerRadarPtr->mapsec == MAPSEC_LILYCOVE_CITY)
                    return (gSaveBlock2Ptr->playerGender == MALE) ? TRAINER_MAY_LILYCOVE_MUDKIP : TRAINER_BRENDAN_LILYCOVE_MUDKIP;
            }
        }
    }
    return trainerId;
}

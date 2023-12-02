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
    u8 scrollIndicatorsTaskId;
    u16 selectedRow;
    u16 scrollOffset;
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
static const u8 sText_InstructionsArea[] = _("{DPAD_LEFTRIGHT}Area");
static const u8 sText_InstructionsAreaTrainer[] = _("{DPAD_LEFTRIGHT}Area  {DPAD_UPDOWN}Trainer");
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
		.width = 12,
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
		.baseBlock = 258,
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
//static void ClearTasksAndGraphicalStructs(void);
//static void ClearVramOamPlttRegs(void);
static void Task_TrainerRadarFadeOut(u8 taskId);
static void Task_TrainerRadarMainWaitForKeyPress(u8 taskId);
static void Task_TrainerRadarRouteWaitForKeyPress(u8 taskId);
static void Task_TrainerRadarFadeIn(u8 taskId);
static void Task_TrainerRadarChangePage(u8 taskId);
static void Task_TrainerRadarWaitChangePage(u8 taskId);
static void InitTrainerRadarScreen(void);
static void CreateTrainerRadarCursor(void);

static void Task_TrainerRadarWaitFadeIn(u8 taskId);
static void Task_TrainerRadarFadeAndChangePage(u8 taskId);

static void TrainerRadarBuildMainListMenuTemplate(void);
static void TrainerRadarMainListMenuMoveCursorFunc(s32 listItem, bool8 onInit, struct ListMenu *list);
static void TrainerRadarAddScrollIndicatorArows(void);
static void TrainerRadarRemoveScrollIndicatorArrows(void);

// skin functions
static void UpdateTrainerRadarData(void);
static void UpdateTrainerRadarVisualElements(void);
static void PrintTrainerList(void);
static void PrintRightHeader(void);
static void PrintTrainerClass(void);
static void PrintTrainerPic(void);
static void PrintTrainerOW(void);
static void PrintTrainerParty(void);
static void PrintTrainerCount(void);
static void PrintInstructions(void);
static void TrainerRadar_CursorCallback(struct Sprite *sprite);

EWRAM_DATA static struct TrainerRadar *sTrainerRadarPtr = NULL;
EWRAM_DATA static u8 *sBg1TilemapBuffer = NULL;
EWRAM_DATA static struct ListMenuItem *sListMenuItems = NULL;
static EWRAM_DATA u8 (*sItemNames)[MAP_NAME_LENGTH + 2] = {0};

#define VISIBLE_CURSOR_MAX_VALUE 5 //6 slots - 1
#define MAIN_LIST_MENU_NUMBER_OF_ITEMS NELEMS(sTrainerRadarMapsecs)

#define SELECTION_CURSOR_TAG    0x4005
#define TAG_SCROLL_ARROW   2100
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

static const struct ListMenuTemplate sTrainerRadarMainMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = TrainerRadarMainListMenuMoveCursorFunc, // change trainer graphics
    .itemPrintFunc = NULL, //BuyMenuPrintPriceInList // print number of trainer defeated per route
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
        LoadCompressedPalette(sTrainerRadarBgPal, 0, 32/*BG_PLTT_ID(2)*/);
        //LoadPalette(sTrainerRadarBgPal, 0, 32);
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
    ListMenuGetScrollAndRow(sTrainerRadarPtr->listTaskId, &sTrainerRadarPtr->scrollOffset, &sTrainerRadarPtr->selectedRow);

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_POKENAV_OFF);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        task->func = Task_TrainerRadarFadeAndExit;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        sTrainerRadarPtr->page ^= 1;
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
        TrainerRadarAddScrollIndicatorArows();
        taskId = CreateTask(Task_TrainerRadarWaitFadeIn, 0);
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
    if ((sTrainerRadarPtr = AllocZeroed(sizeof(struct TrainerRadar))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sTrainerRadarPtr->state = 0;
    sTrainerRadarPtr->page = PAGE_MAIN;
    sTrainerRadarPtr->savedCallback = callback;
    sTrainerRadarPtr->scrollIndicatorsTaskId = TASK_NONE;
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

static void Task_TrainerRadarWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_TrainerRadarMain;
}

static void Task_TrainerRadarFadeAndChangePage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (TrainerRadar_LoadGraphics() == TRUE)
        {
            ScheduleBgCopyTilemapToVram(1);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gTasks[taskId].func = Task_TrainerRadarWaitFadeIn;
        }
            
    }
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
        sListMenuItems[i].id = i;
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
    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    // print trainer graphics
}

static void TrainerRadarAddScrollIndicatorArows(void)
{
    if (sTrainerRadarPtr->scrollIndicatorsTaskId == TASK_NONE && MAIN_LIST_MENU_NUMBER_OF_ITEMS > 6)
    {
        sTrainerRadarPtr->scrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            82,
            42,
            142,
            MAIN_LIST_MENU_NUMBER_OF_ITEMS - 6,
            TAG_SCROLL_ARROW,
            TAG_SCROLL_ARROW,
            &sTrainerRadarPtr->scrollOffset
        );
    }
}

static void TrainerRadarRemoveScrollIndicatorArrows(void)
{
    if (sTrainerRadarPtr->scrollIndicatorsTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sTrainerRadarPtr->scrollIndicatorsTaskId);
        sTrainerRadarPtr->scrollIndicatorsTaskId = TASK_NONE;
    }
}



/*static void VBlankCB_TrainerRadar(void)
{
	LoadOam();
	ProcessSpriteCopyRequests();
	TransferPlttBuffer();
}*/

/*void CB2_TrainerRadar(void)
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
            sTrainerRadarPtr->tilemapPtr = AllocZeroed(BG_SCREEN_SIZE);
            sBg1TilemapBuffer = Alloc(0x800);
            memset(sBg1TilemapBuffer, 0, 0x800);
            ResetBgsAndClearDma3BusyFlags(0);
            
            InitBgsFromTemplates(0, sTrainerRadarBgTemplates, 3);
            SetBgTilemapBuffer(1, sBg1TilemapBuffer);
            SetBgTilemapBuffer(2, sTrainerRadarPtr->tilemapPtr);
            ScheduleBgCopyTilemapToVram(1);
            ScheduleBgCopyTilemapToVram(2);
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
                CopyBgTilemapBufferToVram(1);
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
}*/

/*static void Task_TrainerRadarFadeOut(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        SetMainCallback2(sTrainerRadarPtr->savedCallback);
        Free(sBg1TilemapBuffer);
		Free(sTrainerRadarPtr->tilemapPtr);
		Free(sTrainerRadarPtr);
        sTrainerRadarPtr = NULL;
		FreeAllWindowBuffers();
		DestroyTask(taskId);
	}
}

static void Task_TrainerRadarMainWaitForKeyPress(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarFadeOut;
        SetVBlankCallback(VBlankCB_TrainerRadar);
        SetMainCallback2(MainCB2_TrainerRadar);
    }
    else if(JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        sTrainerRadarPtr->page = PAGE_ROUTE;
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarChangePage;
    }
}

static void Task_TrainerRadarRouteWaitForKeyPress(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);

        sTrainerRadarPtr->page = PAGE_MAIN;
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarChangePage;
    }
    else if (JOY_NEW(DPAD_DOWN) && sTrainerRadarPtr->numOfTrainers != 0) // move cursors down
    {
        PlaySE(SE_SELECT);
        if (sTrainerRadarPtr->absoluteCursorPosition < sTrainerRadarPtr->numOfTrainers-1)
        {
            sTrainerRadarPtr->absoluteCursorPosition++;
            if (sTrainerRadarPtr->visibleCursorPosition < VISIBLE_CURSOR_MAX_VALUE)
                sTrainerRadarPtr->visibleCursorPosition++;
        }
        else
            sTrainerRadarPtr->visibleCursorPosition = sTrainerRadarPtr->absoluteCursorPosition = 0;
        
        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }    
    else if (JOY_NEW(DPAD_UP) && sTrainerRadarPtr->numOfTrainers != 0) // move cursors up
    {
        PlaySE(SE_SELECT);
        if (sTrainerRadarPtr->absoluteCursorPosition > 0)
        {
            sTrainerRadarPtr->absoluteCursorPosition--;
            if (sTrainerRadarPtr->visibleCursorPosition > 0)
                sTrainerRadarPtr->visibleCursorPosition--;
        }
        else
        {
            sTrainerRadarPtr->absoluteCursorPosition = sTrainerRadarPtr->numOfTrainers-1;
            sTrainerRadarPtr->visibleCursorPosition = VISIBLE_CURSOR_MAX_VALUE;
            if (sTrainerRadarPtr->numOfTrainers-1 < VISIBLE_CURSOR_MAX_VALUE)
                sTrainerRadarPtr->visibleCursorPosition = sTrainerRadarPtr->numOfTrainers-1;
        }

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        PlaySE(SE_SELECT);
        sTrainerRadarPtr->visibleCursorPosition = sTrainerRadarPtr->absoluteCursorPosition = 0;

        if (sTrainerRadarPtr->mapsec > MAPSEC_LITTLEROOT_TOWN)
            sTrainerRadarPtr->mapsec--;
        else
            sTrainerRadarPtr->mapsec = MAPSEC_NONE-1;
    
        // skip over kanto mapsecs & MAPSEC_SECRET_BASE & MAPSEC_DYNAMIC
        if (sTrainerRadarPtr->mapsec >= MAPSEC_SECRET_BASE && sTrainerRadarPtr->mapsec <= KANTO_MAPSEC_END)
            sTrainerRadarPtr->mapsec = MAPSEC_SECRET_BASE - 1;

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        sTrainerRadarPtr->visibleCursorPosition = sTrainerRadarPtr->absoluteCursorPosition = 0;

        if (sTrainerRadarPtr->mapsec < MAPSEC_NONE-1)
            sTrainerRadarPtr->mapsec++;
        else
            sTrainerRadarPtr->mapsec = MAPSEC_LITTLEROOT_TOWN;

        // skip over kanto mapsecs & MAPSEC_SECRET_BASE & MAPSEC_DYNAMIC
        if (sTrainerRadarPtr->mapsec >= MAPSEC_SECRET_BASE && sTrainerRadarPtr->mapsec <= KANTO_MAPSEC_END)
            sTrainerRadarPtr->mapsec = KANTO_MAPSEC_END + 1;

        UpdateTrainerRadarData();
        UpdateTrainerRadarVisualElements();
    }
}

static void Task_TrainerRadarFadeIn(u8 taskId)
{
	if (!gPaletteFade.active)
	{
        PlaySE(SE_RG_CARD_OPEN);
        if (sTrainerRadarPtr->page == PAGE_MAIN)
            gTasks[taskId].func = Task_TrainerRadarMainWaitForKeyPress;
        else
    		gTasks[taskId].func = Task_TrainerRadarRouteWaitForKeyPress;
	}
}

static void Task_TrainerRadarChangePage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        ScheduleBgCopyTilemapToVram(2);
        LoadTrainerRadarGfx();
        gTasks[taskId].func = Task_TrainerRadarWaitChangePage;
    }
}

static void Task_TrainerRadarWaitChangePage(u8 taskId)
{
    if (IsDma3ManagerBusyWithBgCopy() != TRUE)
    {
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gTasks[taskId].func = Task_TrainerRadarFadeIn;
    }
}*/

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
    sTrainerRadarPtr->mapsec = MAPSEC_ROUTE_103;//GetCurrentRegionMapSectionId();
    sTrainerRadarPtr->visibleCursorPosition = 0;
    sTrainerRadarPtr->absoluteCursorPosition = 0;
    sTrainerRadarPtr->trainerFrontPicSpriteId = 0xFF;
    sTrainerRadarPtr->trainerObjEventSpriteId = 0xFF;
    for (i = 0; i < PARTY_SIZE; i++)
        sTrainerRadarPtr->trainerPartySpriteIds[i]=0xFF;
    
    UpdateTrainerRadarData();
    CreateTrainerRadarCursor();

    UpdateTrainerRadarVisualElements();
}

static void LoadTrainerRadarGfx(void)
{	
    if (sTrainerRadarPtr->page == PAGE_MAIN)
    {
        DecompressAndCopyTileDataToVram(2, &sTrainerRadarMainBgGfx, 0, 0, 0);
	    LZDecompressWram(sTrainerRadarMainBgMap, sTrainerRadarPtr->tilemapPtr);
    }
    else
    {
        DecompressAndCopyTileDataToVram(2, &sTrainerRadarRouteBgGfx, 0, 0, 0);
	    LZDecompressWram(sTrainerRadarRouteBgMap, sTrainerRadarPtr->tilemapPtr);
    }
    LoadCompressedPalette(sTrainerRadarBgPal, 0, BG_PLTT_ID(2));
    ListMenuLoadStdPalAt(BG_PLTT_ID(12), 1);
    LoadPalette(&gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
}

/*static void ClearTasksAndGraphicalStructs(void)
{
	ScanlineEffect_Stop();
	ResetTasks();
	ResetSpriteData();
	ResetTempTileDataBuffers();
	ResetPaletteFade();
	FreeAllSpritePalettes();
}*/

/*static void ClearVramOamPlttRegs(void)
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
}*/



























static void CreateTrainerRadarCursor(void)
{
    u8 spriteId;
    struct CompressedSpriteSheet spriteSheet;
    
    spriteSheet.data = sSelectionCursorGfx;
    spriteSheet.size = 0x200;
    spriteSheet.tag = SELECTION_CURSOR_TAG;
    LoadCompressedSpriteSheet(&spriteSheet);
    
    LoadPalette(sSelectionCursorPal, (16 * sSelectionCursorOam.paletteNum) + 0x100, 32);
    
    spriteId = CreateSprite(&sSelectionCursorSpriteTemplate, 11, 52 + sTrainerRadarPtr->visibleCursorPosition * 16, 0);
}

// code for the UI purpose
static void UpdateTrainerRadarData(void)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];
    
    if (routeTrainersStruct->routeTrainers != NULL)
    {
        sTrainerRadarPtr->trainerId = routeTrainersStruct->routeTrainers[sTrainerRadarPtr->absoluteCursorPosition];
        sTrainerRadarPtr->numOfTrainers = routeTrainersStruct->numTrainers;
    }
    else
    {
        sTrainerRadarPtr->trainerId = TRAINER_NONE;
        sTrainerRadarPtr->numOfTrainers = 0;
    }
}

static void UpdateTrainerRadarVisualElements(void)
{
    CleanWindows();
    PrintTrainerList();
    PrintRightHeader();
    PrintTrainerClass();
    PrintTrainerPic();
    PrintTrainerOW();
    
    if (sTrainerRadarPtr->page == PAGE_ROUTE)
        PrintTrainerParty();
    
    PrintTrainerCount();
    PrintInstructions();
    CommitWindows();
}

static void PrintTrainerList(void)
{
    u32 i, maxSeen = VISIBLE_CURSOR_MAX_VALUE+1;
    u16 trainerNum;
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
    {
        if (routeTrainersStruct->numTrainers < maxSeen)
            maxSeen = routeTrainersStruct->numTrainers;

        for (i = 0; i < maxSeen; i++)
        {
            trainerNum = routeTrainersStruct->routeTrainers[i+sTrainerRadarPtr->absoluteCursorPosition-sTrainerRadarPtr->visibleCursorPosition];
            if (HasTrainerBeenFought(trainerNum))
                AddTextPrinterParameterized3(WIN_TRAINER_LIST, 1, 8, 4 + i*16, sFontColor_Black, 0, gTrainers[trainerNum].trainerName);
            else
                AddTextPrinterParameterized3(WIN_TRAINER_LIST, 1, 8, 4 + i*16, sFontColor_Red, 0, gTrainers[trainerNum].trainerName);
        }
        CopyWindowToVram(WIN_TRAINER_LIST, 3);
    }
}

static void PrintRightHeader(void)
{
    if (sTrainerRadarPtr->page == PAGE_MAIN) //if main page, print UI name, else print map name
        StringCopy(gStringVar3, sText_TrainerDatabase);
    else
        GetMapName(gStringVar3, sTrainerRadarPtr->mapsec, 0);
    AddTextPrinterParameterized3(WIN_MAP_NAME, 1, 2, 7, sFontColor_White, 0, gStringVar3);
    CopyWindowToVram(WIN_MAP_NAME, 3);
}

static void PrintTrainerClass(void) // if main page, print total trainer defeated, else print trainer class
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
    {
        StringCopy(gStringVar1, gTrainerClassNames[gTrainers[sTrainerRadarPtr->trainerId].trainerClass]);
        AddTextPrinterParameterized3(WIN_TRAINER_NAME, 1, 2, 7, sFontColor_White, 0, gStringVar1);
        CopyWindowToVram(WIN_TRAINER_NAME, 3);
    }
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

        /*if (!HasTrainerBeenFought(sTrainerRadarPtr->trainerId))
        {
            u16 paletteOffset = 15 * 16 + 0x100;
            BlendPalette(paletteOffset, 16, 16, RGB(5, 5, 5));
            CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, 32);
        }*/
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
        sTrainerRadarPtr->trainerObjEventSpriteId = CreateObjectGraphicsSprite(sTrainerObjEventGfx[trainerId], SpriteCallbackDummy, x, y, 0);
}

static void PrintTrainerParty(void)
{
    u32 i;
    u16 species, trainerId = sTrainerRadarPtr->trainerId;
    u8 icon_x = 0, icon_y = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sTrainerRadarPtr->trainerPartySpriteIds[i] != 0xFF)
            FreeAndDestroyMonIconSprite(&gSprites[sTrainerRadarPtr->trainerPartySpriteIds[i]]);
    }
    
    FreeMonIconPalettes();

    if (trainerId != TRAINER_NONE)
    {
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

static void PrintTrainerCount(void)
{
    u32 i;
    u8 numTrainers = 0;
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];

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
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];

    if (routeTrainersStruct->routeTrainers != NULL)
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsAreaTrainer);
    else
        AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 5, 4, sFontColor_White, 0, sText_InstructionsArea);

    AddTextPrinterParameterized3(WIN_INSTRUCTIONS, 0, 208, 4, sFontColor_White, 0, sText_InstructionsExit);
    CopyWindowToVram(WIN_INSTRUCTIONS, 3);
}

static void TrainerRadar_CursorCallback(struct Sprite *sprite)
{
    const struct RouteTrainers* routeTrainersStruct = &gRouteTrainers[sTrainerRadarPtr->mapsec];
    
    if (routeTrainersStruct->routeTrainers != NULL)
        sprite->invisible = FALSE;
    else
        sprite->invisible = TRUE;
        
    sprite->y = 52 + sTrainerRadarPtr->visibleCursorPosition * 16;
}

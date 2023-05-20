#include "global.h"
#include "option_menu.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"

#define Y_DIFF 16 // Difference in pixels between items.

enum // pages
{
    PAGE_KEY,
    PAGE_OPTIONS,
    PAGE_RANDOMIZER,
    PAGE_COUNT,
};

enum // standard options
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_FASTFIELDMOVE,
    MENUITEM_LEVELCAP,
    MENUITEM_TYPECHART,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

enum // key options
{
    MENUITEM_KEY_LVLCAP,
    MENUITEM_KEY_BASESTATSEQ,
    MENUITEM_KEY_CANCEL,
    MENUITEM_KEY_COUNT,
};

enum // randomizer options
{
    MENUITEM_RAND_RANDOMNESS_TYPE,
    MENUITEM_RAND_WILDENCOUNTERS,
    MENUITEM_RAND_CANCEL,
    MENUITEM_RAND_COUNT,
};

enum
{
    WIN_HEADER,
    WIN_OPTIONS
};

struct OptionMenu
{
    u8 sel[MENUITEM_COUNT];
    u8 selKey[MENUITEM_KEY_COUNT];
    u8 selRand[MENUITEM_RAND_COUNT];
    int menuCursor;
    int visibleCursor;
    u8 page;
};

static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void HighlightOptionMenuItem(int selection);
static u8 TextSpeed_ProcessInput(u8 selection);
void TextSpeed_DrawChoices(int selection, int y, u8 textSpeed);
static u8 BattleScene_ProcessInput(u8 selection);
void BattleScene_DrawChoices(int selection, int y, u8 textSpeed);
static u8 BattleStyle_ProcessInput(u8 selection);
void BattleStyle_DrawChoices(int selection, int y, u8 textSpeed);
int Sound_ProcessInput(int selection);
void Sound_DrawChoices(int selection, int y, u8 textSpeed);
int FrameType_ProcessInput(int selection);
void FrameType_DrawChoices(int selection, int y, u8 textSpeed);
static u8 ButtonMode_ProcessInput(u8 selection);
void ButtonMode_DrawChoices(int selection, int y, u8 textSpeed);
static void DrawHeaderText(void);
static void DrawOptionMenuTexts(void);
static void DrawBgWindowFrames(void);
static int FourOptions_ProcessInput(int selection);
static int ThreeOptions_ProcessInput(int selection);
static int TwoOptions_ProcessInput(int selection);
void FastFieldMove_DrawChoices(int selection, int y, u8 textSpeed);
void LevelCap_DrawChoices(int selection, int y, u8 textSpeed);
void TypeChart_DrawChoices(int selection, int y, u8 textSpeed);
void BaseStatEq_DrawChoices(int selection, int y, u8 textSpeed);

struct
{
    void (*drawChoices)(int selection, int y, u8 textSpeed);
    int (*processInput)(int selection);
} static const sOptionsItemFunctions[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED] = {TextSpeed_DrawChoices, FourOptions_ProcessInput},
    [MENUITEM_BATTLESCENE] = {BattleScene_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_BATTLESTYLE] = {BattleStyle_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_FASTFIELDMOVE] = {FastFieldMove_DrawChoices,TwoOptions_ProcessInput},
    [MENUITEM_LEVELCAP] = {LevelCap_DrawChoices,ThreeOptions_ProcessInput},
    [MENUITEM_TYPECHART] = {TypeChart_DrawChoices,TwoOptions_ProcessInput},
    [MENUITEM_SOUND] = {Sound_DrawChoices, Sound_ProcessInput},
    [MENUITEM_BUTTONMODE] = {ButtonMode_DrawChoices, ThreeOptions_ProcessInput},
    [MENUITEM_FRAMETYPE] = {FrameType_DrawChoices, FrameType_ProcessInput},
    [MENUITEM_CANCEL] = {NULL, NULL},
};

struct
{
    void (*drawChoices)(int selection, int y, u8 textSpeed);
    int (*processInput)(int selection);
} static const sKeyItemFunctions[MENUITEM_KEY_COUNT] =
{
    [MENUITEM_KEY_LVLCAP] = {LevelCap_DrawChoices, ThreeOptions_ProcessInput},
    [MENUITEM_KEY_BASESTATSEQ] = {BaseStatEq_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_KEY_CANCEL] = {NULL, NULL},
};

struct
{
    void (*drawChoices)(int selection, int y, u8 textSpeed);
    int (*processInput)(int selection);
} static const sRandItemFunctions[MENUITEM_RAND_COUNT] =
{
    [MENUITEM_RAND_RANDOMNESS_TYPE] = {BattleScene_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_RAND_WILDENCOUNTERS] = {BattleScene_DrawChoices, TwoOptions_ProcessInput},
    [MENUITEM_RAND_CANCEL] = {NULL, NULL},
};

// EWRAM vars
EWRAM_DATA static struct OptionMenu *sOptions = NULL;
EWRAM_DATA static bool8 sArrowPressed = FALSE;

static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text.gbapal");
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp");
static const u8 sText_PageKeyOptions[] = _("Key options");
static const u8 sText_PageStandardOptions[] = _("Standard options");
static const u8 sText_PageRandomOptions[] = _("Random options");

static const u8 sText_LevelCap[] = _("Level caps");
static const u8 sText_TypeChart[] = _("Type chart");
static const u8 sText_FastFieldMove[] = _("Fast field move");
static const u8 sText_BaseStats[] = _("Base stats");
static const u8 sText_Seeding[] = _("RNG seeding");
static const u8 sText_WildEncounters[] = _("Wild encounters");
static const u8 sText_Off[]= _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Off");
static const u8 sText_Soft[]= _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Soft");
static const u8 sText_Strict[]= _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Strict");
static const u8 sText_Default[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Default");
static const u8 sText_Equal[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}Equal");

static const u8 *const sTextSpeedStrings[] = {gText_TextSpeedSlow, gText_TextSpeedMid, gText_TextSpeedFast, gText_TextSpeedInstant};
static const u8 *const sLevelCapStrings[] = {sText_Off, sText_Soft, sText_Strict};
static const u8 *const sBaseStatEqStrings[] = {sText_Default, sText_Equal};

static const u8 *const sOptionMenuPageNames[PAGE_COUNT] = 
{
    [PAGE_KEY] = sText_PageKeyOptions,
    [PAGE_OPTIONS] = sText_PageStandardOptions,
    [PAGE_RANDOMIZER] = sText_PageRandomOptions,
};

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_FASTFIELDMOVE] = sText_FastFieldMove,
    [MENUITEM_LEVELCAP]     = sText_LevelCap,
    [MENUITEM_TYPECHART]    = sText_TypeChart,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};

static const u8 *const sOptionMenuKeyItemsNames[MENUITEM_KEY_COUNT] = 
{
    [MENUITEM_KEY_LVLCAP] = sText_LevelCap,
    [MENUITEM_KEY_BASESTATSEQ] = sText_BaseStats,
    [MENUITEM_KEY_CANCEL] = gText_OptionMenuCancel,
};

static const u8 *const sOptionMenuRandomizerItemsNames[MENUITEM_RAND_COUNT] = 
{
    [MENUITEM_RAND_RANDOMNESS_TYPE] = sText_Seeding,
    [MENUITEM_RAND_WILDENCOUNTERS] = sText_WildEncounters,
    [MENUITEM_RAND_CANCEL] = gText_OptionMenuCancel,
};

/*autorun
textspeed
battlestyle
battlescene
battlebars
show type effectiveness
type icons in battle
sound
low health beeps
surf/bike music
fishing style
fast egg hatch
fast evo scene
fast field move
frlg item anim
font 
unit system
frame
cancel*/

/*version
diff
nuzlocke
no free heals
exp team mod
exp multiplier
level cap
party size limit
type chart
eq base stats
mirror parties
evolve trainer mon
scale trainer level
prevent evolution*/

/*randomness type
wild encounters
static encounters
trainer parties
starters
abilities
lvl up moves
tm moves
tutor moves
relearner moves
post evo species
pokemon levels
player party
evo every level
items
held items
marts
music*/

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void DrawChoices(u32 id, int y, u8 textSpeed)
{
    switch (sOptions->page)
    {
    /*case PAGE_KEY:
        if (sKeyItemFunctions[id].drawChoices != NULL)
            sKeyItemFunctions[id].drawChoices(sOptions->selKey[id], y, textSpeed);
        break;*/
    default:
        if (sOptionsItemFunctions[id].drawChoices != NULL)
            sOptionsItemFunctions[id].drawChoices(sOptions->sel[id], y, textSpeed);
        break;
    }
}

void CB2_InitOptionMenu(void)
{
    u32 i, taskId;
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ResetBgPositions();
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        sOptions = AllocZeroed(sizeof(*sOptions));
        sOptions->page = 1;
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 10:
        taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        //sOptions = AllocZeroed(sizeof(*sOptions));
        //sOptions->page = 1;
        sOptions->sel[MENUITEM_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
        sOptions->sel[MENUITEM_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
        sOptions->sel[MENUITEM_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
        sOptions->sel[MENUITEM_FASTFIELDMOVE] = gSaveBlock2Ptr->optionsFastFieldMove;
        sOptions->sel[MENUITEM_LEVELCAP] = gSaveBlock2Ptr->optionsLevelCap;
        sOptions->sel[MENUITEM_TYPECHART] = gSaveBlock2Ptr->optionsTypeChart;
        sOptions->sel[MENUITEM_SOUND] = gSaveBlock2Ptr->optionsSound;
        sOptions->sel[MENUITEM_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
        sOptions->sel[MENUITEM_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;

        sOptions->selKey[MENUITEM_KEY_LVLCAP] = gSaveBlock2Ptr->optionsLevelCap;
        sOptions->selKey[MENUITEM_KEY_BASESTATSEQ] = gSaveBlock2Ptr->optionsBaseStatsEqual;

        sOptions->selRand[MENUITEM_RAND_RANDOMNESS_TYPE] = gSaveBlock2Ptr->optionsRandomnessType;
        sOptions->selRand[MENUITEM_RAND_WILDENCOUNTERS] = gSaveBlock2Ptr->randomWildEncounters;

        for (i = 0; i < 7; i++)
            DrawChoices(i, i * Y_DIFF, 0xFF);
        HighlightOptionMenuItem(sOptions->menuCursor);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void ScrollMenu(int direction)
{
    int menuItem, pos;
    const u8* const* menu = NULL;

    
    switch (sOptions->page)
    {
    case PAGE_OPTIONS:
        menu = sOptionMenuItemsNames;
        break;
    case PAGE_KEY:
        menu = sOptionMenuKeyItemsNames;
        break;
    case PAGE_RANDOMIZER:
        menu = sOptionMenuRandomizerItemsNames;
        break;
    }

    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor + 3, pos = 6;
    else
        menuItem = sOptions->menuCursor - 3, pos = 0;

    // Hide one
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF, PIXEL_FILL(0));
    // Show one
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, Y_DIFF * pos, 26 * 8, Y_DIFF);
    // Print
    DrawChoices(menuItem, pos * Y_DIFF, 0xFF);
    AddTextPrinterParameterized(WIN_OPTIONS, 1, menu[menuItem], 8, (pos * Y_DIFF) + 1, 0xFF, NULL);
    CopyWindowToVram(WIN_OPTIONS, 2);
}

static void ScrollAll(int direction) // to bottom or top
{
    int i, y, menuItem, pos;
    int scrollCount;
    u8 items;
    const u8* const* menu = NULL;

    
    switch (sOptions->page)
    {
    case PAGE_OPTIONS:
        items = MENUITEM_COUNT;
        menu = sOptionMenuItemsNames;
        break;
    case PAGE_KEY:
        items = MENUITEM_KEY_COUNT;
        menu = sOptionMenuKeyItemsNames;
        break;
    case PAGE_RANDOMIZER:
        items = MENUITEM_RAND_COUNT;
        menu = sOptionMenuRandomizerItemsNames;
        break;
    }

    scrollCount = items-7;
    // Move items up/down
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF * scrollCount, PIXEL_FILL(0));

    // Clear moved items
    if (direction == 0)
    {
        y = 7 - scrollCount;
        if (y < 0)
            y = 7;
        y *= Y_DIFF;
    }
    else
    {
        y = 0;
    }

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, y, 26 * 8, Y_DIFF * scrollCount);
    // Print new texts
    for (i = 0; i < scrollCount; i++)
    {
        if (direction == 0) // From top to bottom
            menuItem = items - 1 - i, pos = 6 - i;
        else // From bottom to top
            menuItem = i, pos = i;
        DrawChoices(menuItem, pos * Y_DIFF, 0xFF);
        AddTextPrinterParameterized(WIN_OPTIONS, 1, menu[menuItem], 8, (pos * Y_DIFF) + 1, 0xFF, NULL);
    }
    CopyWindowToVram(WIN_OPTIONS, 2);
}

static u8 Process_ChangePage(u8 CurrentPage)
{
    if (JOY_NEW(R_BUTTON))
    {
        if (CurrentPage < PAGE_COUNT - 1)
            CurrentPage++;
        else
            CurrentPage = 0;
    }
    if (JOY_NEW(L_BUTTON))
    {
        if (CurrentPage != 0)
            CurrentPage--;
        else
            CurrentPage = PAGE_COUNT - 1;
    }
    return CurrentPage;
}

static void Task_ChangePage(u8 taskId)
{
    u32 i;

    DrawHeaderText();
    PutWindowTilemap(WIN_OPTIONS);
    DrawOptionMenuTexts();

    sOptions->visibleCursor = sOptions->menuCursor = 0;
    for (i = 0; i < 7; i++)
        DrawChoices(i, i * Y_DIFF, 0xFF);
    HighlightOptionMenuItem(sOptions->menuCursor);

    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
    gTasks[taskId].func = Task_OptionMenuFadeIn;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    int i, scrollCount = 0, itemsToRedraw;
    u8 maxItems;

    switch (sOptions->page)
    {
    case PAGE_KEY:
        maxItems = MENUITEM_KEY_COUNT;
        break;
    case PAGE_OPTIONS:
        maxItems = MENUITEM_COUNT;
        break;
    case PAGE_RANDOMIZER:
        maxItems = MENUITEM_RAND_COUNT;
        break;
    }

    if (JOY_NEW(L_BUTTON) || JOY_NEW(R_BUTTON))
    {
        FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
        ClearStdWindowAndFrame(WIN_OPTIONS, FALSE);
        sOptions->page = Process_ChangePage(sOptions->page);
//        DrawHeaderText();
        gTasks[taskId].func = Task_ChangePage;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        if (sOptions->menuCursor == maxItems-1)
            gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (sOptions->visibleCursor == 3) // don't advance visible cursor until scrolled to the bottom
        {
            if (--sOptions->menuCursor == sOptions->visibleCursor - 1)
                sOptions->visibleCursor--;
            else
                ScrollMenu(1);
        }
        else
        {
            if (--sOptions->menuCursor < 0) // Scroll all the way to the bottom.
            {
                sOptions->visibleCursor = sOptions->menuCursor = 3;
                ScrollAll(0);
                sOptions->visibleCursor = 6;
                sOptions->menuCursor = maxItems - 1;
            }
            else
            {
                sOptions->visibleCursor--;
            }
        }
        HighlightOptionMenuItem(sOptions->visibleCursor);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (sOptions->visibleCursor == 3) // don't advance visible cursor until scrolled to the bottom
        {
            if (++sOptions->menuCursor == maxItems - 3)
                sOptions->visibleCursor++;
            else
                ScrollMenu(0);
        }
        else
        {
            if (++sOptions->menuCursor >= maxItems) // Scroll all the way to the tom.
            {
                sOptions->visibleCursor = 3;
                sOptions->menuCursor = maxItems - 4;
                ScrollAll(1);
                sOptions->visibleCursor = sOptions->menuCursor = 0;
            }
            else
            {
                sOptions->visibleCursor++;
            }
        }
        HighlightOptionMenuItem(sOptions->visibleCursor);
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        int cursor = sOptions->menuCursor;
        u8 previousOption;

        switch(sOptions->page)
        {
        case PAGE_KEY:
            previousOption = sOptions->selKey[cursor];
            if (sKeyItemFunctions[cursor].processInput != NULL)
                sOptions->selKey[cursor] = sKeyItemFunctions[cursor].processInput(previousOption);
            
            if(previousOption != sOptions->selKey[cursor])
                DrawChoices(cursor, sOptions->visibleCursor * Y_DIFF, 0);
            break;
        default:
            previousOption = sOptions->sel[cursor];
            if (sOptionsItemFunctions[cursor].processInput != NULL)
                sOptions->sel[cursor] = sOptionsItemFunctions[cursor].processInput(previousOption);

            if (previousOption != sOptions->sel[cursor])
                DrawChoices(cursor, sOptions->visibleCursor * Y_DIFF, 0);
            break;
        }
        
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = sOptions->sel[MENUITEM_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleSceneOff = sOptions->sel[MENUITEM_BATTLESCENE];
    gSaveBlock2Ptr->optionsBattleStyle = sOptions->sel[MENUITEM_BATTLESTYLE];
    gSaveBlock2Ptr->optionsFastFieldMove = sOptions->sel[MENUITEM_FASTFIELDMOVE];
    gSaveBlock2Ptr->optionsLevelCap = sOptions->sel[MENUITEM_LEVELCAP];
    gSaveBlock2Ptr->optionsTypeChart = sOptions->sel[MENUITEM_TYPECHART];
    gSaveBlock2Ptr->optionsSound = sOptions->sel[MENUITEM_SOUND];
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_NORMAL; //sOptions->sel[MENUITEM_BUTTONMODE];
    gSaveBlock2Ptr->optionsWindowFrameType = sOptions->sel[MENUITEM_FRAMETYPE];

    gSaveBlock2Ptr->optionsLevelCap = sOptions->selKey[MENUITEM_KEY_LVLCAP];
    gSaveBlock2Ptr->optionsBaseStatsEqual = sOptions->selKey[MENUITEM_KEY_BASESTATSEQ];

    gSaveBlock2Ptr->optionsRandomnessType = sOptions->selRand[MENUITEM_RAND_RANDOMNESS_TYPE];
    gSaveBlock2Ptr->randomWildEncounters = sOptions->selRand[MENUITEM_RAND_WILDENCOUNTERS];

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        FREE_AND_SET_NULL(sOptions);
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(int cursor)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 40, cursor * Y_DIFF + 56));
}

// Process Input functions
static int XOptions_ProcessInput(int x, int selection)
{
    if (gMain.newKeys & DPAD_RIGHT)
    {
        if (++selection > (x - 1))
            selection = 0;
    }
    if (gMain.newKeys & DPAD_LEFT)
    {
        if (--selection < 0)
            selection = (x - 1);
    }
    return selection;
}

static int ThreeOptions_ProcessInput(int selection)
{
    return XOptions_ProcessInput(3, selection);
}

static int FourOptions_ProcessInput(int selection)
{
    return XOptions_ProcessInput(4, selection);
}

static int TwoOptions_ProcessInput(int selection)
{
    if (gMain.newKeys & (DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

int FrameType_ProcessInput(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
    }
    return selection;
}

static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3)
{
    int xMid;
    int widthLeft = GetStringWidth(1, txt1, 0);
    int widthMid = GetStringWidth(1, txt2, 0);
    int widthRight = GetStringWidth(1, txt3, 0);

    widthMid -= (198 - 104);
    xMid = (widthLeft - widthMid - widthRight) / 2 + 104;
    return xMid;
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, u8 textSpeed)
{
    u8 dst[16];
    u32 i;

    for (i = 0; *text != EOS && i < ARRAY_COUNT(dst) - 1; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = TEXT_COLOR_RED;
        dst[5] = TEXT_COLOR_LIGHT_RED;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, dst, x, y + 1, textSpeed, NULL);
}

void BattleScene_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), y, styles[1], textSpeed);
}

void BattleStyle_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), y, styles[1], textSpeed);
}

static void FourOptions_DrawChoices(const u8 *const *const strings, int selection, int y, u8 textSpeed)
{
    static const u8 choiceOrders[][3] =
    {
        {0, 1, 2},
        {0, 1, 2},
        {1, 2, 3},
        {1, 2, 3},
    };
    u8 styles[4] = {0};
    int xMid;
    const u8 *order = choiceOrders[selection];

    styles[selection] = 1;
    xMid = GetMiddleX(strings[order[0]], strings[order[1]], strings[order[2]]);

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 104, y, 26 * 8 - 104, Y_DIFF);
    CopyWindowToVram(WIN_OPTIONS, 2);

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], textSpeed);
    DrawOptionMenuChoice(strings[order[1]], xMid, y, styles[order[1]], textSpeed);
    DrawOptionMenuChoice(strings[order[2]], GetStringRightAlignXOffset(1, strings[order[2]], 198), y, styles[order[2]], textSpeed);
}

void TextSpeed_DrawChoices(int selection, int y, u8 textSpeed)
{
    FourOptions_DrawChoices(sTextSpeedStrings, selection, y, textSpeed);
}

void FastFieldMove_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOff, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_BattleSceneOn, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), y, styles[1], textSpeed);
}

void TypeChart_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;

    DrawOptionMenuChoice(gText_TypeChartNormal, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_TypeChartInverse, GetStringRightAlignXOffset(FONT_NORMAL, gText_TypeChartInverse, 198), y, styles[1], textSpeed);
}

void LevelCap_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[3] ={0};
    int xMid = GetMiddleX(sText_Off, sText_Soft, sText_Strict);

    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(sText_Soft, xMid, y, styles[1], textSpeed);
    DrawOptionMenuChoice(sText_Strict, GetStringRightAlignXOffset(FONT_NORMAL, sText_Strict, 198), y, styles[2], textSpeed);
}

void BaseStatEq_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[2] = {0};

    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Default, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(sText_Equal, GetStringRightAlignXOffset(FONT_NORMAL, sText_Equal, 198), y, styles[1], textSpeed);
}




static u8 BattleScene_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}



static u8 BattleStyle_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}



int Sound_ProcessInput(int selection)
{
    int previous = selection;

    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection == 2)
            selection = 0;
        else
            selection++;
        sArrowPressed = TRUE;
    }
        
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection == 0)
            selection = 2;
        else
            selection--;
        sArrowPressed = TRUE;
    }

    if (selection != 2)
    {
        gDisableMusic = FALSE;
        SetPokemonCryStereo(selection);
        if (previous == 2)
            PlayNewMapMusic(GetCurrentMapMusic());
    }
    else
    {
        PlayBGM(0);
        gDisableMusic = TRUE;
    }

    return selection;
}

void Sound_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 styles[3] = {0};
    u8 sText_Off[]= _("Off");
    int xMid = GetMiddleX(gText_SoundMono, gText_SoundStereo, sText_Off);

    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_SoundStereo, xMid, y, styles[1], textSpeed);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), y, styles[2], textSpeed);
}



void FrameType_DrawChoices(int selection, int y, u8 textSpeed)
{
    u8 text[16];
    u8 n = selection + 1;
    u16 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = CHAR_SPACER;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, 104, y, 0, textSpeed);
    DrawOptionMenuChoice(text, 128, y, 1, textSpeed);
}

void ButtonMode_DrawChoices(int selection, int y , u8 textSpeed)
{
    u8 styles[3] ={0};
    int xMid = GetMiddleX(gText_ButtonTypeNormal, gText_ButtonTypeLR, gText_ButtonTypeLEqualsA);

    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ButtonTypeNormal, 104, y, styles[0], textSpeed);
    DrawOptionMenuChoice(gText_ButtonTypeLR, xMid, y, styles[1], textSpeed);
    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(FONT_NORMAL, gText_ButtonTypeLEqualsA, 198), y, styles[2], textSpeed);
}

static void DrawHeaderText(void)
{
    u32 i, widthOptions, xMid;
    u8 pageDots[9] = _("");  // Array size should be at least (2 * PAGE_COUNT) -1

    for (i = 0; i < PAGE_COUNT; i++)
    {
        if (i == sOptions->page)
            StringAppend(pageDots, gText_LargeDot);
        else
            StringAppend(pageDots, gText_SmallDot);
        if (i < PAGE_COUNT - 1)
            StringAppend(pageDots, gText_Space);            
    }
    widthOptions = GetStringWidth(FONT_NORMAL, pageDots, 0);
    xMid = (8 + widthOptions + 5);

    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, pageDots, 8, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sOptionMenuPageNames[sOptions->page], xMid, 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, gText_PageNav, GetStringRightAlignXOffset(FONT_NORMAL, gText_PageNav, 198), 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void)
{
    u8 i, items;
    const u8* const* menu = NULL;

    
    switch (sOptions->page)
    {
    case PAGE_OPTIONS:
        items = MENUITEM_COUNT;
        menu = sOptionMenuItemsNames;
        break;
    case PAGE_KEY:
        items = MENUITEM_KEY_COUNT;
        menu = sOptionMenuKeyItemsNames;
        break;
    case PAGE_RANDOMIZER:
        items = MENUITEM_RAND_COUNT;
        menu = sOptionMenuRandomizerItemsNames;
        break;
    }

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < items; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, menu[i], 8, (i * Y_DIFF) + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}

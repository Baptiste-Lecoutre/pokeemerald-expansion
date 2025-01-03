#include "global.h"
#include "main.h"
#include "menu.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "palette.h"
#include "quests.h"
#include "international_string_util.h"
#include "item.h"
#include "sprite.h"
#include "string_util.h"
#include "text.h"
#include "trig.h"
#include "util.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/quests.h"
#include "constants/rgb.h"
#include "data/quests.h"
#include "data/text/quest_descriptions.h"

// States and data defines for Task_MapNamePopUpWindow
enum {
    STATE_SLIDE_IN,
    STATE_WAIT,
    STATE_SLIDE_OUT,
    STATE_UNUSED,
    STATE_ERASE,
    STATE_END,
    STATE_PRINT, // For some reason the first state is numerically last.
};

#define TAG_QUEST_ICON      0x8001
#define POPUP_ONSCREEN_TIME 120
#define POPUP_OFFSCREEN_Y   24
#define POPUP_SLIDE_SPEED   2

#define tState         data[0]
#define tOnscreenTimer data[1]
#define tYOffset       data[2]
#define tIncomingPopUp data[3]
#define tPrintTimer    data[4]
#define tSpriteId      data[5]
#define tQuestId       data[6]

static u8 *GetQuestPointer(u16 id);
static void Task_QuestPopUpWindow(u8 taskId);
static void ShowQuestPopUpWindow(void);
static void LoadQuestPopUpWindowBgs(void);
static void SpriteCB_QuestIcons(struct Sprite *sprite);

static const u32 gPopUpWindowBorderTop_Tiles[] = INCBIN_U32("graphics/map_popup/bw/bw_primary.4bpp");
static const u32 gPopUpWindowBorderBottom_Tiles[] = INCBIN_U32("graphics/map_popup/bw/bw_secondary.4bpp");
//static const u16 gPopUpWindowBorder_Palette[] = INCBIN_U16("graphics/map_popup/bw/black.gbapal");
static const u32 gQuestPopUpIconTiles[] = INCBIN_U32("graphics/interface/quest_popup_icons.4bpp");
static const u16 gQuestPopUpIconPalette[] = INCBIN_U16("graphics/interface/quest_popup_icons.gbapal");

// .rodata
static const struct SpritePalette sSpritePalette_QuestIcons =
{
    .data = gQuestPopUpIconPalette,
    .tag = TAG_QUEST_ICON
};

static const struct SpriteSheet sSpriteSheet_QuestIcons =
{
    .data = gQuestPopUpIconTiles,
    .size = 0x100,
    .tag = TAG_QUEST_ICON,
};

static const union AnimCmd sSpriteAnim_StoryIcon[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_LoggersIcon[] =
{
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_FossilsIcon[] =
{
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_OceanicIcon[] =
{
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_SideIcon[] =
{
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_QuestIcons[] =
{
    sSpriteAnim_StoryIcon,
    sSpriteAnim_LoggersIcon,
    sSpriteAnim_FossilsIcon,
    sSpriteAnim_OceanicIcon,
    sSpriteAnim_SideIcon,
};


static const struct OamData sOamData_QuestIcons =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

const struct SpriteTemplate sSpriteTemplate_QuestIcons =
{
    .tileTag = TAG_QUEST_ICON,
    .paletteTag = TAG_QUEST_ICON,
    .oam = &sOamData_QuestIcons,
    .anims = sSpriteAnimTable_QuestIcons,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_QuestIcons,
};

static const u8 sText_NewQuestUnlocked[] = _("New quest unlocked!");

// .text
static u8 *GetQuestPointer(u16 id)
{
    if (id > NUM_QUESTS - 1)
        return NULL;
    return &gSaveBlock3Ptr->quests[id / 8];
}

u8 EnableQuest(u16 id)
{
    u8 *ptr = GetQuestPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 DisableQuest(u16 id)
{
    u8 *ptr = GetQuestPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 QuestGet(u16 id)
{
    u8 *ptr = GetQuestPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}

const u8 *QuestGetName(u16 id)
{
    return gQuests[id].name;
}

u8 QuestGetProgress(u16 id)
{
    return gQuests[id].progress();
}

u16 QuestGetGraphicsId(u16 id)
{
    u8 progress = QuestGetProgress(id);

    return gQuests[id].graphics(progress);
}

const u8 *const *QuestGetDescription(u16 id)
{
    u8 progress = QuestGetProgress(id);

    return gQuests[id].description(progress);
}

u8 QuestGetLines(u16 id)
{
    u8 progress = QuestGetProgress(id);

    return gQuests[id].lines(progress);
}

u8 QuestGetType(u16 id)
{
    return gQuests[id].type;
}

void ShowQuestPopup(u16 id)
{
    if (!FuncIsActiveTask(Task_QuestPopUpWindow))
    {
        gPopupTaskId = CreateTask(Task_QuestPopUpWindow, 100);
        gTasks[gPopupTaskId].tState = STATE_PRINT;
        gTasks[gPopupTaskId].tYOffset = POPUP_OFFSCREEN_Y;
        gTasks[gPopupTaskId].tQuestId = id;
    }
    else
    {
        if (gTasks[gPopupTaskId].tState != STATE_SLIDE_OUT)
            gTasks[gPopupTaskId].tState = STATE_SLIDE_OUT;
        gTasks[gPopupTaskId].tIncomingPopUp = TRUE;
    }
}

void HideQuestPopUpWindow(void)
{
    if (FuncIsActiveTask(Task_QuestPopUpWindow))
    {
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        ClearStdWindowAndFrame(GetSecondaryPopUpWindowId(), TRUE);
        RemoveMapNamePopUpWindow();
        RemoveSecondaryPopUpWindow();
        DisableInterrupts(INTR_FLAG_HBLANK);
        SetHBlankCallback(NULL);
        SetGpuReg_ForcedBlank(REG_OFFSET_BG0VOFS, 0);
        DestroyTask(gPopupTaskId);
    }
}

static void Task_QuestPopUpWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case STATE_PRINT:
        task->tPrintTimer++;
        if (task->tPrintTimer > 30)
        {
            task->tState = STATE_SLIDE_IN;
            task->tPrintTimer = 0;
            ShowQuestPopUpWindow();
            EnableInterrupts(INTR_FLAG_HBLANK);
            SetHBlankCallback(HBlankCB_DoublePopupWindow);
        }
        break;
    case STATE_SLIDE_IN:
        task->tYOffset -= POPUP_SLIDE_SPEED;
        if (task->tYOffset <= 0 )
        {
            task->tYOffset = 0;
            task->tState = STATE_WAIT;
            gTasks[gPopupTaskId].tOnscreenTimer = 0;
        }
        break;
    case STATE_WAIT:
        task->tOnscreenTimer++;
        if (task->tOnscreenTimer > POPUP_ONSCREEN_TIME)
        {
            task->tOnscreenTimer = 0;
            task->tState = STATE_SLIDE_OUT;
        }
        break;
    case STATE_SLIDE_OUT:
        task->tYOffset += POPUP_SLIDE_SPEED;
        if (task->tYOffset > POPUP_OFFSCREEN_Y - 1)
        {
            task->tYOffset = POPUP_OFFSCREEN_Y;
            if (task->tIncomingPopUp)
            {
                task->tState = STATE_PRINT;
                task->tPrintTimer = 0;
                task->tIncomingPopUp = FALSE;
            }
            else
            {
                task->tState = STATE_ERASE;
                return;
            }
        }
        break;
    case STATE_ERASE:
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        ClearStdWindowAndFrame(GetSecondaryPopUpWindowId(), TRUE);
        task->tState = STATE_END;
        break;
    case STATE_END:
        HideQuestPopUpWindow();
        return;
    }
}

static void ShowQuestPopUpWindow(void)
{
    u8 string[QUEST_NAME_LENGTH];
    u8 *txtPtr;
    u8 primaryWindowId = AddMapNamePopUpWindow();
    u8 secondaryWindowId = AddSecondaryPopUpWindow();
    
    LoadSpritePalette(&sSpritePalette_QuestIcons);
    LoadSpriteSheet(&sSpriteSheet_QuestIcons);
    LoadQuestPopUpWindowBgs();
    LoadPalette(gPopUpWindowBorder_Palette, BG_PLTT_ID(14), PLTT_SIZE_4BPP);

    gTasks[gPopupTaskId].tSpriteId = CreateSprite(&sSpriteTemplate_QuestIcons, 10, 12, 0);

    string[0] = EXT_CTRL_CODE_BEGIN;
    string[1] = EXT_CTRL_CODE_HIGHLIGHT;
    string[2] = TEXT_COLOR_TRANSPARENT;
    txtPtr = &(string[3]);

    StringCopy(txtPtr, QuestGetName(gTasks[gPopupTaskId].tQuestId));
    AddTextPrinterParameterized(primaryWindowId, FONT_SHORT, string, 20, 4, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(secondaryWindowId, FONT_SMALL, sText_NewQuestUnlocked, 144, 8, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(primaryWindowId, COPYWIN_FULL);
    CopyWindowToVram(secondaryWindowId, COPYWIN_FULL);
}

static void LoadQuestPopUpWindowBgs(void)
{
    u8 primaryWindowId = GetMapNamePopUpWindowId();
    u8 secondaryWindowId = GetSecondaryPopUpWindowId();

    PutWindowTilemap(primaryWindowId);
    PutWindowTilemap(secondaryWindowId);
    CopyToWindowPixelBuffer(primaryWindowId, gPopUpWindowBorderTop_Tiles, 2880, 0);
    CopyToWindowPixelBuffer(secondaryWindowId, gPopUpWindowBorderBottom_Tiles, 2880, 0);
}

static void SpriteCB_QuestIcons(struct Sprite *sprite)
{
    struct Task *task = &gTasks[gPopupTaskId];

    sprite->animNum = QuestGetType(task->tQuestId);
    sprite->y2 = -task->data[2];
    sprite->data[0] += 4;
    sprite->data[0] &= 0x7F;
    sprite->data[1] = gSineTable[sprite->data[0]] >> 5;

    BlendPalette(256 + (sprite->oam.paletteNum * 16) + 4, 12, sprite->data[1], RGB_WHITEALPHA);

    if (!FuncIsActiveTask(Task_QuestPopUpWindow))
        DestroySpriteAndFreeResources(sprite);
}

u8 QuestProgressFunc1(void)
{
    u8 count = CountTotalItemQuantityInBag(ITEM_POTION);

    if (count >= 5)
        return QUEST_READY;
    else
        return count;
}

u16 QuestGraphicsFunc1(u8 progress)
{
    return OBJ_EVENT_GFX_MAN_2;
}

const u8 *const *QuestDescriptionFunc1(u8 progress)
{
    if (progress == QUEST_READY)
    {
        return sQuestDescriptionList2;
    }
    else
    {
        ConvertIntToDecimalStringN(gStringVar2, progress, STR_CONV_MODE_LEFT_ALIGN, 1);
        return sQuestDescriptionList1;
    }
}

u8 QuestDescriptionLinesFunc1(u8 progress)
{
    if (progress == QUEST_READY)
        return ARRAY_COUNT(sQuestDescriptionList2);
    else
        return ARRAY_COUNT(sQuestDescriptionList1);
}

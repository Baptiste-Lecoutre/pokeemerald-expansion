#ifndef GUARD_QUESTS_H
#define GUARD_QUESTS_H

struct Quest
{
    const u8 name[QUEST_NAME_LENGTH + 1];
    u8 (*progress)(void);
    u16 (*graphics)(u8 progress);
    const u8 *const *(*description)(u8 progress);
    u8 (*lines)(u8 progress);
    u8 type;
};

extern const struct Quest gQuests[];

u8 EnableQuest(u16 id);
u8 DisableQuest(u16 id);
bool8 QuestGet(u16 id);
const u8 *QuestGetName(u16 id);
u8 QuestGetProgress(u16 id);
u16 QuestGetGraphicsId(u16 id);
const u8 *const *QuestGetDescription(u16 id);
u8 QuestGetLines(u16 id);
u8 QuestGetType(u16 id);

void ShowQuestPopup(u16 id);
void HideQuestPopUpWindow(void);

u8 QuestProgressFunc1(void);
u16 QuestGraphicsFunc1(u8 progress);
const u8 *const *QuestDescriptionFunc1(u8 progress);
u8 QuestDescriptionLinesFunc1(u8 progress);

#endif // GUARD_QUESTS_H

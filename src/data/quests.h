const struct Quest gQuests[] = 
{
    [QUEST_TEST] = 
    {
        .name = _("POTION RUN!"),
        .progress = QuestProgressFunc1,
        .graphics = QuestGraphicsFunc1,
        .description = QuestDescriptionFunc1,
        .lines = QuestDescriptionLinesFunc1,
        .type = QUEST_TYPE_GUILD_FOSSILS,
    },
};

#ifndef GUARD_QUEST_CONSTANTS_H
#define GUARD_QUEST_CONSTANTS_H

#define QUEST_NAME_LENGTH      18
#define QUEST_DESC_LINE_LENGTH 16

#define QUEST_TYPE_STORY         0
#define QUEST_TYPE_GUILD_LOGGERS 1
#define QUEST_TYPE_GUILD_FOSSILS 2
#define QUEST_TYPE_GUILD_OCEANIC 3
#define QUEST_TYPE_SIDE          4

#define QUEST_READY        0xFE
#define QUEST_COMPLETED    0xFF

// These constants are used in gQuests
#define QUEST_TEST  0

#define NUM_QUESTS (QUEST_TEST + 1)

#endif // GUARD_QUEST_CONSTANTS_H

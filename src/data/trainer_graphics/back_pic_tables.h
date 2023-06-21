const struct MonCoords gTrainerBackPicCoords[] =
{
    [TRAINER_BACK_PIC_BRENDAN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_MAY] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_RED] = {.size = 8, .y_offset = 5},
    [TRAINER_BACK_PIC_LEAF] = {.size = 8, .y_offset = 5},
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_MAY] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_WALLY] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_STEVEN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_ETHAN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_LYRA] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_KRIS] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_LUCAS] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_DAWN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_LUCAS_PLATINUM] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_DAWN_PLATINUM] = {.size = 8, .y_offset = 4},
};

// this table goes functionally unused, since none of these pics are compressed
// and the place they would get extracted to gets overwritten later anyway
// the casts are so they'll play nice with the strict struct definition
const struct CompressedSpriteSheet gTrainerBackPicTable[] =
{
    [TRAINER_BACK_PIC_BRENDAN] = {
        .data = (const u32 *)gTrainerBackPic_Brendan,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Brendan),
        .tag = TRAINER_BACK_PIC_BRENDAN,
    },
    [TRAINER_BACK_PIC_MAY] = {
        .data = (const u32 *)gTrainerBackPic_May,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_May),
        .tag = TRAINER_BACK_PIC_MAY,
    },
    [TRAINER_BACK_PIC_RED] = {
        .data = (const u32 *)gTrainerBackPic_Red,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Red),
        .tag = TRAINER_BACK_PIC_RED,
    },
    [TRAINER_BACK_PIC_LEAF] = {
        .data = (const u32 *)gTrainerBackPic_Leaf,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Leaf),
        .tag = TRAINER_BACK_PIC_LEAF,
    },
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN] = {
        .data = (const u32 *)gTrainerBackPic_RubySapphireBrendan,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_RubySapphireBrendan),
        .tag = TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN,
    },
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_MAY] = {
        .data = (const u32 *)gTrainerBackPic_RubySapphireMay,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_RubySapphireMay),
        .tag = TRAINER_BACK_PIC_RUBY_SAPPHIRE_MAY,
    },
    [TRAINER_BACK_PIC_WALLY] = {
        .data = (const u32 *)gTrainerBackPic_Wally,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Wally),
        .tag = TRAINER_BACK_PIC_WALLY,
    },
    [TRAINER_BACK_PIC_STEVEN] = {
        .data = (const u32 *)gTrainerBackPic_Steven,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Steven),
        .tag = TRAINER_BACK_PIC_STEVEN,
    },
    [TRAINER_BACK_PIC_ETHAN] = {
        .data = (const u32 *)gTrainerBackPic_Ethan,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Ethan),
        .tag = TRAINER_BACK_PIC_ETHAN,
    },
    [TRAINER_BACK_PIC_LYRA] = {
        .data = (const u32 *)gTrainerBackPic_Lyra,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Lyra),
        .tag = TRAINER_BACK_PIC_LYRA,
    },
    [TRAINER_BACK_PIC_KRIS] = {
        .data = (const u32 *)gTrainerBackPic_Kris,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Kris),
        .tag = TRAINER_BACK_PIC_KRIS,
    },
    [TRAINER_BACK_PIC_LUCAS] = {
        .data = (const u32 *)gTrainerBackPic_Lucas,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Lucas),
        .tag = TRAINER_BACK_PIC_LUCAS,
    },
    [TRAINER_BACK_PIC_DAWN] = {
        .data = (const u32 *)gTrainerBackPic_Dawn,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_Dawn),
        .tag = TRAINER_BACK_PIC_DAWN,
    },
    [TRAINER_BACK_PIC_LUCAS_PLATINUM] = {
        .data = (const u32 *)gTrainerBackPic_LucasPlatinum,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_LucasPlatinum),
        .tag = TRAINER_BACK_PIC_LUCAS_PLATINUM,
    },
    [TRAINER_BACK_PIC_DAWN_PLATINUM] = {
        .data = (const u32 *)gTrainerBackPic_DawnPlatinum,
        .size = TRAINER_PIC_SIZE * ARRAY_COUNT(gTrainerBackPicTable_DawnPlatinum),
        .tag = TRAINER_BACK_PIC_DAWN_PLATINUM,
    },
};

#define TRAINER_BACK_PAL(trainerPic, pal) [TRAINER_BACK_PIC_##trainerPic] = {pal, TRAINER_BACK_PIC_##trainerPic}

const struct CompressedSpritePalette gTrainerBackPicPaletteTable[] =
{
    TRAINER_BACK_PAL(BRENDAN, gTrainerPalette_Brendan),
    TRAINER_BACK_PAL(MAY, gTrainerPalette_May),
    TRAINER_BACK_PAL(RED, gTrainerBackPicPalette_Red),
    TRAINER_BACK_PAL(LEAF, gTrainerBackPicPalette_Leaf),
    TRAINER_BACK_PAL(RUBY_SAPPHIRE_BRENDAN, gTrainerPalette_RubySapphireBrendan),
    TRAINER_BACK_PAL(RUBY_SAPPHIRE_MAY, gTrainerPalette_RubySapphireMay),
    TRAINER_BACK_PAL(WALLY, gTrainerPalette_Wally),
    TRAINER_BACK_PAL(STEVEN, gTrainerPalette_Steven),
    TRAINER_BACK_PAL(ETHAN, gTrainerBackPicPalette_Ethan),
    TRAINER_BACK_PAL(LYRA, gTrainerBackPicPalette_Lyra),
    TRAINER_BACK_PAL(KRIS, gTrainerBackPicPalette_Kris),
    TRAINER_BACK_PAL(LUCAS, gTrainerBackPicPalette_Lucas),
    TRAINER_BACK_PAL(DAWN, gTrainerBackPicPalette_Dawn),
    TRAINER_BACK_PAL(LUCAS_PLATINUM, gTrainerBackPicPalette_LucasPlatinum),
    TRAINER_BACK_PAL(DAWN_PLATINUM, gTrainerBackPicPalette_DawnPlatinum),
};

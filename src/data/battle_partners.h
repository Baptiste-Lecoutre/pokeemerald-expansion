    [DIFFICULTY_NORMAL][PARTNER_NONE] =
    {
        .party = NULL,
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _(""),
        .items = {},
    },

    [DIFFICULTY_NORMAL][PARTNER_STEVEN] =
    {
        .party = TRAINER_PARTY(sParty_StevenPartner),
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_STEVEN,
        .trainerName = _("Steven"),
    },

    [DIFFICULTY_NORMAL][PARTNER_RAYQUAZA] = 
    {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Rayquaza"),
        .party = TRAINER_PARTY(sParty_RayquazaPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110MudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110TreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110TorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110MudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110TreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110TorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayMudkipMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTorchicMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTreeckoMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTreeckoMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanMudkipMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTorchicMeteorFallsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119MudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119TreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119TorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119MudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119TreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119TorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_MAY_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadMudkipPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTreeckoPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_BRENDAN_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTorchicPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_RED_PETALBURG_WOODS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedPetalburgWoodsPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_RED_FALLARBOR] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedFallarborPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_RED_ROUTE121] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedRoute121Partner),
    },

    [DIFFICULTY_NORMAL][PARTNER_RED_VICTORY_ROAD] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedVictoryRoadPartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_WALLY_PETALBURG] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyPetalburgPartner),
    },
    
    [DIFFICULTY_NORMAL][PARTNER_WALLY_MAUVILLE] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyMauvillePartner),
    },

    [DIFFICULTY_NORMAL][PARTNER_WALLY_VICTORY_ROAD] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyVictoryRoadPartner),
    },

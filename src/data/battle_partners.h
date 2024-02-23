const struct Trainer gBattlePartners[] = {
    [PARTNER_NONE] =
    {
        .party = NULL,
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _(""),
        .items = {},
    },

    [PARTNER_STEVEN] =
    {
        .party = TRAINER_PARTY(sParty_StevenPartner),
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_STEVEN,
        .trainerName = _("Steven"),
    },

    [PARTNER_RAYQUAZA] = 
    {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Rayquaza"),
        .party = TRAINER_PARTY(sParty_RayquazaPartner),
    },

    [PARTNER_MAY_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroMudkipPartner),
    },

    [PARTNER_MAY_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroTreeckoPartner),
    },

    [PARTNER_MAY_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRustboroTorchicPartner),
    },

    [PARTNER_BRENDAN_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroMudkipPartner),
    },

    [PARTNER_BRENDAN_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroTreeckoPartner),
    },

    [PARTNER_BRENDAN_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRustboroTorchicPartner),
    },

    [PARTNER_MAY_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110MudkipPartner),
    },

    [PARTNER_MAY_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110TreeckoPartner),
    },

    [PARTNER_MAY_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute110TorchicPartner),
    },

    [PARTNER_BRENDAN_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110MudkipPartner),
    },

    [PARTNER_BRENDAN_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110TreeckoPartner),
    },

    [PARTNER_BRENDAN_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute110TorchicPartner),
    },

    [PARTNER_MAY_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayMudkipMeteorFallsPartner),
    },

    [PARTNER_MAY_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTorchicMeteorFallsPartner),
    },

    [PARTNER_MAY_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTreeckoMeteorFallsPartner),
    },

    [PARTNER_BRENDAN_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTreeckoMeteorFallsPartner),
    },

    [PARTNER_BRENDAN_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanMudkipMeteorFallsPartner),
    },

    [PARTNER_BRENDAN_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTorchicMeteorFallsPartner),
    },

    [PARTNER_MAY_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119MudkipPartner),
    },

    [PARTNER_MAY_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119TreeckoPartner),
    },

    [PARTNER_MAY_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayRoute119TorchicPartner),
    },

    [PARTNER_BRENDAN_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119MudkipPartner),
    },

    [PARTNER_BRENDAN_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119TreeckoPartner),
    },

    [PARTNER_BRENDAN_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanRoute119TorchicPartner),
    },

    [PARTNER_MAY_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveMudkipPartner),
    },

    [PARTNER_MAY_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveTreeckoPartner),
    },

    [PARTNER_MAY_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayLilycoveTorchicPartner),
    },

    [PARTNER_BRENDAN_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveMudkipPartner),
    },

    [PARTNER_BRENDAN_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveTreeckoPartner),
    },

    [PARTNER_BRENDAN_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanLilycoveTorchicPartner),
    },

    [PARTNER_MAY_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadMudkipPartner),
    },

    [PARTNER_MAY_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTreeckoPartner),
    },

    [PARTNER_MAY_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTorchicPartner),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadMudkipPartner),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTreeckoPartner),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTorchicPartner),
    },

    [PARTNER_RED_PETALBURG_WOODS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedPetalburgWoodsPartner),
    },

    [PARTNER_RED_FALLARBOR] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedFallarborPartner),
    },

    [PARTNER_RED_ROUTE121] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedRoute121Partner),
    },

    [PARTNER_RED_VICTORY_ROAD] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_RED,
        .trainerName = _("Red"),
        .party = TRAINER_PARTY(sParty_RedVictoryRoadPartner),
    },

    [PARTNER_WALLY_PETALBURG] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyPetalburgPartner),
    },
    
    [PARTNER_WALLY_MAUVILLE] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyMauvillePartner),
    },

    [PARTNER_WALLY_VICTORY_ROAD] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .trainerName = _("Wally"),
        .party = TRAINER_PARTY(sParty_WallyVictoryRoadPartner),
    },
};

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

    [PARTNER_MAY_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayMudkipMeteorFalls),
    },

    [PARTNER_MAY_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTorchicMeteorFalls),
    },

    [PARTNER_MAY_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayTreeckoMeteorFalls),
    },

    [PARTNER_BRENDAN_TREECKO_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTreeckoMeteorFalls),
    },

    [PARTNER_BRENDAN_MUDKIP_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanMudkipMeteorFalls),
    },

    [PARTNER_BRENDAN_TORCHIC_METEOR_FALLS] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanTorchicMeteorFalls),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadMudkip),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTreecko),
    },

    [PARTNER_BRENDAN_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .trainerName = _("Brendan"),
        .party = TRAINER_PARTY(sParty_BrendanVictoryRoadTorchic),
    },

    [PARTNER_MAY_VICTORY_ROAD_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadMudkip),
    },

    [PARTNER_MAY_VICTORY_ROAD_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTreecko),
    },

    [PARTNER_MAY_VICTORY_ROAD_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_BACK_PIC_MAY,
        .trainerName = _("May"),
        .party = TRAINER_PARTY(sParty_MayVictoryRoadTorchic),
    },

};

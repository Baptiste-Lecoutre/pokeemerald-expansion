static const struct TrainerMon sParty_StevenPartner[] = { // 3 more mons to add
    {
        .species = SPECIES_CRADILY,
        .lvl = 42,
        .heldItem = ITEM_BIG_ROOT,
        .nature = TRAINER_PARTY_NATURE(NATURE_CALM),
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(255, 0, 6, 0, 255, 0),
        .moves = {MOVE_GIGA_DRAIN, MOVE_POWER_GEM, MOVE_EARTH_POWER, MOVE_RECOVER},
    },
    {
        .species = SPECIES_AERODACTYL,
        .lvl = 43,
        .heldItem = ITEM_LIFE_ORB,
        .nature = TRAINER_PARTY_NATURE(NATURE_JOLLY),
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(6, 255, 0, 0, 0, 252),
        .moves = {MOVE_BRAVE_BIRD, MOVE_ROCK_SLIDE, MOVE_EARTHQUAKE, MOVE_TAILWIND},
    },
    {
        .species = SPECIES_METAGROSS,
        .lvl = 42,
        .heldItem = ITEM_METAGROSSITE,
        .nature = TRAINER_PARTY_NATURE(NATURE_JOLLY),
        .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
        .ev = TRAINER_PARTY_EVS(6, 252, 0, 0, 0, 255),
        .moves = {MOVE_METEOR_MASH, MOVE_ZEN_HEADBUTT, MOVE_HAMMER_ARM, MOVE_BULLET_PUNCH},
    }
};

static const struct TrainerMon sParty_RayquazaPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .ev = TRAINER_PARTY_EVS(6, 252, 0, 0, 0, 252),
    .lvl = 80,
    .nature = TRAINER_PARTY_NATURE(NATURE_ADAMANT),
    .species = SPECIES_RAYQUAZA,
    .moves = {MOVE_DRAGON_ASCENT, MOVE_SWORDS_DANCE, MOVE_OUTRAGE, MOVE_EXTREME_SPEED}
    }
};

static const struct TrainerMon sParty_BrendanMudkipMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_SCEPTILE,
    .heldItem = ITEM_SITRUS_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_GRASS_PLEDGE, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_THUNDER_PUNCH}
    },
    {
    .lvl = 30, 
    .species = SPECIES_ARCANINE,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_FLARE_BLITZ, MOVE_EXTREME_SPEED, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_BrendanTreeckoMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_BLAZIKEN,
    .heldItem = ITEM_SITRUS_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_BLAZE_KICK, MOVE_SKY_UPPERCUT, MOVE_SHADOW_CLAW, MOVE_QUICK_ATTACK}
    },
    {
    .lvl = 30, 
    .species = SPECIES_ARAQUANID,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_LIQUIDATION, MOVE_LEECH_LIFE, MOVE_ICE_FANG, MOVE_AQUA_RING}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_BrendanTorchicMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_SWAMPERT,
    .heldItem = ITEM_RINDO_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_WATER_PLEDGE, MOVE_DIG, MOVE_ROCK_SLIDE, MOVE_ICE_PUNCH}
    },
    {
    .lvl = 30, 
    .species = SPECIES_ARCANINE,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_FLARE_BLITZ, MOVE_EXTREME_SPEED, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_MayMudkipMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_SCEPTILE,
    .heldItem = ITEM_SITRUS_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_GRASS_PLEDGE, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_THUNDER_PUNCH}
    },
    {
    .lvl = 30, 
    .species = SPECIES_RAPIDASH,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_BLAZE_KICK, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_MayTreeckoMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_BLAZIKEN,
    .heldItem = ITEM_SITRUS_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_BLAZE_KICK, MOVE_SKY_UPPERCUT, MOVE_SHADOW_CLAW, MOVE_QUICK_ATTACK}
    },
    {
    .lvl = 30, 
    .species = SPECIES_STARMIE,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_WATER_PULSE, MOVE_PSYCHIC, MOVE_AURORA_BEAM, MOVE_POWER_GEM}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_MayTorchicMeteorFalls[] = { // 2-3 more mons to add
    {
    .lvl = 30, 
    .species = SPECIES_SWAMPERT,
    .heldItem = ITEM_RINDO_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_WATER_PLEDGE, MOVE_DIG, MOVE_ROCK_SLIDE, MOVE_ICE_PUNCH}
    },
    {
    .lvl = 30, 
    .species = SPECIES_RAPIDASH,
    .heldItem = ITEM_LIFE_ORB,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_BLAZE_KICK, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .lvl = 30, 
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .moves = {MOVE_PLAY_ROUGH, MOVE_SHADOW_CLAW, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    }
};

static const struct TrainerMon sParty_BrendanVictoryRoadMudkip[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_ARAQUANID,
    .heldItem = ITEM_FOCUS_SASH,
    .moves = {MOVE_LIQUIDATION, MOVE_LEECH_LIFE, MOVE_ICE_FANG, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_EXTREME_SPEED, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_ARCANINE,
    .heldItem = ITEM_ASSAULT_VEST,
    .moves = {MOVE_FLARE_BLITZ, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_AURORA_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 55,
    .species = SPECIES_SCEPTILE,
    .heldItem = ITEM_SCEPTILITE,
    .moves = {MOVE_SOLAR_BEAM, MOVE_DRAGON_PULSE, MOVE_EARTHQUAKE, MOVE_GROWTH}
    }
};

static const struct TrainerMon sParty_BrendanVictoryRoadTreecko[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_ARAQUANID,
    .heldItem = ITEM_FOCUS_SASH,
    .moves = {MOVE_LIQUIDATION, MOVE_LEECH_LIFE, MOVE_ICE_FANG, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_EXTREME_SPEED, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_BRELOOM,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_MACH_PUNCH, MOVE_BULLET_SEED, MOVE_ROCK_TOMB, MOVE_SPORE}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_AURORA_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 55,
    .species = SPECIES_BLAZIKEN,
    .heldItem = ITEM_BLAZIKENITE,
    .moves = {MOVE_FLARE_BLITZ, MOVE_HIGH_JUMP_KICK, MOVE_THUNDER_PUNCH, MOVE_SWORDS_DANCE}
    }
};

static const struct TrainerMon sParty_BrendanVictoryRoadTorchic[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_EXTREME_SPEED, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_ARCANINE,
    .heldItem = ITEM_ASSAULT_VEST,
    .moves = {MOVE_FLARE_BLITZ, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_BRELOOM,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_CLOSE_COMBAT, MOVE_BULLET_SEED, MOVE_ROCK_TOMB, MOVE_SPORE}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 55,
    .species = SPECIES_SWAMPERT,
    .heldItem = ITEM_SWAMPERTITE,
    .moves = {MOVE_LIQUIDATION, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE}
    }
};

static const struct TrainerMon sParty_MayVictoryRoadMudkip[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_REVERSAL, MOVE_PROTECT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_STARMIE,
    .heldItem = ITEM_ASSAULT_VEST,
    .moves = {MOVE_HYDRO_PUMP, MOVE_PSYSHOCK, MOVE_THUNDER, MOVE_ICE_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_RAPIDASH,
    .heldItem = ITEM_FIRE_GEM,
    .moves = {MOVE_FLARE_BLITZ, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SCEPTILE,
    .heldItem = ITEM_SCEPTILITE,
    .moves = {MOVE_SOLAR_BEAM, MOVE_DRAGON_PULSE, MOVE_EARTHQUAKE, MOVE_GROWTH}
    }
};

static const struct TrainerMon sParty_MayVictoryRoadTreecko[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_REVERSAL, MOVE_PROTECT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_STARMIE,
    .heldItem = ITEM_WATER_GEM,
    .moves = {MOVE_HYDRO_PUMP, MOVE_PSYSHOCK, MOVE_THUNDER, MOVE_ICE_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_TSAREENA,
    .heldItem = ITEM_ASSAULT_VEST,
    .moves = {MOVE_POWER_WHIP, MOVE_HIGH_JUMP_KICK, MOVE_KNOCK_OFF, MOVE_STRENGTH}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 55,
    .species = SPECIES_BLAZIKEN,
    .heldItem = ITEM_BLAZIKENITE,
    .moves = {MOVE_FLARE_BLITZ, MOVE_HIGH_JUMP_KICK, MOVE_THUNDER_PUNCH, MOVE_SWORDS_DANCE}
    }
};

static const struct TrainerMon sParty_MayVictoryRoadTorchic[] = {
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_VIKAVOLT,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_THUNDERBOLT, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_SWELLOW,
    .heldItem = ITEM_FLAME_ORB,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FACADE, MOVE_REVERSAL, MOVE_PROTECT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_RAPIDASH,
    .heldItem = ITEM_FIRE_GEM,
    .moves = {MOVE_FLARE_BLITZ, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_TSAREENA,
    .heldItem = ITEM_ASSAULT_VEST,
    .moves = {MOVE_POWER_WHIP, MOVE_HIGH_JUMP_KICK, MOVE_KNOCK_OFF, MOVE_STRENGTH}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 53,
    .species = SPECIES_MIMIKYU,
    .heldItem = ITEM_LUM_BERRY,
    .moves = {MOVE_LIQUIDATION, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE}
    },    
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 55,
    .species = SPECIES_SWAMPERT,
    .heldItem = ITEM_SWAMPERTITE,
    .moves = {MOVE_LIQUIDATION, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE}
    }
};

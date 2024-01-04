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

// Rival
static const struct TrainerMon sParty_BrendanRustboroMudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_TAILLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_DEWPIDER,
    .moves = {MOVE_BUG_BITE, MOVE_BUBBLE, MOVE_INFESTATION, MOVE_WATER_SPORT}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_GROWLITHE,
    .moves = {MOVE_FLAME_WHEEL, MOVE_BITE, MOVE_REVERSAL, MOVE_ROAR}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_GROVYLE,
    .moves = {MOVE_MEGA_DRAIN, MOVE_DRAGON_BREATH, MOVE_FURY_CUTTER, MOVE_ROCK_TOMB}
    }
};

static const struct TrainerMon sParty_BrendanRustboroTreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_TAILLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_DEWPIDER,
    .moves = {MOVE_BUG_BITE, MOVE_BUBBLE, MOVE_INFESTATION, MOVE_WATER_SPORT}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_SHROOMISH,
    .moves = {MOVE_BULLET_SEED, MOVE_STUN_SPORE, MOVE_LEECH_SEED, MOVE_HEADBUTT}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_COMBUSKEN,
    .moves = {MOVE_DOUBLE_KICK, MOVE_ROCK_TOMB, MOVE_FLAME_CHARGE, MOVE_PECK}
    }
};

static const struct TrainerMon sParty_BrendanRustboroTorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_TAILLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_GROWLITHE,
    .moves = {MOVE_FLAME_WHEEL, MOVE_BITE, MOVE_REVERSAL, MOVE_ROAR}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_SHROOMISH,
    .moves = {MOVE_BULLET_SEED, MOVE_STUN_SPORE, MOVE_LEECH_SEED, MOVE_HEADBUTT}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_MARSHTOMP,
    .moves = {MOVE_MUD_SHOT, MOVE_WATER_GUN, MOVE_ROCK_TOMB, MOVE_GROWL}
    }
};

static const struct TrainerMon sParty_MayRustboroMudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_STARYU,
    .moves = {MOVE_BUBBLE_BEAM, MOVE_RECOVER, MOVE_PSYWAVE, MOVE_SWIFT}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_PONYTA,
    .moves = {MOVE_FLAME_WHEEL, MOVE_TAIL_WHIP, MOVE_TACKLE, MOVE_DOUBLE_KICK}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_GROVYLE,
    .moves = {MOVE_MEGA_DRAIN, MOVE_DRAGON_BREATH, MOVE_FURY_CUTTER, MOVE_ROCK_TOMB}
    }
};

static const struct TrainerMon sParty_MayRustboroTreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_STARYU,
    .moves = {MOVE_BUBBLE_BEAM, MOVE_RECOVER, MOVE_PSYWAVE, MOVE_SWIFT}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_STEENEE,
    .moves = {MOVE_RAZOR_LEAF, MOVE_CHARM, MOVE_ACUPRESSURE, MOVE_SYNTHESIS}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_COMBUSKEN,
    .moves = {MOVE_DOUBLE_KICK, MOVE_ROCK_TOMB, MOVE_FLAME_CHARGE, MOVE_PECK}
    }
};

static const struct TrainerMon sParty_MayRustboroTorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_REFRESH}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_STEENEE,
    .moves = {MOVE_RAZOR_LEAF, MOVE_CHARM, MOVE_ACUPRESSURE, MOVE_SYNTHESIS}
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 14,
    .species = SPECIES_PONYTA,
    .moves = {MOVE_FLAME_WHEEL, MOVE_TAIL_WHIP, MOVE_TACKLE, MOVE_DOUBLE_KICK}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 15,
    .species = SPECIES_MARSHTOMP,
    .moves = {MOVE_MUD_SHOT, MOVE_WATER_GUN, MOVE_ROCK_TOMB, MOVE_GROWL}
    }
};

static const struct TrainerMon sParty_BrendanRoute110MudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_ARAQUANID,
    .moves = {MOVE_BUG_BITE, MOVE_WATER_PULSE, MOVE_ICE_FANG, MOVE_SPIDER_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_ARCANINE,
    .moves = {MOVE_FLAME_BURST, MOVE_THUNDER_FANG, MOVE_EXTREME_SPEED, MOVE_ROAR}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_GROVYLE,
    .moves = {MOVE_GRASS_PLEDGE, MOVE_DRAGON_BREATH, MOVE_FURY_CUTTER, MOVE_ROCK_TOMB}
    }
};

static const struct TrainerMon sParty_BrendanRoute110TreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_ARAQUANID,
    .moves = {MOVE_BUG_BITE, MOVE_WATER_PULSE, MOVE_ICE_FANG, MOVE_SPIDER_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_BRELOOM,
    .moves = {MOVE_BULLET_SEED, MOVE_MACH_PUNCH, MOVE_ROCK_TOMB, MOVE_BULK_UP}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_COMBUSKEN,
    .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_TOMB, MOVE_FIRE_PLEDGE, MOVE_BULK_UP}
    }
};

static const struct TrainerMon sParty_BrendanRoute110TorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_ARCANINE,
    .moves = {MOVE_FLAME_BURST, MOVE_THUNDER_FANG, MOVE_EXTREME_SPEED, MOVE_ROAR}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_BRELOOM,
    .moves = {MOVE_BULLET_SEED, MOVE_MACH_PUNCH, MOVE_ROCK_TOMB, MOVE_BULK_UP}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_MARSHTOMP,
    .moves = {MOVE_BULLDOZE, MOVE_WATER_PLEDGE, MOVE_ROCK_SLIDE, MOVE_BRICK_BREAK}
    }
};

static const struct TrainerMon sParty_MayRoute110MudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_STARMIE,
    .moves = {MOVE_WATER_PULSE, MOVE_RECOVER, MOVE_PSYBEAM, MOVE_ICY_WIND}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_PONYTA,
    .moves = {MOVE_BLAZE_KICK, MOVE_WILD_CHARGE, MOVE_TAKE_DOWN, MOVE_DOUBLE_KICK}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_GROVYLE,
    .moves = {MOVE_GRASS_PLEDGE, MOVE_DRAGON_BREATH, MOVE_FURY_CUTTER, MOVE_ROCK_TOMB}
    }
};

static const struct TrainerMon sParty_MayRoute110TreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_STARMIE,
    .moves = {MOVE_WATER_PULSE, MOVE_RECOVER, MOVE_PSYBEAM, MOVE_ICY_WIND}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_STEENEE,
    .moves = {MOVE_TROP_KICK, MOVE_LOW_SWEEP, MOVE_U_TURN, MOVE_SYNTHESIS}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_COMBUSKEN,
    .moves = {MOVE_BRICK_BREAK, MOVE_ROCK_TOMB, MOVE_FIRE_PLEDGE, MOVE_BULK_UP}
    }
};

static const struct TrainerMon sParty_MayRoute110TorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ROOST, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_STEENEE,
    .moves = {MOVE_TROP_KICK, MOVE_LOW_SWEEP, MOVE_U_TURN, MOVE_SYNTHESIS}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_PONYTA,
    .moves = {MOVE_BLAZE_KICK, MOVE_WILD_CHARGE, MOVE_TAKE_DOWN, MOVE_DOUBLE_KICK}
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 23,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_SHADOW_SNEAK, MOVE_BULK_UP, MOVE_DRAIN_PUNCH}
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 25,
    .species = SPECIES_MARSHTOMP,
    .moves = {MOVE_BULLDOZE, MOVE_WATER_PLEDGE, MOVE_ROCK_SLIDE, MOVE_BRICK_BREAK}
    }
};

static const struct TrainerMon sParty_BrendanMudkipMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_BrendanTreeckoMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_BrendanTorchicMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_MayMudkipMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_MayTreeckoMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_MayTorchicMeteorFallsPartner[] = { // 2-3 more mons to add
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

static const struct TrainerMon sParty_BrendanRoute119MudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_LIQUIDATION, MOVE_LEECH_LIFE, MOVE_ICE_FANG, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_ARAQUANID,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_ARCANINE,
    .moves = {MOVE_FLARE_BLITZ, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 45,
    .species = SPECIES_SCEPTILE,
    .moves = {MOVE_FRENZY_PLANT, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_GRASSY_TERRAIN}
    }
};

static const struct TrainerMon sParty_BrendanRoute119TreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_LIQUIDATION, MOVE_LEECH_LIFE, MOVE_ICE_FANG, MOVE_STICKY_WEB}
    },
    {
    .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25),
    .lvl = 43,
    .species = SPECIES_ARAQUANID,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25),
    .lvl = 43,
    .species = SPECIES_BRELOOM,
    .moves = {MOVE_FOCUS_PUNCH, MOVE_SEED_BOMB, MOVE_SPORE, MOVE_SUBSTITUTE}
    },
    {
    .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 45,
    .species = SPECIES_BLAZIKEN,
    .moves = {MOVE_BLAST_BURN, MOVE_AURA_SPHERE, MOVE_SOLAR_BEAM, MOVE_SUNNY_DAY}
    }
};

static const struct TrainerMon sParty_BrendanRoute119TorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_ARCANINE,
    .moves = {MOVE_FLARE_BLITZ, MOVE_WILD_CHARGE, MOVE_CLOSE_COMBAT, MOVE_EXTREME_SPEED}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_BRELOOM,
    .moves = {MOVE_FOCUS_PUNCH, MOVE_SEED_BOMB, MOVE_SPORE, MOVE_SUBSTITUTE}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 45,
    .species = SPECIES_SWAMPERT,
    .moves = {MOVE_HYDRO_CANNON, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE}
    }
};

static const struct TrainerMon sParty_MayRoute119MudkipPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_STARMIE,
    .moves = {MOVE_HYDRO_PUMP, MOVE_PSYSHOCK, MOVE_THUNDER, MOVE_ICE_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_RAPIDASH,
    .moves = {MOVE_FLARE_BLITZ, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 43,
    .species = SPECIES_SCEPTILE,
    .moves = {MOVE_FRENZY_PLANT, MOVE_DRAGON_PULSE, MOVE_FOCUS_BLAST, MOVE_GRASSY_TERRAIN}
    }
};

static const struct TrainerMon sParty_MayRoute119TreeckoPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_STARMIE,
    .moves = {MOVE_HYDRO_PUMP, MOVE_PSYSHOCK, MOVE_THUNDER, MOVE_ICE_BEAM}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_TSAREENA,
    .moves = {MOVE_POWER_WHIP, MOVE_HIGH_JUMP_KICK, MOVE_PLAY_ROUGH, MOVE_STRENGTH}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 45,
    .species = SPECIES_BLAZIKEN,
    .moves = {MOVE_BLAST_BURN, MOVE_AURA_SPHERE, MOVE_SOLAR_BEAM, MOVE_SUNNY_DAY}
    }
};

static const struct TrainerMon sParty_MayRoute119TorchicPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_SWELLOW,
    .moves = {MOVE_HURRICANE, MOVE_BOOMBURST, MOVE_HEAT_WAVE, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_RAPIDASH,
    .moves = {MOVE_FLARE_BLITZ, MOVE_JUMP_KICK, MOVE_WILD_CHARGE, MOVE_POISON_JAB}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_TSAREENA,
    .moves = {MOVE_POWER_WHIP, MOVE_HIGH_JUMP_KICK, MOVE_PLAY_ROUGH, MOVE_STRENGTH}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_MIMIKYU,
    .moves = {MOVE_SHADOW_CLAW, MOVE_PLAY_ROUGH, MOVE_SWORDS_DANCE, MOVE_SHADOW_SNEAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_VIKAVOLT,
    .moves = {MOVE_THUNDER, MOVE_BUG_BUZZ, MOVE_ENERGY_BALL, MOVE_MUD_SHOT}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 45,
    .species = SPECIES_SWAMPERT,
    .moves = {MOVE_HYDRO_CANNON, MOVE_EARTHQUAKE, MOVE_ICE_PUNCH, MOVE_RAIN_DANCE}
    }
};

static const struct TrainerMon sParty_BrendanLilycoveMudkipPartner[] = {
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

static const struct TrainerMon sParty_BrendanLilycoveTreeckoPartner[] = {
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

static const struct TrainerMon sParty_BrendanLilycoveTorchicPartner[] = {
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

static const struct TrainerMon sParty_MayLilycoveMudkipPartner[] = {
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

static const struct TrainerMon sParty_MayLilycoveTreeckoPartner[] = {
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

static const struct TrainerMon sParty_MayLilycoveTorchicPartner[] = {
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

static const struct TrainerMon sParty_BrendanVictoryRoadMudkipPartner[] = {
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

static const struct TrainerMon sParty_BrendanVictoryRoadTreeckoPartner[] = {
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

static const struct TrainerMon sParty_BrendanVictoryRoadTorchicPartner[] = {
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

static const struct TrainerMon sParty_MayVictoryRoadMudkipPartner[] = {
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

static const struct TrainerMon sParty_MayVictoryRoadTreeckoPartner[] = {
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

static const struct TrainerMon sParty_MayVictoryRoadTorchicPartner[] = {
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

// Red
static const struct TrainerMon sParty_RedPetalburgWoodsPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 15,
    .species = SPECIES_CHARMANDER,
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 15,
    .species = SPECIES_BULBASAUR,
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 15,
    .species = SPECIES_SQUIRTLE,
    }
};

static const struct TrainerMon sParty_RedFallarborPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 37,
    .heldItem = ITEM_LIGHT_BALL,
    .species = SPECIES_PIKACHU_PH_D,
    .moves = {MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_NASTY_PLOT, MOVE_BODY_SLAM},
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 37,
    .heldItem = ITEM_WHITE_HERB,
    .species = SPECIES_VENUSAUR,
    .moves = {MOVE_LEAF_STORM, MOVE_TOXIC, MOVE_SLUDGE_BOMB, MOVE_EARTH_POWER},
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 37,
    .heldItem = ITEM_WHITE_HERB,
    .species = SPECIES_BLASTOISE,
    .moves = {MOVE_WATER_PULSE, MOVE_SHELL_SMASH, MOVE_AURA_SPHERE, MOVE_AURORA_BEAM},
    },
    {
    .iv = TRAINER_PARTY_IVS(6, 6, 6, 6, 6, 6),
    .lvl = 37,
    .heldItem = ITEM_CHARIZARDITE_X,
    .species = SPECIES_CHARIZARD,
    .moves = {MOVE_FLAMETHROWER, MOVE_THUNDER_PUNCH, MOVE_BRICK_BREAK, MOVE_DRAGON_CLAW},
    },
    {
    .iv = TRAINER_PARTY_IVS(12, 12, 12, 12, 12, 12),
    .lvl = 37,
    .heldItem = ITEM_LEFTOVERS,
    .species = SPECIES_SNORLAX,
    .moves = {MOVE_BODY_SLAM, MOVE_CURSE, MOVE_REST, MOVE_SLEEP_TALK},
    }
};

static const struct TrainerMon sParty_RedRoute121Partner[] = {
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_LIGHT_BALL,
    .species = SPECIES_PIKACHU_FLYING,
    .moves = {MOVE_THUNDERBOLT, MOVE_AERIAL_ACE, MOVE_THUNDER_WAVE, MOVE_BODY_SLAM},
    },
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_FAIRY_GEM,
    .species = SPECIES_ESPEON,
    .moves = {MOVE_DAZZLING_GLEAM, MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_CALM_MIND},
    },
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_WHITE_HERB,
    .species = SPECIES_VENUSAUR,
    .moves = {MOVE_LEAF_STORM, MOVE_TOXIC, MOVE_SLUDGE_BOMB, MOVE_EARTH_POWER},
    },
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_WHITE_HERB,
    .species = SPECIES_BLASTOISE,
    .moves = {MOVE_WATER_PULSE, MOVE_SHELL_SMASH, MOVE_AURA_SPHERE, MOVE_AURORA_BEAM},
    },
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_CHARIZARDITE_X,
    .species = SPECIES_CHARIZARD,
    .moves = {MOVE_FLAMETHROWER, MOVE_THUNDER_PUNCH, MOVE_BRICK_BREAK, MOVE_DRAGON_CLAW},
    },
    {
    .iv = TRAINER_PARTY_IVS(18, 18, 18, 18, 18, 18),
    .lvl = 65,
    .heldItem = ITEM_LEFTOVERS,
    .species = SPECIES_SNORLAX,
    .moves = {MOVE_BODY_SLAM, MOVE_CURSE, MOVE_REST, MOVE_SLEEP_TALK},
    }
};

static const struct TrainerMon sParty_RedVictoryRoadPartner[] = { // 3 more mons to add
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 75,
    .species = SPECIES_CHARIZARD,
    .heldItem = ITEM_CHARIZARDITE_X,
    .moves = {MOVE_DRAGON_CLAW, MOVE_FLARE_BLITZ, MOVE_THUNDER_PUNCH, MOVE_BRICK_BREAK}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 75,
    .species = SPECIES_VENUSAUR,
    .heldItem = ITEM_LIFE_ORB,
    .moves = {MOVE_GIGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_WEATHER_BALL, MOVE_GROWTH}
    },
    {
    .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
    .lvl = 75,
    .species = SPECIES_BLASTOISE,
    .heldItem = ITEM_WHITE_HERB,
    .moves = {MOVE_FLASH_CANNON, MOVE_DARK_PULSE, MOVE_SKULL_BASH, MOVE_SHELL_SMASH}
    }
};

// Wally
static const struct TrainerMon sParty_WallyPetalburgPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 8,
    .species = SPECIES_RALTS,
    }
};

static const struct TrainerMon sParty_WallyMauvillePartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 20,
    .species = SPECIES_ROSELIA,
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 20,
    .species = SPECIES_FLETCHINDER,
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 20,
    .species = SPECIES_MARILL,
    },
    {
    .iv = TRAINER_PARTY_IVS(3, 3, 3, 3, 3, 3),
    .lvl = 22,
    .species = SPECIES_KIRLIA,
    }
};

static const struct TrainerMon sParty_WallyVictoryRoadPartner[] = {
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 44,
    .species = SPECIES_GARCHOMP,
    .moves = {MOVE_DRAGON_RUSH, MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_STEALTH_ROCK}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 43,
    .species = SPECIES_AZUMARILL,
    .moves = {MOVE_LIQUIDATION, MOVE_PLAY_ROUGH, MOVE_IRON_TAIL, MOVE_AQUA_JET}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 44,
    .species = SPECIES_ROSERADE,
    .moves = {MOVE_MEGA_DRAIN, MOVE_SLUDGE_BOMB, MOVE_SLEEP_POWDER, MOVE_QUIVER_DANCE}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 41,
    .species = SPECIES_MAGNEZONE,
    .moves = {MOVE_FLASH_CANNON, MOVE_HIDDEN_POWER, MOVE_VOLT_SWITCH, MOVE_THUNDER_WAVE}
    },
    {
    .iv = TRAINER_PARTY_IVS(24, 24, 24, 24, 24, 24),
    .lvl = 41,
    .species = SPECIES_TALONFLAME,
    .moves = {MOVE_BRAVE_BIRD, MOVE_FLARE_BLITZ, MOVE_STEEL_WING, MOVE_U_TURN}
    },
    {
    .iv = TRAINER_PARTY_IVS(30, 30, 30, 30, 30, 30),
    .lvl = 45,
    .species = SPECIES_GARDEVOIR,
    .moves = {MOVE_DOUBLE_TEAM, MOVE_CALM_MIND, MOVE_PSYCHIC, MOVE_FUTURE_SIGHT}
    }
};

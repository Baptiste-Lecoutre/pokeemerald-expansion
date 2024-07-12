#ifndef GUARD_CONSTANTS_BATTLE_RAID_H
#define GUARD_CONSTANTS_BATTLE_RAID_H

// Raid shield IDs
#define RAID_SHIELD_MAX     0
#define RAID_SHIELD_TERA    1
#define RAID_SHIELD_MEGA    2

// Raid rules IDs
#define RAID_RULES_MAX  0
#define RAID_RULES_TERA 1
#define RAID_RULES_MEGA 2

// Raid gimmick IDs
#define RAID_GIMMICK_DYNAMAX 0
#define RAID_GIMMICK_TERA    1
#define RAID_GIMMICK_MEGA    2
#define RAID_GIMMICK_PRIMAL  3

// Raid Type IDs
#define RAID_TYPE_MAX    0
#define RAID_TYPE_TERA   1
#define RAID_TYPE_MEGA   2
#define RAID_TYPE_PRIMAL 3
#define NUM_RAID_TYPES   4

// Raid Shockwave IDs
#define RAID_SHOCKWAVE_MAX  0
#define RAID_SHOCKWAVE_TERA 1
#define RAID_SHOCKWAVE_MEGA 2
#define NUM_RAID_SHOCKWAVE  3

// Raid Battle States
#define RAID_INTRO_COMPLETE     (1 << 1)
#define RAID_CREATE_SHIELD      (1 << 2)
#define RAID_BREAK_SHIELD       (1 << 3)
#define RAID_CATCHING_BOSS      (1 << 4)
#define RAID_RESHOW_SHIELD     (1 << 5)
#define RAID_HIDE_SHIELD       (1 << 6)

// Raid Storm Turn Thresholds
#define RAID_STORM_TURNS_LEVEL_1    3    // number of turns
#define RAID_STORM_TURNS_LEVEL_2    6
#define RAID_STORM_TURNS_LEVEL_3    9
#define RAID_STORM_TURNS_MAX        10

// Raid Storm Timer Thresholds
#define RAID_STORM_TIMER_WARNING    23400 // 6.5 minutes
#define RAID_STORM_TIMER_MAX        27000 // 7.5 minutes, in frames

// Raid Ranks
#define NO_RAID         0
#define RAID_RANK_1     1
#define RAID_RANK_2     2
#define RAID_RANK_3     3
#define RAID_RANK_4     4
#define RAID_RANK_5     5
#define RAID_RANK_6     6
#define RAID_RANK_7     7
#define MAX_RAID_RANK   RAID_RANK_7

// Raid Partners
#define MAX_NUM_PARTNERS 3
#define MAX_TEAM_SIZE 3

// Other Constants
#define MAX_RAID_DROPS     12
#define MAX_BARRIER_COUNT   5
#define RAID_MAX_TERA_ORB_CHARGE    3

// Config
#define B_MAX_RAID_ENERGY_POSITION TRUE

#endif

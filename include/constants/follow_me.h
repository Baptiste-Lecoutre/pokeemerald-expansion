#ifndef GUARD_CONSTANTS_FOLLOW_ME_H
#define GUARD_CONSTANTS_FOLLOW_ME_H

#define FOLLOWER_FLAG_HAS_RUNNING_FRAMES    0x1
#define FOLLOWER_FLAG_CAN_BIKE              0x2
#define FOLLOWER_FLAG_CAN_LEAVE_ROUTE       0x4     // teleport, dig, fly, etc
#define FOLLOWER_FLAG_CAN_SURF              0x8
#define FOLLOWER_FLAG_CAN_WATERFALL         0x10
#define FOLLOWER_FLAG_CAN_DIVE              0x20
#define FOLLOWER_FLAG_CAN_ROCK_CLIMB        0x40    // need rock climb implemented
#define FOLLOWER_FLAG_CLEAR_ON_WHITE_OUT    0x80

#define FOLLOWER_FLAG_ALL_WATER             FOLLOWER_FLAG_CAN_SURF | FOLLOWER_FLAG_CAN_WATERFALL | FOLLOWER_FLAG_CAN_DIVE
#define FOLLOWER_FLAG_ALL_LAND              FOLLOWER_FLAG_HAS_RUNNING_FRAMES | FOLLOWER_FLAG_CAN_BIKE | FOLLOWER_FLAG_CAN_LEAVE_ROUTE
#define FOLLOWER_FLAG_ALL                   FOLLOWER_FLAG_ALL_WATER | FOLLOWER_FLAG_ALL_LAND | FOLLOWER_FLAG_CLEAR_ON_WHITE_OUT


// If set to TRUE, the Player's party will be automatically healed after every battle the follower partner participates in
#define HEAL_AFTER_FOLLOWER_BATTLE          TRUE

// If set to TRUE, a preview of the player's and partner's teams will be shown before every trainer battle
#define FOLLOWER_PARTY_PREVIEW              FALSE

// If set to TRUE, the follower partner will join you for wild battles
#define FOLLOWER_PARTNER_WILD_BATTLES       TRUE

// If set to FALSE, only one wild Pokemon will show up to the battle instead of two
#define FOLLOWER_WILD_BATTLE_VS_2           TRUE

#endif // GUARD_CONSTANTS_FOLLOW_ME_H
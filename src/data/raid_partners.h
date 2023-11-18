const struct RaidPartnerData sRaidPartnerData_Rank1[]=
{
	{
        .trainerNum = TRAINER_NONE,
        .graphicsId = OBJ_EVENT_GFX_SNORLAX_SLEEPING,
        .trainerBackPic = TRAINER_BACK_PIC_BRENDAN,
    },
    {
		.trainerNum = TRAINER_STEVEN,
		.graphicsId = OBJ_EVENT_GFX_STEVEN,
		.trainerBackPic = TRAINER_BACK_PIC_STEVEN,
	},
	{
		.trainerNum = TRAINER_MAY_LILYCOVE_MUDKIP,
		.graphicsId = OBJ_EVENT_GFX_MAY_NORMAL,
		.trainerBackPic = TRAINER_BACK_PIC_MAY,
	},
	{
		.trainerNum = TRAINER_RED_VICTORY_ROAD,
		.graphicsId = OBJ_EVENT_GFX_RED,
		.trainerBackPic = TRAINER_BACK_PIC_RED,
	},
	// wally
	// steven
	// brendan
	// may
	// chase
	// elaine
	// gold
	// lyra
	// red
	// leaf
	// lucas
	// dawn
};

const struct RaidPartner gRaidPartners[MAX_RAID_RANK + 1] =
{
	[NO_RAID]     = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
    [RAID_RANK_1] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_2] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_3] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_4] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_5] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_6] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
    [RAID_RANK_7] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
};

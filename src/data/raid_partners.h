const struct RaidPartnerData sRaidPartnerData_Rank0[] = {};

const struct RaidPartnerData sRaidPartnerData_Rank1[] =
{
    {
		.trainerNum = PARTNER_STEVEN,
		.graphicsId = OBJ_EVENT_GFX_STEVEN,
	},
	{
		.trainerNum = TRAINER_RIVAL_OVERRIDE,
		.graphicsId = OBJ_EVENT_GFX_MAY_NORMAL,
	},
	{
		.trainerNum = TRAINER_RED_OVERRIDE,
		.graphicsId = OBJ_EVENT_GFX_RED,
	},
	{
		.trainerNum = TRAINER_WALLY_OVERRIDE,
		.graphicsId = OBJ_EVENT_GFX_WALLY,
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

	// old man FRLG
	// pokedude FRLG
	// cynthia
};

const struct RaidPartner gRaidPartners[MAX_RAID_RANK + 1] =
{
	[NO_RAID]     = {sRaidPartnerData_Rank0, NELEMS(sRaidPartnerData_Rank0)},
    [RAID_RANK_1] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_2] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_3] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_4] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_5] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
	[RAID_RANK_6] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
    [RAID_RANK_7] = {sRaidPartnerData_Rank1, NELEMS(sRaidPartnerData_Rank1)},
};

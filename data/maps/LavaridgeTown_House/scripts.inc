LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_EventScript_SuckerPunchTM::
	lock
	faceplayer
	checkitem ITEM_TM94_SUCKER_PUNCH, 1
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_House_EventScript_ReceivedTM94
	msgbox MoveTutor_MimicTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_MimicDeclined
	msgbox LavaridgeTown_House_Text_GiveTM94, MSGBOX_DEFAULT
	giveitem ITEM_TM94_SUCKER_PUNCH
	msgbox LavaridgeTown_House_Text_HaveTM94, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_EventScript_ReceivedTM94::
	msgbox LavaridgeTown_House_Text_HaveTM94, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_Text_HaveTM94::
	.string "TM94 teaches Sucker Punch.\p"
	.string "It's a move that may go first if the\n"
	.string "target Pokémon is about to attack.$"

LavaridgeTown_House_Text_GiveTM94::
	.string "Too bad!\p"
	.string "You can have this TM instead.$"

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
	.string "My wife's warming an Egg in the hot\n"
	.string "springs. This is what she told me.\p"
	.string "She left two Pokémon with the Day Care.\n"
	.string "And they discovered that Egg!$"

LavaridgeTown_House_Text_Zigzagoon:
	.string "Zigzagoon: Pshoo!$"


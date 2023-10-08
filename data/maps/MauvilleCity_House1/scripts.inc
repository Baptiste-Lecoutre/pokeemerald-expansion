MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House1_EventScript_ReceiveRockSmash
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House1_EventScript_ReceiveRockSmash
	goto MauvilleCity_House1_EventScript_DontReceiveRockSmash
MauvilleCity_House1_EventScript_ReceiveRockSmash:
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_DontReceiveRockSmash::
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeDontTakeThis, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "I hear people call me the Rock Smash\n"
	.string "Guy, but I find that sort of degrading.\p"
	.string "I think I deserve a bit more respect,\n"
	.string "like maybe the Rock Smash Cool Guy.\p"
	.string "Woohoo!\p"
	.string "Anyways, you look pretty cool with\n"
	.string "this bike.\p"
	.string "I like that!\n"
	.string "You know what else is cool?\p"
	.string "Smashing rocks!\n"
	.string "Here, take this Hidden Machine!$"

MauvilleCity_House1_Text_ImRockSmashDudeDontTakeThis:
	.string "Woohoo!\p"
	.string "I hear people call me the Rock Smash\n"
	.string "Guy, but I find that sort of degrading.\p"
	.string "I think I deserve a bit more respect,\n"
	.string "like maybe the Rock Smash Cool Guy.\p"
	.string "Woohoo!\p"
	.string "Anyways, I like cool guys.\p"
	.string "You look like you have some potential,\n"
	.string "but you lack something to be cool.\p"
	.string "I know! What about a bike?\p"
	.string "Come back here all biker and cool,\n"
	.string "and I'll gift you something cooler!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "That HM contains Rock Smash.\p"
	.string "If you come across large boulders\n"
	.string "that block your path…\p"
	.string "Well, use that HM move and smash\n"
	.string "them right out of your way!\p"
	.string "Yes, sir! Smash rocks aside, I say!\n"
	.string "So cool! Woohoo!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, yes, if you smash a rock, a Pokémon\n"
	.string "could come flying out of hiding.\p"
	.string "Woohoo!$"


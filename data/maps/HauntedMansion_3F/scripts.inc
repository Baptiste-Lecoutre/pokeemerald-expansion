.set LOCALID_GIRL, 1

HauntedMansion_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedMansion_3F_OnTransition
	.byte 0

HauntedMansion_3F_OnTransition:
	call_if_gt VAR_LAVARIDGE_TOWN_STATE, 5, LavaridgeTown_EventScript_RemoveLittleGirl
	end

HauntedMansion_3F_EventScript_RemoveLittleGirl::
	setflag FLAG_TEMP_B
	removeobject LOCALID_GIRL
	return

HauntedMansion_3F_EventScript_LittleGirl::
	lockall
	msgbox HauntedMansion_3F_Text_WhoAreYou, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_GENGAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement OBJ_EVENT_ID_FOLLOW_ME, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIRL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_FOLLOW_ME, Common_Movement_ExclamationMark
	applymovement LOCALID_GIRL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_FOLLOW_ME, Common_Movement_Delay48
	applymovement LOCALID_GIRL, Common_Movement_Delay48
	waitmovement 0
	msgbox HauntedMansion_3F_Text_WhatWasThatNoise, MSGBOX_DEFAULT
	closemessage
	specialvar VAR_RESULT, IsPokeballPocketEmpty
	call_if_eq VAR_RESULT, TRUE, HauntedMansion_3F_EventScript_GiveFreePokeball
	preparefixedraid RAID_TYPE_MEGA, RAID_RANK_4, SPECIES_GENGAR, 40, ITEM_GENGARITE
	specialvar VAR_0x8007, GetHighestLevelInPlayerParty
	special InitStoryRaid
	doraidbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, HauntedMansion_3F_EventScript_LostGengarBattle
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement OBJ_EVENT_ID_FOLLOW_ME, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_GIRL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox HauntedMansion_3F_Text_TheGhostIsItGone, MSGBOX_DEFAULT
	closemessage
	facefollower
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, HauntedMansion_3F_EventScript_MayGoBack
	goto_if_eq VAR_RESULT, FEMALE, HauntedMansion_3F_EventScript_BrendanGoBack
HauntedMansion_3F_EventScript_LittleGirlEnd::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_GIRL
	setflag FLAG_TEMP_B
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_LAVARIDGE_TOWN_STATE, 6
	releaseall
	end

HauntedMansion_3F_EventScript_MayGoBack::
	msgbox HauntedMansion_3F_Text_MayTeleportYouBack, MSGBOX_NPC
	goto HauntedMansion_3F_EventScript_LittleGirlEnd

HauntedMansion_3F_EventScript_BrendanGoBack::
	msgbox HauntedMansion_3F_Text_BrendanTeleportYouBack, MSGBOX_NPC
	goto HauntedMansion_3F_EventScript_LittleGirlEnd

HauntedMansion_3F_EventScript_LostGengarBattle::
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

HauntedMansion_3F_EventScript_GiveFreePokeball::
	additem ITEM_POKE_BALL, 1
	return

HauntedMansion_3F_Text_WhoAreYou:
	.string "Kid: Wh- Who are you?\n"
	.string "Oh you were searching for me?\p"
	.string "I'm… I'm scared!\p"
	.string "I was playing the Ashen Woods when\n"
	.string "something invisible grabbed me and\l"
	.string "pulled me in this scary mansion…\p"
	.string "Was that a ghost? Did you see it?$"

HauntedMansion_3F_Text_WhatWasThatNoise:
	.string "Kid: That noise! It's the ghost!\n"
	.string "It's coming back! Aaaaah!$"

HauntedMansion_3F_Text_TheGhostIsItGone:
	.string "Kid: The ghost…\n"
	.string "Is it gone?$"

HauntedMansion_3F_Text_MayTeleportYouBack:
	.string "May: Yes!\n"
	.string "I'll use my psychic Pokémon to\l"
	.string "teleport you back to Lavaridge Town.\p"
	.string "Your grandma is waiting for you,\n"
	.string "she was really worried!\p"
	.string "I'll join you soon after, I have to\n"
	.string "escort {PLAYER}{KUN} out of this mansion…\p"
	.string "See you soon!$"

HauntedMansion_3F_Text_BrendanTeleportYouBack:
	.string "Brendan: Yup!\n"
	.string "I'll use my psychic Pokémon\l"
	.string "to send you back to Lavaridge Town.\p"
	.string "Your granny is waiting for you,\n"
	.string "she was really worried!\l"
	.string "Almost like one of these ghosts!\p"
	.string "I'll see you soon after, I gotta\n"
	.string "help {PLAYER} out of this mansion…\p"
	.string "Bye for now!$"

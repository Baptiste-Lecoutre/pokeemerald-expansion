.set LOCALID_GIRL, 1

HauntedMansion_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedMansion_3F_OnTransition
	.byte 0

HauntedMansion_3F_OnTransition:
	call_if_gt VAR_LAVARIDGE_TOWN_STATE, 2, LavaridgeTown_EventScript_RemoveLittleGirl
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
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GIRL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_ExclamationMark
	applymovement LOCALID_GIRL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_Delay48
	applymovement LOCALID_GIRL, Common_Movement_Delay48
	waitmovement 0
	msgbox HauntedMansion_3F_Text_WhatWasThatNoise, MSGBOX_DEFAULT
	closemessage
	preparefixedraid 2, 4, SPECIES_GENGAR, 40, ITEM_GENGARITE
	specialvar VAR_0x8007, GetHighestLevelInPlayerParty
	special InitStoryRaid
	doraidbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, HauntedMansion_3F_EventScript_LostGengarBattle
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_GIRL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox HauntedMansion_3F_Text_TheGhostIsItGone, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, HauntedMansion_3F_EventScript_MayGoBack
	call_if_eq VAR_RESULT, FEMALE, HauntedMansion_3F_EventScript_BrendanGoBack
	setvar VAR_POKE_VIAL_MAX_CHARGES, 2
	setvar VAR_LAVARIDGE_TOWN_STATE, 3
	fadescreenswapbuffers FADE_TO_BLACK
	destroyfollower
	removeobject LOCALID_GIRL
	setflag FLAG_TEMP_B
	fadescreenswapbuffers FADE_FROM_BLACK
	callnative UpdateFollowingPokemon
	releaseall
	end

HauntedMansion_3F_EventScript_MayGoBack::
	msgbox HauntedMansion_3F_Text_MayGoNorman, MSGBOX_NPC
	return

HauntedMansion_3F_EventScript_BrendanGoBack::
	msgbox HauntedMansion_3F_Text_BrendanGoNorman, MSGBOX_NPC
	return

HauntedMansion_3F_EventScript_LostGengarBattle::
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

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

HauntedMansion_3F_Text_MayGoNorman:
	.string "May: Yes!\n"
	.string "I'll escort you back to Lavarige Town.\p"
	.string "{PLAYER}{KUN}, I can see\n"
	.string "you're trying hard because you don't\l"
	.string "want to lose to me, I bet!\p"
	.string "You should take one of my Pokévial\n"
	.string "charges for the trip back.\p"
	.string "{PLAYER}{KUN}, I think I should challenge\n"
	.string "your dad in Petalburg Gym.\p"
	.string "See you again!$"

HauntedMansion_3F_Text_BrendanGoNorman:
	.string "Brendan: Yup!\n"
	.string "I'll escort you back to Lavarige Town.\p"
	.string "Here {PLAYER}, take one of my Pokévial\n"
	.string "charges for the trip back.\p"
	.string "As for me…\n"
	.string "I'm considering challenging Norman,\l"
	.string "the Gym Leader of Petalburg.\p"
	.string "Unlike you, {PLAYER}, your dad looks like\n"
	.string "he really is tough.\p"
	.string "See you around!$"
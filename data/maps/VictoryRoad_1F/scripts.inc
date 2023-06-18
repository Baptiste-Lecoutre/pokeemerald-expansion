.set LOCALID_WALLY_ENTRANCE, 4
.set LOCALID_RED, 10
.set LOCALID_RIVAL, 11

VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call VictoryRoad_1F_EventScript_HideRival
	call_if_defeated TRAINER_WALLY_VR_1, VictoryRoad_1F_EventScript_HideRed
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_HideRival::
	setflag FLAG_TEMP_7
	removeobject LOCALID_RIVAL
	return

VictoryRoad_1F_EventScript_HideRed::
	setflag FLAG_TEMP_8
	removeobject LOCALID_RED
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	addobject LOCALID_RIVAL
	call_if_set FLAG_TEMP_8, VictoryRoad_1F_EventScript_ShowRed
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RED, VictoryRoad_1F_Movement_RedApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedVictoryRoad, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, VictoryRoad_1F_EventScript_MayLaunchBattle1
	goto_if_eq VAR_RESULT, FEMALE, VictoryRoad_1F_EventScript_BrendanLaunchBattle1
	end

VictoryRoad_1F_EventScript_MayLaunchBattle1::
	msgbox VictoryRoad_1F_Text_MayWasWorking, MSGBOX_DEFAULT
	choose_mons
	multi_2_vs_2 TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat, TRAINER_RED_VICTORY_ROAD, VictoryRoad_1F_Text_RedDefeat, TRAINER_WALLACE, TRAINER_BACK_PIC_MAY
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedIllTrainAndBecome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_TEMP_8
	removeobject LOCALID_RED
	fadescreen FADE_FROM_BLACK
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox VictoryRoad_1F_Text_MayGladItWentWell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalExit
	waitmovement 0
	setflag FLAG_TEMP_7
	removeobject LOCALID_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_EventScript_BrendanLaunchBattle1::
	msgbox VictoryRoad_1F_Text_BrendanWasWorking, MSGBOX_DEFAULT
	choose_mons
	multi_2_vs_2 TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat, TRAINER_RED_VICTORY_ROAD, VictoryRoad_1F_Text_RedDefeat, TRAINER_WALLACE, TRAINER_BACK_PIC_BRENDAN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedIllTrainAndBecome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_TEMP_8
	removeobject LOCALID_RED
	fadescreen FADE_FROM_BLACK
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox VictoryRoad_1F_Text_BrendanGladItWentWell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalExit
	waitmovement 0
	setflag FLAG_TEMP_7
	removeobject LOCALID_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	addobject LOCALID_RIVAL
	call_if_set FLAG_TEMP_8, VictoryRoad_1F_EventScript_ShowRed
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RED, VictoryRoad_1F_Movement_RedApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedVictoryRoad, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, VictoryRoad_1F_EventScript_MayLaunchBattle2
	goto_if_eq VAR_RESULT, FEMALE, VictoryRoad_1F_EventScript_BrendanLaunchBattle2
	end

VictoryRoad_1F_EventScript_MayLaunchBattle2::
	msgbox VictoryRoad_1F_Text_MayWasWorking, MSGBOX_DEFAULT
	choose_mons
	multi_2_vs_2 TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat, TRAINER_RED_VICTORY_ROAD, VictoryRoad_1F_Text_RedDefeat, TRAINER_WALLACE, TRAINER_BACK_PIC_MAY
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedIllTrainAndBecome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_TEMP_8
	removeobject LOCALID_RED
	fadescreen FADE_FROM_BLACK
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox VictoryRoad_1F_Text_MayGladItWentWell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalExit
	waitmovement 0
	setflag FLAG_TEMP_7
	removeobject LOCALID_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_EventScript_BrendanLaunchBattle2::
	msgbox VictoryRoad_1F_Text_BrendanWasWorking, MSGBOX_DEFAULT
	choose_mons
	multi_2_vs_2 TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat, TRAINER_RED_VICTORY_ROAD, VictoryRoad_1F_Text_RedDefeat, TRAINER_WALLACE, TRAINER_BACK_PIC_BRENDAN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox VictoryRoad_1F_Text_RedIllTrainAndBecome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_TEMP_8
	removeobject LOCALID_RED
	fadescreen FADE_FROM_BLACK
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox VictoryRoad_1F_Text_BrendanGladItWentWell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, VictoryRoad_1F_Movement_RivalExit
	waitmovement 0
	setflag FLAG_TEMP_7
	removeobject LOCALID_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_EventScript_ShowRed::
	addobject LOCALID_RED
	return

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_RedApproachPlayer1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VictoryRoad_1F_Movement_RedApproachPlayer2:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VictoryRoad_1F_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

VictoryRoad_1F_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

VictoryRoad_1F_Movement_RivalExit:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_MayWasWorking:
	.string "May: Hi {PLAYER}!\p"
	.string "I was working on the Pokédex with\n"
	.string "my dad, but I missed the action\l"
	.string "and the battles.\p"
	.string "So I figured I should aim for the\n"
	.string "Pokémon League and challenge you!\p"
	.string "Are they teaming up against you?\n"
	.string "I'll lend you a hand!$"

VictoryRoad_1F_Text_BrendanWasWorking:
	.string "Brendan: Hi {PLAYER}!\p"
	.string "I was working on the Pokédex with\n"
	.string "my dad, but I missed the action\l"
	.string "and the battles.\p"
	.string "So I figured I should aim for the\n"
	.string "Pokémon League and challenge you!\p"
	.string "Are they teaming up against you?\n"
	.string "I Guess I'll lend you a hand!$"

VictoryRoad_1F_Text_RedVictoryRoad:
	.string "Red: Victory Road, the last challenge\n"
	.string "before the Pokémon League…\p"
	.string "No wonder I meet you in this place,\n"
	.string "{PLAYER}!\p"
	.string "Let me see if you are ready for\n"
	.string "the Elite Four!$"

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "Wally: Hi! {PLAYER}!\p"
	.string "I bet you're surprised to see me here!\p"
	.string "I made it all the way here, and it's\n"
	.string "all thanks to you!\p"
	.string "{PLAYER}, losing to you that time\n"
	.string "made me stronger!\p"
	.string "But I'm not going to lose anymore!\p"
	.string "I'm going to win! For the Pokémon who\n"
	.string "gave me courage and strength!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "Wow!\n"
	.string "{PLAYER}, you are strong, after all!$"

VictoryRoad_1F_Text_RedDefeat:
	.string "I lost again…$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "Wally: I couldn't beat you today,\n"
	.string "{PLAYER}, but one of these days, I'll\l"
	.string "catch up to you!$"

VictoryRoad_1F_Text_WallyIntro:
	.string "Wally: Hi! {PLAYER}!\p"
	.string "I've gotten stronger since that last\n"
	.string "time! I wanted to show you, {PLAYER}!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "Wow!\n"
	.string "{PLAYER}, you are strong, after all!$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "Wally: I couldn't beat you this time,\n"
	.string "too… But one of these days, {PLAYER},\l"
	.string "I'm going to catch up to you…\p"
	.string "And challenge the Pokémon League!$"

VictoryRoad_1F_Text_RedIllTrainAndBecome:
	.string "Red: Once again I lost to you…\n"
	.string "I'm far from becoming Kanto's best\l"
	.string "trainer.\p"
	.string "I'll train even more and become one of\n"
	.string "the most powerful trainers ever.\p"
	.string "Bye.$"

VictoryRoad_1F_Text_MayGladItWentWell:
	.string "May: I'm glad everything went well!\p"
	.string "I'll head back to the Pokémon center\n"
	.string "and train more before challenging the\l"
	.string "the Pokémon League. See you!$"

VictoryRoad_1F_Text_BrendanGladItWentWell:
	.string "Brendan: I'm glad everything went well!\p"
	.string "I'll head back to the Pokémon center\n"
	.string "and train more before challenging the\l"
	.string "the Pokémon League. See you!$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "I've made it this far a couple times,\n"
	.string "but the last stretch is so long…$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "My dream ends here again…$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "You've made it this far. Keep the\n"
	.string "momentum going and become the\l"
	.string "Champion! If anyone can, it's you!$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "I didn't come all this way to lose now.\n"
	.string "That possibility doesn't exist!$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "Impossible…\n"
	.string "I lost?$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "I lost here…\p"
	.string "That means I lack the qualifications\n"
	.string "to become the Champion…$"

VictoryRoad_1F_Text_HopeIntro:
	.string "This seemingly infinite and harsh road\n"
	.string "lives up to its name of Victory.$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "Your battle style is fantastic…$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "You seem to have the potential for\n"
	.string "becoming the Champion.$"

VictoryRoad_1F_Text_QuincyIntro:
	.string "What is the Victory Road?\n"
	.string "I'll tell you if you win!$"

VictoryRoad_1F_Text_QuincyDefeat:
	.string "Okay!\n"
	.string "Well done!$"

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "Getting through here safely--that's\n"
	.string "the final test for any Trainer aiming\l"
	.string "to become the Pokémon Champion.\p"
	.string "That's why it's called the Victory\n"
	.string "Road.$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "I have nothing to say to anyone\n"
	.string "that's come this far. Come on!$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "This is a disgrace…$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "Humph, go right on ahead.\n"
	.string "See if I care.$"

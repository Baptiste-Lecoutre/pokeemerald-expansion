.set LOCALID_GRUNT_1, 12
.set LOCALID_GRUNT_2, 13
.set LOCALID_GRUNT_3, 14
.set LOCALID_RED, 30
.set LOCALID_RED_TREE, 15

Route121_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route121_OnTransition
	.byte 0

Route121_OnTransition:
	goto_if_defeated TRAINER_RED_ROUTE121, Route121_EventScript_HideRed
	end

Route121_EventScript_HideRed::
	setflag FLAG_TEMP_7
	removeobject LOCALID_RED
	return

Route121_EventScript_Woman::
	msgbox Route121_Text_AheadLoomsMtPyre, MSGBOX_NPC
	end

Route121_EventScript_MtPyrePierSign::
	msgbox Route121_Text_MtPyrePierSign, MSGBOX_SIGN
	end

Route121_EventScript_SafariZoneSign::
	msgbox Route121_Text_SafariZoneSign, MSGBOX_SIGN
	end

Route121_EventScript_AquaGruntsMoveOut::
	lockall
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox Route121_Text_OkayMoveOutToMtPyre, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_1, Route121_Movement_Grunt1Exit
	applymovement LOCALID_GRUNT_2, Route121_Movement_Grunt2Exit
	applymovement LOCALID_GRUNT_3, Route121_Movement_Grunt3Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	goto Route121_EventScript_RedScene
	setvar VAR_ROUTE121_STATE, 1
	releaseall
	end

Route121_EventScript_RedScene::
	applymovement LOCALID_RED, Route121_Movement_RedMoveLeft
	waitmovement 0
	applymovement LOCALID_RED_TREE, Movement_CutTreeDown
	waitmovement 0
	removeobject LOCALID_RED_TREE
	getplayerxy VAR_0x8004, VAR_0x8005
	switch VAR_0x8005
	case 5, Route121_EventScript_MoveRed0
	case 6, Route121_EventScript_MoveRed1
	case 7, Route121_EventScript_MoveRed2
	case 8, Route121_EventScript_MoveRed3
	goto Route121_EventScript_Red
	return

Route121_EventScript_Red::
	msgbox Route121_Text_OhHeyPlayer, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_RED_ROUTE121, Route121_Text_DidntTrainEnough
	msgbox Route121_Text_ImImpressed, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_RED
	setflag FLAG_TEMP_7
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_ROUTE121_STATE, 1
	releaseall
	end

Route121_Text_OhHeyPlayer:
	.string "Oh, hey {PLAYER}!\p"
	.string "I was looking for great Pokémons in\n"
	.string "the Safari zone, but then I heard those\l"
	.string "weird people scaring the Pokémons…\p"
	.string "By the way, have you gotten any better?\n"
	.string "Let's test your training!$"

Route121_Text_DidntTrainEnough:
	.string "I didn't train enough…$"

Route121_Text_ImImpressed:
	.string "I'm impressed by how strong you've become!\n"
	.string "Will you try to challenge the Pokémon\l"
	.string "League?\p"
	.string "The path is still long, but I'm sure you\n"
	.string "can get there!\p"
	.string "I'll train a lot, even more than you, and\n"
	.string "I'll challenge you there! See you!$"

Route121_EventScript_MoveRed0::
	applymovement LOCALID_RED, Route121_Movement_RedApproach0
	waitmovement 0
	goto Route121_EventScript_Red
	end

Route121_EventScript_MoveRed1::
	applymovement LOCALID_RED, Route121_Movement_RedApproach1
	waitmovement 0
	goto Route121_EventScript_Red
	end

Route121_EventScript_MoveRed2::
	applymovement LOCALID_RED, Route121_Movement_RedApproach2
	waitmovement 0
	goto Route121_EventScript_Red
	end

Route121_EventScript_MoveRed3::
	applymovement LOCALID_RED, Route121_Movement_RedApproach3
	waitmovement 0
	goto Route121_EventScript_Red
	end

Route121_Movement_RedMoveLeft:
	walk_left
	step_end

Route121_Movement_RedApproach0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route121_Movement_RedApproach1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	step_end

Route121_Movement_RedApproach2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

Route121_Movement_RedApproach3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

Route121_Movement_Grunt1Exit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route121_Movement_Grunt2Exit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route121_Movement_Grunt3Exit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route121_EventScript_Vanessa::
	trainerbattle_single TRAINER_VANESSA, Route121_Text_VanessaIntro, Route121_Text_VanessaDefeat
	msgbox Route121_Text_VanessaPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Walter::
	trainerbattle_single TRAINER_WALTER_1, Route121_Text_WalterIntro, Route121_Text_WalterDefeat, Route121_EventScript_RegisterWalter
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route121_EventScript_RematchWalter
	msgbox Route121_Text_WalterPostBattle, MSGBOX_DEFAULT
	release
	end

Route121_EventScript_RegisterWalter::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route121_Text_WalterRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WALTER_1
	release
	end

Route121_EventScript_RematchWalter::
	trainerbattle_rematch TRAINER_WALTER_1, Route121_Text_WalterRematchIntro, Route121_Text_WalterRematchDefeat
	msgbox Route121_Text_WalterPostRematch, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Tammy::
	trainerbattle_single TRAINER_TAMMY, Route121_Text_TammyIntro, Route121_Text_TammyDefeat
	msgbox Route121_Text_TammyPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Kate::
	trainerbattle_double TRAINER_KATE_AND_JOY, Route121_Text_KateIntro, Route121_Text_KateDefeat, Route121_Text_KateNotEnoughMons
	msgbox Route121_Text_KatePostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Joy::
	trainerbattle_double TRAINER_KATE_AND_JOY, Route121_Text_JoyIntro, Route121_Text_JoyDefeat, Route121_Text_JoyNotEnoughMons
	msgbox Route121_Text_JoyPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Jessica::
	trainerbattle_single TRAINER_JESSICA_1, Route121_Text_JessicaIntro, Route121_Text_JessicaDefeat, Route121_EventScript_RegisterJessica
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route121_EventScript_RematchJessica
	msgbox Route121_Text_JessicaPostBattle, MSGBOX_DEFAULT
	release
	end

Route121_EventScript_RegisterJessica::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route121_Text_JessicaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JESSICA_1
	release
	end

Route121_EventScript_RematchJessica::
	trainerbattle_rematch TRAINER_JESSICA_1, Route121_Text_JessicaRematchIntro, Route121_Text_JessicaRematchDefeat
	msgbox Route121_Text_JessicaPostRematch, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Cale::
	trainerbattle_single TRAINER_CALE, Route121_Text_CaleIntro, Route121_Text_CaleDefeat
	msgbox Route121_Text_CalePostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Myles::
	trainerbattle_single TRAINER_MYLES, Route121_Text_MylesIntro, Route121_Text_MylesDefeat
	msgbox Route121_Text_MylesPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Pat::
	trainerbattle_single TRAINER_PAT, Route121_Text_PatIntro, Route121_Text_PatDefeat
	msgbox Route121_Text_PatPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Marcel::
	trainerbattle_single TRAINER_MARCEL, Route121_Text_MarcelIntro, Route121_Text_MarcelDefeat
	msgbox Route121_Text_MarcelPostBattle, MSGBOX_AUTOCLOSE
	end

Route121_EventScript_Cristin::
	trainerbattle_single TRAINER_CRISTIN_1, Route121_Text_CristinIntro, Route121_Text_CristinDefeat, Route121_EventScript_RegisterCristin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route121_EventScript_RematchCristin
	msgbox Route121_Text_CristinPostBattle, MSGBOX_DEFAULT
	release
	end

Route121_EventScript_RegisterCristin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route121_Text_CristinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CRISTIN_1
	release
	end

Route121_EventScript_RematchCristin::
	trainerbattle_rematch TRAINER_CRISTIN_1, Route121_Text_CristinRematchIntro, Route121_Text_CristinRematchDefeat
	msgbox Route121_Text_CristinPostRematch, MSGBOX_AUTOCLOSE
	end

Route121_Text_OkayMoveOutToMtPyre:
	.string "Okay!\n"
	.string "We're to move out to Mt. Pyre!$"

Route121_Text_AheadLoomsMtPyre:
	.string "Ahead looms Mt. Pyre…\p"
	.string "It is a natural monument to the spirits \n"
	.string "of departed Pokémon…$"

Route121_Text_MtPyrePierSign:
	.string "Mt. Pyre Pier\p"
	.string "…The sign is old and worn out.\n"
	.string "The words are barely legible…$"

Route121_Text_SafariZoneSign:
	.string "“Filled with rare Pokémon!”\n"
	.string "Safari Zone$"


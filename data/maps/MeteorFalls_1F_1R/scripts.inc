.set LOCALID_MAGMA_GRUNT_1, 5
.set LOCALID_MAGMA_GRUNT_2, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_AQUA_GRUNT_1, 8
.set LOCALID_AQUA_GRUNT_2, 9
.set LOCALID_STEVEN, 11
.set LOCALID_RIVAL, 12

MeteorFalls_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	call Common_EventScript_SetupRivalGfxId
	end

MeteorFalls_1F_1R_EventScript_OpenStevensCave::
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, TRUE
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, TRUE
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, FALSE
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, TRUE
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, MeteorFalls_1F_1R_Movement_WalkDown2
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MeteorFalls_1F_1R_EventScript_May
	compare VAR_RESULT, FEMALE
	goto_if_eq MeteorFalls_1F_1R_EventScript_Brendan
MeteorFalls_1F_1R_EventScript_MagmaAfterBattle::
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	addobject LOCALID_ARCHIE
	addobject LOCALID_AQUA_GRUNT_1
	addobject LOCALID_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_WatchAquaLeave
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_WatchAquaLeave
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	special RemoveCameraObject
	addobject LOCALID_STEVEN
	applymovement LOCALID_STEVEN, MeteorFalls_1F_1R_Movement_StevenArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_StevenGiveMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING, 1
	msgbox MeteorFalls_1F_1R_Text_StevenExplainMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_SCEPTILITE
	waitmessage
	giveitem ITEM_BLAZIKENITE
	waitmessage
	giveitem ITEM_SWAMPERTITE
	waitmessage
	msgbox MeteorFalls_1F_1R_Text_StevenShouldLeave, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, MeteorFalls_1F_1R_Movement_StevenLeaves
	applymovement LOCALID_RIVAL, MeteorFalls_1F_1R_Movement_WatchStevenGo
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_WatchStevenGo
	waitmovement 0
	removeobject LOCALID_STEVEN
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	end

MeteorFalls_1F_1R_EventScript_May::
	msgbox MeteorFalls_1F_1R_Text_MayBozos, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_Brat, MSGBOX_DEFAULT
	closemessage
MeteorFalls_1F_1R_EventScript_MayAfterCancel::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_WalkDown2
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_MayPlayerHere, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, MeteorFalls_1F_1R_EventScript_CancelMultiBattle
	case YES, MeteorFalls_1F_1R_EventScript_MultiMay
	end

MeteorFalls_1F_1R_EventScript_Brendan::
	msgbox MeteorFalls_1F_1R_Text_BrendanJerks, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_Brat, MSGBOX_DEFAULT
	closemessage
MeteorFalls_1F_1R_EventScript_BrendanAfterCancel::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_WalkDown2
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BrendanPlayerHere, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, MeteorFalls_1F_1R_EventScript_CancelMultiBattle
	case YES, MeteorFalls_1F_1R_EventScript_MultiBrendan
	end

MeteorFalls_1F_1R_EventScript_MultiMay::
	msgbox MeteorFalls_1F_1R_Text_MayLetsBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_WalkRight1
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyLetsBattle, MSGBOX_DEFAULT
	choose_mons
    call_if_eq VAR_RESULT, 0, MeteorFalls_1F_1R_EventScript_ChooseMons
	switch VAR_STARTER_MON
	case 0, MeteorFalls_1F_1R_EventScript_MayBattleTreecko
	case 1, MeteorFalls_1F_1R_EventScript_MayBattleTorchic
	case 2, MeteorFalls_1F_1R_EventScript_MayBattleMudkip
	end

MeteorFalls_1F_1R_EventScript_MultiBrendan::
	msgbox MeteorFalls_1F_1R_Text_BrendayLetsBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_WalkRight1
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_CourtneyLetsBattle, MSGBOX_DEFAULT
	choose_mons
    call_if_eq VAR_RESULT, 0, MeteorFalls_1F_1R_EventScript_ChooseMons
	switch VAR_STARTER_MON
	case 0, MeteorFalls_1F_1R_EventScript_BrendanBattleTreecko
	case 1, MeteorFalls_1F_1R_EventScript_BrendanBattleTorchic
	case 2, MeteorFalls_1F_1R_EventScript_BrendanBattleMudkip
	end

MeteorFalls_1F_1R_EventScript_MayBattleTreecko::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, MAY_TREECKO_METEOR_FALLS, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_MayBattleTorchic::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, MAY_TORCHIC_METEOR_FALLS, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_MayBattleMudkip::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, MAY_MUDKIP_METEOR_FALLS, TRAINER_BACK_PIC_MAY
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_BrendanBattleTreecko::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, BRENDAN_TREECKO_METEOR_FALLS, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_BrendanBattleTorchic::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, BRENDAN_TORCHIC_METEOR_FALLS, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_BrendanBattleMudkip::
    multi_2_vs_2 TRAINER_COURTNEY_METEOR_FALLS, MeteorFalls_1F_1R_Text_CourtneyLose, TRAINER_GRUNT_METEOR_FALLS, MeteorFalls_1F_1R_Text_GruntLose, BRENDAN_MUDKIP_METEOR_FALLS, TRAINER_BACK_PIC_BRENDAN
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq MeteorFalls_1F_1R_EventScript_Lost
	goto MeteorFalls_1F_1R_EventScript_MagmaAfterBattle
    releaseall
    end

MeteorFalls_1F_1R_EventScript_ChooseMons::
    msgbox MeteorFalls_1F_1R_Text_ChooseMons, MSGBOX_DEFAULT
    choose_mons
    compare VAR_RESULT, 0
    goto_if_eq MeteorFalls_1F_1R_EventScript_CancelMultiBattle
    return

MeteorFalls_1F_1R_EventScript_CancelMultiBattle::
    msgbox MeteorFalls_1F_1R_Text_CancelMultiBattle, MSGBOX_DEFAULT
	setvar VAR_METEOR_FALLS_STATE, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	applymovement OBJ_EVENT_ID_CAMERA, MeteorFalls_1F_1R_Movement_Camera2
	waitmovement 0
	special RemoveCameraObject
	fadedefaultbgm
    releaseall
    end

MeteorFalls_1F_1R_EventScript_Lost::
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

MeteorFalls_1F_1R_EventScript_MultiCancelled::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, MeteorFalls_1F_1R_Movement_WalkDown2
	waitmovement 0
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, MeteorFalls_1F_1R_EventScript_MayAfterCancel
	goto_if_eq VAR_RESULT, FEMALE, MeteorFalls_1F_1R_EventScript_BrendanAfterCancel

MeteorFalls_1F_1R_EventScript_RivalTalkAfterBattle::
	lock
	faceplayer
	msgbox MeteorFalls_1F_1R_Text_RivalAfterBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Movement_WalkDown2:
	walk_down
	walk_down
	step_end

MeteorFalls_1F_1R_Movement_Camera2:
	walk_up
	walk_up
	step_end

MeteorFalls_1F_1R_Movement_WalkRight1:
	walk_right
	step_end


MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit:
	delay_16
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit:
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie:
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit:
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie:
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay:
	walk_in_place_faster_left
	delay_4
	walk_in_place_faster_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_Movement_WatchAquaLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_right
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MeteorFalls_1F_1R_Movement_StevenArrives:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

MeteorFalls_1F_1R_Movement_StevenLeaves:
	walk_up
	walk_up
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

MeteorFalls_1F_1R_Movement_WatchStevenGo:
	delay_16
	delay_16
	walk_in_place_faster_right
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end


MeteorFalls_1F_1R_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo::
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Text_StevenGiveMegaRing:
	.string "Steven: Hi, {PLAYER}{KUN}!\p"
	.string "It's me, Steven!\n"
	.string "We met in the cave near Dewford.\p"
	.string "I see you have already met some\n"
	.string "grunts of Team Aqua and Team Magma.\p"
	.string "These people are dangerous, someone\n"
	.string "needs to stop them.\p"
	.string "Since you have made it until here,\n"
	.string "I should give this Mega Ring, it\l"
	.string "will help you in upcoming battles.$"

MeteorFalls_1F_1R_Text_StevenExplainMegaRing:
	.string "This Mega Ring will allow certain\n"
	.string "Pokémon to Mega Evolve in battle.\p"
	.string "It's no good on its own, though.\p"
	.string "To Mega Evolve a Pokémon, you must\n"
	.string "also let it hold its Mega Stone.\p"
	.string "Then, press START before choosing a\n"
	.string "move.\p"
	.string "Mega Evolution is a very powerful\n"
	.string "technique, but I think you and your\l"
	.string "Pokémon are ready for it.\p"
	.string "Here, take these Mega Stones too.$"

MeteorFalls_1F_1R_Text_StevenShouldLeave:
	.string "I have to leave now, take care!$"

MeteorFalls_1F_1R_Text_MayBozos:
	.string "May: Give it up, you bozos!\n"
	.string "Let the professor go!$"

MeteorFalls_1F_1R_Text_BrendanJerks:
	.string "Brendan: Hey! You jerks!\n"
	.string "Let Professor Cozmo go!$"

MeteorFalls_1F_1R_Text_Brat:
	.string "Hmm?\p"
	.string "What's this?\n"
	.string "Who is this spoiled brat?$"

MeteorFalls_1F_1R_Text_MayPlayerHere:
	.string "May: {PLAYER}{KUN}! You came!\p"
	.string "We've got to save Professor Cozmo\n"
	.string "from these people!\p"
	.string "There are two of them…\n"
	.string "And two of us…\p"
	.string "{PLAYER}{KUN}, please!\n"
	.string "Battle together with me!$"

MeteorFalls_1F_1R_Text_BrendanPlayerHere:
	.string "Brendan: {PLAYER}! You finally made\n" 
	.string "it, huh!\p"
	.string "We've gotta protect the professor\n"
	.string "from these lunatics!\p"
	.string "There's two of them…\n"
	.string "And two of us, huh?\p"
	.string "Sorry to ask, {PLAYER}, but…\n"
	.string "Battle alongside me!$"

MeteorFalls_1F_1R_Text_MayLetsBattle:
	.string "Thanks a mill!$"

MeteorFalls_1F_1R_Text_BrendayLetsBattle:
	.string "Thanks, pal!$"

MeteorFalls_1F_1R_Text_CourtneyLetsBattle:
	.string "Ahahaha!\p"
	.string "You brats are no match for a Team\n"
	.string "Magma Admin!\p"
	.string "I'll put you in your place, kiddos!$"

MeteorFalls_1F_1R_Text_CourtneyLose:
	.string "Ahhh?! Did I go too easy on you?!$"

MeteorFalls_1F_1R_Text_GruntLose:
	.string "Are you telling me you're that strong\n"
	.string "and still just kids?!$"

MeteorFalls_1F_1R_Text_ChooseMons:
	.string "Choose which Pokémon will battle.$"

MeteorFalls_1F_1R_Text_CancelMultiBattle:
	.string "Oh, you've got to get ready first?\n"
	.string "OK, but please hurry!$"

MeteorFalls_1F_1R_Text_WithThisMeteorite:
	.string "Hehehe!\p"
	.string "Well, that's embarrasing.\n"
	.string "But it doesn't matter.\p"
	.string "With this Meteorite, that thing in\n"
	.string "Mt. Chimney will…$"

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma:
	.string "Heh?\p"
	.string "I don't know who you are, but if you get\n"
	.string "in the way of Team Magma, don't\l"
	.string "expect any mercy!$"

MeteorFalls_1F_1R_Text_HoldItRightThereMagma:
	.string "Hold it right there, Team Magma!\p"
	.string "You're badly mistaken if you think you\n"
	.string "can have your way with the world!$"

MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua:
	.string "Hehehe!\n"
	.string "Even Team Aqua joins us!\p"
	.string "But it's too much trouble to deal with\n"
	.string "you all…\p"
	.string "Heh, it doesn't matter!\p"
	.string "We've got the Meteorite, so off to\n"
	.string "Mt. Chimney we go!\p"
	.string "Hehehe! Be seeing you, you brats\n"
	.string "and Team Aqua dingbats!$"

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore:
	.string "Archie: Didn't I see you before?\n"
	.string "At Slateport's Museum?\p"
	.string "Ah, so your name is {PLAYER}.\p"
	.string "At the time, I thought you were one\n"
	.string "of Team Magma's goons.\p"
	.string "Humph…\n"
	.string "You're one odd kid.\p"
	.string "Team Magma is a dangerous group of\n"
	.string "total fanatics.\p"
	.string "They engage in destruction, claiming\n"
	.string "to expand the land mass.\p"
	.string "They are the rivals to us,\n"
	.string "the sea-loving Team Aqua!$"

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma:
	.string "Boss, we should give chase to\n"
	.string "Team Magma…$"

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo:
	.string "Archie: Yes, yes, we must!\n"
	.string "We've got to hurry.\p"
	.string "There's no telling what Team Magma\n"
	.string "will do at Mt. Chimney!$"

MeteorFalls_1F_1R_Text_ArchieFarewell:
	.string "Archie: {PLAYER}, you should keep\n"
	.string "an eye out for Team Magma, too.\p"
	.string "Farewell!$"

MeteorFalls_1F_1R_Text_MeetProfCozmo:
	.string "I… I'm Cozmo…\n"
	.string "I'm a Professor…\p"
	.string "Team Magma asked me to guide them\n"
	.string "to Meteor Falls…\p"
	.string "But they tricked me.\n"
	.string "They even took my Meteorite away…\p"
	.string "And then another similar bunch,\n"
	.string "Team Aqua showed up.\p"
	.string "After that…\n"
	.string "I don't understand any of it.\p"
	.string "But that Team Magma…\p"
	.string "What are they going to do with that\n"
	.string "Meteorite at Mt. Chimney?$"

MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney:
	.string "Prof. Cozmo: But that Team Magma…\p"
	.string "What are they going to do with that\n"
	.string "Meteorite at Mt. Chimney?$"

MeteorFalls_1F_1R_Text_RivalAfterBattle:
	.string "Never mind what's happened!\p"
	.string "I've got to get the professor back to\n"
	.string "his lab in Fallarbor!$"

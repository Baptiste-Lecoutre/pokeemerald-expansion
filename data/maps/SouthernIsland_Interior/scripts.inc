.set LOCALID_LATIOS, 2
.set LOCALID_LATIAS, 3

SouthernIsland_Interior_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SouthernIsland_Interior_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SouthernIsland_Interior_OnTransition
	.byte 0

SouthernIsland_Interior_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SouthernIsland_Interior_EventScript_TryRemoveLati
	end

SouthernIsland_Interior_EventScript_TryRemoveLati::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SouthernIsland_Interior_OnTransition:
	call SouthernIsland_Interior_EventScript_SetUpLatios
	call SouthernIsland_Interior_EventScript_SetUpLatias
	call SouthernIsland_Interior_EventScript_SetUpPlayerGfx
	end

SouthernIsland_Interior_EventScript_SetUpLatios::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_LATIOS
	setvar VAR_TEMP_4, SPECIES_LATIOS
	return

SouthernIsland_Interior_EventScript_SetUpLatias::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_LATIAS
	setvar VAR_TEMP_5, SPECIES_LATIAS
	return

SouthernIsland_Interior_EventScript_SetUpPlayerGfx::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SouthernIsland_Interior_EventScript_SetBrendanGfx
	goto_if_eq VAR_RESULT, FEMALE, SouthernIsland_Interior_EventScript_SetMayGfx
	end

SouthernIsland_Interior_EventScript_SetBrendanGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

SouthernIsland_Interior_EventScript_SetMayGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

SouthernIsland_Interior_EventScript_TryLatiEncounter::
	lockall
	setvar VAR_0x8008, 12  @ Player's Y coordinate. Not read
	goto SouthernIsland_Interior_EventScript_Lati
	end

SouthernIsland_Interior_EventScript_Lati::
	goto_if_set FLAG_TEMP_2, SouthernIsland_Interior_EventScript_Sign
	call_if_set FLAG_DEFEATED_LATIOS, SouthernIsland_Interior_EventScript_SignLatiasPart
	call_if_set FLAG_CAUGHT_LATIOS, SouthernIsland_Interior_EventScript_SignLatiasPart
	call_if_set FLAG_DEFEATED_LATIAS, SouthernIsland_Interior_EventScript_SignLatiosPart
	call_if_set FLAG_CAUGHT_LATIAS, SouthernIsland_Interior_EventScript_SignLatiosPart
	goto_if_unset FLAG_ENABLE_SHIP_SOUTHERN_ISLAND, SouthernIsland_Interior_EventScript_Sign
	setflag FLAG_ENCOUNTERED_LATIAS_OR_LATIOS
	setflag FLAG_TEMP_2
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SouthernIsland_Interior_Movement_CameraPanUp
	waitmovement 0
	delay 50
	waitse
	call_if_unset FLAG_TEMP_4, SouthernIsland_Interior_EventScript_PlayCryLatios
	call_if_unset FLAG_TEMP_5, SouthernIsland_Interior_EventScript_PlayCryLatias
	delay 30
	waitmoncry
	call_if_unset FLAG_TEMP_4, SouthernIsland_Interior_EventScript_AddLatios
	call_if_unset FLAG_TEMP_5, SouthernIsland_Interior_EventScript_AddLatias
	delay 30
	applymovement OBJ_EVENT_ID_CAMERA, SouthernIsland_Interior_Movement_CameraPanDown
	call_if_unset FLAG_TEMP_4, SouthernIsland_Interior_EventScript_MoveLatios
	call_if_unset FLAG_TEMP_5, SouthernIsland_Interior_EventScript_MoveLatias
	waitmovement 0
	delay 50
	special RemoveCameraObject
	releaseall
	end

SouthernIsland_Interior_EventScript_AddLatias::
	addobject LOCALID_LATIAS
	return

SouthernIsland_Interior_EventScript_AddLatios::
	addobject LOCALID_LATIOS
	return

SouthernIsland_Interior_EventScript_PlayCryLatias::
	playmoncry SPECIES_LATIAS, CRY_MODE_NORMAL
	return

SouthernIsland_Interior_EventScript_PlayCryLatios::
	playmoncry SPECIES_LATIOS, CRY_MODE_NORMAL
	return

SouthernIsland_Interior_EventScript_MoveLatios::
	applymovement LOCALID_LATIOS, SouthernIsland_Interior_Movement_LatiApproach
	return

SouthernIsland_Interior_EventScript_MoveLatias::
	applymovement LOCALID_LATIAS, SouthernIsland_Interior_Movement_LatiApproach
	return

Toto_dummy::
	setvar VAR_LAST_TALKED, LOCALID_LATIOS
	call_if_eq VAR_ROAMER_POKEMON, 0, SouthernIsland_Interior_EventScript_SetLatiosBattleVars
	call_if_ne VAR_ROAMER_POKEMON, 0, SouthernIsland_Interior_EventScript_SetLatiasBattleVars
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLatiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SouthernIsland_Interior_EventScript_LatiosDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SouthernIsland_Interior_EventScript_RanFromLati
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SouthernIsland_Interior_EventScript_RanFromLati
	setflag FLAG_CAUGHT_LATIOS
	releaseall
	end

SouthernIsland_Interior_EventScript_Latios::
	setvar VAR_LAST_TALKED, LOCALID_LATIOS
	call SouthernIsland_Interior_EventScript_SetLatiosBattleVars
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLatiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SouthernIsland_Interior_EventScript_LatiosDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SouthernIsland_Interior_EventScript_RanFromLati
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SouthernIsland_Interior_EventScript_RanFromLati
	setflag FLAG_CAUGHT_LATIOS
	releaseall
	end

SouthernIsland_Interior_EventScript_Latias::
	setvar VAR_LAST_TALKED, LOCALID_LATIAS
	call SouthernIsland_Interior_EventScript_SetLatiasBattleVars
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLatiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SouthernIsland_Interior_EventScript_LatiasDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SouthernIsland_Interior_EventScript_RanFromLati
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SouthernIsland_Interior_EventScript_RanFromLati
	setflag FLAG_CAUGHT_LATIAS
	releaseall
	end

SouthernIsland_Interior_EventScript_LatiosDefeated::
	setflag FLAG_DEFEATED_LATIOS
	copyvar VAR_0x8004, VAR_TEMP_4
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_LatiasDefeated::
	setflag FLAG_DEFEATED_LATIAS
	copyvar VAR_0x8004, VAR_TEMP_5
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_RanFromLati::
	copyvar VAR_0x8004, VAR_TEMP_4
	goto Common_EventScript_LegendaryFlewAway
	end

SouthernIsland_Interior_EventScript_SignLatiasPart::
	setflag FLAG_TEMP_4
	goto_if_set FLAG_DEFEATED_LATIAS, SouthernIsland_Interior_EventScript_Sign
	goto_if_set FLAG_CAUGHT_LATIAS, SouthernIsland_Interior_EventScript_Sign
	return

SouthernIsland_Interior_EventScript_SignLatiosPart::
	setflag FLAG_TEMP_5
	goto_if_set FLAG_DEFEATED_LATIOS, SouthernIsland_Interior_EventScript_Sign
	goto_if_set FLAG_CAUGHT_LATIOS, SouthernIsland_Interior_EventScript_Sign
	return


SouthernIsland_Interior_EventScript_Sign::
	msgbox SouthernIsland_Interior_Text_Sign, MSGBOX_DEFAULT
	goto_if_unset FLAG_RECEIVED_LATI_STONES SouthernIsland_Interior_EventScript_GiveLatiStones
	releaseall
	end

SouthernIsland_Interior_EventScript_GiveLatiStones::
	closemessage
	delay 20
	playse SE_M_DETECT
	dofieldeffectsparkle 13, 11, 0
	waitfieldeffect FLDEFF_SPARKLE
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	giveitem ITEM_LATIOSITE
	waitmessage
	giveitem ITEM_LATIASITE
	waitmessage
	giveitem ITEM_EON_FLUTE
	closemessage
	setflag FLAG_RECEIVED_LATI_STONES
	releaseall
	end

SouthernIsland_Interior_EventScript_SetLatiosBattleVars::
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	seteventmon SPECIES_LATIOS, VAR_RESULT, ITEM_SOUL_DEW
	return

SouthernIsland_Interior_EventScript_SetLatiasBattleVars::
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	seteventmon SPECIES_LATIAS, VAR_RESULT, ITEM_SOUL_DEW
	return

SouthernIsland_Interior_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	step_end

SouthernIsland_Interior_Movement_CameraPanDown:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_up
	step_end

SouthernIsland_Interior_Movement_LatiApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

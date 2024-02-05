.set LOCALID_KYOGRE, 1

MarineCave_End_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MarineCave_End_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MarineCave_End_OnTransition
	.byte 0

MarineCave_End_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MarineCave_End_EventScript_TryRemoveKyogre
	end

MarineCave_End_EventScript_TryRemoveKyogre::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_KYOGRE
	return

MarineCave_End_OnTransition:
	call_if_unset FLAG_DEFEATED_KYOGRE, MarineCave_End_EventScript_ShowKyogre
	end

MarineCave_End_EventScript_ShowKyogre::
	clearflag FLAG_HIDE_MARINE_CAVE_KYOGRE
	setvar VAR_TEMP_1, 1
	return

MarineCave_End_EventScript_Kyogre::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_KYOGRE, MarineCave_End_Movement_KyogreApproach
	waitmovement 0
	waitse
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_KYOGRE
@	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
@	setwildbattle SPECIES_KYOGRE, VAR_RESULT
	specialvar VAR_RESULT, IsPokeballPocketEmpty
	goto_if_eq VAR_RESULT, FALSE, MarineCave_End_EventScript_Kyogre_PrepareRaid
	additem ITEM_POKE_BALL
MarineCave_End_EventScript_Kyogre_PrepareRaid:
	preparefixedraid RAID_TYPE_PRIMAL, 7, SPECIES_KYOGRE, 70, ITEM_BLUE_ORB
	specialvar VAR_0x8007, GetHighestLevelInPlayerParty
	special InitStoryRaid
	setflag FLAG_SYS_CTRL_OBJ_DELETE
@	special BattleSetup_StartLegendaryBattle
@	waitstate
	doraidbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_TEMP_1, 0
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MarineCave_End_EventScript_DefeatedKyogre
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MarineCave_End_EventScript_RanFromKyogre
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MarineCave_End_EventScript_RanFromKyogre
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_KYOGRE
	releaseall
	end

MarineCave_End_EventScript_DefeatedKyogre::
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_KYOGRE
	goto Common_EventScript_RemoveStaticPokemon
	end

MarineCave_End_EventScript_RanFromKyogre::
	setvar VAR_0x8004, SPECIES_KYOGRE
	goto Common_EventScript_LegendaryFlewAway
	end

MarineCave_End_Movement_KyogreApproachBroken:
	init_affine_anim
	walk_down_start_affine
	delay_16
	delay_16
	walk_down_affine
	delay_16
	delay_16
	walk_down_affine
	step_end

MarineCave_End_Movement_KyogreApproach:
	walk_slow_down
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	walk_slow_down
	step_end

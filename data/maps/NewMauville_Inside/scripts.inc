.set LOCALID_SURGE, 9
.set LOCALID_ZAPDOS, 10

NewMauville_Inside_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, NewMauville_Inside_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, NewMauville_Inside_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, NewMauville_Inside_OnLoad
	.byte 0

NewMauville_Inside_OnResume:
	call_if_eq VAR_TEMP_1, 1, NewMauville_Inside_EventScript_SetBarrierStateBlueButton
	call_if_eq VAR_TEMP_2, 1, NewMauville_Inside_EventScript_SetBarrierStateGreenButton
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, NewMauville_Inside_EventScript_TryRemoveVoltorb
	end

NewMauville_Inside_EventScript_TryRemoveVoltorb::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

NewMauville_Inside_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	call_if_unset FLAG_DEFEATED_ELECTRODE_1_NEW_MAUVILLE, NewMauville_Inside_EventScript_ShowVoltorb1
	call_if_unset FLAG_DEFEATED_ELECTRODE_2_NEW_MAUVILLE, NewMauville_Inside_EventScript_ShowVoltorb2
	call_if_unset FLAG_DEFEATED_ELECTRODE_3_NEW_MAUVILLE, NewMauville_Inside_EventScript_ShowVoltorb3
	goto_if_defeated TRAINER_LT_SURGE NewMauville_Inside_EventScript_HideSurge
	end

NewMauville_Inside_EventScript_HideSurge::
	setflag FLAG_TEMP_7
	removeobject LOCALID_SURGE
	return

NewMauville_Inside_EventScript_ShowVoltorb1::
	clearflag FLAG_HIDE_NEW_MAUVILLE_ELECTRODE_1
	return

NewMauville_Inside_EventScript_ShowVoltorb2::
	clearflag FLAG_HIDE_NEW_MAUVILLE_ELECTRODE_2
	return

NewMauville_Inside_EventScript_ShowVoltorb3::
	clearflag FLAG_HIDE_NEW_MAUVILLE_ELECTRODE_3
	return

NewMauville_Inside_OnLoad:
	call_if_eq VAR_NEW_MAUVILLE_STATE, 2, NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	call_if_eq VAR_NEW_MAUVILLE_STATE, 4, NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	call_if_eq VAR_NEW_MAUVILLE_STATE, 6, NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	end

NewMauville_Inside_EventScript_Surge::
	lock
	faceplayer
	msgbox NewMauville_Inside_Text_ImSurge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LT_SURGE, NewMauville_Inside_Text_NowThatsAShowker
	msgbox NewMauville_Inside_Text_YoureSpecialKid, MSGBOX_DEFAULT
	giveitem ITEM_TM93 @ wild charge
	msgbox NewMauville_Inside_Text_MaybeThatBird, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_SURGE
	setflag FLAG_TEMP_7
	fadescreen FADE_FROM_BLACK
	releaseall
	end

NewMauville_Inside_Text_ImSurge:
	.string "Hey, kid! What do you think you're\n"
    .string "doing here? This bird is mine!\p"
    .string "You won't live long in combat!\n"
    .string "Not with your puny power!\p"
    .string "I tell you, kid, electric Pokémon\n"
    .string "saved me during the war!\p"
    .string "They zapped my enemies into\n"
    .string "paralysis!\p"
    .string "The same as I, Kanto's great Lt. Surge\n"
	.string "will do to you!$"

NewMauville_Inside_Text_YoureSpecialKid:
	.string "Now that's a shocker!\n"
	.string "You're the real deal, kid!$"

NewMauville_Inside_Text_NowThatsAShowker:
	.string "You're special, kid! Take this!$"

NewMauville_Inside_Text_MaybeThatBird:
	.string "Maybe that bird's a better fit for you.\n"
	.string "Time for me to retreat.$"

NewMauville_Inside_EventScript_BlueButton::
	lockall
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 0
	playse SE_PIN
	call NewMauville_Inside_EventScript_SetBarrierStateBlueButton
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_GreenButton::
	lockall
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 1
	playse SE_PIN
	call NewMauville_Inside_EventScript_SetBarrierStateGreenButton
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_SetBarrierStateBlueButton::
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 23, 36, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 23, 37, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 18, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 19, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 2, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 3, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 37, 35, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 37, 36, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 28, 24, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 28, 25, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 10, 26, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 10, 27, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Green_Top, TRUE
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Green_TopMid, TRUE
	setmetatile 21, 4, METATILE_BikeShop_Barrier_Green_BottomMid, TRUE
	setmetatile 21, 5, METATILE_BikeShop_Barrier_Green_Bottom, TRUE
	setmetatile 6, 11, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 13, 10, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 16, 22, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 4, 26, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 30, 38, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 2, 11, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 17, 10, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 25, 18, METATILE_BikeShop_Button_Green, FALSE
	setmetatile 18, 36, METATILE_BikeShop_Button_Green, FALSE
	return

NewMauville_Inside_EventScript_SetBarrierStateGreenButton::
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 23, 36, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 23, 37, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 10, 18, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 10, 19, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Blue_Top, TRUE
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Blue_TopMid, TRUE
	setmetatile 10, 2, METATILE_BikeShop_Barrier_Blue_BottomMid, TRUE
	setmetatile 10, 3, METATILE_BikeShop_Barrier_Blue_Bottom, TRUE
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 37, 35, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 37, 36, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 28, 24, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 28, 25, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 10, 26, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 10, 27, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Hidden_Top, TRUE
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Hidden_Bottom, TRUE
	setmetatile 21, 4, METATILE_BikeShop_Floor_Shadow_Top, FALSE
	setmetatile 21, 5, METATILE_BikeShop_Wall_Edge_Top, FALSE
	setmetatile 2, 11, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 17, 10, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 25, 18, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 18, 36, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 6, 11, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 13, 10, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 16, 22, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 4, 26, METATILE_BikeShop_Button_Blue, FALSE
	setmetatile 30, 38, METATILE_BikeShop_Button_Blue, FALSE
	return

NewMauville_Inside_EventScript_RedButton::
	lockall
	msgbox NewMauville_Inside_Text_SteppedOnSwitchGeneratorStopped, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 2
	releaseall
	end

NewMauville_Inside_EventScript_Rotom::
	lockall
	playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewMauville_Inside_Text_GeneratorRestarted, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOnMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 3
	releaseall
	end

NewMauville_Inside_EventScript_RedButton2::
	lockall
	msgbox NewMauville_Inside_Text_SteppedOnSwitchGeneratorStopped, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 4
	releaseall
	end

NewMauville_Inside_EventScript_Rotom2::
	lockall
	playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewMauville_Inside_Text_GeneratorRestartedAgain, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOnMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 5
	releaseall
	end

NewMauville_Inside_EventScript_RotomEncounter::
	lock
	faceplayer
	setmetatile 33, 6, METATILE_BikeShop_Button_Pressed, 0
	special DrawWholeMapView
	playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	msgbox NewMauville_Inside_Text_PokemonCameOut, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_ROTOM, VAR_0x800A ITEM_NONE
	waitse
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedRotom
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, NewMauville_Inside_EventScript_PlayerCaughtRotom
	setvar VAR_NEW_MAUVILLE_STATE, 5
	release
	end

NewMauville_Inside_EventScript_DefeatedRotom::
	msgbox NewMauville_Inside_Text_RotomLeftGenerator, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 6
	release
	end

NewMauville_Inside_EventScript_PlayerCaughtRotom::
	msgbox NewMauville_Inside_Text_GeneratorStopped, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_SetGeneratorOffMetatiles
	setvar VAR_NEW_MAUVILLE_STATE, 6
	release
	end

NewMauville_Inside_EventScript_SetGeneratorOffMetatiles::
	setmetatile 33, 6, METATILE_BikeShop_Button_Pressed, FALSE
	setmetatile 32, 2, METATILE_BikeShop_Generator_Off_Tile0, TRUE
	setmetatile 33, 2, METATILE_BikeShop_Generator_Off_Tile1, TRUE
	setmetatile 34, 2, METATILE_BikeShop_Generator_Off_Tile2, TRUE
	setmetatile 35, 2, METATILE_BikeShop_Generator_Off_Tile3, TRUE
	setmetatile 32, 3, METATILE_BikeShop_Generator_Off_Tile4, TRUE
	setmetatile 33, 3, METATILE_BikeShop_Generator_Off_Tile5, TRUE
	setmetatile 34, 3, METATILE_BikeShop_Generator_Off_Tile6, TRUE
	setmetatile 35, 3, METATILE_BikeShop_Generator_Off_Tile7, TRUE
	special DrawWholeMapView
	return

NewMauville_Inside_EventScript_SetGeneratorOnMetatiles::
	setmetatile 33, 6, METATILE_BikeShop_Button_Red, FALSE
	setmetatile 32, 2, METATILE_BikeShop_Generator_On_Tile0, TRUE
	setmetatile 33, 2, METATILE_BikeShop_Generator_On_Tile1, TRUE
	setmetatile 34, 2, METATILE_BikeShop_Generator_On_Tile2, TRUE
	setmetatile 35, 2, METATILE_BikeShop_Generator_On_Tile3, TRUE
	setmetatile 32, 3, METATILE_BikeShop_Generator_On_Tile4, TRUE
	setmetatile 33, 3, METATILE_BikeShop_Generator_On_Tile5, TRUE
	setmetatile 34, 3, METATILE_BikeShop_Generator_On_Tile6, TRUE
	setmetatile 35, 3, METATILE_BikeShop_Generator_On_Tile7, TRUE
	special DrawWholeMapView
	return

NewMauville_Inside_EventScript_Generator::
	lockall
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, NewMauville_Inside_EventScript_GeneratorOff
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 4, NewMauville_Inside_EventScript_GeneratorOff
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 6, NewMauville_Inside_EventScript_GeneratorOff
	msgbox NewMauville_Inside_Text_GeneratorRadiatingHeat, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_GeneratorOff::
	msgbox NewMauville_Inside_Text_GeneratorQuietedDown, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_Voltorb1::
	lock
	faceplayer
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_ELECTRODE, VAR_0x800A
	waitse
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb1
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb1
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb1
	setflag FLAG_DEFEATED_ELECTRODE_1_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb1::
	setflag FLAG_DEFEATED_ELECTRODE_1_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_Voltorb2::
	lock
	faceplayer
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_ELECTRODE, VAR_0x800A
	waitse
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb2
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb2
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb2
	setflag FLAG_DEFEATED_ELECTRODE_2_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb2::
	setflag FLAG_DEFEATED_ELECTRODE_2_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_Voltorb3::
	lock
	faceplayer
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_ELECTRODE, VAR_0x800A
	waitse
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedVoltorb3
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_DefeatedVoltorb3
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_DefeatedVoltorb3
	setflag FLAG_DEFEATED_ELECTRODE_3_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_DefeatedVoltorb3::
	setflag FLAG_DEFEATED_ELECTRODE_3_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_Zapdos::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_ZAPDOS, VAR_0x800A, ITEM_WACAN_BERRY
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_EventScript_DefeatedZapdos
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_EventScript_RanFromZapdos
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_EventScript_RanFromZapdos
	setflag FLAG_DEFEATED_ZAPDOS
	release
	end

NewMauville_Inside_EventScript_DefeatedZapdos:: @ 8238F9F
	setflag FLAG_DEFEATED_ZAPDOS
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_RanFromZapdos:: @ 8238FA8
	setvar VAR_0x8004, SPECIES_ZAPDOS
	goto Common_EventScript_LegendaryFlewAway
	end

NewMauville_Inside_Text_GeneratorRadiatingHeat:
	.string "The generator is radiating heat that\n"
	.string "can be felt even at a distance.\p"
	.string "It looks like it should be turned off\n"
	.string "as soon as possible.$"

NewMauville_Inside_Text_GeneratorQuietedDown:
	.string "The generator quieted down.$"

NewMauville_Inside_Text_SteppedOnSwitchGeneratorStopped:
	.string "{PLAYER} stepped on the switch.\p"
	.string "Click…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "The generator appears to have\n"
	.string "stopped…$"

NewMauville_Inside_Text_GeneratorRestarted:
	.string "The generator restarted!$"

NewMauville_Inside_Text_GeneratorRestartedAgain:
	.string "The generator restarted again!$"

NewMauville_Inside_Text_RotomLeftGenerator:
	.string "Rotom left the generator and vanished…$"

NewMauville_Inside_Text_GeneratorStopped:
	.string "The generator appears to have\n"
	.string "stopped…$"

NewMauville_Inside_Text_PokemonCameOut:
	.string "A Pokémon came out of the generator!$"

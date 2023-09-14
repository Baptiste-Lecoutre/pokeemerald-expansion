SealedChamber_InnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Common_EventScript_RemoveOverworldAfterBattle
	.byte 0

SealedChamber_InnerRoom_EventScript_Regigigas::
	lock
	msgbox SealedChamber_InnerRoom_Text_RegigigasStatue, MSGBOX_DEFAULT
	closemessage
	braillemessage SealedChamber_InnerRoom_Braille_Regigigas
	waitbuttonpress
	closebraillemessage
	setvar VAR_0x8004, SPECIES_REGICE
	setvar VAR_0x8005, SPECIES_REGIROCK
	setvar VAR_0x8006, SPECIES_REGISTEEL
	setvar VAR_0x8007, 3
	specialvar VAR_RESULT, CheckSpeciesInParty
	goto_if_eq VAR_RESULT, FALSE, SealedChamber_InnerRoom_EventScript_RegigigasStatue
	setvar VAR_0x8004, SPECIES_REGIDRAGO
	setvar VAR_0x8005, SPECIES_REGIELEKI
	setvar VAR_0x8006, 0xFFFF
	setvar VAR_0x8007, 2
	specialvar VAR_RESULT, CheckSpeciesInParty
	goto_if_eq VAR_RESULT, FALSE, SealedChamber_InnerRoom_EventScript_RegigigasStatue
	waitse
	playmoncry SPECIES_REGIGIGAS, 2
	delay 40
	waitmoncry
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_REGIGIGAS, VAR_0x800A, ITEM_NORMAL_GEM
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SealedChamber_InnerRoom_EventScript_DefeatedRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SealedChamber_InnerRoom_EventScript_RanFromRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SealedChamber_InnerRoom_EventScript_RanFromRegigigas
	setflag FLAG_DEFEATED_REGIGIGAS
	release
	end

SealedChamber_InnerRoom_EventScript_DefeatedRegigigas::
	setflag FLAG_DEFEATED_REGIGIGAS
	goto Common_EventScript_RemoveStaticPokemon
	end

SealedChamber_InnerRoom_EventScript_RanFromRegigigas::
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	goto Common_EventScript_LegendaryFlewAway
	end

SealedChamber_InnerRoom_EventScript_RegigigasStatue::
	release
	end

SealedChamber_InnerRoom_EventScript_BrailleBackWall::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_FirstWailordLastRelicanth
	goto_if_set FLAG_REGI_DOORS_OPENED, SealedChamber_InnerRoom_EventScript_NoEffect
	specialvar VAR_RESULT, CheckRelicanthWailord
	goto_if_eq VAR_RESULT, FALSE, SealedChamber_InnerRoom_EventScript_NoEffect
	fadeoutbgm 0
	playse SE_TRUCK_MOVE
	special DoSealedChamberShakingEffect_Long
	waitstate
	delay 40
	special DoSealedChamberShakingEffect_Short
	waitstate
	playse SE_DOOR
	delay 40
	special DoSealedChamberShakingEffect_Short
	waitstate
	playse SE_DOOR
	delay 40
	special DoSealedChamberShakingEffect_Short
	waitstate
	playse SE_DOOR
	delay 40
	msgbox gText_DoorOpenedFarAway, MSGBOX_DEFAULT
	closemessage
	fadeinbgm 0
	setflag FLAG_REGI_DOORS_OPENED
	releaseall
	end

SealedChamber_InnerRoom_EventScript_NoEffect::
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart1::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_InThisCaveWeHaveLived
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart2::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_WeOweAllToThePokemon
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart3::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_ButWeSealedThePokemonAway
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart4::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_WeFearedIt
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart5::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_ThoseWithCourageHope
	releaseall
	end

SealedChamber_InnerRoom_EventScript_BrailleStoryPart6::
	lockall
	braillemsgbox SealedChamber_InnerRoom_Braille_OpenDoorEternalPokemonWaits
	releaseall
	end

SealedChamber_InnerRoom_Text_RegigigasStatue:
	.string "It's a statue of a Pokémon.\n"
	.string "It exudes tremendous power…\p"
	.string "There's something engraved on it…$"

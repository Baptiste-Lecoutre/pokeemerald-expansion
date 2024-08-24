EmberPath_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Common_EventScript_RemoveOverworldAfterBattle
	.byte 0

EmberPath_EventScript_Moltres::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES, 2
	delay 40
	waitmoncry
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	copyvar VAR_0x800A, VAR_RESULT
	setwildbattle SPECIES_MOLTRES, VAR_0x800A, ITEM_OCCA_BERRY
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, EmberPath_EventScript_DefeatedMoltres
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, EmberPath_EventScript_RanFromMoltres
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, EmberPath_EventScript_RanFromMoltres
	setflag FLAG_DEFEATED_MOLTRES
	release
	end

EmberPath_EventScript_DefeatedMoltres:: @ 8238F9F
	setflag FLAG_DEFEATED_MOLTRES
	goto Common_EventScript_RemoveStaticPokemon
	end

EmberPath_EventScript_RanFromMoltres:: @ 8238FA8
	setvar VAR_0x8004, SPECIES_MOLTRES
	goto Common_EventScript_LegendaryFlewAway
	end

EmberPath_EventScript_ThisIsTheWayTrigger1::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto EmberPath_EventScript_ThisIsTheWay

EmberPath_EventScript_ThisIsTheWayTrigger2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto EmberPath_EventScript_ThisIsTheWay

EmberPath_EventScript_ThisIsTheWayTrigger3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto EmberPath_EventScript_ThisIsTheWay

EmberPath_EventScript_ThisIsTheWay::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EmberPath_EventScript_MayThisIsEmberPath
	goto_if_eq VAR_RESULT, FEMALE, EmberPath_EventScript_BrendanThisIsEmberPath
EmberPath_EventScript_ThisIsTheWayEnd::
	setvar VAR_LAVARIDGE_TOWN_STATE, 3
	end

EmberPath_EventScript_MayThisIsEmberPath::
	msgbox EmberPath_Text_MayThisIsEmberPath, MSGBOX_DEFAULT
	closemessage
	goto EmberPath_EventScript_ThisIsTheWayEnd

EmberPath_EventScript_BrendanThisIsEmberPath::
	msgbox EmberPath_Text_BrendanThisIsEmberPath, MSGBOX_DEFAULT
	closemessage
	goto EmberPath_EventScript_ThisIsTheWayEnd

EmberPath_Text_MayThisIsEmberPath:
	.string "May: So this is the Ember Path…\n"
	.string "We are on the right way!\p"
	.string "This is so hot! Is there lava in there?\n"
	.string "I wonder what kind of Pokémon live\l"
	.string "here, this should be interesting for Dad…$"

EmberPath_Text_BrendanThisIsEmberPath:
	.string "Brendan: There! the Ember Path!\n"
	.string "We're on the right way!\p"
	.string "That's hot! Is there lava in there?\n"
	.string "I'm sure a strong Pokémon lives\l"
	.string "here, this should be interesting…$"

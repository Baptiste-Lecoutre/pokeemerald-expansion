.set LOCALID_RED, 7

FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	setflag FLAG_TEMP_7
	removeobject LOCALID_RED
	goto_if_defeated TRAINER_RED_FALLARBOR, FallarborTown_EventScript_PreventDoingRedScene
	end

FallarborTown_EventScript_PreventDoingRedScene::
	setvar VAR_TEMP_E, 1
	return

FallarborTown_EventScript_RedScene2::
	lockall
	clearflag FLAG_TEMP_7
	opendoor 8, 7
	waitdooranim
	addobject LOCALID_RED
	applymovement LOCALID_RED, FallarborTown_Movement_RedStepDown
	waitmovement 0
	closedoor 8, 7
	waitdooranim
	delay 10
	applymovement LOCALID_RED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, FallarborTown_Movement_RedArrives2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto FallarborTown_EventScriptRed
	end

FallarborTown_EventScript_RedScene3::
	lockall
	clearflag FLAG_TEMP_7
	opendoor 8, 7
	waitdooranim
	addobject LOCALID_RED
	applymovement LOCALID_RED, FallarborTown_Movement_RedStepDown
	waitmovement 0
	closedoor 8, 7
	waitdooranim
	delay 10
	applymovement LOCALID_RED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, FallarborTown_Movement_RedArrives3
	waitmovement 0
	goto FallarborTown_EventScriptRed
	end

FallarborTown_EventScript_RedScene1::
	lockall
	clearflag FLAG_TEMP_7
	opendoor 8, 7
	waitdooranim
	addobject LOCALID_RED
	applymovement LOCALID_RED, FallarborTown_Movement_RedStepDown
	waitmovement 0
	closedoor 8, 7
	waitdooranim
	delay 10
	applymovement LOCALID_RED, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, FallarborTown_Movement_RedArrives1
	waitmovement 0
	goto FallarborTown_EventScriptRed
	end

FallarborTown_EventScript_RedScene4::
	lockall
	clearflag FLAG_TEMP_7
	opendoor 8, 7
	waitdooranim
	addobject LOCALID_RED
	applymovement LOCALID_RED, FallarborTown_Movement_RedStepDown
	waitmovement 0
	closedoor 8, 7
	waitdooranim
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_RED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement LOCALID_RED, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, FallarborTown_Movement_RedArrives4
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto FallarborTown_EventScriptRed
	end

FallarborTown_EventScript_RedScene5::
	lockall
	clearflag FLAG_TEMP_7
	opendoor 8, 7
	waitdooranim
	addobject LOCALID_RED
	applymovement LOCALID_RED, FallarborTown_Movement_RedStepDown
	waitmovement 0
	closedoor 8, 7
	waitdooranim
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, FallarborTown_Movement_RedArrives5
	waitmovement 0
	goto FallarborTown_EventScriptRed
	end

FallarborTown_EventScriptRed::
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	msgbox FallarborTown_Text_OhHeyPlayer, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_RED_FALLARBOR, FallarborTown_Text_Again
	msgbox FallarborTown_Text_MyPokemonsAndI, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_RED
	setflag FLAG_TEMP_7
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_TEMP_E, 1
	releaseall
	end

FallarborTown_Movement_RedArrives1:
	walk_right
	walk_right
	walk_right
	step_end

FallarborTown_Movement_RedArrives2:
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

FallarborTown_Movement_RedArrives3:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

FallarborTown_Movement_RedArrives4:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

FallarborTown_Movement_RedArrives5:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end

FallarborTown_Text_OhHeyPlayer:
	.string "Oh, hey {PLAYER}!\n"
	.string "Long time no see!\p"
	.string "Did you try these Pokemon tournaments?\n"
	.string "They are different in every city!\p"
	.string "We don't have these in Kanto, maybe\n"
	.string "I'll open a facility on my way back.\p"
	.string "Did you get any better since last time?\n"
	.string "My Pokémons and I have grown stronger!$"

FallarborTown_Text_Again:
	.string "I lost?! Again?!$"

FallarborTown_Text_MyPokemonsAndI:
	.string "My Pokémons and I trained a lot, but\n"
	.string "it is still not enough.\p"
	.string "I'll continue training even more, and\n"
	.string "next I'll beat you!$"

FallarborTown_Movement_RedStepDown:
	walk_down
	step_end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Something's happening,\n"
	.string "and I don't like it!\p"
	.string "I've seen shady characters wandering\n"
	.string "in and out of Prof. Cozmo's home…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "This region's been known for meteors\n"
	.string "since the olden days.\p"
	.string "They say Meteor Falls was gouged out\n"
	.string "by a falling meteorite long ago.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "See! Take a look!\n"
	.string "This is my precious Azurill!\p"
	.string "It's slick and smooth and plushy, too!$"

FallarborTown_Text_Azurill:
	.string "Azurill: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "Have you already challenged Flannery,\n"
	.string "the Leader of Lavaridge Gym?\p"
	.string "The girl's grandfather was famous.\n"
	.string "He was one of the Elite Four in the\l"
	.string "Pokémon League at one point.\p"
	.string "It wouldn't surprise me to see Flannery\n"
	.string "become a great Trainer in her own\l"
	.string "right.$"

FallarborTown_Text_BattleTentSign:
	.string "Battle Tent Fallarbor Site\n"
	.string "“May the Greatest Teams Gather!”$"

FallarborTown_Text_TownSign:
	.string "Fallarbor Town\n"
	.string "“A farm community with small gardens.”$"

FallarborTown_Text_MoveTutorSign:
	.string "Ivy and Evie's House\n"
	.string "“Special training for Pokémon.”$"


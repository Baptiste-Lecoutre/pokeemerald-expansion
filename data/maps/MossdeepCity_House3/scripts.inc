.set LOCALID_FISHERMAN, 1
.set LOCALID_WAILORD, 2

MossdeepCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_House3_OnTransition
	.byte 0

MossdeepCity_House3_OnTransition::
	call_if_unset FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_ShowFishermanHideWailord
	call_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_HideFishermanShowWailord
	end

MossdeepCity_House3_HideFishermanShowWailord::
	setflag FLAG_TEMP_1
	removeobject LOCALID_FISHERMAN
	return

MossdeepCity_House3_ShowFishermanHideWailord::
	setflag FLAG_TEMP_2
	removeobject LOCALID_WAILORD
	return

MossdeepCity_House3_EventScript_Wailord::
	lock
	playmoncry SPECIES_WAILORD, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	msgbox MossdeepCity_House3_Text_WailordWontMove, MSGBOX_AUTOCLOSE
	release
	end

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPlayerFacingDirection
	clearflag FLAG_TEMP_2
	addobject LOCALID_WAILORD
	call_if_eq VAR_RESULT, DIR_NORTH, MossdeepCity_House3_EventScript_DoMovementsNorth
	call_if_eq VAR_RESULT, DIR_SOUTH, MossdeepCity_House3_EventScript_DoMovementsSouth
	call_if_eq VAR_RESULT, DIR_EAST, MossdeepCity_House3_EventScript_DoMovementsWest
	setflag FLAG_TEMP_1
	removeobject LOCALID_FISHERMAN
	playmoncry SPECIES_WAILORD, CRY_MODE_NORMAL
	msgbox MossdeepCity_House3_Text_Bwaah, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	release
	end

MossdeepCity_House3_EventScript_DoMovementsNorth::
	playse SE_BALL_OPEN
	applymovement LOCALID_WAILORD, MossdeepCity_House3_Movement_ExitPokeball
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_House3_Movement_JumpBackNorth
	waitmovement 0
	return

MossdeepCity_House3_EventScript_DoMovementsSouth::
	playse SE_BALL_OPEN
	applymovement LOCALID_WAILORD, MossdeepCity_House3_Movement_ExitPokeball
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_House3_Movement_JumpBackSouth
	waitmovement 0
	return

MossdeepCity_House3_EventScript_DoMovementsWest::
	playse SE_BALL_OPEN
	applymovement LOCALID_WAILORD, MossdeepCity_House3_Movement_ExitPokeball
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_House3_Movement_JumpBackWest
	waitmovement 0
	return

MossdeepCity_House3_Movement_ExitPokeball:
	exit_pokeball
	face_left
	step_end

MossdeepCity_House3_Movement_JumpBackNorth:
	lock_facing_direction
	jump_down
	unlock_facing_direction
	step_end

MossdeepCity_House3_Movement_JumpBackSouth:
	lock_facing_direction
	jump_up
	unlock_facing_direction
	step_end

MossdeepCity_House3_Movement_JumpBackWest:
	lock_facing_direction
	jump_left
	unlock_facing_direction
	step_end

@applymovement to player to jump back

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "Hey there, Trainer!\n"
	.string "A Super Rod really is super!\p"
	.string "Say all you want, but this baby can\n"
	.string "catch Pokémon off the seafloor!\p"
	.string "What do you think?\n"
	.string "You want it, don't you?$"

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "You bet, you bet!\n"
	.string "After all, a Super Rod is really super!$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "If there's any water, try dropping in\n"
	.string "your Rod and see what bites!\p"
	.string "I caught my Wailord with this baby!\p"
	.string "Hunh?$"

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "Hunh?\n"
	.string "Don't you like to fish?$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "Go after the seafloor Pokémon with\n"
	.string "your Super Rod.$"

MossdeepCity_House3_Text_Bwaah:
	.string "Bwaaah!$"

MossdeepCity_House3_Text_WailordWontMove:
	.string "Loos like it won't move.$"

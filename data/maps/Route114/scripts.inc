.set LOCALID_FISHERMAN, 28
.set LOCALID_MAGIKARP, 30
.set LOCALID_GYARADOS, 31

Route114_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route114_OnFrame
	.byte 0

Route114_OnTransition:
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_114_NORTH, AbnormalWeather_StartGroudonWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_114_SOUTH, AbnormalWeather_StartGroudonWeather
	call_if_set FLAG_RECEIVED_GOOD_ROD, Route114_EventScript_HideFishermanMagikarpGyarados
	call_if_unset FLAG_RECEIVED_GOOD_ROD, Route114_EventScript_HideGyarados
	end

Route114_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_114_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute114North
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_114_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute114South
	goto_if_set FLAG_SYS_IN_MIRAGE_LOCATION, Route114_EventScript_ShowMirageCaveEntrance
	specialvar VAR_RESULT, GetCurrentMirageLocation
	goto_if_eq VAR_RESULT, MIRAGE_LOCATION_ROUTE_114, Route114_EventScript_ShowMirageCaveEntrance
	end

Route114_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route114_EventScript_ShowMirageCaveEntrance::
	setmetatile 7, 11, METATILE_Fallarbor_RedCaveEntrance_Top, TRUE
	setmetatile 7, 12, METATILE_Fallarbor_RedCaveEntrance_Bottom, FALSE
	clearflag FLAG_SYS_IN_MIRAGE_LOCATION
	end

Route114_EventScript_HideFishermanMagikarpGyarados::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	removeobject LOCALID_FISHERMAN
	removeobject LOCALID_MAGIKARP
	removeobject LOCALID_GYARADOS
	return

Route114_EventScript_HideGyarados::
	setflag FLAG_TEMP_3
	removeobject LOCALID_GYARADOS
	return

Route114_EventScript_Man::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_114_RECEIVED_BERRY, Route114_EventScript_ReceivedBerry
	msgbox Route114_Text_LoveUsingBerryCrushShareBerry, MSGBOX_DEFAULT
	random NUM_ROUTE_114_MAN_BERRIES
	addvar VAR_RESULT, NUM_ROUTE_114_MAN_BERRIES_SKIPPED
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_114_RECEIVED_BERRY
	msgbox Route114_Text_TryBerryCrushWithFriends, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_ReceivedBerry::
	msgbox Route114_Text_FunToThinkAboutBerries, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RoarGentleman::
	lock
	faceplayer
	checkitem ITEM_TM05_ROAR
	goto_if_eq VAR_RESULT, TRUE, Route114_EventScript_ReceivedRoar
	msgbox Route114_Text_AllMyMonDoesIsRoarTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM05_ROAR
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route114_Text_ExplainRoar, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_ReceivedRoar::
	msgbox Route114_Text_ExplainRoar, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_Poochyena::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	msgbox Route114_Text_Poochyena, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route114_EventScript_MeteorFallsSign::
	msgbox Route114_Text_MeteorFallsSign, MSGBOX_SIGN
	end

Route114_EventScript_FossilManiacsHouseSign::
	msgbox Route114_Text_FossilManiacsHouseSign, MSGBOX_SIGN
	end

Route114_EventScript_LanettesHouseSign::
	msgbox Route114_Text_LanettesHouse, MSGBOX_SIGN
	end

Route114_EventScript_Lenny::
	trainerbattle_single TRAINER_LENNY, Route114_Text_LennyIntro, Route114_Text_LennyDefeat
	msgbox Route114_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Lucas::
	trainerbattle_single TRAINER_LUCAS_1, Route114_Text_LucasIntro, Route114_Text_LucasDefeat
	msgbox Route114_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Shane::
	trainerbattle_single TRAINER_SHANE, Route114_Text_ShaneIntro, Route114_Text_ShaneDefeat
	msgbox Route114_Text_ShanePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Nancy::
	trainerbattle_single TRAINER_NANCY, Route114_Text_NancyIntro, Route114_Text_NancyDefeat
	msgbox Route114_Text_NancyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Steve::
	trainerbattle_single TRAINER_STEVE_1, Route114_Text_SteveIntro, Route114_Text_SteveDefeat, Route114_EventScript_RegisterSteve
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route114_EventScript_RematchSteve
	msgbox Route114_Text_StevePostBattle, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RegisterSteve::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route114_Text_SteveRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_STEVE_1
	release
	end

Route114_EventScript_RematchSteve::
	trainerbattle_rematch TRAINER_STEVE_1, Route114_Text_SteveRematchIntro, Route114_Text_SteveRematchDefeat
	msgbox Route114_Text_StevePostRematch, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Bernie::
	trainerbattle_single TRAINER_BERNIE_1, Route114_Text_BernieIntro, Route114_Text_BernieDefeat, Route114_EventScript_RegisterBernie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route114_EventScript_RematchBernie
	msgbox Route114_Text_BerniePostBattle, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RegisterBernie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route114_Text_BernieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BERNIE_1
	release
	end

Route114_EventScript_RematchBernie::
	trainerbattle_rematch TRAINER_BERNIE_1, Route114_Text_BernieRematchIntro, Route114_Text_BernieRematchDefeat
	msgbox Route114_Text_BerniePostRematch, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Claude::
	trainerbattle_single TRAINER_CLAUDE, Route114_Text_ClaudeIntro, Route114_Text_ClaudeDefeat
	msgbox Route114_Text_ClaudePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Nolan::
	trainerbattle_single TRAINER_NOLAN, Route114_Text_NolanIntro, Route114_Text_NolanDefeat
	msgbox Route114_Text_NolanPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Tyra::
	trainerbattle_double TRAINER_TYRA_AND_IVY, Route114_Text_TyraIntro, Route114_Text_TyraDefeat, Route114_Text_TyraNotEnoughMons
	msgbox Route114_Text_TyraPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Ivy::
	trainerbattle_double TRAINER_TYRA_AND_IVY, Route114_Text_IvyIntro, Route114_Text_IvyDefeat, Route114_Text_IvyNotEnoughMons
	msgbox Route114_Text_IvyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Angelina::
	trainerbattle_single TRAINER_ANGELINA, Route114_Text_AngelinaIntro, Route114_Text_AngelinaDefeat
	msgbox Route114_Text_AngelinaPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Charlotte::
	trainerbattle_single TRAINER_CHARLOTTE, Route114_Text_CharlotteIntro, Route114_Text_CharlotteDefeat
	msgbox Route114_Text_CharlottePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Kai::
	trainerbattle_single TRAINER_KAI, Route114_Text_KaiIntro, Route114_Text_KaiDefeat
	msgbox Route114_Text_KaiPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_Text_AllMyMonDoesIsRoarTakeThis:
	.string "All my Pokémon does is Roar…\n"
	.string "No one dares to come near me…\p"
	.string "Sigh… If you would, please take\n"
	.string "this TM away…$"

Route114_Text_ExplainRoar:
	.string "TM05 contains Roar.\n"
	.string "A Roar sends Pokémon scurrying.$"

Route114_Text_Poochyena:
	.string "Bow! Bowwow!$"

Route114_Text_MeteorFallsSign:
	.string "Meteor Falls\n"
	.string "Rustboro City through here$"

Route114_Text_FossilManiacsHouseSign:
	.string "Fossil Maniac's House\n"
	.string "“Fossils gratefully accepted!”$"

Route114_Text_LanettesHouse:
	.string "Lanette's House$"

Route114_EventScript_GoodRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOOD_ROD, Route114_EventScript_ReceivedGoodRod
	msgbox Route114_Text_YouAgreeGoodRodIsGood, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_EventScript_ReceiveGoodRod
	goto_if_eq VAR_RESULT, NO, Route114_EventScript_DeclineGoodRod
	end

Route114_EventScript_ReceiveGoodRod::
	msgbox Route114_Text_IdenticalMindsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox Route114_Text_TryYourLuckFishing, MSGBOX_DEFAULT
	applymovement LOCALID_FISHERMAN, Common_Movement_FaceUp
	waitmovement 0
	playse SE_M_DETECT
	dofieldeffectsparkle 22, 28, 0
	waitfieldeffect FLDEFF_SPARKLE
	setflag FLAG_TEMP_2
	removeobject LOCALID_MAGIKARP
	clearflag FLAG_TEMP_3
	addobject LOCALID_GYARADOS
	playmoncry SPECIES_GYARADOS, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	playse SE_LEDGE
	applymovement LOCALID_GYARADOS, Route114_Movement_GoDownFast
	applymovement LOCALID_FISHERMAN, Route114_Movement_JumpRight
	waitmovement 0
	setflag FLAG_TEMP_1
	removeobject LOCALID_FISHERMAN
	specialvar VAR_RESULT, GetPlayerFacingDirection
	call_if_eq VAR_RESULT, DIR_NORTH, Route114_EventScript_GyaradosMovementNorth
	call_if_eq VAR_RESULT, DIR_EAST, Route114_EventScript_GyaradosMovementEast
	msgbox Route114_Text_ThisGyaradosLikesYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_EventScript_GiveGyaradosToPlayer
	goto_if_eq VAR_RESULT, NO, Route114_EventScript_GyaradosJumpsInWater
	release
	end

Route114_EventScript_GiveGyaradosToPlayer::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_GYARADOS
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	givemon SPECIES_GYARADOS, VAR_RESULT, item=ITEM_GYARADOSITE, nature=NATURE_ADAMANT, abilityNum=2, hpEv=252, atkEv=252, speedEv=252, hpIv=31, atkIv=31, defIv=31, speedIv=31, spAtkIv=31, spDefIv=31, move1=MOVE_WATERFALL, move2=MOVE_EARTHQUAKE, move3=MOVE_ICE_FANG, move4=MOVE_DRAGON_DANCE, isShiny=TRUE, teraType=TYPE_STELLAR
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route114_EventScript_ReceiveGyaradosParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route114_EventScript_ReceiveGyaradosPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

Route114_EventScript_ReceiveGyaradosParty::
	call Route114_EventScript_ReceivedGyaradosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route114_EventScript_ReceiveGyaradosPartyEnd
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
Route114_EventScript_ReceiveGyaradosPartyEnd:
	release
	end

Route114_EventScript_ReceiveGyaradosPC::
	call Route114_EventScript_ReceivedGyaradosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route114_EventScript_SendGyaradosToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route114_EventScript_SendGyaradosToPC
	end

Route114_EventScript_SendGyaradosToPC::
	call Common_EventScript_TransferredToPC
	release
	end

Route114_EventScript_ReceivedGyaradosFanfare::
	applymovement LOCALID_GYARADOS, Route114_Movement_EnterPokeball
	waitmovement 0
	setflag FLAG_TEMP_3
	removeobject LOCALID_GYARADOS
	playfanfare MUS_OBTAIN_ITEM
	message Route114_Text_PlayerReceivedGyarados
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_GYARADOS
	return

Route114_EventScript_GyaradosJumpsInWater::
	applymovement LOCALID_GYARADOS, Route114_Movement_GyaradosJumpWater
	waitmovement 0
	setflag FLAG_TEMP_3
	removeobject LOCALID_GYARADOS
	release
	end

Route114_EventScript_GyaradosMovementNorth::
	applymovement LOCALID_GYARADOS, Route114_Movement_GyaradosJumpNorth
	waitmovement 0
	return

Route114_EventScript_GyaradosMovementEast::
	applymovement LOCALID_GYARADOS, Route114_Movement_GyaradosJumpEast
	waitmovement 0
	return

Route114_EventScript_DeclineGoodRod::
	msgbox Route114_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_ReceivedGoodRod::
	msgbox Route114_Text_TryCatchingMonWithGoodRod, MSGBOX_DEFAULT
	release
	end

Route114_Text_YouAgreeGoodRodIsGood:
	.string "Hmm!\n"
	.string "A Good Rod is really good!\p"
	.string "Wouldn't you agree?$"

Route114_Text_IdenticalMindsTakeThis:
	.string "Hmm!\n"
	.string "We're of identical minds!\p"
	.string "Hmm!\n"
	.string "Take this Good Rod!$"

Route114_Text_TryYourLuckFishing:
	.string "Wherever there's water, try your luck\n"
	.string "at fishing.\p"
	.string "That's how I got this Magikarp!$"

Route114_Text_DontYouLikeToFish:
	.string "Don't you like to fish?$"

Route114_Text_TryCatchingMonWithGoodRod:
	.string "Try catching all sorts of Pokémon\n"
	.string "with your Good Rod.$"

Route114_Text_Waaaah:
	.string "Waaaaaah!$"

Route114_Text_ThisGyaradosLikesYou:
	.string "This Gyarados seems to like you!\n"
	.string "Do you want to take it with you?$"

Route114_Text_PlayerReceivedGyarados:
	.string "{PLAYER} adopted Gyarados!$"

Route114_EventScript_Magikarp::
	lock
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	msgbox Route114_Text_ItsDoingItsBest, MSGBOX_AUTOCLOSE
	release
	end

Route114_Text_ItsDoingItsBest:
	.string "This Magikarp is doing its best…\n"
	.string "Better leave it alone!$"

Route114_Movement_JumpRight:
	lock_facing_direction
	jump_right
	unlock_facing_direction
	step_end

Route114_Movement_GoDownFast:
	walk_fast_down
	step_end

Route114_Movement_GyaradosJumpNorth:
	face_down
	delay_16
	jump_in_place_down
	jump_in_place_down
	delay_16
	step_end

Route114_Movement_GyaradosJumpEast:
	face_left
	delay_16
	jump_in_place_left
	jump_in_place_left
	delay_16
	step_end

Route114_Movement_GyaradosJumpWater:
	face_right
	jump_right
	step_end

Route114_Movement_EnterPokeball:
	enter_pokeball
	step_end

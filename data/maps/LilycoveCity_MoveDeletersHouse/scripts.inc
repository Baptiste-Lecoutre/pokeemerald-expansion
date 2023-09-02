.set LOCALID_MOVE_DELETER, 1

LilycoveCity_MoveDeletersHouse_MapScripts::
	.byte 0

LilycoveCity_MoveDeletersHouse_EventScript_MoveDeleter::
	lockall
	applymovement LOCALID_MOVE_DELETER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	case NO, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget::
	msgbox LilycoveCity_MoveDeletersHouse_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_MoveDeletersHouse_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, LilycoveCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, LilycoveCity_MoveDeletersHouse_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, LilycoveCity_MoveDeletersHouse_EventScript_TryForgetMove
	case NO, LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_TryForgetMove::
	special IsLastMonThatKnowsSurf
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_MoveDeletersHouse_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_MonOnlyKnowsOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_EggCantForgetMoves::
	msgbox LilycoveCity_MoveDeletersHouse_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_ComeAgain::
	msgbox LilycoveCity_MoveDeletersHouse_Text_ComeAgain, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_EventScript_LastMonWithSurf::
	special BufferMoveDeleterNicknameAndMove
	msgbox LilycoveCity_MoveDeletersHouse_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_MoveDeletersHouse_Text_ICanMakeMonForgetMove:
	.string "Uh…\n"
	.string "Oh, yes, I'm the Move Deleter.\p"
	.string "I can make Pokémon forget their moves.\p"
	.string "Would you like me to do that?$"

LilycoveCity_MoveDeletersHouse_Text_WhichMonShouldForget:
	.string "Which Pokémon should forget a move?$"

LilycoveCity_MoveDeletersHouse_Text_WhichMoveShouldBeForgotten:
	.string "Which move should be forgotten?$"

LilycoveCity_MoveDeletersHouse_Text_MonOnlyKnowsOneMove:
	.string "{STR_VAR_1} knows only one move\n"
	.string "so it can't be forgotten…$"

LilycoveCity_MoveDeletersHouse_Text_MonsMoveShouldBeForgotten:
	.string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
	.string "That move should be forgotten?$"

LilycoveCity_MoveDeletersHouse_Text_MonHasForgottenMove:
	.string "It worked to perfection!\p"
	.string "{STR_VAR_1} has forgotten\n"
	.string "{STR_VAR_2} completely.$"

LilycoveCity_MoveDeletersHouse_Text_ComeAgain:
	.string "Come again if there are moves that\n"
	.string "need to be forgotten.$"

LilycoveCity_MoveDeletersHouse_Text_EggCantForgetMoves:
	.string "What?\n"
	.string "No Egg should know any moves.$"

LilycoveCity_MoveDeletersHouse_Text_CantForgetSurf:
	.string "Hm!\p"
	.string "Your {STR_VAR_1} doesn't seem willing\n"
	.string "to forget Surf.$"

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ EGG MOVE TUTOR @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
LilycoveCity_EggMoveTutorsHouse_EventScript_EggMoveTutor::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, LilycoveCity_EggMoveTutorsHouse_EventScript_AskTeachMove
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_AskTeachMove
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, LilycoveCity_EggMoveTutorsHouse_EventScript_ComeBackWithHeartScale
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, LilycoveCity_EggMoveTutorsHouse_EventScript_ComeBackWithHeartScale
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMon
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMon::
	setflag FLAG_TEMP_A
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LilycoveCity_EggMoveTutorsHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_EggMoveTutorsHouse_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, LilycoveCity_EggMoveTutorsHouse_EventScript_NoMoveToTeachMon
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMove
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMove::
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMon
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_ComeBackWithHeartScale
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_NoMoveToTeachMon::
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMon
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_CantTeachEgg::
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto LilycoveCity_EggMoveTutorsHouse_EventScript_ChooseMon
	end

LilycoveCity_EggMoveTutorsHouse_EventScript_ComeBackWithHeartScale::
	msgbox LilycoveCity_EggMoveTutorsHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	clearflag FLAG_TEMP_A
	releaseall
	end

LilycoveCity_EggMoveTutorsHouse_Text_ImTheMoveTutor:
	.string "I'm the Egg Move Tutor.\p"
	.string "I know all the moves that Pokémon\n"
	.string "learn when they hatch and I can\l"
	.string "teach Pokémon those moves.\p"
	.string "I can teach a move to a Pokémon\n"
	.string "of yours if you'd like.\p"
	.string "I'll do it for a Heart Scale.\n"
	.string "I'm collecting those now.$"

LilycoveCity_EggMoveTutorsHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! That's it! That's an honest to\n"
	.string "goodness Heart Scale!\p"
	.string "Let me guess, you want me to teach\n"
	.string "a move?$"

LilycoveCity_EggMoveTutorsHouse_Text_TutorWhichMon:
	.string "Which Pokémon needs tutoring?$"

LilycoveCity_EggMoveTutorsHouse_Text_TeachWhichMove:
	.string "Which move should I teach?$"

LilycoveCity_EggMoveTutorsHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Sorry…\p"
	.string "It doesn't appear as if I have any move\n"
	.string "I can teach that Pokémon.$"

LilycoveCity_EggMoveTutorsHouse_Text_HandedOverHeartScale:
	.string "{PLAYER} handed over one Heart Scale\n"
	.string "in exchange.$"

LilycoveCity_EggMoveTutorsHouse_Text_ComeBackWithHeartScale:
	.string "If your Pokémon need to learn a move,\n"
	.string "come back with a Heart Scale.$"

LilycoveCity_EggMoveTutorsHouse_Text_CantTeachEgg:
	.string "Hunh? There isn't a single move that\n"
	.string "I can teach an Egg.$"

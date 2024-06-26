PKMN_Center_Move_Tutor::
	lockall
	message PKMN_Center_Move_Tutor_Text_HowCanHelp
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_POKE_CENTER_TUTOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, PKMN_Center_MoveReminder_EventScript
	case 1, PKMN_Center_MoveDeleter_EventScript
	case 2, PKMN_Center_Move_Tutor_MoveTutorMenu
	case 3, PKMN_Center_NameRater_EventScript
	case 4, EventScript_DoWonderTrade @PKMN_Center_EventScript_Mystery_Gift
	case 5, PKMN_Center_MinimalGrinding @PKMN_Center_EventScript_Event_Reset
	case 6, PKMN_Center_Move_Tutor_General_Exit
	case MULTI_B_PRESSED, PKMN_Center_Move_Tutor_General_Exit

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Move Reminder @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_MoveReminder_EventScript::
	msgbox PKMN_Center_MoveReminder_Text_WantMeToTeachMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PKMN_Center_Move_Tutor_General_Exit
	goto PKMN_Center_MoveReminder_EventScriptChooseMon
	end

PKMN_Center_MoveReminder_EventScriptChooseMon::
	msgbox PKMN_Center_MoveReminder_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, 255, PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, PKMN_Center_MoveReminder_EventScriptCantTeachEgg
	goto_if_eq VAR_0x8005, 0, PKMN_Center_MoveReminder_EventScriptNoMoveToTeachMon
	goto PKMN_Center_MoveReminder_EventScriptChooseMove
	end

PKMN_Center_MoveReminder_EventScriptChooseMove::
	msgbox PKMN_Center_MoveReminder_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, PKMN_Center_MoveReminder_EventScriptChooseMon
	goto PKMN_Center_MoveReminder_EventScriptRememberAnotherMove
	end

PKMN_Center_MoveReminder_EventScriptNoMoveToTeachMon::
	msgbox PKMN_Center_MoveReminder_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto PKMN_Center_MoveReminder_EventScriptChooseMon
	end

PKMN_Center_MoveReminder_EventScriptCantTeachEgg::
	msgbox PKMN_Center_MoveReminder_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto PKMN_Center_MoveReminder_EventScriptChooseMon
	end
	
PKMN_Center_MoveReminder_EventScriptRememberAnotherMove::
	msgbox PKMN_Center_MoveReminder_Text_RememberAnotherMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PKMN_Center_Move_Tutor_General_Exit
	goto PKMN_Center_MoveReminder_EventScriptChooseMon

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Move Deleter @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_MoveDeleter_EventScript::
	msgbox PKMN_Center_MoveDeleter_Text_ICanMakeMonForgetMove, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget
	case NO, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget::
	msgbox PKMN_Center_MoveDeleter_Text_WhichMonShouldForget, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, 255, PKMN_Center_Move_Tutor_General_Exit
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, PKMN_Center_MoveDeleter_EventScript_EggCantForgetMoves
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, PKMN_Center_MoveDeleter_EventScript_MonOnlyKnowsOneMove
	msgbox PKMN_Center_MoveDeleter_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, PKMN_Center_MoveDeleter_EventScript_ChooseMonAndMoveToForget
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, PKMN_Center_MoveDeleter_EventScript_TryForgetMove
	case NO, PKMN_Center_Move_Tutor_General_Exit
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_TryForgetMove::
	special IsLastMonThatKnowsSurf
	goto_if_eq VAR_RESULT, TRUE, PKMN_Center_MoveDeleter_EventScript_LastMonWithSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox PKMN_Center_MoveDeleter_Text_MonHasForgottenMove, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_MonOnlyKnowsOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_EggCantForgetMoves::
	msgbox PKMN_Center_MoveDeleter_Text_EggCantForgetMoves, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MoveDeleter_EventScript_LastMonWithSurf::
	special BufferMoveDeleterNicknameAndMove
	msgbox PKMN_Center_MoveDeleter_Text_CantForgetSurf, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Name Rater @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_NameRater_EventScript::
	msgbox PKMN_Center_NameRater_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, 255, PKMN_Center_NameRater_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, 255, PKMN_Center_Move_Tutor_General_Exit
	end

PKMN_Center_NameRater_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PKMN_Center_NameRater_EventScript_CantRateEgg
	special BufferMonNickname
	msgbox PKMN_Center_NameRater_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, PKMN_Center_NameRater_EventScript_NewNameDifferent
	msgbox PKMN_Center_NameRater_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_NameRater_EventScript_CantRateEgg::
	msgbox PKMN_Center_NameRater_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_NameRater_EventScript_NewNameDifferent::
	msgbox PKMN_Center_NameRater_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_Move_Tutor_General_Exit::
    msgbox PKMN_Center_Move_Tutor_Text_SeeYou, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Move Tutor @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_Move_Tutor_NoBadges::
	msgbox PKMN_Center_Move_Tutor_Text_NoBadgeNoMoves, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_Move_Tutor_MoveTutorMenu::
	setvar VAR_0x8008, 0
	goto_if_unset FLAG_BADGE01_GET, PKMN_Center_Move_Tutor_NoBadges
	msgbox PKMN_Center_Move_Tutor_Text_WhichSetofMoves, MSGBOX_DEFAULT
	special ScriptMenu_CreatePKMNCenterMoveTutorMultichoice
	waitstate
	special GetPKMNCenterMoveListMultichoice
	switch VAR_RESULT
	case 0, PKMN_Center_Move_Tutor_MoveList1
	case 1, PKMN_Center_Move_Tutor_MoveList2
	case 2, PKMN_Center_Move_Tutor_MoveList3
	case 3, PKMN_Center_Move_Tutor_MoveList4
	case 4, PKMN_Center_Move_Tutor_MoveList5
	case 5, PKMN_Center_Move_Tutor_MoveList6
	case 6, PKMN_Center_Move_Tutor_MoveList7
	case 7, PKMN_Center_Move_Tutor_ExitReturn
	case MULTI_B_PRESSED, PKMN_Center_Move_Tutor_ExitReturn
	releaseall
	end
	
PKMN_Center_Move_Tutor_MoveList1::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_1
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 20
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_1
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove
	
PKMN_Center_Move_Tutor_MoveList2::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_2
	setvar VAR_TEMP_E, 1
	setvar VAR_TEMP_F, 18
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_2
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_MoveList3::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_3
	setvar VAR_TEMP_E, 2
	setvar VAR_TEMP_F, 18
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_3
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_MoveList4::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_4
	setvar VAR_TEMP_E, 3
	setvar VAR_TEMP_F, 18
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_4
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_MoveList5::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_5
	setvar VAR_TEMP_E, 4
	setvar VAR_TEMP_F, 18
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_5
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_MoveList6::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_6
	setvar VAR_TEMP_E, 5
	setvar VAR_TEMP_F, 18
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_6
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_MoveList7::
	setvar VAR_TEMP_C, SCROLL_MULTI_PC_TUTOR_SET_7
	setvar VAR_TEMP_E, 6
	setvar VAR_TEMP_F, 15
	setvar VAR_0x8004, SCROLL_MULTI_PC_TUTOR_SET_7
	setvar VAR_0x8006, 0
	goto PKMN_Center_Move_Tutor_ChooseMove

PKMN_Center_Move_Tutor_ChooseMove::
    msgbox PKMN_Center_Move_Tutor_Text_WhichMove, MSGBOX_DEFAULT
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	goto_if_eq VAR_RESULT, VAR_TEMP_F, PKMN_Center_Move_Tutor_Exit @ VAR_TEMP_F is set to the ID of the "Exit" option
	goto_if_eq VAR_RESULT MULTI_B_PRESSED, PKMN_Center_Move_Tutor_CloseDescriptionWindow
	goto PKMN_Center_Move_Tutor_ConfirmMoveSelection
	end
	
PKMN_Center_Move_Tutor_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_D
	copyvar VAR_0x8005, VAR_TEMP_E
	special GetBattleFrontierTutorMoveIndex
	special BufferBattleFrontierTutorMoveName
	buffernumberstring 1, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox PKMN_Center_Move_Tutor_Text_IsThisRightMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PKMN_Center_Move_Tutor_CloseDescriptionWindow
	goto PKMN_Center_Move_Tutor_TeachTutorMove
	end

PKMN_Center_Move_Tutor_TeachTutorMove::
	msgbox PKMN_Center_Move_Tutor_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	@special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, PKMN_Center_Move_Tutor_CloseDescriptionWindow
	msgbox PKMN_Center_Move_Tutor_Text_TeachAnotherMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PKMN_Center_Move_Tutor_Exit
    goto PKMN_Center_Move_Tutor_CloseDescriptionWindow
	end

PKMN_Center_Move_Tutor_CloseDescriptionWindow::
    special CloseBattleFrontierTutorWindow
    goto PKMN_Center_Move_Tutor_MoveTutorMenu

PKMN_Center_Move_Tutor_CloseDescriptionWindowReturn::
    special CloseBattleFrontierTutorWindow
    goto PKMN_Center_Move_Tutor

PKMN_Center_Move_Tutor_ExitReturn::
    goto PKMN_Center_Move_Tutor

PKMN_Center_Move_Tutor_Exit::
	special CloseBattleFrontierTutorWindow
    msgbox PKMN_Center_Move_Tutor_Text_SeeYou, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Minimal grinding @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_MinimalGrinding::
	goto_if_unset FLAG_VISITED_RUSTBORO_CITY, PKMN_Center_MinimalGrindingTooEarly
	special BufferNextLevelCap
	msgbox PKMN_Center_Text_CurrentLvlCapIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PKMN_Center_MinimalGrindingIncreaseLevels
	msgbox PKMN_Center_Move_Tutor_Text_SeeYou, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MinimalGrindingIncreaseLevels::
	special IncreasePartyLevelToLevelCap
	playfanfare MUS_LEVEL_UP
	waitfanfare
	msgbox PKMN_Center_Text_YourPartyLevelsincreased, MSGBOX_DEFAULT
	releaseall
	end

PKMN_Center_MinimalGrindingTooEarly::
	msgbox PKMN_Center_Text_CurrentLvlCapTooEarly, MSGBOX_DEFAULT
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Strings @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PKMN_Center_Text_CurrentLvlCapTooEarly:
	.string "The advised level for the upcoming\n"
	.string "events is {STR_VAR_1}.\p"
	.string "It is too early for you to have\n"
	.string "your party be trained.$"

PKMN_Center_Text_CurrentLvlCapIs:
	.string "The advised level for the upcoming\n"
	.string "events is {STR_VAR_1}.\p"
	.string "Would you like to train your party\n"
	.string "up to two levels below this value?$"

PKMN_Center_Text_YourPartyLevelsincreased:
	.string "Your party levels increased!$"

PKMN_Center_EventReset_Text_Reset:
	.string "Events reset!$"

PKMN_Center_EventReset_Text_AlreadyReset:
	.string "You've already reset events.$"

PKMN_Center_EventResetText_WhatsBrokenThisTime:
	.string "If you've updated from an earlier\n"
	.string "version of Inclement Emerald, you may\l"
	.string "have encountered some buggy events.\p"
	.string "If needed, I can reset these events\n"
	.string "so they can be played again.\p"
	.string "Each event can only be reset\n"
	.string "once per save.\p"
	.string "Would you like to reset these events?$"

PKMN_Center_EventResetText_AlreadyReset:

PKMN_Center_Move_Tutor_Text_HowCanHelp:
	.string "How can I help you today?$"

PKMN_Center_Move_Tutor_Text_Explanation:
	.string "I can teach your Pokémon moves\n"
	.string "that they can't learn anywhere else.\p"
	.string "There's no charge, but you'll only\n"
	.string "have access to some moves to start\l"
	.string "with.\p"
	.string "As you earn more Gym Badges, I'll\n"
	.string "be able to teach you more moves,\l"
	.string "so please check back often!$"

PKMN_Center_Move_Tutor_Text_NoBadgeNoMoves:
	.string "I'm sorry, but there are no moves I\n"
	.string "can teach you right now.\p"
	.string "Come back when you have at least\n"
	.string "one Gym Badge.$"

PKMN_Center_Move_Tutor_Text_WhichSetofMoves:
	.string "Which set of moves would you\n"
	.string "like to choose from?$"

PKMN_Center_Move_Tutor_Text_WhichMove:
	.string "Which move should I teach to your\n"
	.string "Pokémon?$"
	
PKMN_Center_Move_Tutor_Text_IsThisRightMove:
	.string "The move {STR_VAR_1}, is it?$"

PKMN_Center_Move_Tutor_Text_TeachMoveToWhichMon:
	.string "Which Pokémon should learn\n"
	.string "{STR_VAR_1}?$"
	
PKMN_Center_Move_Tutor_Text_TeachAnotherMove:
	.string "Would you like me to teach\n"
    .string "another move?$"

PKMN_Center_Move_Tutor_Text_SeeYou:
	.string "See you later, then!$"

PKMN_Center_MoveReminder_Text_WantMeToTeachMove:
	.string "Would you like a Pokémon to remember\n"
	.string "a move it has forgotten?$"

PKMN_Center_MoveReminder_Text_TutorWhichMon:
	.string "Which Pokémon should remember a move?$"

PKMN_Center_MoveReminder_Text_TeachWhichMove:
	.string "Which move would you like it to\n"
	.string "remember?$"

PKMN_Center_MoveReminder_Text_DontHaveMoveToTeachPokemon:
	.string "I'm sorry, that Pokémon doesn't have\n"
	.string "any moves it can remember.$"

PKMN_Center_MoveReminder_Text_CantTeachEgg:
	.string "I'm sorry, an Egg can't remember any\n"
	.string "moves.$"

PKMN_Center_MoveReminder_Text_RememberAnotherMove:
	.string "Would you like a Pokémon to remember\n"
	.string "another move?$"

PKMN_Center_MoveDeleter_Text_ICanMakeMonForgetMove:
	.string "Would you like one of your Pokémon\n"
	.string "to forget a move?$"

PKMN_Center_MoveDeleter_Text_WhichMonShouldForget:
	.string "Which Pokémon should forget a move?$"

PKMN_Center_MoveDeleter_Text_WhichMoveShouldBeForgotten:
	.string "Which move should be forgotten?$"

PKMN_Center_MoveDeleter_Text_MonOnlyKnowsOneMove:
	.string "{STR_VAR_1} knows only one move,\n"
	.string "so it can't be forgotten.$"

PKMN_Center_MoveDeleter_Text_MonsMoveShouldBeForgotten:
	.string "Hm! {STR_VAR_1}'s {STR_VAR_2}?\n"
	.string "That move should be forgotten?$"

PKMN_Center_MoveDeleter_Text_MonHasForgottenMove:
	.string "It worked to perfection!\p"
	.string "{STR_VAR_1} has forgotten\n"
	.string "{STR_VAR_2} completely.$"

PKMN_Center_MoveDeleter_Text_EggCantForgetMoves:
	.string "What?\n"
	.string "No Egg should know any moves.$"

PKMN_Center_MoveDeleter_Text_CantForgetSurf:
	.string "Hm!\p"
	.string "Your {STR_VAR_1} doesn't seem willing\n"
	.string "to forget Surf.$"

PKMN_Center_NameRater_Text_CritiqueWhichMonNickname:
	.string "Which Pokémon's nickname should\n"
	.string "be changed?$"

PKMN_Center_NameRater_Text_WhatShallNewNameBe:
	.string "What would you like {STR_VAR_1}'s\n"
	.string "new nickname to be?$"

PKMN_Center_NameRater_Text_MonShallBeKnownAsName:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!$"

PKMN_Center_NameRater_Text_NameNoDifferentYetSuperior:
	.string "Okay! {STR_VAR_1}'s nickname\n"
	.string "will stay as it is.$"

PKMN_Center_NameRater_Text_ThatIsMerelyAnEgg:
	.string "Now, now.\n"
	.string "That is merely an Egg!$"

PKMN_Center_Text_Mystery_Gift_NoGiftAvailable:
	.string "I'm sorry, there are no Mystery Gifts\n"
	.string "available at this time.$"

PKMN_Center_Mystery_Gift_Text_ReceivedGift::
	.string "{PLAYER} received {STR_VAR_1}!\p"
	.string "Take good care of {STR_VAR_1}!$"

PKMN_Center_Text_Mystery_Gift_WouldYouLikeGift::
	.string "Thank you for playing\n"
	.string "Inclement Emerald!\p"
	.string "You have a Mystery Gift available:\n"
	.string "a special {STR_VAR_1}!\p"
	.string "Would you like to receive\n"
	.string "{STR_VAR_1}?$"

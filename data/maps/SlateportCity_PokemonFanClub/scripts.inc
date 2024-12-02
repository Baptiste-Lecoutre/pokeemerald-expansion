SlateportCity_PokemonFanClub_MapScripts::
	.byte 0

.set GROOM_PRICE, 1000
.set SHINY_PRICE, 50000

SlateportCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_unset FLAG_ENTERED_CONTEST, SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest
	call_if_unset FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_MeetChairman
	switch VAR_SLATEPORT_FAN_CLUB_STATE
	case 0, SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment
	case 1, SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon
	case 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 1
	msgbox SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon::
	setvar VAR_TEMP_2, 0
	call_if_set FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_eq VAR_TEMP_2, CONTEST_CATEGORIES_COUNT, SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves
	goto_if_eq VAR_SLATEPORT_FAN_CLUB_STATE, 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	msgbox SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_NoMoreScarves::
	msgbox SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon::
	msgbox SlateportCity_PokemonFanClub_Text_HmHmISee, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	call_if_unset FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonTough
	call_if_unset FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonSmart
	call_if_unset FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCute
	call_if_unset FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty
	call_if_unset FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCool
	bufferleadmonspeciesname STR_VAR_1
	switch VAR_TEMP_1
	case 0, SlateportCity_PokemonFanClub_EventScript_NoHighConditions
	case 1, SlateportCity_PokemonFanClub_EventScript_GiveRedScarf
	case 2, SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf
	case 3, SlateportCity_PokemonFanClub_EventScript_GivePinkScarf
	case 4, SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf
	case 5, SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 2
	return

SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf::
	addvar VAR_TEMP_2, 1
	return

SlateportCity_PokemonFanClub_EventScript_NoHighConditions::
	msgbox SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveRedScarf::
	checkitemspace ITEM_RED_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RED_SCARF
	giveitem ITEM_RED_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainRedScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf::
	checkitemspace ITEM_BLUE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BLUE_SCARF
	giveitem ITEM_BLUE_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainBlueScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GivePinkScarf::
	checkitemspace ITEM_PINK_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_PINK_SCARF
	giveitem ITEM_PINK_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainPinkScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf::
	checkitemspace ITEM_GREEN_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_GREEN_SCARF
	giveitem ITEM_GREEN_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainGreenScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf::
	checkitemspace ITEM_YELLOW_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_YELLOW_SCARF
	giveitem ITEM_YELLOW_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainYellowScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf::
	msgbox SlateportCity_PokemonFanClub_Text_NoSpaceForReward, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CheckMonCool::
	specialvar VAR_RESULT, CheckLeadMonCool
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCool
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCool::
	setvar VAR_TEMP_1, 1
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty::
	specialvar VAR_RESULT, CheckLeadMonBeauty
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonBeauty
	return

SlateportCity_PokemonFanClub_EventScript_SetMonBeauty::
	setvar VAR_TEMP_1, 2
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonCute::
	specialvar VAR_RESULT, CheckLeadMonCute
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCute
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCute::
	setvar VAR_TEMP_1, 3
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonSmart::
	specialvar VAR_RESULT, CheckLeadMonSmart
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonSmart
	return

SlateportCity_PokemonFanClub_EventScript_SetMonSmart::
	setvar VAR_TEMP_1, 4
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonTough::
	specialvar VAR_RESULT, CheckLeadMonTough
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonTough
	return

SlateportCity_PokemonFanClub_EventScript_SetMonTough::
	setvar VAR_TEMP_1, 5
	return

SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest::
	goto_if_set FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest::
	msgbox SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_MeetChairman::
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	return

SlateportCity_PokemonFanClub_EventScript_SootheBellWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SOOTHE_BELL, SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell
	msgbox SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, SlateportCity_PokemonFanClub_EventScript_GiveSootheBell
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveSootheBell::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_PokemonFanClub_Text_PokemonAdoresYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SOOTHE_BELL
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell::
	msgbox SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GroomLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox SlateportCity_PokemonFanClub_Text_IGroomPokemon, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, SlateportCity_PokemonFanClub_EventScript_DeclineGroom
	checkmoney GROOM_PRICE, 0
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NotEnoughMoney
	hidemoneybox
	msgbox SlateportCity_PokemonFanClub_Text_ChooseAPokemonToGroom, MSGBOX_DEFAULT
    special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, 0xFF, SlateportCity_PokemonFanClub_EventScript_NoMonSelected
	goto_if_eq VAR_0x8004, PARTY_SIZE, SlateportCity_PokemonFanClub_EventScript_NoMonSelected
	special IsSelectedMonEgg
    goto_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SelectedMonIsEgg
	special CanGroomSelectedMon
	goto_if_eq VAR_RESULT, 0, SlateportCity_PokemonFanClub_EventScript_CannotGroom
	goto_if_eq VAR_RESULT, 2, SlateportCity_PokemonFanClub_EventScript_GroomOnlyFriendship
SlateportCity_PokemonFanClub_EventScript_ContinueGroom:
	removemoney GROOM_PRICE, 0
	special GroomSelectedMon
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_GroomFailed
	msgbox SlateportCity_PokemonFanClub_Text_GroomSucceeded, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_DeclineGroom:
	hidemoneybox
SlateportCity_PokemonFanClub_EventScript_NoMonSelected:
	msgbox SlateportCity_PokemonFanClub_Text_WellThatsTooBad, MSGBOX_AUTOCLOSE
	release
	end

SlateportCity_PokemonFanClub_EventScript_NotEnoughMoney:
	hidemoneybox
	msgbox SlatePortCity_PokemonFanClub_Text_YouDontHaveEnoughMoney, MSGBOX_AUTOCLOSE
	release
	end

SlateportCity_PokemonFanClub_EventScript_SelectedMonIsEgg:
	msgbox SlateportCity_PokemonFanClub_Text_GroomEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CannotGroom:
	msgbox SlateportCity_PokemonFanClub_Text_CannotGroom, MSGBOX_DEFAULT
	checkmoney SHINY_PRICE, 0
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_AskShiny
SlateportCity_PokemonFanClub_EventScript_NoGroomEnd:
	release
	end

SlateportCity_PokemonFanClub_EventScript_GroomOnlyFriendship:
	msgbox SlateportCity_PokemonFanClub_Text_GroomOnlyFriendship, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_ContinueGroom
	goto SlateportCity_PokemonFanClub_EventScript_NoMonSelected

SlateportCity_PokemonFanClub_EventScript_GroomFailed:
	msgbox SlateportCity_PokemonFanClub_Text_GroomFailed, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_AskShiny:
	special IsSelectedMonShiny
	goto_if_eq VAR_RESULT, YES, SlateportCity_PokemonFanClub_EventScript_NoGroomEnd
	showmoneybox 0, 0
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	msgbox SlateportCity_PokemonFanClub_Text_AskShiny, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_PokemonFanClub_EventScript_DeclineGroom
	hidemoneybox
	special MakeSelectedMonShiny
	removemoney SHINY_PRICE, 0
	msgbox SlateportCity_PokemonFanClub_Text_GroomSucceeded, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_Text_IGroomPokemon:
	.string "Oh, my! Look at your Pokémon!\n"
	.string "How about a bit of grooming?\p"
	.string "I charge ¥1000 per session, the result\n"
	.string "is garanteed, your Pokémon will love it!\p"
	.string "So, how about a session right now?$"

SlateportCity_PokemonFanClub_Text_WellThatsTooBad:
	.string "Well, that's too bad.\n"
	.string "Feel free to come back anytime!$"

SlatePortCity_PokemonFanClub_Text_YouDontHaveEnoughMoney:
	.string "You don't have enough money, you should\n"
	.string "start saving some to offer a bit of\l"
	.string "well-being to your Pokémon!$"

SlateportCity_PokemonFanClub_Text_ChooseAPokemonToGroom:
	.string "Choose a Pokémon to groom.$"

SlateportCity_PokemonFanClub_Text_GroomEgg:
	.string "What? An Egg?\n"
	.string "How do you want me to groom an Egg?$"

SlateportCity_PokemonFanClub_Text_CannotGroom:
	.string "I can't groom this Pokémon,\n"
	.string "look how glowing it is!$"

SlateportCity_PokemonFanClub_Text_GroomOnlyFriendship:
	.string "Hum… This Pokémon is already beautiful\n"
	.string "as it is, I can't make it any prettier.\p"
	.string "But it will definitely make it happier.\n"
	.string "So, shall I begin?$"

SlateportCity_PokemonFanClub_Text_GroomFailed:
	.string "Alright, let's take care of your {STR_VAR_1}!\p"
	.string "… {PAUSE 32}\n"
	.string "… … … … … …\p"
	.string "Here! There we go!\n"
	.string "Oh! {PAUSE 32}It looks like I messed up!\p"
	.string "Please come back soon, I promise\n"
	.string "the result will be better!$"

SlateportCity_PokemonFanClub_Text_GroomSucceeded:
	.string "Alright, let's take care of your {STR_VAR_1}!\p"
	.string "… {PAUSE 32}\n"
	.string "… … … … … …\p"
	.string "Here! There we go!\n"
	.string "Oh! {PAUSE 32}It looks wonderful!\p"
	.string "Please come back soon, I'm sure\n"
	.string "you have other Pokémon waiting!$"

SlateportCity_PokemonFanClub_Text_AskShiny:
	.string "Oh, wait! Your {STR_VAR_1} seems to really\n"
	.string "love you, I'm sure he will do anything\l"
	.string "to please you!\p"
	.string "I happen to know of a secret grooming\n"
	.string "technique that makes a Pokémon\l"
	.string "actually shine!\p"
	.string "How about we have a go? For this one,\n"
	.string "the cost is ¥50000.$"

SlateportCity_PokemonFanClub_EventScript_Man::
	msgbox SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Twin::
	msgbox SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_EndureTM::
	lock
	faceplayer
	checkitem ITEM_TM58_ENDURE, 1
	goto_if_eq VAR_RESULT, TRUE,SlateportCity_PokemonFanClub_EventScript_ReceivedTM58
	msgbox SlateportCity_PokemonFanClub_Text_GiveTM58, MSGBOX_DEFAULT
	giveitem ITEM_TM58_ENDURE
	msgbox SlateportCity_PokemonFanClub_Text_HaveTM58, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedTM58::
	lock
	faceplayer
	msgbox SlateportCity_PokemonFanClub_Text_HaveTM58, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_Text_GiveTM58:
	.string "Check out my Azumarill! It's pretty\n"
	.string "sturdy, right? Almost as sturdy as\l"
	.string "a Roggenrola with Sturdy!\p"
	.string "Your Pokémon can be sturdy too,\n"
	.string "if you use this TM!$"

SlateportCity_PokemonFanClub_Text_HaveTM58:
	.string "Endure allows a Pokémon to withstand\n"
	.string "any attack with one HP left.\p"
	.string "It might not work if you use it too\n"
	.string "many times in a row, though.$"

SlateportCity_PokemonFanClub_Text_MeetChairman:
	.string "Er-hem! I am the Chairman of the\n"
	.string "Pokémon Fan Club!\p"
	.string "Being the Chairman, I am naturally\n"
	.string "the most important!\p"
	.string "No one can best me when it comes\n"
	.string "to raising Pokémon. No one!\p"
	.string "Well, let me tell you about\n"
	.string "Pokémon Contests.\p"
	.string "They're events where one can show off\n"
	.string "Pokémon for the world to see!\p"
	.string "However, they're held in far-off towns,\n"
	.string "so I cannot participate often enough.\p"
	.string "That is why we gather here to show\n"
	.string "off our Pokémon, and have others\l"
	.string "show us theirs.$"

SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon:
	.string "The Pokémon of a Trainer who has\n"
	.string "entered a Pokémon Contest…\l"
	.string "That, I would like to see.$"

SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon:
	.string "Er-hem! I see you've participated in\n"
	.string "a Pokémon Contest!\p"
	.string "Please! Allow me to examine how you\n"
	.string "have raised your Pokémon.\p"
	.string "It delights me no end to see Pokémon\n"
	.string "raised by other Trainers.\p"
	.string "The happy expressions of Pokémon\n"
	.string "raised with proper care…\p"
	.string "The kindly eyes of the Trainer that\n"
	.string "nurtured and raised the Pokémon…\p"
	.string "The very thought fills my heart to\n"
	.string "overwhelming with joy.\p"
	.string "Oh! I do beg your pardon!\n"
	.string "Forgive me for prattling on so!\p"
	.string "Please! Allow me to examine how much\n"
	.string "your Pokémon has grown!$"

SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing:
	.string "How is your Pokémon growing?\n"
	.string "Allow me to examine it.$"

SlateportCity_PokemonFanClub_Text_HmHmISee:
	.string "Hm, hm…\n"
	.string "I see…$"

SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks:
	.string "Hmmm… It's not bad, but it's not\n"
	.string "good, either…\p"
	.string "You, the Trainer, must put more\n"
	.string "effort into raising this Pokémon!\p"
	.string "For instance, may I suggest that\n"
	.string "you give it more {POKEBLOCK}s?$"

SlateportCity_PokemonFanClub_Text_NoSpaceForReward:
	.string "Oh, my…\p"
	.string "Your Pokémon is growing quite well,\n"
	.string "so you deserve a reward.\p"
	.string "Unfortunately, you have no space for\n"
	.string "this in your Bag.$"

SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis:
	.string "Your {STR_VAR_1}, it is growing in\n"
	.string "a most impressive manner!\l"
	.string "It is one fine specimen!\p"
	.string "But! If you were to give it this,\n"
	.string "it would grow even better! Indeed!$"

SlateportCity_PokemonFanClub_Text_ExplainRedScarf:
	.string "Let a Pokémon hold that Red Scarf.\p"
	.string "Everyone will recognize the coolness\n"
	.string "of that Pokémon!$"

SlateportCity_PokemonFanClub_Text_ExplainBlueScarf:
	.string "Let a Pokémon hold that Blue Scarf.\p"
	.string "Its beauty will be accentuated much\n"
	.string "more than now!$"

SlateportCity_PokemonFanClub_Text_ExplainPinkScarf:
	.string "Let a Pokémon hold that Pink Scarf.\p"
	.string "It will draw out the cuteness of\n"
	.string "the Pokémon some more!$"

SlateportCity_PokemonFanClub_Text_ExplainGreenScarf:
	.string "Let a Pokémon hold that Green Scarf.\p"
	.string "That will enhance the\n"
	.string "smartness of Pokémon!$"

SlateportCity_PokemonFanClub_Text_ExplainYellowScarf:
	.string "Let a Pokémon hold that Yellow Scarf.\p"
	.string "It will bolster your Pokémon's\n"
	.string "toughness so much more!$"

SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou:
	.string "I'm sorry, but I've nothing else to\n"
	.string "give you! None at all!\p"
	.string "After all, you're blessed with the gift\n"
	.string "of raising Pokémon without resorting\l"
	.string "to any items!$"

SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou:
	.string "I love seeing Pokémon that love\n"
	.string "their Trainers.\p"
	.string "Pokémon are very sensitive to\n"
	.string "the feelings of their Trainers.\p"
	.string "If you treat your Pokémon with love\n"
	.string "and care, they'll love you back.\p"
	.string "When your Pokémon grow to love you,\n"
	.string "please come show me.$"

SlateportCity_PokemonFanClub_Text_PokemonAdoresYou:
	.string "Your Pokémon really adores you.\p"
	.string "For you, a most compassionate\n"
	.string "Trainer, a gift from the Fan Club!$"

SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove:
	.string "Pokémon are very sensitive to\n"
	.string "the feelings of their Trainers.\p"
	.string "If you treat your Pokémon with love\n"
	.string "and care, they'll love you back.$"

SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting:
	.string "If you keep letting a Pokémon faint\n"
	.string "in battle, it'll come to resent it.\p"
	.string "Soon, it will become less trusting\n"
	.string "of the Trainer.\p"
	.string "In other words, it certainly won't\n"
	.string "like you very much.$"

SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein:
	.string "Do Pokémon enjoy having items used\n"
	.string "on them?\p"
	.string "Mine acted really happy when I gave\n"
	.string "it some Protein.$"

SlateportCity_PokemonFanClub_Text_Skitty:
	.string "Skitty: Fffnyaaaah…$"

SlateportCity_PokemonFanClub_Text_Zigzagoon:
	.string "Zigzagoon: Kyuuu…$"

SlateportCity_PokemonFanClub_Text_Azumarill:
	.string "Azumarill: Marimari?$"


MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	giveitem ITEM_COIN_CASE
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_Tutor::
	lock
	faceplayer
	msgbox MauvilleCity_House2_Text_StarterMoveTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_StarterMoveDeclined
	setvar VAR_0x8008, TRUE
	message MauvilleCity_House2_Text_StarterMoveWhichMove
	waitmessage
	multichoice 0, 0, MULTI_STARTER_MOVES, 0
	switch VAR_RESULT
	case 0, MauvilleCity_House2_EventScript_StarterMoveGrassPledge
	case 1, MauvilleCity_House2_EventScript_StarterMoveFirePledge
	case 2, MauvilleCity_House2_EventScript_StarterMoveWaterPledge
	case 3, MauvilleCity_House2_EventScript_StarterMoveFrenzyPlant
	case 4, MauvilleCity_House2_EventScript_StarterMoveBlastBurn
	case 5, MauvilleCity_House2_EventScript_StarterMoveHydroCannon
	case MULTI_B_PRESSED, MauvilleCity_House2_EventScript_StarterMoveDeclined
	goto MauvilleCity_House2_EventScript_StarterMoveDeclined
	end

	MauvilleCity_House2_EventScript_StarterMoveGrassPledge::
	setvar VAR_0x8005, MOVE_GRASS_PLEDGE
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_StarterMoveFirePledge::
	setvar VAR_0x8005, MOVE_FIRE_PLEDGE
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_StarterMoveWaterPledge::
	setvar VAR_0x8005, MOVE_WATER_PLEDGE
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_StarterMoveFrenzyPlant::
	setvar VAR_0x8005, MOVE_FRENZY_PLANT
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_StarterMoveBlastBurn::
	setvar VAR_0x8005, MOVE_BLAST_BURN
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_StarterMoveHydroCannon::
	setvar VAR_0x8005, MOVE_HYDRO_CANNON
	goto MauvilleCity_House2_EventScript_TeachMove

	MauvilleCity_House2_EventScript_TeachMove::
	buffermovename 0, VAR_0x8005
	msgbox MauvilleCity_House2_Text_StarterMoveWhichMon, MSGBOX_DEFAULT
	call MauvilleCity_House2_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MauvilleCity_House2_EventScript_StarterMoveDeclined
	goto MauvilleCity_House2_EventScript_StarterMoveTaught
	end

MauvilleCity_House2_EventScript_StarterMoveDeclined::
	setvar VAR_0x8008, FALSE
	msgbox MauvilleCity_House2_Text_StarterMoveDeclined, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_OpenPartyMenu:: @ 82C8326
	special ChooseMonForMoveTutor
	waitstate
	lock
	faceplayer
	return

MauvilleCity_House2_EventScript_StarterMoveTaught::
	setvar VAR_0x8008, FALSE
	msgbox MauvilleCity_House2_Text_StarterMoveTaught, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "If I had a Bike, it'd be easy to cycle to\n"
	.string "Slateport for some shopping.\p"
	.string "I'd be able to buy Harbor Mail at the\n"
	.string "Pokémon Mart in Slateport…$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "Oh! You have Harbor Mail?\n"
	.string "Will you trade it for a Coin Case?$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "Oh, I'm so happy!\n"
	.string "Okay, I'll trade you a Coin Case!$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "That Coin Case can be used\n"
	.string "at the Game Corner.$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "Oh, that's disappointing.\p"
	.string "A Coin Case is needed for the\n"
	.string "Game Corner.$"

MauvilleCity_House2_Text_StarterMoveTeach:
	.string "If you've got any Pokémon from a\n"
	.string "Professor - starter Pokémon, in other\l"
	.string "words - I can teach them special moves.\p"
	.string "Would you like a Pokémon to learn one?$"

MauvilleCity_House2_Text_StarterMoveDeclined:
	.string "Suit yourself. Come back if you change\n"
	.string "your mind.$"

MauvilleCity_House2_Text_StarterMoveTaught:
	.string "If you want to try out more of these\n"
	.string "moves, you can get more starter\l"
	.string "Pokémon at the Game Corner.$"

MauvilleCity_House2_Text_StarterMoveWhichMove:
	.string "Which move should I teach?$"

MauvilleCity_House2_Text_StarterMoveWhichMon:
	.string "Which Pokémon should learn\n"
	.string "{STR_VAR_1}?$"

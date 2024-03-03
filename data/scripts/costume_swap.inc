EventScript_Dresser::
	lockall
	msgbox Text_ChangeClothes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CloseDresser
	special StorePlayerCoordsInVars
	goto_if_lt VAR_0x8004, 3, EventScript_DresserFemaleRoom
	goto EventScript_DresserMaleRoom
	end

EventScript_DresserMaleRoom::
	message Text_ChooseRegionStyle
	waitmessage
	multichoicedefault 22, 2, MULTI_DRESSER_DRAWERS, 5, FALSE
@	switch VAR_RESULT
@	setvar VAR_0x8004, SCROLL_MULTI_COSTUME
@	special ShowScrollableMultichoice
@	waitstate
	switch VAR_RESULT
@	case 6, EventScript_Dresser_Exit
	case 4, EventScript_Dresser_Exit
	case MULTI_B_PRESSED, EventScript_Dresser_Exit
	goto EventScript_ChangeCostume
	end

EventScript_DresserFemaleRoom::
	message Text_ChooseRegionStyle
	waitmessage
	multichoicedefault 0, 2, MULTI_DRESSER_DRAWERS, 5, FALSE
@	switch VAR_RESULT
@	setvar VAR_0x8004, SCROLL_MULTI_COSTUME
@	special ShowScrollableMultichoice
@	waitstate
	switch VAR_RESULT
@	case 6, EventScript_Dresser_Exit
	case 4, EventScript_Dresser_Exit
	case MULTI_B_PRESSED, EventScript_Dresser_Exit
	goto EventScript_ChangeCostume
	end

Text_ChangeClothes:
	.string "It's full of clean clothes!\p"
	.string "Would you like to change?$"

Text_ChooseRegionStyle:
	.string "Which drawer do you want to\n"
	.string "to choose an outfit from?$"

EventScript_CloseDresser::
	closemessage
	releaseall
	end

EventScript_ChangeCostume::
	lockall
	fadescreen FADE_TO_BLACK
	copyvar VAR_TEMP_1, VAR_RESULT
	special SwapPlayersCostume
	fadescreen FADE_FROM_BLACK
	goto EventScript_Dresser_Finish
	end

EventScript_Dresser_Exit::
	closemessage
	msgbox Text_ChangeClothes_Cancel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, EventScript_Dresser_Loop
	releaseall
	end

Text_ChangeClothes_Cancel:
	.string "Would you like to keep\n"
	.string "your current outfit?$"

EventScript_Dresser_Loop::
	special StorePlayerCoordsInVars
	goto_if_lt VAR_0x8004, 3, EventScript_DresserFemaleRoom
	goto EventScript_DresserMaleRoom
	end

EventScript_Dresser_Finish::
	closemessage
	msgbox Text_ChangeClothes_Confirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, EventScript_Dresser_Loop
	msgbox Text_ChangeClothes_Finished, MSGBOX_DEFAULT
	releaseall
	end

Text_ChangeClothes_Confirm:
	.string "Wear this outfit?$"

Text_ChangeClothes_Finished:
	.string "Lookin' good!$"

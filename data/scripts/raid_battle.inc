EventScript_RaidBattle::
    lockall
    checkitem ITEM_DYNAMAX_BAND, 1
    goto_if_eq VAR_RESULT, FALSE, EventScript_RaidBattleNoDynamaxBand
    special IsRaidBattleAvailable
    goto_if_eq VAR_RESULT, FALSE, EventScript_NoRaidBattle
    msgbox Text_DenEmitsMysteriousEnergy, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, TRUE, EventScript_RaidBattleIntroScreen
    goto EventScript_RaidBattleEnd

EventScript_RaidBattleIntroScreen::
    special InitRaidIntro
    waitstate
    goto_if_eq VAR_RESULT, FALSE, EventScript_RaidBattleEnd
    special SetRaidBattleFlag
    setvar VAR_TEMP_A, 0
    goto EventScript_RaidBattleGiveRewards

EventScript_RaidBattleGiveRewards::
    special GiveRaidBattleRewards
    goto_if_eq VAR_0x800B, TRUE, EventScript_RaidBattleEnd
    callstd STD_FIND_ITEM
    goto EventScript_RaidBattleGiveRewards

EventScript_ThrowWishingPiece::
    msgbox Text_ThrowAWishingPiece, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, EventScript_RaidBattleEnd
    msgbox Text_PlayerThrewAWishingPiece
    waitmessage
    removeitem ITEM_WISHING_PIECE, 1
    setflag FLAG_TEMP_C
    special ClearRaidBattleFlag
    goto EventScript_RaidBattleIntroScreen

EventScript_NoRaidBattle::
    msgbox Text_DenIsEmpty
    checkitem ITEM_WISHING_PIECE, 1
    releaseall
    end

EventScript_RaidBattleNoDynamaxBand::
    msgbox Text_DenIsEmpty
EventScript_RaidBattleEnd:
    clearflag FLAG_TEMP_C
    releaseall
    end

@ Text for the file
Text_DenEmitsMysteriousEnergy::
	.string "The den emits mysterious energy.\n"
	.string "Do you want to look inside?$"

Text_DenIsEmpty::
    .string "The den is empty.$"

Text_ThrowAWishingPiece::
    .string "Do you want to throw a\n"
    .string "Wishing Piece in?$"

Text_PlayerThrewAWishingPiece::
    .string "{PLAYER} threw a Wishing Piece\n"
    .string "into the den.$"

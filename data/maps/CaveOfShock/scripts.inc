CaveOfShock_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CaveOfShock_OnLoad
	.byte 0

CaveOfShock_OnLoad::
	call_if_unset FLAG_SYS_BRAILLE_WAIT, CaveOfShock_EventScript_HideRegiEntrance
	end

CaveOfShock_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

EventScript_OpenRegielekiChamber::
	setmetatile 7, 19, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 8, 19, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 19, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 9, 20, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	setflag FLAG_SYS_BRAILLE_WAIT
	end

CaveOfShock_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_BRAILLE_WAIT, CaveOfShock_EventScript_BigHoleInWall
	braillemsgbox CaveOfShock_Braille_Wait2Minutes
	special DoRegielekiPuzzle
	waitstate
	goto CaveOfShock_EventScript_Wait
	end

CaveOfShock_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

CaveOfShock_EventScript_CaveEntranceSide::
	lockall
	braillemsgbox CaveOfShock_Braille_Wait2Minutes
	goto_if_set FLAG_SYS_BRAILLE_WAIT, CaveOfShock_EventScript_Wait
	special DoRegielekiPuzzle
	waitstate
	goto CaveOfShock_EventScript_Wait
	end

CaveOfShock_EventScript_Wait::
	waitbuttonpress
	erasebox 0, 0, 29, 19
	releaseall
	end

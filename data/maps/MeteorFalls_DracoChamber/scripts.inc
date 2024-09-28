MeteorFalls_DracoChamber_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_DracoChamber_OnLoad
	.byte 0

MeteorFalls_DracoChamber_OnLoad:
	call_if_unset FLAG_SYS_REGIDRAGO_PUZZLE_COMPLETED, MeteorFalls_DracoChamber_EventScript_HideRegiEntrance
	end

MeteorFalls_DracoChamber_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

MeteorFalls_DracoChamber_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_REGIDRAGO_PUZZLE_COMPLETED, MeteorFalls_DracoChamber_EventScript_BigHoleInWall
	braillemsgbox MeteorFalls_DracoChamber_Braille_UseStrength
	releaseall
	end

MeteorFalls_DracoChamber_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

MeteorFalls_DracoChamber_EventScript_CaveEntranceSide::
	lockall
	braillemsgbox MeteorFalls_DracoChamber_Braille_UseStrength
	releaseall
	end

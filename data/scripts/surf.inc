EventScript_UseSurf::
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_EndUseSurf
	callnative IsFieldMoveFastToVarResult
	goto_if_eq VAR_RESULT, TRUE, EventScript_DoUseSurf
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ReleaseUseSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
EventScript_DoUseSurf:
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end

EventScript_UseSurfNoText::
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	goto EventScript_DoUseSurf

EventScript_UseRod::
	lock
	startfishing
	end

EventScript_UseSurfOrRod::
	lockall
	msgbox gText_TheWaterIsBeautiful, MSGBOX_DEFAULT
	dynmultipush EventScript_RodSurf_Text_Surf, 0
	dynmultipush EventScript_RodSurf_Text_Fish, 1
	dynmultipush EventScript_RodSurf_Text_Cancel, 2
	dynmultistack 22, 6, FALSE, 3, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, EventScript_UseSurfNoText
	case 1, EventScript_UseRod
	releaseall
	end

EventScript_RodSurf_Text_Surf:
	.string "Surf$"

EventScript_RodSurf_Text_Fish:
	.string "Fish$"

EventScript_RodSurf_Text_Cancel:
	.string "Cancel$"

gText_TheWaterIsBeautiful:
	.string "The water is dyed a beautiful blue…\n"
	.string "What would you like to do?$"

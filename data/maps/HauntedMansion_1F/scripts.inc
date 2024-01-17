HauntedMansion_1F_MapScripts::
	.byte 0

HauntedMansion_1F_EventScript_DragapultGhost::
	lockall
	msgbox HauntedMansion_1F_Text_BeGoneIntruders
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_Delay48
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, Common_Movement_Delay48
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, HauntedMansion_1F_EventScript_MayUseDevonScope
	call_if_eq VAR_RESULT, FEMALE, HauntedMansion_1F_EventScript_BrendanUseDevonScope
	closemessage
	specialvar VAR_RESULT, GetHighestLevelInPlayerParty
	setwildbattle SPECIES_DRAGAPULT, VAR_RESULT
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HauntedMansion_1F_EventScript_DefeatedDragapultGhost
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HauntedMansion_1F_EventScript_DefeatedDragapultGhost
	applymovement OBJ_EVENT_ID_PLAYER, HauntedMansion_1F_Movement_ForcePlayerLeft
	applymovement OBJ_EVENT_ID_FOLLOWER_NPC, HauntedMansion_1F_Movement_ForcePlayerLeft
	waitmovement 0
	releaseall
	end

HauntedMansion_1F_EventScript_DefeatedDragapultGhost::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, HauntedMansion_1F_EventScript_MaySoThereAreGhostsHere
	call_if_eq VAR_RESULT, FEMALE, HauntedMansion_1F_EventScript_BrendanSoThereAreGhostsHere
	closemessage
	setvar VAR_LAVARIDGE_TOWN_STATE, 3
	releaseall
	end

HauntedMansion_1F_EventScript_MayUseDevonScope::
	msgbox HauntedMansion_1F_Text_MayWhatIsIt
	return

HauntedMansion_1F_EventScript_BrendanUseDevonScope::
	msgbox HauntedMansion_1F_Text_BrendanWhatIsIt
	return

HauntedMansion_1F_EventScript_MaySoThereAreGhostsHere::
	msgbox HauntedMansion_1F_Text_MaySoThereAreGhostsHere
	return

HauntedMansion_1F_EventScript_BrendanSoThereAreGhostsHere::
	msgbox HauntedMansion_1F_Text_BrendanSoThereAreGhostsHere
	return

HauntedMansion_1F_Movement_ForcePlayerLeft:
	walk_left
	step_end

HauntedMansion_1F_Text_BeGoneIntruders:
	.string "Be gone…\n"
    .string "Intruders…$"

HauntedMansion_1F_Text_MayWhatIsIt:
	.string "May: Who is that!?\n"
    .string "I don't see anybody!\l"
	.string "Is there something invisible?\p"
	.string "Hold on, I'll use my Devon Scope\n"
	.string "to reveal invisible things!$"

HauntedMansion_1F_Text_MaySoThereAreGhostsHere:
	.string "May: So there are ghosts here…\p"
	.string "I'm sure the mising kid is somewhere\n"
	.string "in this mansion, let's go further!$"

HauntedMansion_1F_Text_BrendanWhatIsIt:
	.string "Brendan: Who are you!?\n"
    .string "Show yourself!\l"
	.string "Do you want to keep hiding?\p"
	.string "Fine by me, I'll use my Devon Scope\n"
	.string "to reveal invisible beings!$"

HauntedMansion_1F_Text_BrendanSoThereAreGhostsHere:
	.string "Brendan: So there are ghosts here…\p"
	.string "I'm sure the mising kid is somewhere\n"
	.string "in this mansion, let's go further!$"

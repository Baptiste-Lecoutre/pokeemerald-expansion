.set LOCALID_GIRL, 1

HauntedMansion_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedMansion_3F_OnTransition
	.byte 0

HauntedMansion_3F_OnTransition:
	call_if_gt VAR_LAVARIDGE_TOWN_STATE, 2, LavaridgeTown_EventScript_RemoveLittleGirl
	end

HauntedMansion_3F_EventScript_RemoveLittleGirl::
	setflag FLAG_TEMP_B
	removeobject LOCALID_GIRL
	return

HauntedMansion_3F_EventScript_LittleGirl::
	lockall
	setvar VAR_LAVARIDGE_TOWN_STATE, 3
	fadescreenswapbuffers FADE_TO_BLACK
	destroyfollower
	removeobject LOCALID_GIRL
	setflag FLAG_TEMP_B
	fadescreenswapbuffers FADE_FROM_BLACK
	callnative UpdateFollowingPokemon
	releaseall
	end

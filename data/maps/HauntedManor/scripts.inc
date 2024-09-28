HauntedManor_MapScripts::
	.byte 0

HauntedManor_EventScript_RivalGivesGoGoggles::
	facefollower
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, HauntedManor_EventScript_MayGoBack
	goto_if_eq VAR_RESULT, FEMALE, HauntedManor_EventScript_BrendanGoBack
HauntedManor_EventScript_RivalGhostEnd::
	addvar VAR_POKE_VIAL_MAX_CHARGES, 1
	addvar VAR_POKE_VIAL_CHARGES, 1
	setvar VAR_LAVARIDGE_TOWN_STATE, 7
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 7, Common_EventScript_ReadyPetalburgGymForBattle
	fadescreenswapbuffers FADE_TO_BLACK
	destroyfollower
	fadescreenswapbuffers FADE_FROM_BLACK
	callnative UpdateFollowingPokemon
	end

HauntedManor_EventScript_MayGoBack::
	msgbox HauntedManor_Text_MayReceiveGoGoggles, MSGBOX_NPC
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox HauntedManor_Text_MayGoNorman, MSGBOX_NPC
	goto HauntedManor_EventScript_RivalGhostEnd

HauntedManor_EventScript_BrendanGoBack::
	msgbox HauntedManor_Text_BrendanReceiveGoGoggles, MSGBOX_NPC
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox HauntedManor_Text_BrendanGoNorman, MSGBOX_NPC
	goto HauntedManor_EventScript_RivalGhostEnd

HauntedManor_Text_MayReceiveGoGoggles:
	.string "May: Wew, finally out of these\n"
	.string "cursed grounds! I feel better…\p"
	.string "{PLAYER}{KUN}, you must have collected\n"
	.string "good Pokémon…\l"
	.string "No, I believe you raised some.\p"
	.string "I guess it would be okay for you to\n"
	.string "have this.$"

HauntedManor_Text_MayGoNorman:
	.string "May: With those Go-Goggles, you'll\n"
	.string "have no trouble getting through the\l"
	.string "desert near Route 111.\p"
	.string "You should also take one of my\n"
	.string "Pokévial charges for the trip back.\p"
	.string "But, wow, {PLAYER}{KUN}…\p"
	.string "You're trying hard because you don't\n"
	.string "want to lose to me, I bet!\p"
	.string "{PLAYER}{KUN}, I think I should challenge\n"
	.string "your dad in Petalburg Gym.\p"
	.string "See you again!$"

HauntedManor_Text_BrendanReceiveGoGoggles:
	.string "Brendan: Ok!\n"
	.string "Bye-bye ghosts!\p"
	.string "Here {PLAYER}, take one of my Pokévial\n"
	.string "charges for the trip back, it's obvious\l"
	.string "you need this.\p"
	.string "Hmm… Gotta say,\n"
	.string "that's a decent collection of Badges.\p"
	.string "All right, then.\n"
	.string "You may as well have this.$"

HauntedManor_Text_BrendanGoNorman:	
	.string "Brendan: Keep those with you if you're\n"
	.string "planning on going into that desert near\l"
	.string "Route 111.\p"
	.string "There should be some Pokémon that\n"
	.string "are exclusively desert-dwellers.\l"
	.string "You might look around for those.\p"
	.string "As for me…\n"
	.string "I'm considering challenging Norman,\l"
	.string "the Gym Leader of Petalburg.\p"
	.string "Unlike you, {PLAYER}, your dad looks like\n"
	.string "he really is tough.\p"
	.string "See you around!$"

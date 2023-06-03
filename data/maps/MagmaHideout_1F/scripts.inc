.set LOCALID_BLAINE, 7

MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	goto_if_defeated TRAINER_BLAINE, MagmaHideout_1F_EventScript_HideBlaine
	end

MagmaHideout_1F_EventScript_HideBlaine::
	setflag FLAG_TEMP_7
	removeobject LOCALID_BLAINE
	return

MagmaHideout_1F_EventScript_Blaine::
	lock
	faceplayer
	msgbox MagmaHideout_1F_Text_ImBlaine, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLAINE, MagmaHideout_1F_Text_IveBeenBurntOut
	msgbox MagmaHideout_1F_Text_WhoaHey, MSGBOX_DEFAULT
	giveitem ITEM_TM83 @ flame charge
	msgbox MagmaHideout_1F_Text_ItsTime, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_BLAINE
	setflag FLAG_TEMP_7
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_1F_Text_ImBlaine:
	.string "Hah! I am Blaine, the red-hot\n"
	.string "gym leader from Kanto.\p"
	.string "I wanted to dig my gym a bit closer\n"
	.string "to the Cinnabar volcano, I went too far,\l"
	.string "and here I am!\p"
	.string "My fiery Pokémon are all ready with\n"
	.string "intense heat! Will you be the next\l"
	.string "challenger they incinerate?$"

MagmaHideout_1F_Text_IveBeenBurntOut:
	.string "I have burned down to nothing!\n"
	.string "Not even ashes remain!$"

MagmaHideout_1F_Text_WhoaHey:
	.string "Whoa hey! I'll power up my Pokémon with\n"
	.string "the heat from this ferocious battle\p"
	.string "Here, take this TM as reward.$"

MagmaHideout_1F_Text_ItsTime:
	.string "It's time to find that volcano,\n"
	.string "if it hasn't already erupted…\l"
	.string "Bye.$"

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "When Team Magma has roll call, we get\n"
	.string "important guarding assignments in\l"
	.string "the order that we line up.\p"
	.string "That's why I'm stuck off in this corner.\n"
	.string "I'm always late to roll call!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "I'm always late for training sessions,\n"
	.string "too!\p"
	.string "I hate to say it, but I'm wimpy…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Okay, I'll try to put a little more\n"
	.string "effort into things from now on…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Our leader told us to dig into\n"
	.string "Mt. Chimney, so we dug and dug.\p"
	.string "And in the course of digging, we came\n"
	.string "across something that blew our minds!\p"
	.string "What did we find?\p"
	.string "Fuhahaha!\n"
	.string "I'll tell you if you beat me!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "Arrgh!\n"
	.string "Taken down!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "I won't tell you after all.\n"
	.string "You'll find out when you get there!\p"
	.string "It'd be better if you saved surprises\n"
	.string "to the end, don't you think?$"


.set LOCALID_BROCK, 10

GraniteCave_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GraniteCave_B2F_OnTransition
	.byte 0

GraniteCave_B2F_OnTransition::
	goto_if_defeated TRAINER_BROCK, GraniteCave_B2F_EventScript_HideBrock
	end

GraniteCave_B2F_EventScript_HideBrock::
	setflag FLAG_TEMP_7
	removeobject LOCALID_BROCK
	return

GraniteCave_B2F_EventScript_Brock::
	lock
	faceplayer
	msgbox GraniteCave_B2F_Text_ImBrock, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BROCK, GraniteCave_B2F_Text_YoureStrongerThanIExpected
	msgbox GraniteCave_B2F_Text_ITookYouForGranted, MSGBOX_DEFAULT
	giveitem ITEM_TM76
	msgbox GraniteCave_B2F_Text_IShouldReturnToKanto, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject LOCALID_BROCK
	setflag FLAG_TEMP_7
	fadescreen 0
	releaseall
	end


GraniteCave_B2F_Text_ImBrock:
	.string "I'm Brock, a Gym Leader from the\n"
	.string "distant region of Kanto.\p"
	.string "I came here to study fossils\n"
	.string "and mega stones.\p"
	.string "How about a battle? My Pokemon\n"
	.string "are all rock-hard!$"

GraniteCave_B2F_Text_YoureStrongerThanIExpected:
	.string "You're stronger than I expected!$"

GraniteCave_B2F_Text_ITookYouForGranted:
	.string "I took you for granted, and as\n"
	.string "a result I lost…\p"
	.string "Here, take this techincal machine\n"
	.string "as a gift!$"

GraniteCave_B2F_Text_IShouldReturnToKanto:
	.string "I should return to Kanto now…\n"
	.string "Bye!$"

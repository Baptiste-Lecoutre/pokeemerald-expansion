Route110_CaveOfShock_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_CaveOfShock_OnLoad
	.byte 0

Route110_CaveOfShock_OnLoad:
	call_if_unset FLAG_REGI_DOORS_OPENED, Route110_CaveOfShock_CloseRegiEntrance
	end

Route110_CaveOfShock_CloseRegiEntrance::
	setmetatile 14, 14, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 14, 15, METATILE_General_RockWall_SandBase, TRUE
	return

Route110_CaveOfShock_Scientist1::
	msgbox Route110_CaveOfShock_Scientist1_Text, MSGBOX_NPC
	release
	end

Route110_CaveOfShock_Scientist2::
	msgbox Route110_CaveOfShock_Scientist2_Text, MSGBOX_NPC
	release
	end

Route110_CaveOfShock_Scientist3::
	msgbox Route110_CaveOfShock_Scientist3_Text, MSGBOX_NPC
	release
	end

Route110_CaveOfShock_Scientist1_Text:
	.string "I have seen this kind of rock structure\n"
	.string "in other places, like in Meteor Falls.\p"
	.string "What is the meaning of these rock\n"
	.string "formations?\p"
	.string "I'm totally sure that they are man-made.\n"
	.string "Do you have any clue?$"

Route110_CaveOfShock_Scientist2_Text:
	.string "Every time there's a thunderstorm, some\n"
	.string "lighting strikes end up hitting this\l"
	.string "small island. Isn't that suspicious?\p"
	.string "We think there's a Pokémon living\n"
	.string "here whose only nourishment are\l"
	.string "lightning strikes.$"

Route110_CaveOfShock_Scientist3_Text:
	.string "We are researching a strange\n"
	.string "phenomenon that has been happening\l"
	.string "for a few months. This island is\l"
	.string "unhabited by humans, so something\l"
	.string "happening here is extremely myterious,\l"
	.string "to say the least.$"

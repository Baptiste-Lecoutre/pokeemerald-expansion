FallarborTown_Mart_MapScripts::
	.byte 0

FallarborTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_SP_DEF
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_NONE
	release
	end

FallarborTown_Mart_EventScript_Woman::
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM::
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_EventScript_DrainPunchTM::
	lock
	faceplayer
	checkitem ITEM_TM60_DRAIN_PUNCH, 1
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_Mart_EventScript_ReceivedTM60
	msgbox FallarborTown_Mart_Text_FreeSample, MSGBOX_DEFAULT
	giveitem ITEM_TM60_DRAIN_PUNCH
	msgbox FallarborTown_Mart_Text_HaveTM60, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_EventScript_ReceivedTM60::
	msgbox FallarborTown_Mart_Text_HaveTM60, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_Text_FreeSample:
	.string "Hi there! How are you today?\p"
	.string "Can I interest you in a free sample\n"
	.string "of Devon Corporation's new cleaning\l"
	.string "product, DRAIN PUNCH?\p"
	.string "It's super effective against grime,\n"
	.string "gunk and gunge!\p"
	.string "… … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "Hmm? You're on an adventure?\n"
	.string "You don't need drain cleaner?\p"
	.string "Well, how about you take this TM\n"
	.string "instead?$"

FallarborTown_Mart_Text_HaveTM60:
	.string "TM60 is also Drain Punch, but it's\n"
	.string "a punch that drains HP instead.\p"
	.string "Please don't use it on any drains!$"

FallarborTown_Mart_Text_DecidingSkittyEvolve:
	.string "I'm having a hard time deciding if I\n"
	.string "should make my Skitty evolve or not.\p"
	.string "I only have to use this Moon Stone,\n"
	.string "but it's so hard to decide…\p"
	.string "If I make it evolve, it will become\n"
	.string "much stronger.\p"
	.string "But it will look so different, too.$"

FallarborTown_Mart_Text_Skitty:
	.string "Skitty: Miyao?$"

FallarborTown_Mart_Text_SellNuggetIFound:
	.string "This Nugget I found here…\n"
	.string "I suppose I'll have to sell it, seeing\l"
	.string "as how it has no other use.$"


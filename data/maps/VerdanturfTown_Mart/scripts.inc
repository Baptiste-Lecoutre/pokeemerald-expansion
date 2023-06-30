VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0 @VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_SP_DEF
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_PaybackTM::
	lock
	faceplayer
	checkitem ITEM_TM66_PAYBACK, 1
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_Mart_EventScript_ReceivedTM66
	msgbox VerdanturfTown_Mart_Text_SlowPokemon, MSGBOX_DEFAULT
	giveitem ITEM_TM66_PAYBACK
	msgbox VerdanturfTown_Mart_Text_HaveTM66, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_Mart_EventScript_ReceivedTM66::
	msgbox VerdanturfTown_Mart_Text_HaveTM66, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_Mart_Text_SlowPokemon:
	.string "Do you think slow Pokémon ever get\n"
	.string "tired of taking the first hit in every\l"
	.string "battle?\p"
	.string "I think they'd be itching for a little\n"
	.string "payback!\p"
	.string "If you've got any slow Pokémon, give\n"
	.string "this TM a try.$"

VerdanturfTown_Mart_Text_HaveTM66:
	.string "TM66 contains Payback!\p"
	.string "It's an attack that doubles in power\n"
	.string "if the user moves after its target.$"

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "For any Pokémon match, X Special\n"
	.string "is crucial.\p"
	.string "It jacks up the power of some moves\n"
	.string "even though it's only for one battle.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "They don't seem to sell any winning\n"
	.string "strategy guides for the Battle Tent…\p"
	.string "It seems one must rely on one's\n"
	.string "own wits after all…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "The Nest Ball works better on\n"
	.string "weakened Pokémon.\p"
	.string "Verdanturf is the only place you can\n"
	.string "buy it.$"


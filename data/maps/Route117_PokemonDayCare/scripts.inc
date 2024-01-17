Route117_PokemonDayCare_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
	.byte 0

Route117_PokemonDayCare_OnTransition:
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
	end

Route117_PokemonDayCare_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_eq VAR_DAYCARE_ADOPTION_SPECIALS, 0, Route117_PokemonDayCare_EventScript_IntroduceAdoption
	goto_if_eq VAR_DAYCARE_ADOPTION_SPECIALS, 6, Route117_PokemonDayCare_EventScript_AdoptedFivePokemon
	goto_if_eq VAR_DAYCARE_ADOPTION_SPECIALS, 11, Route117_PokemonDayCare_EventScript_AdoptedTenPokemon
	goto_if_set FLAG_DAILY_ADOPT_EGG, Route117_PokemonDayCare_EventScript_ReceivedEgg
	goto_if_gt VAR_DAYCARE_ADOPTION_SPECIALS, 0, Route117_PokemonDayCare_EventScript_LadyUsesName
	msgbox Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
Route117_PokemonDayCare_EventScript_TryGiveEgg::
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route117_PokemonDayCare_EventScript_NoRoomForEgg
	msgbox Route117_PokemonDayCare_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_DAILY_ADOPT_EGG
	playfanfare MUS_OBTAIN_ITEM
	message Route117_PokemonDayCare_Text_ReceivedTheEgg
	waitfanfare
	specialvar VAR_RESULT, GetSpeciesForRandomEgg
	giveegg VAR_RESULT
	special IncrementAdoptionSpecials
	release
	end

Route117_PokemonDayCare_EventScript_IntroduceAdoption::
	setvar VAR_DAYCARE_ADOPTION_SPECIALS, 1
	msgbox Route117_PokemonDayCare_Text_IntroduceAdoptionOfferEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_EventScript_ReceivedEgg::
	msgbox Route117_PokemonDayCare_Text_NoEggsAtTheMinute, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_NoRoomForEgg::
	msgbox Route117_PokemonDayCare_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_DeclineEgg::
	msgbox Route117_PokemonDayCare_Text_ThatsOk, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_AdoptedFivePokemon::
	goto_if_eq VAR_DAYCARE_ADOPTION_SPECIALS, 6, Route117_PokemonDayCare_EventScript_AdoptedFivePokemonEvent
	msgbox Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_EventScript_AdoptedFivePokemonEvent::
	msgbox Route117_PokemonDayCare_Text_YouveAdoptedFivePokemonNow, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_EventScript_AdoptedTenPokemon::
	goto_if_eq VAR_DAYCARE_ADOPTION_SPECIALS, 11, Route117_PokemonDayCare_EventScript_AdoptedTenPokemonEvent
	msgbox Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_EventScript_AdoptedTenPokemonEvent::
	msgbox Route117_PokemonDayCare_Text_HopeYouDidntForget, MSGBOX_DEFAULT
	giveitem ITEM_OVAL_CHARM
	msgbox Route117_PokemonDayCare_Text_IHopeYouLikeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_EventScript_LadyUsesName::
	msgbox Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_DeclineEgg
	goto Route117_PokemonDayCare_EventScript_TryGiveEgg

Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt:
	.string "Oh! Welcome back!\p"
	.string "Would you like to adopt a\n"
	.string "Pokémon Egg?$"

Route117_PokemonDayCare_Text_HaveEggWillYouTakeIt2:
	.string "Oh! Welcome back {PLAYER}!\p"
	.string "Would you like to adopt a\n"
	.string "Pokémon Egg?$"

Route117_PokemonDayCare_Text_HopeYoullWalkPlentyWithEgg:
	.string "Thank you so much!\p"
	.string "I can tell this little Pokémon will\n"
	.string "be very happy travelling with you.$"

Route117_PokemonDayCare_Text_ReceivedTheEgg:
	.string "{PLAYER} received the Egg.$"

Route117_PokemonDayCare_Text_NoEggsAtTheMinute:
	.string "Thank you for helping give these\n"
	.string "Pokémon a good home!\p"
	.string "There aren't any more eggs that need\n"
	.string "rehomed right now.\p"
	.string "But please come back soon!$"

Route117_PokemonDayCare_Text_NoRoomForThisEgg:
	.string "Oh? You're already travelling\n"
	.string "with 6 Pokémon.\p"
	.string "There's no room for this EGG…$"

Route117_PokemonDayCare_Text_ThatsOk:
	.string "Oh? That's Ok!\p"
	.string "Come back if you want to help\n"
	.string "rehome another Pokémon.$"

Route117_PokemonDayCare_Text_IntroduceAdoptionOfferEgg:
	.string "Welcome to the Pokémon Daycare!\p"
	.string "If you want to leave a Pokémon\n"
	.string "in our care, you'll want to speak\l"
	.string "to my Grandma!\p"
	.string "I just help look after the\n"
	.string "Pokémon here.\p"
	.string "It's lovely to care for them…\n"
	.string "but it's been getting busy.\p"
	.string "… … …\p"
	.string "Some trainer's never come back to\n"
	.string "pick their Pokémon up, so they\l"
	.string "end up permanently in my care.\p"
	.string "… … …\p"
	.string "Say. You're a Pokémon Trainer,\n"
	.string "right?\p"
	.string "Would you like to adopt one of\n"
	.string "the eggs left here?$"

Route117_PokemonDayCare_Text_YouveAdoptedFivePokemonNow:
	.string "Oh! Welcome back {PLAYER}!\p"
	.string "I was hoping to see you today!\p"
	.string "Did you know you have helped\n"
	.string "rehome Five Pokémon now?\p"
	.string "You're just incredible!\p"
	.string "… … …\p"
	.string "Say, would you like to adopt another\n"
	.string "of the Pokémon eggs left here?$"

Route117_PokemonDayCare_Text_HopeYouDidntForget:
	.string "Hey {PLAYER}!\p"
	.string "You're exactly who I was hoping\n"
	.string "to see today!\p"
	.string "Did you know that you've helped\n"
	.string "rehome Ten Pokémon now?\p"
	.string "Well…\p"
	.string "You're by the far the trainer\n"
	.string "that adopted the most eggs!$"

Route117_PokemonDayCare_Text_IHopeYouLikeIt:
	.string "We're all proud of your good deeds!\p"
	.string "With that said…\p"
	.string "Would you like to adopt a\n"
	.string "Pokémon Egg now?$"

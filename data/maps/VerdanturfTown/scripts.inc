.set LOCALID_TWIN, 2
.set LOCALID_ERIKA, 7

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	goto_if_defeated TRAINER_ERIKA, VerdanturfTown_EventScript_HideErika
	end

VerdanturfTown_EventScript_HideErika::
	setflag FLAG_TEMP_7
	removeobject LOCALID_ERIKA
	return

VerdanturfTown_EventScript_Erika::
	lock
	msgbox VerdanturfTown_Text_ShouldIGoIn, MSGBOX_DEFAULT
	applymovement LOCALID_ERIKA, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ERIKA, Common_Movement_Delay48
	waitmovement 0
	faceplayer
	msgbox VerdanturfTown_Text_ImErika, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ERIKA, VerdanturfTown_Text_IConcedeDefeat
	msgbox VerdanturfTown_Text_ThatWasDelightful, MSGBOX_DEFAULT
	giveitem ITEM_TM86 @ grass knot
	msgbox VerdanturfTown_Text_IShallNowHeadBack, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ERIKA
	setflag FLAG_TEMP_7
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

VerdanturfTown_Text_ShouldIGoIn:
	.string "Should I go in? Really? Am I\n"
	.string "ready to be in the spotlight?$"

VerdanturfTown_Text_ImErika:
	.string "Oh, hi. I'm Erika. I am a gym\n"
	.string "leader from Kanto.\p"
	.string "I heard the Pokémon tournaments held\n"
	.string "in these battle tents were similar\l"
	.string "to regular battles.\p"
	.string "Let me see if you are worth\n"
	.string "entering!$"

VerdanturfTown_Text_IConcedeDefeat:
	.string "Oh! I concede defeat. You are\n"
	.string "Remarkably strong.$"

VerdanturfTown_Text_ThatWasDelightful:
	.string "That was a delightful match.\n"
	.string "I felt inspired.\p"
	.string "Please, I wish you to have this\n"
	.string "technical machine.$"

VerdanturfTown_Text_IShallNowHeadBack:
	.string "I shall now head back to my\n"
	.string "city. Bye.$"

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "My papa told me.\p"
	.string "He says this tunnel is full of\n"
	.string "timid Pokémon.\p"
	.string "They get all scared of loud noise and\n"
	.string "make a big uproar.\p"
	.string "So they had to stop the big tunnel\n"
	.string "project.\p"
	.string "But there's one man. He's trying to dig\n"
	.string "the tunnel by himself!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "There was a man who dug a tunnel for\n"
	.string "a lady he loved.\p"
	.string "I don't really get it, but hey!$"

VerdanturfTown_Text_AirCleanHere:
	.string "The way the winds blow, volcanic ash\n"
	.string "is never blown in this direction.\p"
	.string "The air is clean and delicious here.\n"
	.string "Living here should do wonders for even\l"
	.string "frail and sickly people.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "My Pokémon and I, we've been riding\n"
	.string "a hot winning streak.\p"
	.string "So I decided to make my Battle Tent\n"
	.string "debut in this town.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "Did you see the cave next to the\n"
	.string "Pokémon Mart?\p"
	.string "There's a guy in there who's trying to\n"
	.string "bust up boulders so he can bust out\l"
	.string "through to the other side.\p"
	.string "It'd be great if we could go through…\n"
	.string "It'll make it easy to visit Rustboro.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "That cave next to the Pokémon Mart\n"
	.string "is now a tunnel to the other side.\p"
	.string "It's great--it's easy to go shop for\n"
	.string "new Devon products in Rustboro now.$"

VerdanturfTown_Text_TownSign:
	.string "Verdanturf Town\p"
	.string "“The windswept highlands with the\n"
	.string "sweet fragrance of grass.”$"

VerdanturfTown_Text_WandasHouse:
	.string "Wanda's House$"

VerdanturfTown_Text_BattleTentSign:
	.string "Battle Tent Verdanturf Site\n"
	.string "“Feast Your Eyes on Battles!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "Rusturf Tunnel\n"
	.string "“Linking Rustboro and Verdanturf\p"
	.string "“The tunnel project has been\n"
	.string "canceled.”$"


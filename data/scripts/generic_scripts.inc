FollowerSpottedAnItemNearby::
	playse SE_PIN
	applymovement OBJ_EVENT_ID_FOLLOWER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 48
	setflag FLAG_FOLLOWER_FINDER_INTRO
	bufferlivemonnickname 0
	msgbox FollowerSpottedAnItemNearby_Text, MSGBOX_SIGN
	end
FollowerAfterFindingItem::
	bufferlivemonnickname 0
	msgbox FollowerSpottedAnItemNearby_Text, MSGBOX_NPC
	return

FollowerSpottedAnItemNearby_Text::
	.string "{STR_VAR_1} seems to have spotted\n"
	.string "something interesting nearby!$"

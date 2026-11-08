ArtisanCave_1F_MapScripts::
	.byte 0

ArtisanCave_1F_EventScript_MoveRelearner::
	lockall
	setflag FLAG_EGG_MOVES_TUTOR
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, ArtisanCave_1F_EventScript_AskTeachMove
	msgbox ArtisanCave_1F_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto ArtisanCave_1F_EventScript_AskTeachMove
	end

ArtisanCave_1F_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, ArtisanCave_1F_EventScript_ComeBackWithHeartScale
	msgbox ArtisanCave_1F_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, ArtisanCave_1F_EventScript_ComeBackWithHeartScale
	goto ArtisanCave_1F_EventScript_ChooseMon
	end

ArtisanCave_1F_EventScript_ChooseMon::
	msgbox ArtisanCave_1F_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, ArtisanCave_1F_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, ArtisanCave_1F_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, ArtisanCave_1F_EventScript_NoMoveToTeachMon
	goto ArtisanCave_1F_EventScript_ChooseMove
	end

ArtisanCave_1F_EventScript_ChooseMove::
	msgbox ArtisanCave_1F_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, ArtisanCave_1F_EventScript_ChooseMon
	msgbox ArtisanCave_1F_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto ArtisanCave_1F_EventScript_ComeBackWithHeartScale
	end

ArtisanCave_1F_EventScript_NoMoveToTeachMon::
	msgbox ArtisanCave_1F_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto ArtisanCave_1F_EventScript_ChooseMon
	end

ArtisanCave_1F_EventScript_CantTeachEgg::
	msgbox ArtisanCave_1F_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto ArtisanCave_1F_EventScript_ChooseMon
	end

ArtisanCave_1F_EventScript_ComeBackWithHeartScale::
	msgbox ArtisanCave_1F_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	clearflag FLAG_EGG_MOVES_TUTOR
	end

ArtisanCave_1F_Text_ImTheMoveTutor:
	.string "Ich bin der EI-ATTACKEN-KÜNSTLER.\p"
	.string "Ich betrachte Attacken mit dem Auge\n"
	.string "eines Künstlers und zeichne sie wie\l"
	.string "FARBEAGLE. Ich lehre Attacken, die\l"
	.string "für Neugeborene gedacht sind.\p"
	.string "Ich kann deinen POKéMON EI-Attacken\n"
	.string "schenken, wenn du magst.\p"
	.string "Alles für eine HERZSCHUPPE.\n"
	.string "Ich arbeite an meinem nächsten\l"
	.string "Meisterwerk.$"

ArtisanCave_1F_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! Das ist es! Eine echte HERZSCHUPPE\n"
	.string "der Leidenschaft, nicht weniger!\p"
	.string "Lass mich raten… Ich soll einem POKéMON\n"
	.string "eine neue Attacke zeichnen?!?$"

ArtisanCave_1F_Text_TutorWhichMon:
	.string "Welches POKéMON soll eine EI-Attacke\n"
	.string "lernen?$"

ArtisanCave_1F_Text_TeachWhichMove:
	.string "Welche Attacke soll ich es lehren?$"

ArtisanCave_1F_Text_DontHaveMoveToTeachPokemon:
	.string "Tut mir leid…\p"
	.string "Die Kunst dieser Attacke beherrsche\n"
	.string "ich für dieses POKéMON noch nicht.$"

ArtisanCave_1F_Text_HandedOverHeartScale:
	.string "{PLAYER} tauscht eine HERZSCHUPPE ein.$"

ArtisanCave_1F_Text_ComeBackWithHeartScale:
	.string "Falls deine POKéMON neue EI-Attacken\n"
	.string "lernen sollen, komm mit einer\l"
	.string "HERZSCHUPPE wieder.$"

ArtisanCave_1F_Text_CantTeachEgg:
	.string "Bitte? In meinem Skizzenbuch passt\n"
	.string "keine Attacke zu einem EI.$"

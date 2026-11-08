.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_2, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	goto_if_unset FLAG_RECEIVED_EON_TICKET, MeteorFalls_StevensCave_EventScript_GiveEonTicket
	release
	end

MeteorFalls_StevensCave_EventScript_GiveEonTicket::
	checkitemspace ITEM_EON_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MeteorFalls_StevensCave_EventScript_EonTicketBagFull
	giveitem ITEM_EON_TICKET
	setflag FLAG_RECEIVED_EON_TICKET
	setvar VAR_DISTRIBUTE_EON_TICKET, 0
	releaseall
	end

MeteorFalls_StevensCave_EventScript_EonTicketBagFull::
	vmessage MeteorFalls_StevensCave_Text_EonTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	goto_if_unset FLAG_RECEIVED_EON_TICKET, MeteorFalls_StevensCave_EventScript_GiveEonTicket
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "TROY: Oh, wow, {PLAYER}{KUN}!\n"
	.string "Ich bin erstaunt, dass du mich\l"
	.string "gefunden hast!\p"
	.string "Du, äh… denkst bestimmt, ich bin nur\n"
	.string "verrückt nach Steinen, nicht wahr?\p"
	.string "Nein, das tust du bestimmt nicht.\p"
	.string "Wir haben ja schon als Team im\n"
	.string "MOOSBACH CITY RAUMFAHRTZENTRUM\l"
	.string "gekämpft.\p"
	.string "Da hast du bestimmt einen Eindruck\n"
	.string "davon gewonnen, wie gut ich bin.\p"
	.string "Okay, {PLAYER}{KUN}, wenn du dich auf eine\n"
	.string "ernsthafte Herausforderung einlässt,\l"
	.string "sei auf das Schlimmste gefasst!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Du…\n"
	.string "Ich hätte nie gedacht, dass du so stark\l"
	.string "werden würdest…$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "TROY: Aber wenn ich es recht bedenke…\n"
	.string "Damals, als wir uns zum ersten Mal in der\p"
	.string "GRANITHÖHLE von FAUSTAUHAVEN\n"
	.string "begegneten, hatte ich schon dieses\l"
	.string "Gefühl.\p"
	.string "Ich wusste, du würdest irgendwann der\n"
	.string "CHAMP werden.\p"
	.string "Und mein Gefühl trügt mich nie!\p"
	.string "Wohin wird dein Weg dich jetzt führen?\p"
	.string "… … … … …\n"
	.string "…\l"
	.string "… … … … …\l"
	.string "…\p"
	.string "Hähähähä, das kann selbst ich dir\n"
	.string "nicht sagen.$"

MeteorFalls_StevensCave_Text_EonTicket1:
	.string "Du bist unglaublich stark geworden,\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Als Zeichen meines Respekts möchte ich\n"
	.string "dir das hier geben.$"

MeteorFalls_StevensCave_Text_EonTicketBagFull:
	.string "Oh, es tut mir leid, {PLAYER}! Die\n"
	.string "BASIS-ITEM-TASCHE in deinem\l"
	.string "BEUTEL ist voll.\l"
	.string "Lagere etwas auf deinem PC und\l"
	.string "komme anschließend zurück.$"

MeteorFalls_StevensCave_Text_EonTicket2:
	.string "Damit kannst du in SEEGRASULB CITY\n"
	.string "die Fähre zur INSEL IM SÜDEN nehmen.\p"
	.string "Ich habe Gerüchte über ein außer-\n"
	.string "gewöhnlich starkes POKéMON dort gehört.\p"
	.string "Bei deiner Stärke traue ich dir zu,\n"
	.string "besser damit fertigzuwerden als ich.\p"
	.string "Du hast bewiesen, dass du ein wahrer\n"
	.string "CHAMP bist, {PLAYER}{KUN}.$"

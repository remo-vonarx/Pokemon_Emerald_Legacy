PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	goto_if_set FLAG_SHOW_MIRAGE_ISLAND, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_EventScript_OldWoman::
	msgbox PacifidlogTown_House5_Text_OldWoman, MSGBOX_NPC
	end

PacifidlogTown_House5_EventScript_OldMan::
	msgbox PacifidlogTown_House5_Text_OldMan, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
	.string "Ich kann WUNDEREILAND heute\n"
	.string "nicht sehen…$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
	.string "Oh! Oh! Heute kann ich WUNDEREILAND\n"
	.string "sehen!$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
	.string "WUNDEREILAND…\p"
	.string "Die Insel ist sichtbar oder nicht\n"
	.string "sichtbar. Das hängt vom Wetter ab, das\l"
	.string "Fata Morganen möglich macht oder nicht.\p"
	.string "Oder verschwindet die Insel\n"
	.string "tatsächlich manchmal?$"

PacifidlogTown_House5_Text_OldWoman:
	.string "Ich habe Leute darüber reden hören,\n"
	.string "dass die Zeit nicht überall gleich\l"
	.string "vergeht.\p"
	.string "Angeblich können Uhren seltsame Dinge\n"
	.string "tun. Ich habe mal lange auf meine Uhr\l"
	.string "gestarrt, aber es ist nichts passiert.$"

PacifidlogTown_House5_Text_OldMan:
	.string "Bei Sonnenaufgang sind die Wellen am\n"
	.string "leisesten… ruhig zur Tageswende… und\l"
	.string "wieder still bei Einbruch der Nacht.\p"
	.string "Das alles wirkt wie ein friedlicher\n"
	.string "Tanz, nicht wahr?\p"
	.string "Ich habe immer geglaubt, WUNDEREILAND\n"
	.string "erscheint, wenn der Tag friedlich\l"
	.string "wirkt.$"

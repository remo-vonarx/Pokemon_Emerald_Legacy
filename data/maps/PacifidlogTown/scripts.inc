PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_EventScript_Fisherman::
	faceplayer
	call PacifidlogTown_EventScript_FishermanCheckFishingRod
	call PacifidlogTown_EventScript_FishermanCheckPokeballs
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	release
	end

PacifidlogTown_EventScript_FishermanCheckFishingRod::
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	msgbox PacifidlogTown_Text_NoFishingRod, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	return
PacifidlogTown_EventScript_FishermanCheckPokeballs::
	checkitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_ULTRA_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_POKE_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_NET_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_DIVE_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_NEST_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_REPEAT_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_TIMER_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_LUXURY_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	checkitem ITEM_PREMIER_BALL
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_EventScript_Return
	msgbox PacifidlogTown_Text_NoPokeballs, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
PacifidlogTown_EventScript_Return::
	return

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "Im Meer zwischen FLOSSBRUNN und\n"
	.string "GRAPHITPORT CITY befinden sich\l"
	.string "reißende Strömungen.\p"
	.string "Wenn du dort SURFER einsetzt, kann es\n"
	.string "sein, dass du fortgetrieben wirst.$"

PacifidlogTown_Text_NeatHousesOnWater:
	.string "Schau mal. Ist das nicht hübsch?\n"
	.string "Die Häuser stehen auf dem Wasser.\p"
	.string "Ich wurde hier geboren.$"

PacifidlogTown_Text_SkyPillarTooScary:
	.string "Der HIMMELTURM?\p"
	.string "Ach, du meinst bestimmt diesen hohen,\n"
	.string "hohen Turm, der sich hier in der Nähe\l"
	.string "befindet.\p"
	.string "Also, wenn du mich fragst - ich würde\n"
	.string "niemals da hochgehen. Da hätte ich viel\l"
	.string "zu viel Angst, weil das so hoch ist!\p"
	.string "Leben auf Höhe des Meeresspiegels in\n"
	.string "FLOSSBRUNN, das ist mein Ding.$"

PacifidlogTown_Text_NoFishingRod:
	.string "Moment mal, du hast nicht einmal eine\n"
	.string "ANGEL? Wie bist du überhaupt bis\l"
	.string "hierhergekommen?\p"
	.string "Hier, nimm eine von meinen.$"

PacifidlogTown_Text_NoPokeballs:
	.string "Warte mal… Hast du überhaupt POKéBÄLLe\n"
	.string "dabei?\p"
	.string "Du brauchst welche, bevor du\n"
	.string "weitergehst. Nimm ein paar von meinen.$"

PacifidlogTown_Text_TownSign:
	.string "FLOSSBRUNN\p"
	.string "“Wo die Morgensonne ein Lächeln auf\n"
	.string "das Meer zaubert.”$"

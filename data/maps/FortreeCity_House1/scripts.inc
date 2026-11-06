FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_LOUDRED
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "Hey, hör mal zu! Ich suche schon ewig\n"
	.string "nach einem {STR_VAR_1}!\l"
	.string "Ich habe keine Ruhe, bis ich eins habe!\p"
	.string "…Hast du das gehört?\n"
	.string "Das ist der Klang purer\l"
	.string "Entschlossenheit!\p"
	.string "Jetzt, wo du das weißt, tauschst du\n"
	.string "doch bestimmt dein {STR_VAR_1}\l"
	.string "gegen mein {STR_VAR_2}?!?$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "Wow! Du willst wirklich tauschen! Ich\n"
	.string "sorge dafür, dass dieses {STR_VAR_1}\l"
	.string "in Topform bleibt.\p"
	.string "Pass du gut auf mein {STR_VAR_2} auf,\n"
	.string "okay?$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Hmm, nee, das ist es nicht.\n"
	.string "Ich brauche ein echtes {STR_VAR_1}.$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "Ach so… Du willst also nicht tauschen,\n"
	.string "was? Schon okay, vielleicht ja ein\l"
	.string "anderes Mal!$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "Mein KECLEON wird das stärkste weit\n"
	.string "und breit! Ich hoffe, KRAKEELO passt\l"
	.string "gut in dein Team!$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "Mit anderen POKéMON tauschen…\p"
	.string "Das ist, als ob du die Erinnerungen mit\n"
	.string "anderen Menschen teilst.$"

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZACHS: Gumomoh?$"


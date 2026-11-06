BattleFrontier_Lounge8_MapScripts::
	.byte 0

BattleFrontier_Lounge8_EventScript_Man::
	msgbox BattleFrontier_Lounge8_Text_WhatATrainerNeeds, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_Woman::
	msgbox BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains, MSGBOX_NPC
	end

BattleFrontier_Lounge8_EventScript_NinjaBoy::
	lock
	faceplayer
	goto_if_set FLAG_FRONTIER_PLUSLE_NPC_TRADE_COMPLETED, BattleFrontier_Lounge8_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_Lounge8_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge8_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge8_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_Lounge8_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge8_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FRONTIER_PLUSLE_NPC_TRADE_COMPLETED
	release
	end

BattleFrontier_Lounge8_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge8_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge8_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge8_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge8_Text_YouWillTradeWontYou:
	.string "Im DUELLTURM hat mir ein älteres\n"
	.string "Mädchen gesagt, dass ich sehr viel\l"
	.string "Talent fürs Kämpfen habe!\p"
	.string "Ich mag aber lieber POKéMON\n"
	.string "WETTBEWERBE!\p"
	.string "Aber bei den WETTBEWERBEn schneide\n"
	.string "ich nie so sonderlich gut ab.\p"
	.string "Ich muss mir unbedingt ein {STR_VAR_1}\n"
	.string "besorgen! Das hilft mir, POKéMON\l"
	.string "WETTBEWERBE zu gewinnen.\p"
	.string "Nachdem du das gehört hast, tauschst\n"
	.string "du doch dein {STR_VAR_1} gegen mein\l"
	.string "{STR_VAR_2}, oder?$"

BattleFrontier_Lounge8_Text_MonYouTakeCare:
	.string "Oh, super! Dann mal los!\p"
	.string "Willkommen, {STR_VAR_1}!\n"
	.string "Pass auf dich auf, {STR_VAR_2}!$"

BattleFrontier_Lounge8_Text_ThisIsntAMon:
	.string "Äh, nee, so geht das nicht!\n"
	.string "Das ist doch gar kein {STR_VAR_1}.$"

BattleFrontier_Lounge8_Text_YouWontTradeMe:
	.string "Nein? Du willst nicht tauschen?\n"
	.string "Obwohl ich dir mein Herz offenbart\l"
	.string "habe?$"

BattleFrontier_Lounge8_Text_GoingToMakeVolbeatStrong:
	.string "Ich werde dafür sorgen, dass VOLBEAT\n"
	.string "super-megastark wird!\p"
	.string "Ich hoffe, du sorgst dich genauso um\n"
	.string "PLUSLE!$"

BattleFrontier_Lounge8_Text_WhatATrainerNeeds:
	.string "Was braucht ein TRAINER?\p"
	.string "Kenntnis…\n"
	.string "Strategie…\l"
	.string "Ein glückliches Los…\l"
	.string "Einen groben Überblick…\l"
	.string "Seele…\l"
	.string "Bravur…\l"
	.string "Und eine gute Anlage…\p"
	.string "Nun, das bringe ich alles mit!\n"
	.string "Ich werde überall einfach unschlagbar\l"
	.string "sein!\p"
	.string "Was? POKéMON?!?\n"
	.string "Was ist das denn? Kann man das essen?$"

BattleFrontier_Lounge8_Text_KnowAboutFrontierBrains:
	.string "Hast du schon mal was über die\n"
	.string "KAMPFKORYPHÄEN gehört?\p"
	.string "So nennt SCOTT die sieben TRAINER,\n"
	.string "die die sieben Einrichtungen der\l"
	.string "KAMPFZONE leiten.$"

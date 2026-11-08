RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_NUMEL
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "Oh, du findest mein POKéMON cool?\n"
	.string "Ja, das finde ich auch!\p"
	.string "Aber hey, wenn du magst, würde ich es\n"
	.string "mit dir tauschen.\p"
	.string "Ich gebe dir mein {STR_VAR_2}, wenn du\n"
	.string "mir ein {STR_VAR_1} gibst.\l"
	.string "Einverstanden?$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Hehe… Pass gut auf {STR_VAR_2} auf,\n"
	.string "ja? Es liebt Abenteuer!$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "Hmm? Das sieht für mich aber nicht wie\n"
	.string "ein {STR_VAR_1} aus…$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Du willst nicht tauschen? Kein Problem.\n"
	.string "CAMAUB bleibt immer mein kleiner\l"
	.string "Entdecker.$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Weißt du, jedes POKéMON kann etwas\n"
	.string "Besonderes sein, wenn du ihm Liebe\l"
	.string "und Geduld schenkst.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "An allen Orten gibt es alle Sorten von\n"
	.string "POKéMON und Menschen.\p"
	.string "Ich finde das faszinierend, daher\n"
	.string "besuche ich alle möglichen Orte.$"


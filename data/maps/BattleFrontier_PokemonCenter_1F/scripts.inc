.set LOCALID_NURSE, 1

BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	lock
	faceplayer
	goto_if_set FLAG_FRONTIER_SEEDOT_NPC_TRADE_COMPLETED, BattleFrontier_PokemonCenter_1F_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_PokemonCenter_1F_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_PokemonCenter_1F_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_PokemonCenter_1F_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_PokemonCenter_1F_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox BattleFrontier_PokemonCenter_1F_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_FRONTIER_SEEDOT_NPC_TRADE_COMPLETED
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox BattleFrontier_PokemonCenter_1F_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_PokemonCenter_1F_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_TradeCompleted::
	msgbox BattleFrontier_PokemonCenter_1F_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker::
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end
	
BattleFrontier_PokemonCenter_1F_Text_IllTradeIfYouWant:
	.string "Hier war gerade jemand, der hat ein\n"
	.string "{STR_VAR_1} gehabt, ein POKéMON, das\l"
	.string "ich vorher noch nie gesehen habe.\p"
	.string "Mir ist gleich aufgefallen, wie selten\n"
	.string "und beeindruckend es ist.\p"
	.string "Falls du eins findest, tausche ich es\n"
	.string "gern gegen mein {STR_VAR_2}.\p"
	.string "Es ist vielleicht nicht so selten,\n"
	.string "aber mein POKéMON ist süß. Vielleicht\l"
	.string "findest du ja, der Tausch lohnt sich.$"

BattleFrontier_PokemonCenter_1F_Text_PleaseBeGoodToMyPokemon:
	.string "Ähähähähä…\n"
	.string "Sei nett zu meinem POKéMON.$"

BattleFrontier_PokemonCenter_1F_Text_DoesntLookLikeMonToMe:
	.string "Wie? Das sieht für mich aber nicht wie\n"
	.string "ein {STR_VAR_1} aus!$"

BattleFrontier_PokemonCenter_1F_Text_YouDontWantToThatsOkay:
	.string "Du willst nicht tauschen? Kein Problem.\n"
	.string "Aber mein POKéMON ist wirklich niedlich,\l"
	.string "das weißt du schon?!?$"

BattleFrontier_PokemonCenter_1F_Text_AnyPokemonCanBeCute:
	.string "Jedes POKéMON ist niedlich, wenn es mit\n"
	.string "Freundlichkeit und Fürsorge\l"
	.string "aufgezogen wird.$"

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena:
	.string "Okay! Nächster Halt: KAMPFRING!\n"
	.string "Ich sollte mir schnell ein POKéMON aus\l"
	.string "dem POKéMON-Lagerungs-System nehmen.$"

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge:
	.string "Kicher… Mit diesem Schatz hier werde\n"
	.string "ich jede Herausforderung bestehen!$"

BattleFrontier_PokemonCenter_1F_Text_Skitty:
	.string "ENECO: Mya myaaah!$"

.set LOCALID_NURSE, 1

MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_MAUVILLE_NPC_TRADE_COMPLETED, MauvilleCity_PokemonCenter_1F_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SNORUNT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclinePokemonTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MauvilleCity_PokemonCenter_1F_EventScript_DeclinePokemonTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, MauvilleCity_PokemonCenter_1F_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox MauvilleCity_PokemonCenter_1F_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_MAUVILLE_NPC_TRADE_COMPLETED
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclinePokemonTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TradeCompleted::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThrilledToSeeNewPlaces, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
	.string "Wenn ich auf STATISTIKTAUSCH Zugriff\n"
	.string "nehme, werden die neuesten Nachrichten\l"
	.string "aus FAUSTAUHAVEN hochgeladen.\p"
	.string "Diese Daten decken sich nun mit denen\n"
	.string "meines Freundes!$"

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
	.string "Im oberen Stockwerk des POKéMON-\n"
	.string "CENTERs wurde die Möglichkeit des\l"
	.string "STATISTIKTAUSCHes eingerichtet.\p"
	.string "Ich weiß nicht genau, was das ist. Aber\n"
	.string "das werde ich herausfinden! Ist\l"
	.string "bestimmt lustig!$"

MauvilleCity_PokemonCenter_1F_Text_YouWillTradeWontYou:
	.string "Oh! Du hast ein {STR_VAR_1}, nicht wahr?\p"
	.string "Die sind so lebhaft! Würdest du es\n"
	.string "gegen mein {STR_VAR_2} tauschen?\p"
	.string "Es ist ein wirklich einzigartiges\n"
	.string "POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_MonYouTakeCare:
	.string "Pass gut auf FROSTI auf, ja?\p"
	.string "Am Anfang ist es etwas schüchtern, aber\n"
	.string "es taut schnell auf!$"

MauvilleCity_PokemonCenter_1F_Text_ThisIsntAMon:
	.string "Hm? Moment mal… Das ist nicht das\n"
	.string "{STR_VAR_1}, auf das ich gehofft habe!\p"
	.string "Willst du mich auf den Arm nehmen?$"

MauvilleCity_PokemonCenter_1F_Text_YouWontTradeMe:
	.string "Oh, du willst nicht tauschen?\p"
	.string "Schon gut, aber falls du es dir anders\n"
	.string "überlegst: Ich würde für mein\l"
	.string "SCHNEPPKE gerne einen guten Partner\l"
	.string "finden!$"

MauvilleCity_PokemonCenter_1F_Text_ThrilledToSeeNewPlaces:
	.string "FROSTI wird sich bestimmt freuen, neue\n"
	.string "Orte zu sehen! Mit etwas Training wird\l"
	.string "es sicher ein echter Star!$"

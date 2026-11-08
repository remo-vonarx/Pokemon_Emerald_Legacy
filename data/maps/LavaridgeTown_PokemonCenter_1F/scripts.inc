.set LOCALID_NURSE, 1

LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_May::
	lock
	faceplayer
	msgbox LavaridgeTown_PokemonCenter_1F_Text_MayTravelToPetalburg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LavaridgeTown_PokemonCenter_1F_EventScript_TravelToPetalburg
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_PokemonCenter_1F_EventScript_RivalWaits
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Brendan::
	lock
	faceplayer
	msgbox LavaridgeTown_PokemonCenter_1F_Text_BrendanTravelToPetalburg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LavaridgeTown_PokemonCenter_1F_EventScript_TravelToPetalburg
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_PokemonCenter_1F_EventScript_RivalWaits
	end

LavaridgeTown_PokemonCenter_1F_EventScript_TravelToPetalburg::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_RivalTravelToPetalburgLeaves, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 6
	setflag FLAG_HIDE_PETALBURG_CITY_MAY
	setflag FLAG_HIDE_PETALBURG_CITY_BRENDAN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgCity_LoadMay
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgCity_LeadBrendan
LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgCity_LoadMay::
	clearflag FLAG_HIDE_PETALBURG_CITY_MAY
	goto LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgWarp
LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgCity_LeadBrendan::
	clearflag FLAG_HIDE_PETALBURG_CITY_BRENDAN
LavaridgeTown_PokemonCenter_1F_EventScript_PetalburgWarp::
	special HealPlayerParty
	warp MAP_PETALBURG_CITY, 15, 12
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_HIDE_LAVARIDGE_POKEMON_CENTER_BRENDAN
	setflag FLAG_HIDE_LAVARIDGE_POKEMON_CENTER_MAY
	releaseall
	end

LavaridgeTown_PokemonCenter_1F_EventScript_RivalWaits:
	msgbox LavaridgeTown_PokemonCenter_1F_Text_RivalWaits, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "Ich denke, die POKéMON fühlen sich\n"
	.string "ihrem TRAINER mehr verbunden, wenn sie\l"
	.string "viel Zeit miteinander verbringen.\p"
	.string "Je länger, desto besser.\n"
	.string "Das ist meine Meinung.$"

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "Es grenzt an Magie, wie ein Bad in der\n"
	.string "Heißen Quelle einen stärkt.\p"
	.string "Ich wünschte, ich könnte meinen\n"
	.string "POKéMON auch so ein Bad gönnen.$"

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "Hohoho! Hey, Kindchen, du kannst von\n"
	.string "hier die Heißen Quellen erreichen.\p"
	.string "Wenn POKéMON ruhen, sollten sich\n"
	.string "ihre TRAINER auch ausruhen.$"

LavaridgeTown_PokemonCenter_1F_Text_MayTravelToPetalburg:
	.string "MAIKE: Ich will als Nächstes zur ARENA\n"
	.string "von BLÜTENBURG CITY…\p"
	.string "Sollen wir zusammen zurückreisen?\n"
	.string "Zurück nach BLÜTENBURG CITY?$"

LavaridgeTown_PokemonCenter_1F_Text_BrendanTravelToPetalburg:
	.string "BRIX: Ich will als Nächstes zur ARENA\n"
	.string "von BLÜTENBURG CITY…\p"
	.string "Sollen wir zusammen zurückreisen?\n"
	.string "Zurück nach BLÜTENBURG CITY?$"

LavaridgeTown_PokemonCenter_1F_Text_RivalTravelToPetalburgLeaves:
	.string "Aye, aye!\n"
	.string "Dann nichts wie los!$"

LavaridgeTown_PokemonCenter_1F_Text_RivalWaits:
	.string "Oh, das ist okay.\p"
	.string "Ich bleibe noch eine Weile hier, falls\n"
	.string "du es dir anders überlegst.\p"
	.string "Man sieht sich!$"

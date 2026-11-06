.set LOCALID_ZINNIA, 1

SkyPillar_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_3F_OnTransition
	.byte 0

SkyPillar_3F_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_3F_EventScript_CleanFloor
	end

SkyPillar_3F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_3F_CLEAN
	return

SkyPillar_3F_EventScript_Zinnia::
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SkyPillar_3F_Text_Zinnia, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ZINNIA, Common_Movement_FaceUp
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZINNIA
	fadescreen FADE_FROM_BLACK
	setflag FLAG_SPOKE_TO_ZINNIA_3F
	setflag FLAG_HIDE_ZINNIA_3F
	clearflag FLAG_HIDE_ZINNIA_4F
	release
	end

SkyPillar_3F_Text_Zinnia::
	.string "Nach diesem heftigen Zusammenstoß,\n"
	.string "als KYOGRE und GROUDON wieder in die\l"
	.string "Tiefe gesunken waren, kehrte RAYQUAZA\l"
	.string "in den Himmel zurück, von wo aus es\l"
	.string "über uns wacht.\p"
	.string "Da erbaute mein Volk den\n"
	.string "HIMMELTURM…\p"
	.string "Einen Ort, an dem wir unseren\n"
	.string "DRACHENGOTT erreichen können, wenn\l"
	.string "die Welt in Gefahr ist.\p"
	.string "Er ist wie unsere eigene Verbindung\n"
	.string "zum Himmel. Hier können wir RAYQUAZA\l"
	.string "rufen, falls wir es je wieder\l"
	.string "brauchen.$"

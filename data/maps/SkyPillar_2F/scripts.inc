.set LOCALID_ZINNIA, 1

SkyPillar_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_2F_SetHoleWarp
	.byte 0

SkyPillar_2F_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_2F_EventScript_CleanFloor
	copyvar VAR_ICE_STEP_COUNT, 1
	end

SkyPillar_2F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_2F_CLEAN
	return

SkyPillar_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_SKY_PILLAR_1F
	end

SkyPillar_2F_EventScript_Zinnia::
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SkyPillar_2F_Text_Zinnia, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ZINNIA, Common_Movement_FaceUp
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZINNIA
	fadescreen FADE_FROM_BLACK
	setflag FLAG_SPOKE_TO_ZINNIA_2F
	setflag FLAG_HIDE_ZINNIA_2F
	clearflag FLAG_HIDE_ZINNIA_3F
	release
	end

SkyPillar_2F_Text_Zinnia::
	.string "Lass mich dir eine Geschichte erzählen.\p"
	.string "Vor tausend Jahren stieg ein gewaltiger\n"
	.string "Ausbruch aus dem Meer empor.\p"
	.string "So entstand XENEROVILLE, aber dadurch\n"
	.string "wurden auch GROUDON und KYOGRE\l"
	.string "aufgeschreckt.\p"
	.string "Anfangs schienen sie ruhig… bis sie\n"
	.string "aufeinandertrafen.\l"
	.string "Dann: Chaos!\p"
	.string "Meine Vorfahrin war damals die\n"
	.string "WISSENSHÜTERIN, und sie betete mit\l"
	.string "allem, was sie hatte, um RAYQUAZAs\l"
	.string "Rückkehr.\p"
	.string "Und als RAYQUAZA kam, beruhigte es\n"
	.string "den Sturm und schickte die beiden\l"
	.string "wieder schlafen.\p"
	.string "Seitdem führen wir diese Aufgabe fort\n"
	.string "und geben unser Wissen weiter…\p"
	.string "bereit, RAYQUAZA wieder zu rufen,\n"
	.string "falls es je nötig sein sollte.$"

SkyPillar_5F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_5F_OnTransition
	.byte 0

SkyPillar_5F_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_5F_EventScript_CleanFloor
	return

SkyPillar_5F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_5F_CLEAN
	return

SkyPillar_5F_EventScript_Zinnia::
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SkyPillar_5F_Text_Zinnia, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ZINNIA, Common_Movement_FaceUp
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZINNIA
	fadescreen FADE_FROM_BLACK
	setflag FLAG_SPOKE_TO_ZINNIA_5F
	setflag FLAG_HIDE_ZINNIA_5F
	clearflag FLAG_HIDE_ZINNIA_TOP
	release
	end

SkyPillar_5F_Text_Zinnia::
	.string "Wir wussten, dass KYOGRE und GROUDON\n"
	.string "vielleicht wieder erwachen könnten,\l"
	.string "selbst nach so vielen Jahren Frieden.\p"
	.string "Als Schutz erschufen wir daher die\n"
	.string "ROTE und die BLAUE KUGEL, in der\l"
	.string "Hoffnung, dass sie den Frieden\l"
	.string "bewahren.\p"
	.string "Aber sie wurden nie wirklich auf die\n"
	.string "Probe gestellt.\p"
	.string "Niemand wusste sicher, ob sie so\n"
	.string "mächtige Wesen kontrollieren können.\p"
	.string "Wir hofften, RAYQUAZA nie wieder\n"
	.string "rufen zu müssen…\p"
	.string "Aber das Schicksal ist schon komisch,\n"
	.string "oder?\p"
	.string "Und nun sind wir hier… Und ausgerechnet\n"
	.string "du hast RAYQUAZA gerufen, als HOENN\l"
	.string "es am meisten brauchte.$"

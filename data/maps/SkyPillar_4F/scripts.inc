SkyPillar_4F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_4F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_4F_SetHoleWarp
	.byte 0

SkyPillar_4F_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_4F_EventScript_CleanFloor
	copyvar VAR_ICE_STEP_COUNT, 1
	end

SkyPillar_4F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_4F_CLEAN
	return

SkyPillar_4F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_SKY_PILLAR_3F
	end

SkyPillar_4F_EventScript_Zinnia::
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SkyPillar_4F_Text_Zinnia, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ZINNIA, Common_Movement_FaceUp
	waitmovement 0
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZINNIA
	fadescreen FADE_FROM_BLACK
	setflag FLAG_SPOKE_TO_ZINNIA_4F
	setflag FLAG_HIDE_ZINNIA_4F
	clearflag FLAG_HIDE_ZINNIA_5F
	release
	end

SkyPillar_4F_Text_Zinnia::
	.string "Aus jenem Ausbruch entstand die\n"
	.string "URZEITHÖHLE…\p"
	.string "Ein Ort voller Geheimnisse, die bis zu\n"
	.string "den Wurzeln von XENEROVILLE selbst\l"
	.string "zurückreichen.\p"
	.string "Nur wenige, wie WASSILI, können sie\n"
	.string "wirklich verstehen.\p"
	.string "Die URZEITHÖHLE und der HIMMELTURM?\p"
	.string "Sie sind zwei Hälften desselben\n"
	.string "Rätsels, beide ein Teil des\l"
	.string "Gleichgewichts des Lebens.\p"
	.string "WASSILI konnte dich dorthin führen,\n"
	.string "weil er das alte Blut von XENEROVILLE\l"
	.string "in sich trägt, so wie ich das der\l"
	.string "METEORANER.\p"
	.string "Siehst du? So sind wir miteinander\n"
	.string "verbunden.$"

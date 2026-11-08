.set LOCALID_RAYQUAZA_SLEEPING, 1
.set LOCALID_ASTER, 3
.set LOCALID_ZINNIA, 4

SkyPillar_Top_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_Top_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Top_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SkyPillar_Top_OnWarp
	.byte 0

SkyPillar_Top_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SkyPillar_Top_EventScript_TryRemoveRayquaza
	end

SkyPillar_Top_EventScript_TryRemoveRayquaza::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SkyPillar_Top_OnTransition:
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_SetCleanLayout
	call_if_ge VAR_SKY_PILLAR_STATE, 2, SkyPillar_Top_EventScript_TryShowRayquaza
	end

SkyPillar_Top_EventScript_SetCleanLayout::
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	setobjectmovementtype LOCALID_RAYQUAZA_SLEEPING, MOVEMENT_TYPE_FACE_DOWN
	return

SkyPillar_Top_EventScript_TryShowRayquaza::
	call_if_unset FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ShowRayquaza
	return

SkyPillar_Top_EventScript_ShowRayquaza::
	clearflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL
	return

SkyPillar_Top_OnWarp:
	map_script_2 VAR_SKY_PILLAR_STATE, 0, SkyPillar_Top_EventScript_RayquazaFaceDown
	.2byte 0

SkyPillar_Top_EventScript_RayquazaFaceDown::
	turnobject LOCALID_RAYQUAZA_SLEEPING, DIR_SOUTH
	end

SkyPillar_Top_EventScript_Rayquaza::
	lockall
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAYQUAZA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SkyPillar_Top_EventScript_DefeatedRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SkyPillar_Top_EventScript_RanFromRayquaza
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SkyPillar_Top_EventScript_RanFromRayquaza
	setflag FLAG_DEFEATED_RAYQUAZA
	releaseall
	end

SkyPillar_Top_EventScript_DefeatedRayquaza::
	setflag FLAG_DEFEATED_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_RanFromRayquaza::
	setvar VAR_0x8004, SPECIES_RAYQUAZA
	goto SkyPillar_Top_EventScript_RanFromRayquaza2
	end

SkyPillar_Top_EventScript_DefeatedRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Top_EventScript_RanFromRayquaza2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Top_EventScript_AwakenRayquaza::
	lockall
	fadeoutbgm 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaStir
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, CRY_MODE_ENCOUNTER
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	applymovement LOCALID_RAYQUAZA_SLEEPING, SkyPillar_Top_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject LOCALID_RAYQUAZA_SLEEPING
	msgbox SkyPillar_Top_Text_RayquazaFlewOff, MSGBOX_DEFAULT
	closemessage
	delay 20
	fadeinbgm 1
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	releaseall
	end

SkyPillar_Top_EventScript_Zinnia::
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_ASTER, Common_Movement_FaceLeft
	waitmovement 0
	delay 20
	applymovement LOCALID_ASTER, Common_Movement_FaceDown
	waitmovement 0
	msgbox SkyPillar_Top_Text_Zinnia, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ZINNIA, SkyPillar_Top_Text_ZinniaDefeat
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SkyPillar_Top_EventScript_ZinniaPostBattle1Male
	call_if_eq VAR_RESULT, FEMALE, SkyPillar_Top_EventScript_ZinniaPostBattle1Female
	applymovement LOCALID_ZINNIA, Common_Movement_FaceRight
	waitmovement 0
	msgbox SkyPillar_Top_Text_ZinniaPostBattle2, MSGBOX_DEFAULT
	applymovement LOCALID_ZINNIA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SkyPillar_Top_Text_ZinniaPostBattle3, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZINNIA
	removeobject LOCALID_ASTER
	fadescreen FADE_FROM_BLACK
	setflag FLAG_DEFEATED_ZINNIA
	release
	end

SkyPillar_Top_EventScript_ZinniaPostBattle1Male::
	msgbox SkyPillar_Top_Text_ZinniaPostBattle1, MSGBOX_DEFAULT
	return

SkyPillar_Top_EventScript_ZinniaPostBattle1Female::
	msgbox SkyPillar_Top_Text_ZinniaPostBattle1Female, MSGBOX_DEFAULT
	return

SkyPillar_Top_EventScript_Aster::
	msgbox SkyPillar_Top_Text_Whismur, MSGBOX_NPC
	end

@ Rayquaza has unusual movement frames
@ See comments, or sAnimTable_Rayquaza
SkyPillar_Top_Movement_RayquazaStir:
	delay_16
	walk_in_place_fast_left  @ Coiled, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left  @ Coiled, mouth open
	delay_16
	walk_in_place_right  @ Normal, awake
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Movement_RayquazaFlyOff:
	delay_16
	walk_in_place_down  @ Coiled, asleep
	delay_8
	walk_in_place_right  @ Normal, awake
	delay_8
	walk_faster_up  @ Fly up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_Movement_CameraPanUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_CameraPanDown:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SkyPillar_Top_Text_RayquazaFlewOff:
	.string "RAYQUAZA ist erwacht und weggeflogen…$"

SkyPillar_Top_Text_Zinnia:
	.string "RAYQUAZAs Aufgabe ist mehr, als nur\n"
	.string "GROUDON und KYOGRE in Schach zu halten…\p"
	.string "Es bewahrt das Gleichgewicht, wenn es\n"
	.string "sonst niemand kann.\p"
	.string "Und wir glauben… Eines Tages könnte\n"
	.string "etwas noch Größeres dieses\l"
	.string "Gleichgewicht bedrohen,\p"
	.string "etwas, dem wir uns vielleicht nicht\n"
	.string "allein stellen können.\p"
	.string "Deshalb bin ich hier… Ich will sehen,\n"
	.string "ob du an RAYQUAZAs Seite stehen\l"
	.string "kannst und wirklich was taugst.\p"
	.string "Also, was meinst du? Zeigst du mir,\n"
	.string "was du draufhast?$"

SkyPillar_Top_Text_ZinniaDefeat:
	.string "…\n"
	.string "…Ich schätze… Jetzt liegt es an dir…$"

SkyPillar_Top_Text_ZinniaPostBattle1:
	.string "{PLAYER}, du und RAYQUAZA…\n"
	.string "gemeinsam.\p"
	.string "Ich überlasse diese Aufgabe dir, unserem\n"
	.string "neuen NACHFOLGER.\p"
	.string "NACHFOLGER {PLAYER}.\p"
	.string "Du und RAYQUAZA müsst die Natur…\n"
	.string "die POKéMON… die Menschen beschützen…$"

SkyPillar_Top_Text_ZinniaPostBattle1Female:
	.string "{PLAYER}, du und RAYQUAZA…\n"
	.string "gemeinsam.\p"
	.string "Ich überlasse diese Aufgabe dir, unserer\n"
	.string "neuen NACHFOLGERIN.\p"
	.string "NACHFOLGERIN {PLAYER}.\p"
	.string "Du und RAYQUAZA müsst die Natur…\n"
	.string "die POKéMON… die Menschen beschützen…$"

SkyPillar_Top_Text_ZinniaPostBattle2:
	.string "Schon als kleines Mädchen habe ich\n"
	.string "immer zum Himmel hinaufgeschaut.\p"
	.string "Wenn ich so voller Zweifel war, dass\n"
	.string "ich dachte, mein Herz würde daran\l"
	.string "zerbrechen…$"

SkyPillar_Top_Text_ZinniaPostBattle3:
	.string "…habe ich immer so zum Himmel hinauf-\n"
	.string "geschaut… Zusammen mit AVELINA.\p"
	.string "Ich glaube, ich werde jetzt versuchen\n"
	.string "herauszufinden, ob etwas, das einst\l"
	.string "verloren ging, neu beginnen kann.\p"
	.string "Bis wir uns wiedersehen…$"

SkyPillar_Top_Text_Whismur:
	.string "Mel, Mel!$"

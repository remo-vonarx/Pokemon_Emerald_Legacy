.set LOCALID_GROUDON, 1
.set LOCALID_MAXIE, 2

TerraCave_End_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TerraCave_End_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, TerraCave_End_OnTransition
	.byte 0

TerraCave_End_OnResume:
	setflag FLAG_HIDE_MAXIE_TERRA_CAVE
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, TerraCave_End_EventScript_TryRemoveGroudon
	end

TerraCave_End_EventScript_TryRemoveGroudon::
	clearflag FLAG_HIDE_MAXIE_TERRA_CAVE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_GROUDON
	return

TerraCave_End_OnTransition:
	call_if_unset FLAG_DEFEATED_GROUDON, TerraCave_End_EventScript_ShowGroudon
	setflag FLAG_HIDE_MAXIE_TERRA_CAVE
	end

TerraCave_End_EventScript_ShowGroudon::
	clearflag FLAG_HIDE_TERRA_CAVE_GROUDON
	setvar VAR_TEMP_1, 1
	return

TerraCave_End_EventScript_Groudon::
	lockall
	call TerraCave_End_EventScript_Maxie
MarineCave_End_EventScript_BeatMaxie::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_GROUDON, TerraCave_End_Movement_GroudonApproach
	waitmovement 0
	waitse
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_GROUDON
	setwildbattle SPECIES_GROUDON, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_TEMP_1, 0
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TerraCave_End_EventScript_DefeatedGroudon
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, TerraCave_End_EventScript_RanFromGroudon
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, TerraCave_End_EventScript_RanFromGroudon
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_GROUDON
	goto TerraCave_End_EventScript_MaxieLeaves
	releaseall
	end

TerraCave_End_EventScript_Maxie::
	addobject LOCALID_MAXIE
	applymovement LOCALID_MAXIE, TerraCave_End_Movement_MaxieApproach
	waitmovement 0
	setvar VAR_LAST_TALKED, LOCALID_MAXIE
	faceplayer
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	goto_if_set FLAG_BEAT_MAXIE_TERRA_CAVE, MarineCave_End_EventScript_MaxiePostBattle
	msgbox TerraCave_End_Text_MaxieIntro, MSGBOX_DEFAULT
	closemessage
	setvar VAR_LAST_TALKED, LOCALID_MAXIE
	trainerbattle_no_intro TRAINER_MAXIE_TERRA_CAVE, TerraCave_End_Text_MaxieDefeat
	special HealPlayerParty
MarineCave_End_EventScript_MaxiePostBattle::
	msgbox TerraCave_End_Text_MaxiePostBattle, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_BEAT_MAXIE_TERRA_CAVE
	return

TerraCave_End_EventScript_DefeatedGroudon::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_GROUDON
	goto TerraCave_End_EventScript_MaxieLeaves
	end

TerraCave_End_EventScript_RanFromGroudon::
	setvar VAR_0x8004, SPECIES_GROUDON
	goto Common_EventScript_LegendaryFlewAway
	msgbox TerraCave_End_Text_MaxieRanFromGroudon, MSGBOX_DEFAULT
	closemessage
	goto TerraCave_End_EventScript_MaxieLeaves_NoText
	end

TerraCave_End_EventScript_MaxieLeaves::
	msgbox TerraCave_End_Text_MaxieCaughtGroudon, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_MAXIE_LEFT_TERRA_CAVE
TerraCave_End_EventScript_MaxieLeaves_NoText::
	setflag FLAG_HIDE_MAXIE_TERRA_CAVE
	call TerraCave_End_EventScript_SetMtPyre
	applymovement LOCALID_MAXIE, TerraCave_End_Movement_MaxieLeaves
	waitmovement 0
	removeobject LOCALID_MAXIE
	releaseall
	end

TerraCave_End_EventScript_SetMtPyre::
	goto_if_unset FLAG_ARCHIE_LEFT_MARINE_CAVE, Common_EventScript_NopReturn
	goto_if_unset FLAG_MAXIE_LEFT_TERRA_CAVE, Common_EventScript_NopReturn
	setvar VAR_MT_PYRE_STATE, 2
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	return

TerraCave_End_Movement_GroudonApproach:
	init_affine_anim
	walk_down_start_affine
	delay_16
	delay_16
	walk_down_affine
	delay_16
	delay_16
	walk_down_affine
	step_end

TerraCave_End_Movement_MaxieApproach:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

TerraCave_End_Movement_MaxieLeaves:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

TerraCave_End_Text_MaxieIntro:
	.string "MARC: Nach allem, was geschehen ist,\n"
	.string "wagst du es, dich GROUDON zu nähern?\p"
	.string "Das ist MEINE Verantwortung, nicht\n"
	.string "deine!\p"
	.string "Ich war es, der seine Kraft entfesselt\n"
	.string "hat, und nur ich kann es aufhalten.\p"
	.string "Wenn du anderer Meinung bist…\n"
	.string "dann zeig mir deine Stärke!$"

TerraCave_End_Text_MaxieDefeat:
	.string "MARC: Das glaube ich nicht…$"

TerraCave_End_Text_MaxiePostBattle:
	.string "MARC: GROUDON in deinen Händen…\n"
	.string "Ich hätte nie gedacht, dass ich diesen\l"
	.string "Tag erleben würde.\p"
	.string "Es ist meine Pflicht, seine Kraft zu\n"
	.string "beherrschen, aber…\p"
	.string "Wenn du glaubst, damit umgehen zu\n"
	.string "können, dann soll es so sein.\p"
	.string "Ich werde hier sein. Und zusehen.$"

TerraCave_End_Text_MaxieCaughtGroudon:
	.string "MARC: Wie konnte das passieren?\n"
	.string "Nach allem, was war…\p"
	.string "Die ganze Zeit habe ich geglaubt, die\n"
	.string "Erweiterung des Landes würde die Welt\l"
	.string "heilen, die Hungernden speisen und\l"
	.string "neue Möglichkeiten schaffen.\p"
	.string "Vielleicht war ich zu vertieft in meine\n"
	.string "Berechnungen, zu sehr auf große Pläne\l"
	.string "fixiert, um die leisen Wahrheiten zu\l"
	.string "bemerken.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Welche Ironie…\p"
	.string "ADRIANs Ideale unterscheiden sich gar\n"
	.string "nicht so sehr von meinen.\p"
	.string "Wir beide strebten nach einer besseren\n"
	.string "Welt, doch in meinem Ehrgeiz, das Land\l"
	.string "umzuformen, habe ich vielleicht das\l"
	.string "Gleichgewicht übersehen, das uns\l"
	.string "erhält.\p"
	.string "Die Natur ist keine Formel, die es zu\n"
	.string "lösen gilt, sondern ein empfindliches\l"
	.string "System, das Respekt verdient.\p"
	.string "Selbst aus den kleinsten Samen können\n"
	.string "mächtige Wälder wachsen, wenn man sie\l"
	.string "richtig pflegt.\p"
	.string "Vielleicht führen kleine, bedachte\n"
	.string "Taten zu dem Wandel, den wir suchen…\p"
	.string "Ich werde meine Vision nicht aufgeben,\n"
	.string "aber vielleicht gibt es einen besseren\l"
	.string "Weg…\p"
	.string "Einen, der eine Katastrophe vermeidet.$"

TerraCave_End_Text_MaxieRanFromGroudon:
    .string "MARC: GROUDON ist entkommen?\n"
    .string "Ich habe befürchtet, dass das uns\l"
    .string "beide überfordern könnte.\p"
    .string "Nur ich verstehe die Tiefe seiner\n"
    .string "Bestimmung, seinen Platz bei der\l"
    .string "Wiederherstellung des Gleichgewichts.\p"
    .string "Das beweist es… GROUDON ist meine\n"
    .string "Verantwortung, und ich werde dafür\l"
    .string "sorgen, dass von nun an richtig mit\l"
    .string "ihm umgegangen wird.$"

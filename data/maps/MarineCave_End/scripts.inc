.set LOCALID_KYOGRE, 1
.set LOCALID_ARCHIE, 2

MarineCave_End_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MarineCave_End_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MarineCave_End_OnTransition
	.byte 0

MarineCave_End_OnResume:
	setflag FLAG_HIDE_ARCHIE_MARINE_CAVE
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MarineCave_End_EventScript_TryRemoveKyogre
	end

MarineCave_End_EventScript_TryRemoveKyogre::
	clearflag FLAG_HIDE_ARCHIE_MARINE_CAVE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_KYOGRE
	return

MarineCave_End_OnTransition:
	call_if_unset FLAG_DEFEATED_KYOGRE, MarineCave_End_EventScript_ShowKyogre
	setflag FLAG_HIDE_ARCHIE_MARINE_CAVE
	end

MarineCave_End_EventScript_ShowKyogre::
	clearflag FLAG_HIDE_MARINE_CAVE_KYOGRE
	setvar VAR_TEMP_1, 1
	return

MarineCave_End_EventScript_Kyogre::
	lockall
	call MarineCave_End_EventScript_Archie
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_KYOGRE, MarineCave_End_Movement_KyogreApproach
	waitmovement 0
	waitse
	playmoncry SPECIES_KYOGRE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_KYOGRE
	setwildbattle SPECIES_KYOGRE, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_TEMP_1, 0
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MarineCave_End_EventScript_DefeatedKyogre
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MarineCave_End_EventScript_RanFromKyogre
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MarineCave_End_EventScript_RanFromKyogre
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_KYOGRE
	goto MarineCave_End_EventScript_ArchieLeaves
	releaseall
	end

MarineCave_End_EventScript_Archie::
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, MarineCave_End_Movement_ArchieApproach
	waitmovement 0
	setvar VAR_LAST_TALKED, LOCALID_ARCHIE
	faceplayer
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	goto_if_set FLAG_BEAT_ARCHIE_MARINE_CAVE, MarineCave_End_EventScript_ArchiePostBattle
	msgbox MarineCave_End_Text_ArchieIntro, MSGBOX_DEFAULT
	closemessage
	setvar VAR_LAST_TALKED, LOCALID_ARCHIE
	trainerbattle_no_intro TRAINER_ARCHIE_MARINE_CAVE, MarineCave_End_Text_ArchieDefeat
	special HealPlayerParty
MarineCave_End_EventScript_ArchiePostBattle::
	msgbox MarineCave_End_Text_ArchiePostBattle, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_BEAT_ARCHIE_MARINE_CAVE
	return

MarineCave_End_EventScript_DefeatedKyogre::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	setvar VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	setflag FLAG_DEFEATED_KYOGRE
	goto MarineCave_End_EventScript_ArchieLeaves
	end

MarineCave_End_EventScript_RanFromKyogre::
	setvar VAR_0x8004, SPECIES_KYOGRE
	goto Common_EventScript_LegendaryFlewAway
	msgbox MarineCave_End_Text_ArchieRanFromKyogre, MSGBOX_DEFAULT
	closemessage
	goto MarineCave_End_EventScript_ArchieLeaves_NoText
	end

MarineCave_End_EventScript_ArchieLeaves::
	msgbox MarineCave_End_Text_ArchieCaughtKyogre, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ARCHIE_LEFT_MARINE_CAVE
MarineCave_End_EventScript_ArchieLeaves_NoText::
	setflag FLAG_HIDE_ARCHIE_MARINE_CAVE
	call MarineCave_End_EventScript_SetMtPyre
	applymovement LOCALID_ARCHIE, MarineCave_End_Movement_ArchieLeaves
	waitmovement 0
	removeobject LOCALID_ARCHIE
	releaseall
	end

MarineCave_End_EventScript_SetMtPyre::
	goto_if_unset FLAG_ARCHIE_LEFT_MARINE_CAVE, Common_EventScript_NopReturn
	goto_if_unset FLAG_MAXIE_LEFT_TERRA_CAVE, Common_EventScript_NopReturn
	setvar VAR_MT_PYRE_STATE, 2
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	return

MarineCave_End_Movement_KyogreApproach:
	init_affine_anim
	walk_down_start_affine
	delay_16
	delay_16
	walk_down_affine
	delay_16
	delay_16
	walk_down_affine
	step_end

MarineCave_End_Movement_ArchieApproach:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

MarineCave_End_Movement_ArchieLeaves:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MarineCave_End_Text_ArchieIntro:
	.string "ADRIAN: Du bist also wegen KYOGRE hier?\n"
	.string "Du verstehst das nicht…\l"
	.string "Diese Bürde muss ich allein tragen!\p"
	.string "Ich war es, der es geweckt hat.\n"
	.string "Nur ich kann es unter Kontrolle halten.\p"
	.string "Ich lasse mich von dir nicht aufhalten.\p"
	.string "Aber wenn du glaubst, du könntest\n"
	.string "damit fertigwerden…\p"
	.string "Dann beweise es mir im Kampf!$"

MarineCave_End_Text_ArchieDefeat:
	.string "ADRIAN: Das kann ich nicht glauben…\n"
	.string "Aber es ist noch nicht vorbei. KYOGRE\l"
	.string "wird sich erheben, und du wirst die\l"
	.string "Wahrheit sehen.$"

MarineCave_End_Text_ArchiePostBattle:
	.string "ADRIAN: So weit ist es also gekommen.\n"
	.string "Ich habe Fehler gemacht, aber jetzt\l"
	.string "kann ich nicht mehr umkehren.\p"
	.string "KYOGREs Zorn liegt noch immer in\n"
	.string "meiner Verantwortung…\p"
	.string "Aber wenn du es versuchen willst,\n"
	.string "werde ich dich nicht aufhalten…\p"
	.string "Glaub nur nicht, dass es leicht wird.$"

MarineCave_End_Text_ArchieCaughtKyogre:
	.string "ADRIAN: Du… hast KYOGRE tatsächlich\n"
	.string "besänftigt? Ich hätte nie gedacht,\l"
	.string "dass das jemand schaffen könnte…\p"
	.string "So weit ist es also gekommen.\p"
	.string "Ich wollte Leben retten, Wasser dorthin\n"
	.string "bringen, wo es gebraucht wird, und\l"
	.string "Wüsten erblühen lassen.\p"
	.string "Vielleicht habe ich mich zu sehr von\n"
	.string "meinen Gefühlen leiten lassen,\p"
	.string "zu schnell die Fluten gerufen, ohne die\n"
	.string "Wellen zu sehen, die sie schlagen.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Vielleicht hatte MARC nicht ganz\n"
	.string "Unrecht.\p"
	.string "Ohne Verständnis für das empfindliche\n"
	.string "Gleichgewicht der Dinge voranzustürmen,\l"
	.string "war töricht.\p"
	.string "Es geht nicht darum, Länder zu fluten\n"
	.string "oder Meere trockenzulegen, sondern die\l"
	.string "Natur ihr Gleichgewicht finden zu\l"
	.string "lassen.\p"
	.string "Ein einziger Tropfen kann Wellen\n"
	.string "schlagen… Vielleicht beginnt dort\l"
	.string "wahrer Wandel.\p"
	.string "Kleine Taten bedeuten vielleicht mehr\n"
	.string "als große Gesten.\p"
	.string "Ich kann meinen Traum nicht aufgeben,\n"
	.string "aber vielleicht gibt es einen besseren\l"
	.string "Weg, ihn zu verwirklichen…\p"
	.string "Einen, der die Welt achtet, zu der wir\n"
	.string "gehören.$"

MarineCave_End_Text_ArchieRanFromKyogre:
	.string "ADRIAN: KYOGRE ist also entkommen?\n"
	.string "Ich wusste, dass niemand es bändigen\l"
	.string "kann!\p"
	.string "Nur ich verstehe seine Kraft,\n"
	.string "seinen Zweck… Die Welt wird es bald\l"
	.string "sehen.\p"
	.string "Du hast es gerade bewiesen.\n"
	.string "KYOGRE liegt in meiner Verantwortung,\l"
	.string "und von nun an kümmere ich mich\l"
	.string "richtig darum.$"

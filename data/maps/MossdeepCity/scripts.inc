.set LOCALID_GIRL, 8
.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16
.set LOCALID_JIRACHI, 18
.set LOCALID_BIRCH, 19

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MossdeepCity_OnResume
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MossdeepCity_EventScript_TryRemoveJirachi
	end

MossdeepCity_EventScript_TryRemoveJirachi::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_JIRACHI
	return

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	goto_if_set FLAG_BATTLED_JIRACHI, MossdeepCity_Text_SpecialSpaceCenterRockPostJirachi
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end
MossdeepCity_Text_SpecialSpaceCenterRockPostJirachi::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRockAfterEvent, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_SceneWithBirch_EventScript_BirchNoticesYou1::
	lockall
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_BirchWalksToPlayerL
	waitmovement 0
	msgbox MossdeepCity_Text_BirchYouMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_BirchWalksToRockL
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWalksToRockL
	waitmovement 0
	goto MossdeepCity_SceneWithBirch_EventScript_Birch

MossdeepCity_SceneWithBirch_EventScript_BirchNoticesYou2::
	lockall
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_BirchWalksToPlayerR
	waitmovement 0
	msgbox MossdeepCity_Text_BirchYouMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_BirchWalksToRockR
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWalksToRockR
	waitmovement 0

MossdeepCity_SceneWithBirch_EventScript_Birch::
	setvar VAR_MOSSDEEP_CITY_STATE, 3
	msgbox MossdeepCity_SceneWithBirch_Text_RockExplanation, MSGBOX_DEFAULT
	msgbox MossdeepCity_SceneWithBirch_Text_WhoKnowsWhatMightHappen, MSGBOX_DEFAULT
	msgbox MossdeepCity_SceneWithBirch_Text_MakeAWish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_SceneWithBirch_EventScript_JustTryIt
	goto_if_eq VAR_RESULT, YES, MossdeepCity_SceneWithBirch_Text_JirachiAppears
	closemessage
	releaseall
	end

MossdeepCity_SceneWithBirch_EventScript_JustTryIt::
	msgbox MossdeepCity_SceneWithBirch_Text_JustTryIt, MSGBOX_DEFAULT
	msgbox MossdeepCity_SceneWithBirch_Text_MakeAWish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_SceneWithBirch_EventScript_JustTryIt
	goto_if_eq VAR_RESULT, YES, MossdeepCity_SceneWithBirch_Text_JirachiAppears
	end

MossdeepCity_SceneWithBirch_Text_JirachiAppears::
	closemessage
	fadescreen FADE_TO_WHITE
	addobject LOCALID_JIRACHI
	special Script_FadeOutMapMusic
	fadescreen FADE_FROM_WHITE
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiAppears
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_FaceUp
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox MossdeepCity_Text_Jirachi, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiThirdEye
	playmoncry SPECIES_JIRACHI, CRY_MODE_ECHO_START
	waitmoncry
	playmoncry SPECIES_JIRACHI, CRY_MODE_ECHO_END
	waitmovement 0
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 3   @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 5   @ shake delay
	special ShakeCamera
	delay 20
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_Spinning1
	applymovement LOCALID_GIRL, MossdeepCity_Movement_Spinning2
	delay 80
	fadescreen FADE_TO_WHITE
	delay 120
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJump
	waitmovement 0
	fadescreen FADE_FROM_WHITE
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJump
	waitmovement 0
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	special Overworld_PlaySpecialMapMusic
	msgbox MossdeepCity_Text_Jirachi, MSGBOX_DEFAULT
	applymovement LOCALID_BIRCH, Common_Movement_FaceUp
	msgbox MossdeepCity_Text_BirchSeesJirachi, MSGBOX_DEFAULT
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJumpsAroundBirch1
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_FaceRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox MossdeepCity_Text_BirchWhatChanges, MSGBOX_DEFAULT
	applymovement LOCALID_BIRCH, Common_Movement_FaceLeft
	waitmovement 0
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJumpsAroundBirch2
	msgbox MossdeepCity_Text_BirchTouchedTheRegion, MSGBOX_DEFAULT
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJumpsAroundGirl
	msgbox MossdeepCity_Text_GirlSeesJirachi, MSGBOX_DEFAULT
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiJumpsBackToCenter
	msgbox MossdeepCity_Text_BirchNewDiscoveries, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_BIRCH, Common_Movement_FaceUp
	applymovement LOCALID_JIRACHI, MossdeepCity_Movement_JirachiWantsToFight
	waitmovement 0
	msgbox MossdeepCity_Text_BirchTestBond, MSGBOX_DEFAULT
	applymovement LOCALID_BIRCH, Common_Movement_FaceLeft
	msgbox MossdeepCity_Text_BirchAreYouReady, MSGBOX_DEFAULT
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_JIRACHI
	seteventmon SPECIES_JIRACHI, 30
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MossdeepCity_EventScript_JirachiRunsAway
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MossdeepCity_EventScript_JirachiRunsAway
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MossdeepCity_EventScript_JirachiRunsAway
	setflag FLAG_BATTLED_JIRACHI
	goto MossdeepCity_EventScript_EndJirachiEvent
	end

MossdeepCity_EventScript_JirachiRunsAway::
	setflag FLAG_BATTLED_JIRACHI
	setvar VAR_0x8004, SPECIES_JIRACHI
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	msgbox MossdeepCity_Text_BirchJirachiFled, MSGBOX_DEFAULT
	goto MossdeepCity_EventScript_EndJirachiEvent
	end

MossdeepCity_EventScript_EndJirachiEvent:
	msgbox MossdeepCity_Text_BirchLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCH, MossdeepCity_Movement_BirchLeaves
	waitmovement 0
	setflag FLAG_HIDE_MOSSDEEP_CITY_BIRCH
	removeobject LOCALID_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_GAME_CORNER_PORYGON_PRIZE
	clearflag FLAG_HIDE_HELIX_FOSSIL
	clearflag FLAG_HIDE_DOME_FOSSIL
	setvar VAR_MOSSDEEP_CITY_STATE, 3
	setvar VAR_ROUTE101_WILD_SET, 1
	setvar VAR_ROUTE102_WILD_SET, 1
	setvar VAR_ROUTE103_WILD_SET, 1
	setvar VAR_ROUTE104_WILD_SET, 1
	setvar VAR_ROUTE110_WILD_SET, 1
	setvar VAR_ROUTE111_WILD_SET, 1
	setvar VAR_ROUTE112_WILD_SET, 1
	setvar VAR_ROUTE114_WILD_SET, 1
	setvar VAR_ROUTE116_WILD_SET, 1
	setvar VAR_ROUTE117_WILD_SET, 1
	setvar VAR_PETALBURG_WOODS_WILD_SET, 1
	setvar VAR_RUSTURF_TUNNEL_WILD_SET, 1
	setvar VAR_GRANITE_CAVE_1F_WILD_SET, 1
	setvar VAR_GRANITE_CAVE_B1F_WILD_SET, 1
	setvar VAR_VICTORY_ROAD_1F_WILD_SET, 1
	setvar VAR_FIERY_PATH_WILD_SET, 1
	setvar VAR_JAGGED_PASS_WILD_SET, 1
	setvar VAR_ROUTE107_WILD_SET, 1
	setvar VAR_ROUTE115_WILD_SET, 1
	setvar VAR_NEW_MAUVILLE_INSIDE_WILD_SET, 1
	setvar VAR_ROUTE119_WILD_SET, 1
	setvar VAR_ROUTE120_WILD_SET, 1
	setvar VAR_ROUTE121_WILD_SET, 1
	setvar VAR_ROUTE122_WILD_SET, 1
	setvar VAR_ROUTE123_WILD_SET, 1
	setvar VAR_MT_PYRE_2F_WILD_SET, 1
	setvar VAR_MT_PYRE_3F_WILD_SET, 1
	setvar VAR_MT_PYRE_4F_WILD_SET, 1
	setvar VAR_MT_PYRE_5F_WILD_SET, 1
	setvar VAR_MT_PYRE_EXTERIOR_WILD_SET, 1
	setvar VAR_ROUTE131_WILD_SET, 1
	setvar VAR_ROUTE133_WILD_SET, 1
	setvar VAR_VICTORY_ROAD_B1F_WILD_SET, 1
	setvar VAR_VICTORY_ROAD_B2F_WILD_SET, 1
	setvar VAR_METEOR_FALLS_1F_1R_WILD_SET, 1
	setvar VAR_SLATEPORT_CITY_WILD_SET, 1
	setvar VAR_MOSSDEEP_CITY_WILD_SET, 1
	setvar VAR_PETALBURG_CITY_WILD_SET, 1
	setvar VAR_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_WILD_SET, 1
	setvar VAR_SOOTOPOLIS_CITY_WILD_SET, 1
	setvar VAR_ARTISAN_CAVE_B1F_WILD_SET, 1
	setvar VAR_SHOAL_CAVE_LOW_TIDE_INNER_ROOM_WILD_SET, 1
	releaseall
	end

MossdeepCity_Movement_BirchWalksToPlayerL:
	walk_down
	walk_down
	walk_down
	step_end

MossdeepCity_Movement_BirchWalksToPlayerR:
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

MossdeepCity_Movement_PlayerWalksToRockL:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

MossdeepCity_Movement_PlayerWalksToRockR:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

MossdeepCity_Movement_BirchWalksToRockL:
	walk_up
	walk_up
	walk_up
	walk_right
	face_left
	step_end

MossdeepCity_Movement_BirchWalksToRockR:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

MossdeepCity_Movement_Spinning1:
	face_down
	delay_16
	face_right
	delay_16
	face_down
	delay_16
	face_right
	delay_16
	face_down
	delay_16
	face_right
	delay_16
	face_left
	step_end

MossdeepCity_Movement_Spinning2:
	face_down
	delay_16
	face_left
	delay_16
	face_down
	delay_16
	face_left
	delay_16
	face_down
	delay_16
	face_left
	delay_16
	face_right
	step_end

MossdeepCity_Movement_JirachiAppears:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	jump_special_in_place_down
	delay_4
	levitate
	step_end

MossdeepCity_Movement_JirachiThirdEye:
	walk_in_place_faster_down
	walk_in_place_faster_down
	walk_in_place_faster_down
	walk_in_place_faster_up
	step_end

MossdeepCity_Movement_JirachiJump:
	jump_special_in_place_right_left
	jump_special_in_place_left_right
	jump_special_in_place_down
	step_end

MossdeepCity_Movement_JirachiJumpsAroundBirch1:
	walk_right
	walk_down
	jump_special_in_place_down_up
	jump_special_in_place_down_up
	walk_right
	walk_down
	face_left
	step_end

MossdeepCity_Movement_JirachiJumpsAroundBirch2:
	jump_special_in_place_left_right
	jump_special_in_place_left_right
	jump_special_down
	walk_left
	jump_special_in_place_up_down
	jump_special_in_place_up_down
	step_end

MossdeepCity_Movement_JirachiJumpsAroundGirl:
	walk_left
	walk_left
	walk_up
	jump_special_in_place_up_down
	jump_special_in_place_up_down
	walk_left
	walk_up
	jump_special_in_place_right_left
	jump_special_in_place_right_left
	step_end

MossdeepCity_Movement_JirachiJumpsBackToCenter:
	walk_up
	walk_right
	walk_right
	jump_special_in_place_Down_Up
	jump_special_in_place_Down_Up
	jump_special_in_place_down
	step_end

MossdeepCity_Movement_JirachiWantsToFight:
	jump_special_in_place_Down_Up
	jump_special_in_place_Down_Up
	jump_special_in_place_Down_Up
	jump_special_down
	step_end

MossdeepCity_Movement_BirchLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "Ich habe das von TROY bekommen, weiß\n"
	.string "aber nicht, was ich damit machen soll.\p"
	.string "Ich glaube, es heißt KING-STEIN.\n"
	.string "Möchtest du das haben?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "Warum willst du das haben?\n"
	.string "Du bist komisch.\p"
	.string "Du kannst es behalten, aber erzähle\n"
	.string "es nicht TROY.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "TROYs Haus befindet sich gleich\n"
	.string "dort drüben.$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "Ach, du denkst das auch! Was soll man\n"
	.string "auch mit komischen Steinen anfangen?$"

MossdeepCity_Text_WailmerWatching:
	.string "In der Nähe von MOOSBACH CITY\n"
	.string "kann man wilde WAILMER sehen.\p"
	.string "Das nennt man, äh…\n"
	.string "Nennt man… äh… ähm…\p"
	.string "WAI…, WAI…, WAI…\p"
	.string "WAILMER Watching!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "Am RAUMFAHRTZENTRUM auf der Insel\n"
	.string "werden große Raketen gestartet.\p"
	.string "Dort ist vor kurzem ein Brief ange-\n"
	.string "kommen, der für Aufregung sorgte.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "Am RAUMFAHRTZENTRUM auf der Insel\n"
	.string "werden große Raketen gestartet.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Ich habe von einem Freund, einem\n"
	.string "MATROSEN, gehört, dass TEAM AQUA sich\p"
	.string "in SEEGRASULB CITY aufgehalten\n"
	.string "haben soll.\p"
	.string "Aber dann ist jemand gekommen und hat\n"
	.string "sie aufgemischt.\p"
	.string "Und in MOOSBACH CITY ist TEAM\n"
	.string "MAGMA.\p"
	.string "Wenn du wissen willst, was sie vorhaben,\n"
	.string "dann geh zum RAUMFAHRTZENTRUM.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Ich bin ein MATROSE, daher ist das Meer\n"
	.string "sehr wichtig für mich.\p"
	.string "Aber weißt du, was? Wenn ich nach einer\n"
	.string "langen Seefahrt wieder festen Boden\p"
	.string "unter den Füßen habe, bin ich jedes Mal\n"
	.string "erleichtert.$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "Wäre das nicht schön?\p"
	.string "Wenn die ganze Welt so mit Blumen und\n"
	.string "Pflanzen bewachsen wäre wie diese\l"
	.string "Insel?$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Alle Lebewesen brauchen das Meer, um\n"
	.string "leben zu können, auch wenn sie an Land\l"
	.string "leben.\p"
	.string "Am Ende ihrer Reise wird aus den\n"
	.string "Lebewesen Erde und sie kehren zurück\l"
	.string "zum Land.\p"
	.string "Und das Meer steht immer in Verbindung\n"
	.string "zum Land.\p"
	.string "Genau wie dieses Ufer hier.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Eine Reise auf einem Schiff ist toll.\p"
	.string "Aber das Meer auf einem POKéMON zu\n"
	.string "überqueren, das SURFER einsetzt…\p"
	.string "Das ist wirklich eine aufregende Sache.\n"
	.string "Meinst du nicht auch, Kindchen?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Dieser Felsen hat eine ganz besondere\n"
	.string "Bedeutung für das RAUMFAHRTZENTRUM.\p"
	.string "Sie haben ihn hier hingesetzt als\n"
	.string "Glücksbringer für den sicheren Flug der\l"
	.string "Raketen.\p"
	.string "Wenn du dir etwas wünschst, was machst\n"
	.string "du dann? Sternschnuppen beobachten?\p"
	.string "Ich benutze ein Wunschkärtchen.\n"
	.string "Genau das mache ich.$"

MossdeepCity_Text_SpecialSpaceCenterRockAfterEvent:
	.string "Hast du das gesehen?\n"
	.string "JIRACHI ist genau hier erschienen!\p"
	.string "Die Leute im RAUMFAHRTZENTRUM glaubten\n"
	.string "immer, dieser Felsen habe eine ganz\l"
	.string "besondere Bedeutung, und jetzt weiß\l"
	.string "ich, warum.\p"
	.string "Er bedeutet, dass unsere Raketen\n"
	.string "fliegen werden… Wir werden wirklich\l"
	.string "die Sterne erreichen!$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Ein weißer Felsen.$"

MossdeepCity_Text_BirchYouMadeIt:
	.string "PROF. BIRK: Ah, {PLAYER}{KUN}!\n"
	.string "Schön, dass du kommen konntest!$"

MossdeepCity_SceneWithBirch_Text_RockExplanation:
	.string "Das ist der Felsen, von dem ich\n"
	.string "erzählt habe.\p"
	.string "Dieser Felsen hat für die Menschen\n"
	.string "hier in MOOSBACH CITY eine ganz\l"
	.string "besondere Bedeutung.\p"
	.string "Er soll ein Symbol für ihren Wunsch\n"
	.string "sein, dass ihre Raketen durch die\l"
	.string "Sterne fliegen. Recht poetisch, nicht?\p"
	.string "Das hat mich nachdenklich gemacht…\n"
	.string "Was, wenn dieser Felsen mehr ist als\l"
	.string "nur ein Symbol?\p"
	.string "Ich habe ein wenig nachgeforscht. Alte\n"
	.string "Legenden erzählen von einem seltenen\l"
	.string "POKéMON, das Wünsche erfüllen kann.\p"
	.string "Manche glauben, es schlafe in einem\n"
	.string "Stern und erwache nur alle tausend\l"
	.string "Jahre.\p"
	.string "Ich glaube, dieser Felsen könnte mit\n"
	.string "diesem POKéMON zusammenhängen. Aber\l"
	.string "was wirklich in ihm steckt… Das werden\l"
	.string "wir vielleicht nie erfahren.$"

MossdeepCity_SceneWithBirch_Text_WhoKnowsWhatMightHappen:
	.string "Versuch doch, dir an diesem Felsen\n"
	.string "etwas zu wünschen. Wer weiß, was dann\l"
	.string "passiert?$"

MossdeepCity_SceneWithBirch_Text_MakeAWish:
	.string "Etwas wünschen?$"

MossdeepCity_SceneWithBirch_Text_JustTryIt:
	.string "Ach komm, {PLAYER}{KUN}! Ein Versuch kann\n"
	.string "doch nicht schaden!\p"
	.string "Selbst die größten Entdeckungen\n"
	.string "beginnen mit einem kleinen Schritt.\l"
	.string "Versuch es einfach!$"

MossdeepCity_Text_Jirachi:
	.string "JIRACHI!$"

MossdeepCity_Text_BirchSeesJirachi:
	.string "PROF. BIRK: Unglaublich… Kann das sein…?\n"
	.string "JIRACHI… Hast du wirklich unsere\l"
	.string "Wünsche gehört?$"

MossdeepCity_Text_BirchWhatChanges:
	.string "Das muss das POKéMON aus den Legenden\n"
	.string "um den Felsen sein. Aber mehr noch…\l"
	.string "Etwas in der Luft ist anders.$"

MossdeepCity_Text_BirchTouchedTheRegion:
	.string "Kann es sein… dass dein Wunsch die\n"
	.string "ganze Region berührt hat? Ich frage\l"
	.string "mich, was sich jetzt alles ändert…$"

MossdeepCity_Text_GirlSeesJirachi:
	.string "MÄDCHEN: Heißt das… wir fliegen wirklich\n"
	.string "durch die Sterne?\p"
	.string "Dass unsere Träume tatsächlich wahr\n"
	.string "werden könnten…$"

MossdeepCity_Text_BirchNewDiscoveries:
	.string "PROF. BIRK: Dein Wunsch, dich mit\n"
	.string "POKéMON aller Art anzufreunden… Es\l"
	.string "scheint, als hätte JIRACHI ihn erfüllt,\l"
	.string "{PLAYER}{KUN}.\p"
	.string "Wer weiß, welche neuen Entdeckungen\n"
	.string "jetzt auf dich warten?$"

MossdeepCity_Text_BirchTestBond:
	.string "Es sieht so aus, als wolle JIRACHI\n"
	.string "euer Band prüfen.$"

MossdeepCity_Text_BirchAreYouReady:
	.string "Bist du bereit? Das könnte deine\n"
	.string "einzige Chance sein!$"

MossdeepCity_Text_BirchJirachiFled:
	.string "PROF. BIRK: Oh… JIRACHI scheint\n"
	.string "verschwunden zu sein.\p"
	.string "Aber lass dich nicht entmutigen,\n"
	.string "{PLAYER}{KUN}. Schon ein so seltenes\l"
	.string "POKéMON zu sehen, ist ein unglaubliches\l"
	.string "Erlebnis.$"

MossdeepCity_Text_BirchLeaves:
	.string "PROF. BIRK: Was für ein außergewöhn-\n"
	.string "liches Ereignis, {PLAYER}{KUN}.\p"
	.string "Dass wir gerade das legendäre JIRACHI\n"
	.string "gesehen haben…\p"
	.string "Die Legenden, die Wünsche… Das alles\n"
	.string "fühlt sich jetzt echter an, nicht wahr?\p"
	.string "Vor allem aber erinnert es uns daran,\n"
	.string "wie weit und geheimnisvoll unser\l"
	.string "Universum ist.\p"
	.string "Nun, ich muss zurück an meine\n"
	.string "Forschung. Es gibt viel festzuhalten\l"
	.string "und so viele neue Fragen zu ergründen.\p"
	.string "Danke für alles, {PLAYER}{KUN}.\n"
	.string "Unsere Wege kreuzen sich sicher bald\l"
	.string "wieder.$"

MossdeepCity_Text_GymSign:
	.string "POKéMON ARENA von MOOSBACH CITY \n"
	.string "LEITER: SVENJA & BEN\p"
	.string "“Die mystische Kombination!”$"

MossdeepCity_Text_CitySign:
	.string "MOOSBACH CITY\n"
	.string "“Unser Motto: Liebe POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "MOOSBACH CITY RAUMFAHRTZENTRUM\n"
	.string "“Der letzte Ort vor dem All.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: Geht es dir gut, {PLAYER}{KUN}?\n"
	.string "Mir geht es fantastisch!\p"
	.string "Ich habe mir sagen lassen, dass die\n"
	.string "ARENALEITER von MOOSBACH sehr stark\l"
	.string "sein sollen.\p"
	.string "Davon musste ich mich einfach selbst\n"
	.string "überzeugen.\p"
	.string "Aber in dieser Stadt geht irgendetwas\n"
	.string "Merkwürdiges vor.\p"
	.string "Die Leute reden über einen Brief mit\n"
	.string "einer Warnung und dem\l"
	.string "RAUMFAHRTZENTRUM…\p"
	.string "Aber ich glaube nicht, dass mich das\n"
	.string "etwas angeht.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Ahh… Ein großartiges Gefühl, wenn\n"
	.string "die Wellen über meine Füße spülen…\p"
	.string "Apropos Wellen. Kennst du die Stadt\n"
	.string "XENEROVILLE?\p"
	.string "Ich glaube, die ARENA dort ist\n"
	.string "ziemlich stark.\p"
	.string "Man sagt, ihr LEITER sei von einem\n"
	.string "TRAINER namens JUAN ausgebildet\l"
	.string "worden.$"


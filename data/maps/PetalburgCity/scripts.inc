.set LOCALID_WALLY, 2
.set LOCALID_BOY, 3
.set LOCALID_WALLYS_DAD, 5
.set LOCALID_GYM_BOY, 8
.set LOCALID_SCOTT, 9
.set LOCALID_MAY, 10
.set LOCALID_BRENDAN, 11

PetalburgCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_OnFrame
	.byte 0

PetalburgCity_OnTransition:
	setflag FLAG_VISITED_PETALBURG_CITY
	call_if_eq VAR_PETALBURG_CITY_STATE, 0, PetalburgCity_EventScript_MoveGymBoyToWestEntrance
	call_if_eq VAR_PETALBURG_CITY_STATE, 2, PetalburgCity_EventScript_DisableMapNameAndMusic
	call_if_eq VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_EventScript_DisableMapNameAndMusic
	call_if_eq VAR_PETALBURG_GYM_STATE, 8, PetalburgCity_EventScript_SetGymDoorsUnlocked
	end

PetalburgCity_PreNormanFight::
	goto_if_set FLAG_BEAT_WALLY_PETALBURG, PetalburgCity_End
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PetalburgCity_MayAppears
	call_if_eq VAR_RESULT, FEMALE, PetalburgCity_BrendanAppears
PetalburgCity_MayAppears::
	setobjectxyperm LOCALID_MAY, 16, 16
	addobject LOCALID_MAY
	applymovement LOCALID_MAY, PetalburgCity_Movement_RivalWalksOnscreen
	waitmovement 0
	goto PetalburgCity_RivalAppears
PetalburgCity_BrendanAppears::
	setobjectxyperm LOCALID_BRENDAN, 16, 16
	addobject LOCALID_BRENDAN
	applymovement LOCALID_BRENDAN, PetalburgCity_Movement_RivalWalksOnscreen
	waitmovement 0
PetalburgCity_RivalAppears::
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox PetalburgCity_Text_Hello, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWalksToRival
	waitmovement 0
PetalburgCity_OnWarp::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_FaceRight
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PetalburgCity_MayLeaves
	call_if_eq VAR_RESULT, FEMALE, PetalburgCity_BrendanLeaves
PetalburgCity_MayLeaves::
	applymovement LOCALID_MAY, PetalburgCity_Movement_FaceLeft
	msgbox PetalburgCity_Text_RivalWeMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAY, PetalburgCity_Movement_RivalLeaves
	waitmovement 0
	removeobject LOCALID_MAY
	setflag FLAG_HIDE_PETALBURG_CITY_MAY
	goto PetalburgCity_WallyFight
PetalburgCity_BrendanLeaves::
	applymovement LOCALID_BRENDAN, PetalburgCity_Movement_FaceLeft
	msgbox PetalburgCity_Text_RivalWeMadeIt, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BRENDAN, PetalburgCity_Movement_RivalLeaves
	waitmovement 0
	removeobject LOCALID_BRENDAN
	setflag FLAG_HIDE_PETALBURG_CITY_BRENDAN

PetalburgCity_WallyFight::
	msgbox PetalburgCity_Text_Hello, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_FaceLeft
	waitmovement 0
	setobjectxyperm LOCALID_WALLY, 7, 12
	addobject LOCALID_WALLY
	applymovement LOCALID_WALLY, PetalburgCity_Movement_WallyWalksToPlayer
	waitmovement 0
	msgbox PetalburgCity_Text_WallyWantsToBattle, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_WALLY_PETALBURG, PetalburgCity_Text_WallyDefeat
	msgbox PetalburgCity_Text_WallyPostBattle, MSGBOX_DEFAULT
	closemessage
	setvar VAR_RESULT, FALSE
	applymovement LOCALID_WALLY, PetalburgCity_Movement_WallyLeaves
	waitmovement 0
	removeobject LOCALID_WALLY
	setflag FLAG_BEAT_WALLY_PETALBURG
	setflag FLAG_HIDE_LAVARIDGE_POKEMON_CENTER_BRENDAN
	setflag FLAG_HIDE_LAVARIDGE_POKEMON_CENTER_MAY
PetalburgCity_End::
	setvar VAR_PETALBURG_CITY_STATE, 3
	releaseall
	end

PetalburgCity_RecievedSurfWallyFastTravel::
	setvar VAR_PETALBURG_CITY_STATE, 5
	setobjectxyperm LOCALID_WALLY, 7, 12
	addobject LOCALID_WALLY
	applymovement LOCALID_WALLY, PetalburgCity_Movement_WallyWalksToPlayer2
	waitmovement 0
	msgbox PetalburgCity_Text_WallyAfterSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_WarpToMauville
	goto_if_eq VAR_RESULT, NO, PetalburgCity_WallyLeaves
PetalburgCity_WarpToMauville::
	msgbox PetalburgCity_Text_WallyGoToMauville, MSGBOX_DEFAULT
	closemessage
	setvar VAR_MAUVILLE_CITY_STATE, 1
	clearflag FLAG_HIDE_MAUVILLE_CITY_WALLY2
	dofieldeffect FLDEFF_NPCFLY_OUT
	warp MAP_MAUVILLE_CITY, 22, 8
	waitstate
	goto PetalburgCity_EndWallyScene2
PetalburgCity_WallyLeaves::
	msgbox PetalburgCity_Text_WallyLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLY, PetalburgCity_Movement_RivalLeaves
	waitmovement 0
PetalburgCity_EndWallyScene2::
	removeobject LOCALID_WALLY 
	releaseall
	end

PetalburgCity_Movement_RivalWalksOnscreen:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalksToRival:
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_RivalLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Movement_WallyWalksToPlayer:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

PetalburgCity_Movement_WallyWalksToPlayer2:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgCity_Movement_WallyLeaves:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_FaceLeft:
	face_left
	step_end

PetalburgCity_Movement_FaceRight:
	face_right
	step_end

PetalburgCity_Text_Hello:
	.string "Hey, {PLAYER}{KUN}!$"

PetalburgCity_Text_RivalWeMadeIt:
	.string "Na, wir haben es geschafft!\n"
	.string "Die ARENA von BLÜTENBURG CITY!\p"
	.string "Es kommt mir vor, als hätten wir unsere\n"
	.string "Reise erst gestern begonnen…\p"
	.string "Aber sieh nur, wie weit wir gekommen\n"
	.string "sind, {PLAYER}{KUN}!\p"
	.string "Ich glaube, du bist bereit für diese\n"
	.string "Herausforderung. Viel Glück gegen\l"
	.string "deinen VATER!\p"
	.string "Ich schaue erst noch zu Hause vorbei,\n"
	.string "bevor ich selbst die ARENA\l"
	.string "herausfordere.\p"
	.string "Bis später, {PLAYER}{KUN}!\n"
	.string "Geben wir beide unser Bestes!$"

PetalburgCity_Text_WallyWantsToBattle:
	.string "Ich hätte nicht erwartet, dich hier zu\n"
	.string "sehen…\p"
	.string "Ich war auf dem Rückweg nach\n"
	.string "MALVENFROH CITY, aber dann habe ich\l"
	.string "gemerkt, dass ich meine Medizin zu\l"
	.string "Hause vergessen habe.\p"
	.string "{PLAYER}{KUN}, ich habe hart trainiert\n"
	.string "und glaube, ich bin bereit für einen\l"
	.string "weiteren Kampf!\p"
	.string "Kämpfst du gegen mich, bevor du die\n"
	.string "ARENA von BLÜTENBURG CITY\l"
	.string "herausforderst?\p"
	.string "Ich will dir zeigen, wie stark ich\n"
	.string "geworden bin!$"

PetalburgCity_Text_WallyAccept:
	.string "Toll! Danke, {PLAYER}{KUN}! Ich bin\n"
	.string "gespannt, wie stark wir beide geworden\l"
	.string "sind!\p"
	.string "Jetzt komme ich!$"

PetalburgCity_Text_WallyWaitInHouse:
	.string "Oh, das ist schon in Ordnung!\p"
	.string "Viel Glück in der ARENA, {PLAYER}{KUN}!\n"
	.string "Ich weiß, dass du es schaffen kannst!$"

PetalburgCity_Text_WallyDefeat:
    .string "Ich muss noch viel lernen…$"

PetalburgCity_Text_WallyPostBattle:
    .string "Du bist immer noch großartig,\n"
    .string "{PLAYER}{KUN}! Ich werde weiter stärker\l"
    .string "werden. Vielleicht klappt es nächstes\l"
    .string "Mal.\p"
    .string "Viel Glück bei deinem Kampf in der\n"
    .string "ARENA!$"

PetalburgCity_Text_WallyAfterSurf:
    .string "Hallo, {PLAYER}{KUN}! Das hast du in der\n"
    .string "ARENA toll gemacht!\p"
    .string "Ich wollte gerade zurück nach\n"
    .string "MALVENFROH CITY.\p"
    .string "Möchtest du mitkommen? Es wäre schön,\n"
    .string "zusammen zu reisen!$"

PetalburgCity_Text_WallyGoToMauville:
	.string "Super! Gehen wir!$"

PetalburgCity_Text_WallyLeaves:
	.string "Schon in Ordnung!\n"
	.string "Pass auf dich auf, {PLAYER}{KUN}!\p"
	.string "Bestimmt warten noch viele weitere\n"
	.string "Abenteuer auf dich!$"

PetalburgCity_EventScript_MoveGymBoyToWestEntrance::
	setobjectxyperm LOCALID_GYM_BOY, 5, 11
	return

PetalburgCity_EventScript_DisableMapNameAndMusic::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_FOLLOW_ME
	return

PetalburgCity_EventScript_SetGymDoorsUnlocked::
	setvar VAR_PETALBURG_GYM_STATE, 7
	return

PetalburgCity_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 2, PetalburgCity_EventScript_WallyTutorial
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_EventScript_WalkToWallyHouse
	map_script_2 VAR_PETALBURG_CITY_STATE, 6, PetalburgCity_OnWarp
	map_script_2 VAR_PETALBURG_CITY_STATE, 7, PetalburgCity_RecievedSurfWallyFastTravel
	.2byte 0

PetalburgCity_EventScript_WallyTutorial::
	lockall
	special SavePlayerParty
	special LoadWallyZigzagoon
	applymovement LOCALID_WALLY, PetalburgCity_Movement_WallyTutorialWally
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_WallyTutorialPlayer
	waitmovement 0
	msgbox Route102_Text_WatchMeCatchPokemon, MSGBOX_DEFAULT
	special StartWallyTutorialBattle
	waitstate
	msgbox Route102_Text_WallyIDidIt, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterLeft, MAP_PETALBURG_CITY
	waitmovement LOCALID_WALLY, MAP_PETALBURG_CITY
	msgbox Route102_Text_LetsGoBack, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_PETALBURG_CITY_STATE, 3
	fadedefaultbgm
	clearflag FLAG_DONT_TRANSITION_MUSIC
	special LoadPlayerParty
	setvar VAR_PETALBURG_GYM_STATE, 1
	warp MAP_PETALBURG_CITY_GYM, 4, 108
	waitstate
	releaseall
	end

PetalburgCity_EventScript_WalkToWallyHouse::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Movement_WalkToWallyHouseWallysDad
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_WalkToWallyHousePlayer
	waitmovement 0
	setvar VAR_0x8004, 7
	setvar VAR_0x8005, 5
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_WALLYS_DAD, PetalburgCity_Movement_WalkInsideHouseWallysDad
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_WalkInsideHousePlayer
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_DAD
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_PETALBURG_CITY
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	fadedefaultbgm
	clearflag FLAG_DONT_TRANSITION_MUSIC
	warp MAP_PETALBURG_CITY_WALLYS_HOUSE, 2, 4
	waitstate
	releaseall
	end

PetalburgCity_EventScript_Boy::
	lock
	faceplayer
	msgbox PetalburgCity_Text_WaterReflection, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PetalburgCity_EventScript_WallysMom::
	msgbox PetalburgCity_Text_WhereIsWally, MSGBOX_NPC
	end

PetalburgCity_Movement_WalkToWallyHousePlayer:
	delay_8
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkInsideHousePlayer:
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkToWallyHouseWallysDad:
	delay_8
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_WalkInsideHouseWallysDad:
	walk_up
	set_invisible
	step_end

PetalburgCity_Movement_WallyTutorialPlayer:
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
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
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

PetalburgCity_Movement_WallyTutorialWally:
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
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
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

PetalburgCity_EventScript_GymSign::
	msgbox PetalburgCity_Text_GymSign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_CitySign::
	msgbox PetalburgCity_Text_CitySign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_Gentleman::
	msgbox PetalburgCity_Text_FullPartyExplanation, MSGBOX_NPC
	end

PetalburgCity_EventScript_WallyHouseSign::
	msgbox PetalburgCity_Text_WallyHouseSign, MSGBOX_SIGN
	end

PetalburgCity_EventScript_ShowGymToPlayer0::
	lockall
	setvar VAR_0x8008, 0
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer1::
	lockall
	setvar VAR_0x8008, 1
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer2::
	lockall
	setvar VAR_0x8008, 2
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer3::
	lockall
	setvar VAR_0x8008, 3
	goto PetalburgCity_EventScript_ShowGymToPlayer
	end

PetalburgCity_EventScript_ShowGymToPlayer::
	applymovement LOCALID_GYM_BOY, Common_Movement_FacePlayer
	waitmovement 0
	playbgm MUS_FOLLOW_ME, FALSE
	playse SE_PIN
	applymovement LOCALID_GYM_BOY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GYM_BOY, Common_Movement_Delay48
	waitmovement 0
	call_if_eq VAR_0x8008, 0, PetalburgCity_EventScript_BoyApproachPlayer0
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_BoyApproachPlayer1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_BoyApproachPlayer2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_BoyApproachPlayer3
	msgbox PetalburgCity_Text_AreYouRookieTrainer, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, PetalburgCity_EventScript_LeadPlayerToGym0
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_LeadPlayerToGym1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_LeadPlayerToGym2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_LeadPlayerToGym3
	msgbox PetalburgCity_Text_ThisIsPetalburgGym, MSGBOX_DEFAULT
	applymovement LOCALID_GYM_BOY, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox PetalburgCity_Text_ThisIsGymSign, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkAway
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

PetalburgCity_EventScript_BoyApproachPlayer0::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer1::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer1
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer2::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_EventScript_BoyApproachPlayer3::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym0::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym0
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym0
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym1::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym1
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym1
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym2::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym2
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym2
	waitmovement 0
	return

PetalburgCity_EventScript_LeadPlayerToGym3::
	applymovement LOCALID_GYM_BOY, PetalburgCity_Movement_BoyWalkToGym3
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWalkToGym3
	waitmovement 0
	return

@ Unused
PetalburgCity_Movement_Delay48::
	delay_16
	delay_16
	delay_16
	step_end

PetalburgCity_Movement_BoyApproachPlayer0:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyApproachPlayer1:
	walk_right
	walk_right
	step_end

PetalburgCity_Movement_BoyApproachPlayer2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyApproachPlayer3:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

PetalburgCity_Movement_BoyWalkToGym0:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyWalkToGym1:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyWalkToGym2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyWalkToGym3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_in_place_faster_up
	step_end

PetalburgCity_Movement_BoyWalkAway:
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
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_PlayerWalkToGym0:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym1:
	delay_16
	delay_16
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym2:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Movement_PlayerWalkToGym3:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

PetalburgCity_EventScript_Scott0::
	lockall
	addobject LOCALID_SCOTT
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_SCOTT, 13, 10
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott1::
	lockall
	addobject LOCALID_SCOTT
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_SCOTT, 13, 11
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott2::
	lockall
	addobject LOCALID_SCOTT
	setvar VAR_0x8008, 2
	setobjectxy LOCALID_SCOTT, 13, 12
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott3::
	lockall
	addobject LOCALID_SCOTT
	setvar VAR_0x8008, 3
	setobjectxy LOCALID_SCOTT, 13, 13
	goto PetalburgCity_EventScript_Scott
	end

PetalburgCity_EventScript_Scott::
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottStartWalkLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_SCOTT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SCOTT, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_SCOTT_STATE, 1
	msgbox PetalburgCity_Text_AreYouATrainer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	msgbox PetalburgCity_Text_WellMaybeNot, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 30
	msgbox PetalburgCity_Text_ImLookingForTalentedTrainers, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, PetalburgCity_EventScript_ScottExit0
	call_if_eq VAR_0x8008, 1, PetalburgCity_EventScript_ScottExit1
	call_if_eq VAR_0x8008, 2, PetalburgCity_EventScript_ScottExit2
	call_if_eq VAR_0x8008, 3, PetalburgCity_EventScript_ScottExit3
	setvar VAR_SCOTT_PETALBURG_ENCOUNTER, 1
	removeobject LOCALID_SCOTT
	releaseall
	end

PetalburgCity_EventScript_ScottExit0::
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit0
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottExit0
	waitmovement 0
	return

PetalburgCity_EventScript_ScottExit1::
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit1
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottExit1
	waitmovement 0
	return

PetalburgCity_EventScript_ScottExit2::
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit2
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottExit2
	waitmovement 0
	return

PetalburgCity_EventScript_ScottExit3::
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Movement_PlayerWatchScottExit3
	applymovement LOCALID_SCOTT, PetalburgCity_Movement_ScottExit3
	waitmovement 0
	return

PetalburgCity_Movement_ScottStartWalkLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_ScottApproachPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_ScottExit0:
	walk_down
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
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_PlayerWatchScottExit0:
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit1:
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
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_PlayerWatchScottExit1:
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit2:
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
	walk_left
	walk_left
	step_end

PetalburgCity_Movement_PlayerWatchScottExit2:
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_Movement_ScottExit3:
	walk_up
	walk_left
	walk_left
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

PetalburgCity_Movement_PlayerWatchScottExit3:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

PetalburgCity_EventScript_GymBoy::
	msgbox PetalburgCity_Text_AreYouRookieTrainer, MSGBOX_NPC
	end

PetalburgCity_Text_WhereIsWally:
	.string "Wohin ist unser HEIKO nur gegangen?\p"
	.string "Wir müssen doch bald nach WIESENFLUR\n"
	.string "aufbrechen…$"

PetalburgCity_Text_AreYouRookieTrainer:
	.string "He da! Bist du vielleicht…\n"
	.string "ein Anfänger unter den TRAINERn?\p"
	.string "Weißt du, was POKéMON-TRAINER machen,\n"
	.string "wenn sie in einen neuen Ort kommen?\p"
	.string "Sie sehen sich als Erstes die ARENA\n"
	.string "im Ort an.$"

PetalburgCity_Text_ThisIsPetalburgGym:
	.string "Schau. Das ist die ARENA von\n"
	.string "BLÜTENBURG CITY.$"

PetalburgCity_Text_ThisIsGymSign:
	.string "Das ist das Logo der ARENA. Daran\n"
	.string "kannst du immer eine ARENA erkennen.$"

PetalburgCity_Text_WaterReflection:
	.string "Mein Gesicht spiegelt sich im Wasser…\p"
	.string "Ein schimmerndes Lächeln der Hoffnung.\p"
	.string "Oder ist es der Ausdruck düsterer\n"
	.string "Stille, an dem die Angst nagt…\p"
	.string "Was siehst du in deinem Spiegelbild?$"

PetalburgCity_Text_FullPartyExplanation:
	.string "Nehmen wir an, du hättest 6 POKéMON.\n"
	.string "Wenn du jetzt ein weiteres fängst…\p"
	.string "wird es automatisch in das POKéMON-\n"
	.string "LAGERUNGS-SYSTEM gesendet.$"

PetalburgCity_Text_GymSign:
	.string "POKéMON ARENA von BLÜTENBURG CITY\n"
	.string "LEITER: NORMAN\l"
	.string "“Ein Mann, der nach Stärke strebt!”$"

PetalburgCity_Text_CitySign:
	.string "BLÜTENBURG CITY\n"
	.string "“Wo Menschen Hand in Hand\l"
	.string "mit der Natur gehen.”$"

PetalburgCity_Text_WallyHouseSign:
	.string "HEIKOS HAUS$"

PetalburgCity_Text_AreYouATrainer:
	.string "Entschuldige bitte!\p"
	.string "Lass mich raten! Deine Kleidung verrät\n"
	.string "mir, dass du ein TRAINER bist.\l"
	.string "Habe ich Recht?$"

PetalburgCity_Text_WellMaybeNot:
	.string "… … … … …\n"
	.string "…\p"
	.string "Nun, vielleicht auch nicht.\n"
	.string "Deine Kleidung ist noch relativ sauber.\p"
	.string "Entweder bist du gerade erst TRAINER\n"
	.string "geworden oder du bist einfach ein ganz\l"
	.string "normales Kind.$"

PetalburgCity_Text_ImLookingForTalentedTrainers:
	.string "Ich reise durch das Land, immer auf der\n"
	.string "Suche nach talentierten TRAINERn.\p"
	.string "Tut mir leid, wenn ich dich aufgehalten\n"
	.string "habe.$"

.set LOCALID_ARCHIE, 2
.set LOCALID_OLD_LADY, 3
.set LOCALID_AQUA_GRUNT_1, 4
.set LOCALID_AQUA_GRUNT_2, 5
.set LOCALID_MAXIE, 6
.set LOCALID_MATT, 7
.set LOCALID_POOCHYENA_1, 8
.set LOCALID_AQUA_GRUNT_3, 9
.set LOCALID_POOCHYENA_2, 10
.set LOCALID_MAGMA_GRUNT_1, 11
.set LOCALID_MAGMA_GRUNT_2, 12
.set LOCALID_POOCHYENA_3, 13
.set LOCALID_POOCHYENA_4, 14
.set LOCALID_POOCHYENA_5, 15
.set LOCALID_MAGMA_GRUNT_3, 16
.set LOCALID_POOCHYENA_6, 17
.set LOCALID_MAGMA_GRUNT_4, 18


MtPyre_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition:
	call_if_eq VAR_MT_PYRE_STATE, 2, MtPyre_Summit_EventScript_SetArchieMaxiePositions
	call_if_unset FLAG_RECEIVED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_UnhideGrunts
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions::
	setobjectxyperm LOCALID_MAXIE, 23, 6
	setobjectxyperm LOCALID_ARCHIE, 22, 6
	applymovement LOCALID_ARCHIE, Common_Movement_FaceUp
	applymovement LOCALID_MAXIE, Common_Movement_FaceUp
	waitmovement 0
	end

MtPyre_Summit_EventScript_UnhideGrunts::
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_MAGMA
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	clearflag FLAG_HIDE_MT_PYRE_SUMMIT_MATT
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, MtPyre_Summit_EventScript_ArchieSaysGoAway
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox MtPyre_Summit_Text_MaxieDangerousFolly, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWalksRight
	waitmovement 0
	msgbox MtPyre_Summit_Text_ArchieDroughtsWillEnd, MSGBOX_DEFAULT
	msgbox MtPyre_Summit_Text_MaxieConsequences, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWalksRight
	waitmovement 0
	msgbox MtPyre_Summit_Text_ArchieSelfRighteousness, MSGBOX_DEFAULT
	msgbox MtPyre_Summit_Text_MaxieLeaves, MSGBOX_DEFAULT
	closemessage
	setvar VAR_LAST_TALKED, LOCALID_MAXIE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	removeobject LOCALID_MAGMA_GRUNT_3
	removeobject LOCALID_MAGMA_GRUNT_4
	removeobject LOCALID_POOCHYENA_1
	removeobject LOCALID_POOCHYENA_2
	removeobject LOCALID_POOCHYENA_3
	removeobject LOCALID_POOCHYENA_4
	removeobject LOCALID_POOCHYENA_5
	removeobject LOCALID_POOCHYENA_6
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	delay 20
	msgbox MtPyre_Summit_Text_ArchieKyogreWillAwaken, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieFacePlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieFacePlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieBumpsIntoPlayer, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MATT, MtPyre_Summit_Movement_MattWalksToPlayer
	waitmovement 0
	setvar VAR_0x8004, SPECIAL_BATTLE_ARCHIE_AND_MATT
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, MtPyre_Summit_EventScript_TeamAquaExits2
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate
	releaseall
	end

MtPyre_Summit_EventScript_ArchieTrainer::
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, TRAINER_ARCHIE_MT_PYRE, 0, MossdeepCity_Gym_Text_ArchieDefeat, MossdeepCity_Gym_Text_ArchieDefeat
	end

MtPyre_Summit_EventScript_MattTrainer::
	trainerbattle TRAINER_BATTLE_SET_TRAINER_B, TRAINER_MATT_MT_PYRE, 0, MossdeepCity_Gym_Text_MattDefeat, MossdeepCity_Gym_Text_MattDefeat
	end

MtPyre_Summit_EventScript_TeamAquaExits2::
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	removeobject LOCALID_AQUA_GRUNT_3
	removeobject LOCALID_MATT
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_MATT
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_MAGMA
	fadedefaultbgm
	fadescreen FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	releaseall
	end

MtPyre_Summit_EventScript_ArchieSaysGoAway::
	msgbox MtPyre_Summit_Text_ArchieSaysGoAway, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWalksAway
	waitmovement 0
	releaseall
	end

MtPyre_Summit_Movement_ArchieWalksRight:
	walk_right
	step_end

MtPyre_Summit_Movement_PlayerWalksAway:
	walk_down
	step_end

MtPyre_Summit_EventScript_ArchieFacePlayer0::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	applymovement LOCALID_MATT, MtPyre_Summit_Movement_MattFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1::
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2::
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	applymovement LOCALID_MATT, MtPyre_Summit_Movement_MattFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2::
	applymovement LOCALID_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1:
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0:
	walk_left
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2:
	walk_right
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MattFacePlayer0:
	walk_left
	step_end

MtPyre_Summit_Movement_MattFacePlayer2:
	walk_right
	step_end

MtPyre_Summit_Movement_MattWalksToPlayer:
	walk_up
	walk_up
	walk_up
	step_end

MtPyre_Summit_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza::
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManNewTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale::
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale::
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale::
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	call_if_ge VAR_MT_PYRE_STATE, 3, MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned::
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake::
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned::
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachArchie0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachArchie1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2::
	applymovement OBJ_EVENT_ID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_ArchieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie:
	delay_16
	walk_in_place_faster_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie:
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_1, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_2, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_3, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_4, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_BusyAquaGrunt::
	msgbox MtPyre_Summit_Text_Grunt3Defeat, MSGBOX_SIGN
	end

MtPyre_Summit_EventScript_BusyMagmaGrunt1::
	msgbox MtPyre_Summit_Text_BusyMagmaGrunt1, MSGBOX_SIGN
	end

MtPyre_Summit_EventScript_BusyMagmaGrunt2::
	msgbox MtPyre_Summit_Text_BusyMagmaGrunt2, MSGBOX_SIGN
	end

MtPyre_Summit_EventScript_BusyMagmaGrunt3::
	msgbox MtPyre_Summit_Text_BusyMagmaGrunt3, MSGBOX_SIGN
	end

MtPyre_Summit_EventScript_BusyAquaGrunt1::
	msgbox MtPyre_Summit_Text_BusyAquaGrunt1, MSGBOX_SIGN
	end

MtPyre_Summit_EventScript_BusyAquaGrunt2::
	msgbox MtPyre_Summit_Text_BusyAquaGrunt2, MSGBOX_SIGN
	end

MtPyre_Summit_Text_BusyMagmaGrunt1:
	.string "Wir sind mitten in einer wichtigen\n"
	.string "Mission!\p"
	.string "Siehst du nicht, dass TEAM AQUA uns\n"
	.string "aufhalten will?$"

MtPyre_Summit_Text_BusyMagmaGrunt2: 
	.string "Die ROTE KUGEL wird uns gehören!\n"
	.string "Für dich haben wir keine Zeit!$"

MtPyre_Summit_Text_BusyMagmaGrunt3: 
	.string "Aus dem Weg! Die Vergrößerung der\n"
	.string "Landmassen hängt von diesem Moment ab!$"

MtPyre_Summit_Text_BusyAquaGrunt1: 
	.string "Geh zur Seite! Wir müssen uns die\n"
	.string "BLAUE KUGEL vor TEAM MAGMA holen!$"

MtPyre_Summit_Text_BusyAquaGrunt2:
	.string "Keine Zeit zum Reden! Das Schicksal\n"
	.string "der Welt steht auf dem Spiel!$"

MtPyre_Summit_Text_Grunt1Intro:
	.string "TEAM AQUA?! Die wollen uns zuvorkommen!\p"
	.string "Ich lasse nicht zu, dass sie sich die\n"
	.string "KUGEL holen!$"

MtPyre_Summit_Text_Grunt1Defeat:
	.string "Argh… Ich dachte, du würdest zu den\n"
	.string "Idioten von TEAM AQUA gehören…$"

MtPyre_Summit_Text_Grunt1PostBattle:
	.string "Ja, du bist ganz schön stark…\n"
	.string "Aber TEAM MAGMA gibt nicht auf!$"

MtPyre_Summit_Text_Grunt2Intro:
	.string "Jetzt stehst du zwischen den Fronten!\n"
	.string "Wir holen uns die KUGEL vor MAGMA!$"

MtPyre_Summit_Text_Grunt2Defeat:
	.string "Ich hätte dich erst von TEAM MAGMA\n"
	.string "zermürben lassen sollen…$"

MtPyre_Summit_Text_Grunt2PostBattle:
	.string "Du weißt doch gar nichts! Misch dich\n"
	.string "besser nicht in unsere Sachen ein!$"

MtPyre_Summit_Text_Grunt3Intro:
	.string "Hey…\n"
	.string "Ich kenne dich doch vom SCHLOTBERG!\p"
	.string "Du gehörst keinem TEAM an. Warum bist\n"
	.string "du hier?$"

MtPyre_Summit_Text_Grunt3Defeat:
	.string "Wenn du dich schon in fremde Ange-\n"
	.string "legenheiten einmischen musst, dann\l"
	.string "mach das bei TEAM MAGMA!$"

MtPyre_Summit_Text_Grunt3PostBattle:
	.string "Ach, das spielt keine Rolle.\n"
	.string "Wir haben Zeit herausgeschlagen!\p"
	.string "Der BOSS müsste mittlerweile haben, was\n"
	.string "er besorgen wollte!$"

MtPyre_Summit_Text_Grunt4Intro:
	.string "Ach, ich weiß!\n"
	.string "Du wolltest Mitglied bei TEAM MAGMA\l"
	.string "werden, aber die wollten dich nicht!\p"
	.string "Denk nur nicht, dass du Mitglied bei\n"
	.string "TEAM AQUA werden kannst!$"

MtPyre_Summit_Text_Grunt4Defeat:
	.string "Wenn du TEAM AQUA unbedingt\n"
	.string "beitreten willst, können wir darüber\l"
	.string "reden…$"

MtPyre_Summit_Text_Grunt4PostBattle:
	.string "Wir Mitglieder und unser Boss sind\n"
	.string "das perfekte Team.$"

MtPyre_Summit_Text_ArchieSaysGoAway:
	.string "ADRIAN: Hmpf, du schon wieder?\p"
	.string "Glaubst du, du kannst dich mir mit nur\n"
	.string "einem POKéMON in den Weg stellen?\p"
	.string "Das ist kein Kinderspiel, Kind.\n"
	.string "Geh nach Hause, bevor du dir wehtust.$"

MtPyre_Summit_Text_MaxieDangerousFolly:
	.string "MARC: Hmpf! Hängst du noch immer an\n"
	.string "deinen naiven Idealen, ADRIAN?\p"
	.string "Deine Jagd nach KYOGRE wird nur\n"
	.string "Verwüstung bringen.\p"
	.string "Mit der ROTEN KUGEL in meinem Besitz\n"
	.string "wird GROUDON erwachen und wahres\l"
	.string "Gleichgewicht bringen.\p"
	.string "Denk an das Ackerland, das wir\n"
	.string "zurückgewinnen könnten.\p"
	.string "Ackerland, das Millionen ernähren\n"
	.string "könnte!\p"
	.string "Deine Kurzsichtigkeit macht dich\n"
	.string "blind, ADRIAN.$"

MtPyre_Summit_Text_ArchieDroughtsWillEnd:
	.string "ADRIAN: Blind bist hier nur du, MARC!\n"
	.string "KYOGRE ist der Schlüssel zur Heilung\l"
	.string "dieser Welt!\p"
	.string "Die BLAUE KUGEL wird es aufwecken, und\n"
	.string "die Dürren werden enden!\p"
	.string "Wasser wird ödes Land wiederbeleben und\n"
	.string "den Durst unzähliger Lebewesen stillen!$"

MtPyre_Summit_Text_MaxieConsequences:
	.string "MARC: Du begreifst die Folgen deines\n"
	.string "Handelns nicht.\p"
	.string "KYOGRE aufzuwecken wird Verderben\n"
	.string "bringen.\p"
	.string "Nur GROUDON kann das Land\n"
	.string "zurückgewinnen und Wohlstand sichern.\p"
	.string "Du würdest die Welt im Chaos ertränken!$"

MtPyre_Summit_Text_ArchieSelfRighteousness:
	.string "ADRIAN: Genug von deiner\n"
	.string "Selbstgerechtigkeit!\p"
	.string "Die Welt braucht Wasser, um zu\n"
	.string "überleben!\p"
	.string "Mit KYOGREs Hilfe werden Wüsten\n"
	.string "erblühen und Hungersnöte enden!\p"
	.string "Das siehst du nicht, weil deine\n"
	.string "Besessenheit vom Land dich blendet!$"

MtPyre_Summit_Text_MaxieLeaves:
	.string "MARC: Ich habe deine Ignoranz lange\n"
	.string "genug ertragen. Mit jemandem, der so\l"
	.string "verblendet ist, kann man nicht reden.\p"
	.string "Ich habe zu tun… richtige Arbeit.\n"
	.string "Leb wohl, ADRIAN.$"

MtPyre_Summit_Text_ArchieKyogreWillAwaken:
	.string "ADRIAN: MARC! Verflucht sei er!\n"
	.string "Er will einfach nicht zur Vernunft\l"
	.string "kommen.\p"
	.string "Was soll's. Mit der BLAUEN KUGEL wird\n"
	.string "KYOGRE erwachen, und ich beweise ihm,\l"
	.string "dass er sich irrt!\p"
	.string "Die Zeit drängt… Ich muss schnell\n"
	.string "handeln.$"

MtPyre_Summit_Text_ArchieBumpsIntoPlayer:
	.string "ADRIAN: Du?!\n"
	.string "Ich kann mir jetzt keine Verzögerung\l"
	.string "leisten!\p"
	.string "Jede Sekunde zählt, um KYOGRE\n"
	.string "aufzuwecken.\p"
	.string "Wenn du uns in die Quere kommen willst,\n"
	.string "machen wir kurzen Prozess mit dir!\p"
	.string "Mach dich auf was gefasst!$"

MossdeepCity_Gym_Text_ArchieDefeat:
	.string "ADRIAN: Tse… Glaub nicht, dass das\n"
	.string "etwas ändert! Wir werden KYOGRE\l"
	.string "trotzdem aufwecken!$"

MossdeepCity_Gym_Text_MattDefeat:
	.string "WOLFGANG: Du glaubst also, du hast\n"
	.string "gewonnen? Das ändert nichts!\l"
	.string "KYOGRE wird uns gehören!$"

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo:
	.string "ADRIAN: MARC von TEAM MAGMA mag uns\n"
	.string "vielleicht einen Schritt voraus sein,\l"
	.string "aber wir haben das, was wir wollten.\p"
	.string "Die BLAUE KUGEL vom PYROBERG…\n"
	.string "Ich, ADRIAN, halte sie endlich in meinen\l"
	.string "Händen!\p"
	.string "Hähähä… Nun werden sich unsere\n"
	.string "ultimativen Träume erfüllen!\p"
	.string "Okay, TEAM!\n"
	.string "Los geht's!$"

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis:
	.string "Oh, nein…\n"
	.string "Das darf nicht sein…\p"
	.string "Nicht nur die ROTE, sondern auch die\n"
	.string "BLAUE KUGEL wurde gestohlen…\p"
	.string "Diese KUGELn sind der Schlüssel dazu,\n"
	.string "KYOGRE und GROUDON friedlich zu halten.\p"
	.string "Was wollen diese Männer nur mit den\n"
	.string "beiden KUGELn?\p"
	.string "… … … … …\n"
	.string "…\l"
	.string "… … … … …\l"
	.string "…\p"
	.string "Ich meine, TEAM MAGMA wäre als Erstes\n"
	.string "wieder gegangen.\p"
	.string "Aber sie hatten es sehr eilig und haben\n"
	.string "dies hier zurückgelassen.\p"
	.string "Ich habe keine Ahnung, was das ist.\p"
	.string "Du kannst es gerne haben.\n"
	.string "Vielleicht kannst du damit was\l"
	.string "anfangen?$"

MtPyre_Summit_Text_OrbsHaveBeenTaken:
	.string "Die BLAUE und die ROTE KUGEL wurden von\n"
	.string "diesen Leuten fortgenommen…\p"
	.string "Sie dürfen nicht missbraucht werden…\n"
	.string "Ich habe Angst, dass etwas\l"
	.string "Schreckliches passieren wird…$"

MtPyre_Summit_Text_GroudonKyogreAwakened:
	.string "Ach, du meine Güte…\p"
	.string "Du sagst, GROUDON und KYOGRE seien\n"
	.string "beide aufgewacht?\p"
	.string "Man sagt, die BLAUE und die ROTE KUGEL\n"
	.string "bezwingen die Wut dieser beiden\l"
	.string "POKéMON…\p"
	.string "Und man sagt auch, dass der wahre\n"
	.string "Besitzer der KUGELn immer noch lebt.\p"
	.string "Aber niemand weiß, zu wem die KUGELn\n"
	.string "gehören.\p"
	.string "Es könnte ein Mensch, aber auch ein\n"
	.string "POKéMON sein. Niemand weiß es.$"

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs:
	.string "Die beiden Männer, die die KUGELn\n"
	.string "genommen hatten, haben sie freiwillig\l"
	.string "wieder zurückgebracht.\p"
	.string "Diese Männer…\n"
	.string "Vielleicht sind sie doch keine\l"
	.string "schlechten Kerle…$"

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs:
	.string "Die Gestaltung des Landes, des Meeres\n"
	.string "und des Himmels…\p"
	.string "Man sagt, dass sich hier die Persönlich-\n"
	.string "keiten uralter POKéMON widerspiegeln…\p"
	.string "So, wie Menschen und POKéMON leben,\n"
	.string "lebt auch die Welt…\p"
	.string "Das haben wir von den uralten POKéMON\n"
	.string "gelernt…$"

MtPyre_Summit_Text_WillYouHearOutMyTale:
	.string "Am PYROBERG legen wir die Geister der\n"
	.string "POKéMON, die von uns gegangen sind, zur\l"
	.string "Ruhe…\p"
	.string "Von hier aus hat man einen Ausblick\n"
	.string "über die ganze Region von HOENN…\p"
	.string "Die körperlosen Geister der POKéMON\n"
	.string "finden hier ihre Ruhe…\p"
	.string "Es ist Fügung, dass du jetzt hier bist…\p"
	.string "Möchtest du meine Geschichte hören?\n"
	.string "Eine lange, sehr alte Geschichte der\l"
	.string "HOENN-Region?$"

MtPyre_Summit_Text_GroudonKyogreTale:
	.string "Es geschah vor langer, langer Zeit…\p"
	.string "Die Welt erbebte unter der\n"
	.string "Auseinandersetzung der POKéMON des\l"
	.string "Landes mit den POKéMON des Meeres…\p"
	.string "Die POKéMON des Landes erschufen\n"
	.string "Berge und Kontinente…\p"
	.string "Die POKéMON des Meeres erschufen hohe\n"
	.string "Wellen und tiefe Meeresbecken…\p"
	.string "Das Duell wütete ohne absehbares Ende.\p"
	.string "Die Welt wurde von erbarmungslosen\n"
	.string "Stürmen und unglaublichen Infernos\l"
	.string "heimgesucht.\p"
	.string "Die BLAUE und die ROTE KUGEL setzten\n"
	.string "schließlich diesem Kampf ein Ende.\p"
	.string "Licht strahlte von den beiden KUGELn\n"
	.string "und beruhigte die Kontrahenten.\p"
	.string "Die beruhigten POKéMON verbargen sich\n"
	.string "in den Tiefen des Meeres und der Erde,\l"
	.string "und eines Tages verschwanden sie.$"

MtPyre_Summit_Text_WellThatTooIsFine:
	.string "Ich verstehe…\n"
	.string "Nun, das ist auch in Ordnung…$"

MtPyre_Summit_Text_MaxieSilence:
	.string "MARC: {PLAYER}…\p"
	.string "… … … … … …\n"
	.string "… … … … … …$"

MtPyre_Summit_Text_HearTheNewLegendOfHoenn:
	.string "Meine Aufgabe ist es, die Legenden von\n"
	.string "HOENN an die nachfolgenden\l"
	.string "Generationen weiterzugeben.\p"
	.string "Die Krise von XENEROVILLE war die\n"
	.string "Wiederholung der Legende…\p"
	.string "Hast du Zeit, dir die neue Legende von\n"
	.string "HOENN anzuhören?$"

MtPyre_Summit_Text_HoennTrioTale:
	.string "Es geschah vor langer, langer Zeit…\p"
	.string "Die Welt erbebte unter der\n"
	.string "Auseinandersetzung des POKéMON des\l"
	.string "Landes mit dem POKéMON des Meeres…\p"
	.string "Das POKéMON des Landes erschuf\n"
	.string "Berge und Kontinente…\p"
	.string "Das POKéMON des Meeres erschuf hohe\n"
	.string "Wellen und tiefe Meeresbecken…\p"
	.string "Das Duell wütete ohne absehbares Ende.\p"
	.string "Die Welt wurde von erbarmungslosen\n"
	.string "Stürmen und unglaublichen Infernos\l"
	.string "heimgesucht.\p"
	.string "Da stieg ein POKéMON in einem Sturm aus\n"
	.string "den Wolken herab.\p"
	.string "Dieses POKéMON, welches in einem\n"
	.string "lebendigen Grün glänzte, beruhigte die\l"
	.string "beiden POKéMON.\p"
	.string "Und als es seine Aufgabe erfüllt hatte,\n"
	.string "stieg das POKéMON wieder in das Blau\l"
	.string "des Himmels hinauf…$"


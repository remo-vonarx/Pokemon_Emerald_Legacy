.set LOCALID_MAGMA_GRUNT_1, 5
.set LOCALID_MAGMA_GRUNT_2, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_AQUA_GRUNT_1, 8
.set LOCALID_AQUA_GRUNT_2, 9

MeteorFalls_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	end

MeteorFalls_1F_1R_EventScript_OpenStevensCave::
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, TRUE
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, TRUE
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, FALSE
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, TRUE
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	addobject LOCALID_ARCHIE
	addobject LOCALID_AQUA_GRUNT_1
	addobject LOCALID_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PlayerToProf
	waitmovement 0
	applymovement 10, MeteorFalls_1F_1R_Movement_Prof
	waitmovement 0
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MeteorFalls_1F_1R_WarpToFallarbor
	goto_if_eq VAR_RESULT, NO, MeteorFalls_1F_1R_ProfCozmoDontWalkToFallarbor
MeteorFalls_1F_1R_ProfCozmoDontWalkToFallarbor:
	msgbox MeteorFalls_1F_1R_Text_ProfCozmoDontWalkToFallarbor, MSGBOX_DEFAULT
	releaseall
	end

MeteorFalls_1F_1R_WarpToFallarbor:
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	clearflag FLAG_RECEIVED_AURORA_TICKET
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	msgbox MeteorFalls_1F_1R_Text_ProfCozmoWalkToFallarbor, MSGBOX_DEFAULT
	delay 30
	warp MAP_FALLARBOR_TOWN_COZMOS_HOUSE, 7, 4
	waitstate
	releaseall
	end

MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_PlayerToProf:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	face_down
	step_end

MeteorFalls_1F_1R_Movement_Prof:
	face_up
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay:
	walk_in_place_faster_down
	delay_4
	walk_in_place_faster_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo::
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MeteorFalls_1F_1R_WarpToFallarbor
	goto_if_eq VAR_RESULT, NO, MeteorFalls_1F_1R_ProfCozmoDontWalkToFallarbor
	release
	end

MeteorFalls_1F_1R_Text_WithThisMeteorite:
	.string "Hähähä!\p"
	.string "Mit diesem METEORITen wird das Ding\n"
	.string "am SCHLOTBERG…$"

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma:
	.string "Häh?\p"
	.string "Ich weiß zwar nicht, wer du bist. Aber\n"
	.string "wenn du dich TEAM MAGMA in den Weg\l"
	.string "stellst, erwarte keine Gnade!$"

MeteorFalls_1F_1R_Text_HoldItRightThereMagma:
	.string "Bleibt sofort stehen, TEAM MAGMA!\p"
	.string "Ihr irrt euch gewaltig, wenn ihr meint,\n"
	.string "ihr könntet mit der Welt machen, was ihr\l"
	.string "wollt!$"

MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua:
	.string "Hähähä!\n"
	.string "Sogar TEAM AQUA leistet uns\l"
	.string "Gesellschaft!\p"
	.string "Aber es ist viel zu anstrengend, sich\n"
	.string "mit allen auseinanderzusetzen…\p"
	.string "Hey, das spielt auch keine Rolle!\p"
	.string "Wir haben den METEORITen und so\n"
	.string "machen wir uns auf zum SCHLOTBERG!\p"
	.string "Hähähä! Wir sehen uns, ihr Würstchen\n"
	.string "von TEAM AQUA!$"

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore:
	.string "ADRIAN: Dich kenne ich doch!\n"
	.string "Vom MUSEUM in GRAPHITPORT.\p"
	.string "Ah, du bist {PLAYER}.\p"
	.string "Damals dachte ich, du würdest zu\n"
	.string "TEAM MAGMA gehören.\p"
	.string "Hmpf…\n"
	.string "Du bist ein merkwürdiges Kind.\p"
	.string "TEAM MAGMA… Die sind auf dem Holzweg.\n"
	.string "Sie glauben, sie könnten die uralte\l"
	.string "Kraft befreien, die uns einst rettete,\l"
	.string "und sie werde wieder Gutes bringen.\p"
	.string "Aber sie sind blind.\p"
	.string "Die Rivalität dieser uralten Mächte\n"
	.string "wird nur Verderben bringen.\p"
	.string "Unser Retter, der Beschützer vor den\n"
	.string "Dürren, muss es sein, der erwacht.\p"
	.string "Nur so lässt sich diese Dürre beenden\n"
	.string "und Frieden schaffen.\p"
	.string "Deshalb sind sie unsere Feinde! Wir\n"
	.string "dürfen sie nicht gewinnen lassen!$"

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma:
	.string "BOSS, wir sollten TEAM MAGMA\n"
	.string "verfolgen…$"

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo:
	.string "ADRIAN: Ja, ja. Das müssen wir!\p"
	.string "Nicht auszudenken, was TEAM MAGMA am\n"
	.string "SCHLOTBERG anrichten will!$"

MeteorFalls_1F_1R_Text_ArchieFarewell:
	.string "ADRIAN: {PLAYER}, du solltest\n"
	.string "TEAM MAGMA im Auge behalten. Sie sind\l"
	.string "gefährlicher, als du ahnst.\p"
	.string "Leb wohl!$"

MeteorFalls_1F_1R_Text_MeetProfCozmo:
	.string "Ich… Ich bin KOSMO…\n"
	.string "Ich bin Professor…\p"
	.string "Einige Typen von TEAM MAGMA haben\n"
	.string "mich überredet, sie zu METEOR-\l"
	.string "FÄLLE zu führen…\p"
	.string "Sie haben mich hereingelegt.\n"
	.string "Sie haben sogar den METEORITen\l"
	.string "mitgenommen…\p"
	.string "Und dann tauchte TEAM AQUA auf. Die\n"
	.string "sind auch nicht anders.\p"
	.string "Und ich?\n"
	.string "Ich verstehe absolut nicht, was los ist.\p"
	.string "TEAM MAGMA…\p"
	.string "Was haben sie mit dem METEORITen am\n"
	.string "SCHLOTBERG vor?\p"
	.string "Ich weiß nicht, was ich tun soll…\n"
	.string "Könntest du mich zurück zu meinem\l"
	.string "Labor in LAUBWECHSELFELD begleiten?$"

MeteorFalls_1F_1R_Text_ProfCozmoWalkToFallarbor:
	.string "Danke.\n"
	.string "Mit dir fühle ich mich sicherer.\p"
	.string "Gehen wir gemeinsam zurück.$"

MeteorFalls_1F_1R_Text_ProfCozmoDontWalkToFallarbor:
	.string "Oh… Verstehe…\n"
	.string "Dann muss ich wohl versuchen,\l"
	.string "allein zurechtzukommen…\p"
	.string "Bitte sei vorsichtig da draußen.$"


MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney:
	.string "PROF. KOSMO: Dieses TEAM MAGMA…\p"
	.string "Was haben sie mit dem METEORITen am\n"
	.string "SCHLOTBERG vor?\p"
	.string "Ich weiß nicht, was ich tun soll…\n"
	.string "Könntest du mich zurück zu meinem\l"
	.string "Labor in LAUBWECHSELFELD begleiten?$"

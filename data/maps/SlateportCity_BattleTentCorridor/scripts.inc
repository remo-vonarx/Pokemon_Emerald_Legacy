.set LOCALID_ATTENDANT, 1

SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_ATTENDANT, 2, 2
	turnobject LOCALID_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests:
	.string "Möchtest du einen kleinen, feinen\n"
	.string "Tipp für WETTBEWERBE?\p"
	.string "Wenn du eine bestimmte Attacke nach\n"
	.string "einer bestimmten anderen Art von\l"
	.string "Attacke einsetzt, bekommst du manchmal\l"
	.string "zusätzliche Aufmerksamkeit.\p"
	.string "Wenn du weißt, was du tust, kannst du\n"
	.string "mit deinem Ausdruck groß punkten.\p"
	.string "Natürlich könnten deine Gegner ver-\n"
	.string "suchen, den Auftritt deines POKéMON\l"
	.string "zu stören.$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
	.string "Mein Papa ist WETTBEWERBS-JUROR.\p"
	.string "Was soll ich nur werden, wenn ich\n"
	.string "groß bin? JUROR oder ARENALEITER?$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
	.string "Hey, Mann, ich bin echt mega sauer,\n"
	.string "weißt du? Ich wollte nur wissen,\l"
	.string "warum mein POKéMON nie gewinnt,\l"
	.string "verstehst du?\p"
	.string "Also hab ich dem JUROR mal meine\n"
	.string "Meinung gesagt, kostet ja nix.\p"
	.string "Und der hört mir nicht mal zu, ey!\n"
	.string "Total ätzend, Mann!\p"
	.string "Hey, du da! Klappe, ja?\n"
	.string "Nimm einfach das hier!$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment:
	.string "Das ist so die TM41, weißt du?\n"
	.string "Hey, das ist FOLTERKNECHT, hörst du?\p"
	.string "Damit kann der andere dieselbe\n"
	.string "Attacke nicht zweimal hintereinander\l"
	.string "einsetzen, klar?\p"
	.string "Hey, jetzt hör mal zu, ey,\n"
	.string "ich will dich hier nicht foltern!$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
	.string "MC: Oh, oh, oh!\n"
	.string "Was für ein prächtiges POKéMON!\p"
	.string "Bitte! Tritt näher und nimm an\n"
	.string "unseren tollen WETTBEWERBEN teil!\p"
	.string "Du wirst dich gut schlagen, da bin\n"
	.string "ich sicher! Mein Auge täuscht sich nie!$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
	.string "JUROR: Na, hallo!\n"
	.string "Du bist also ein TRAINER!\p"
	.string "Dann darfst du dir einen POKéMON-\n"
	.string "WETTBEWERB nicht entgehen lassen!\p"
	.string "Hol dir in WIESENFLUR eine\n"
	.string "WETTB.-KARTE und melde dich an!$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime:
	.string "Zeit für die Vorführung!\n"
	.string "Womit soll ich anfangen?$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
	.string "Die Vorführung meines POKéMON hat\n"
	.string "kaum jemand beachtet…\p"
	.string "Pah, dieser JUROR erkennt etwas\n"
	.string "Gutes nicht, wenn er es sieht.$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
	.string "Oh, hallo! Du musst ein echter Fan sein,\n"
	.string "so nah am Geschehen.\p"
	.string "Für deine Begeisterung bekommst du\n"
	.string "einen weisen Rat von mir.\p"
	.string "Kommt eine Attacke richtig gut an,\n"
	.string "gerät das Publikum in Begeisterung.\p"
	.string "Das POKéMON, das genau dann seine\n"
	.string "Vorführung zeigt…\p"
	.string "Na ja, da sollte doch etwas Gutes\n"
	.string "passieren!$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
	.string "Ich schaffe das nicht! Ich bin noch\n"
	.string "nervöser als mein POKéMON.\p"
	.string "Ich zittere und mein Herz rast!$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike:
	.string "Ein Kampf und ein WETTBEWERB sind nicht\n"
	.string "gleich, aber sie ähneln sich auch.\p"
	.string "Du musst hart arbeiten und an deine\n"
	.string "aufgezogenen POKéMON glauben.$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
	.string "Das POKéMON scheint in Bestform\n"
	.string "zu sein, was?\p"
	.string "Ein POKéMON, das in der zweiten\n"
	.string "Bewertung gut abschneidet, ist bei\l"
	.string "der Vorführung wohl entspannter.$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
	.string "Schau dir nur dieses Trauerspiel an!\p"
	.string "Ha, mein POKéMON ist viel besser\n"
	.string "als dieser Haufen!$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
	.string "Bekommst du nicht auch Lust, dich\n"
	.string "mitzubewegen, wenn POKéMON eine so\l"
	.string "schwungvolle Vorführung zeigen?$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage:
	.string "POKéMON-WETTBEWERBE\n"
	.string "BÜHNE DER HYPER-KLASSE!$"


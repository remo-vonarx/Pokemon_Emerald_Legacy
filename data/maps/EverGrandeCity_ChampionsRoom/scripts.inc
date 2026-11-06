.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3
.set LOCALID_STEVEN, 4

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_SetStevenLayout
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_SetStevenLayout::	
	setmaplayoutindex LAYOUT_EVER_GRANDE_CITY_CHAMPIONS_ROOM_STEVEN
	return	

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_Steven
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Steven::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_1, EverGrandeCity_ChampionsRoom_Text_StevenDefeat
	goto EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF
	
EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF::
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE_2, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_RematchMayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchMayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchMayAdvice, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBrendanAdvice, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBirchCongratulations, MSGBOX_DEFAULT
	closemessage
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF

EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF::
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchWallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_RematchMayCantGoIn
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanCantGoIn
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchWallaceChampion, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchMayCantGoIn::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchMayCantGoIn, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanCantGoIn::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBrendanCantGoIn, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech:
	.string "TROY: Willkommen, {PLAYER}{KUN}.\p"
	.string "Ich habe mich darauf gefreut, dich\n"
	.string "eines Tages hier zu sehen.\p"
	.string "Du… Was hast du auf deiner Reise mit\n"
	.string "den POKéMON gesehen?\p"
	.string "Was hast du gefühlt, als du so viele\n"
	.string "andere TRAINER wie dich getroffen hast?\p"
	.string "Was ist in dir erwacht?\n"
	.string "Ich will alles davon zu spüren kriegen!\p"
	.string "Also, leg los!$"

EverGrandeCity_ChampionsRoom_Text_StevenDefeat:
	.string "Ich, der CHAMP, wurde besiegt…\p"
	.string "Der Ruhm gehört dir, {PLAYER}{KUN}!\p"
	.string "Du bist wahrhaft ein edler\n"
	.string "TRAINER!$"

EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech:
	.string "TROY: Herzlichen Glückwunsch!\p"
	.string "Die Gefühle, die du für deine\n"
	.string "POKéMON hegst…\p"
	.string "Und die POKéMON, die diese Gefühle mit\n"
	.string "aller Kraft erwidert haben…\p"
	.string "Sie sind eins geworden und haben eine\n"
	.string "noch größere Macht erschaffen.\p"
	.string "So konntest du heute den Sieg\n"
	.string "erringen!\p"
	.string "Für die ganze HOENN-Region rufe ich\n"
	.string "dich hiermit zu Recht zum neuen…$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "MAIKE: {PLAYER}{KUN}!\p"
	.string "Ich muss dir unbedingt einen Rat geben,\n"
	.string "bevor du gegen den CHAMP antrittst!$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "MAIKE: Wie? Waswaswas?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Das kann nicht sein…\l"
	.string "Es ist schon vorbei?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRIX: {PLAYER}!\p"
	.string "Möchtest du nicht ein paar Tipps, bevor\n"
	.string "du den CHAMP herausforderst?$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRIX: {PLAYER}!\p"
	.string "Willst du mir etwa sagen…\n"
	.string "Du hast den CHAMP besiegt?!?!?!$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. BIRK: Siehst du?\n"
	.string "Was habe ich dir gesagt, {RIVAL}?\p"
	.string "Ich wusste, du brauchst dir keine\n"
	.string "Sorgen um {PLAYER}{KUN} zu machen!\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, du hast es geschafft.\p"
	.string "Als ich hörte, dass du deinen Vater in\n"
	.string "der ARENA von BLÜTENBURG CITY\p"
	.string "besiegt hast, wusste ich, dass du eine\n"
	.string "Chance hast…\p"
	.string "Aber dass du dann sogar CHAMP\n"
	.string "geworden bist!\p"
	.string "Oh, ja!\p"
	.string "Was ist aus deinem POKéDEX geworden?\n"
	.string "Lass mich mal sehen…$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. BIRK: Also, dann sage ich:\n"
	.string "Herzlichen Glückwunsch!\p"
	.string "Nun kannst du mit Stolz den letzten\n"
	.string "Raum betreten!$"

EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe:
	.string "TROY: {PLAYER}{KUN}…\p"
	.string "Nein! Neuer CHAMP!\p"
	.string "Komm mit mir.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "WASSILI: Tut mir leid, aber…\p"
	.string "Diesen Raum dürfen nur TRAINER\n"
	.string "betreten, die CHAMPs geworden sind.\p"
	.string "Warte bitte draußen mit dem PROFESSOR.$"

EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside:
	.string "TROY: Tut mir leid, aber…\p"
	.string "Diesen Raum dürfen nur TRAINER\n"
	.string "betreten, die CHAMPs geworden sind.\p"
	.string "Warte bitte draußen mit dem PROFESSOR.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "MAIKE: Grummel…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Ich mache nur Spaß! Ist schon okay!\n"
	.string "So sind die Regeln!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Ehrlich. Herzlichen Glückwunsch!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRIX: … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Na, wenn es die Regeln so bestimmen…\p"
	.string "{PLAYER}, das ist dein Tag!\n"
	.string "Herzlichen Glückwunsch!$"

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "WASSILI: Willkommen, {PLAYER}{KUN}.\p"
	.string "Unsere Wege kreuzen sich erneut…\n"
	.string "Diesmal bin ich der Herausforderer.\p"
	.string "Ich habe gesehen, wie du in XENEROVILLE\n"
	.string "für Frieden gesorgt hast… Eine\l"
	.string "bemerkenswerte Leistung, vollbracht\l"
	.string "mit deinen POKéMON an deiner Seite.\p"
	.string "Wir TRAINER ziehen POKéMON auf, indem\n"
	.string "wir ihnen Items geben und neue\l"
	.string "Techniken für den Kampf beibringen.\p"
	.string "Und auch wir lernen viel von den\n"
	.string "POKéMON.\p"
	.string "Du hast die Stärke eines wahren CHAMPs\n"
	.string "gezeigt, {PLAYER}{KUN}.\p"
	.string "Doch nun muss sich deine Leistung der\n"
	.string "ultimativen Prüfung stellen.\p"
	.string "Nun ja!\p"
	.string "Wer kann am elegantesten in ganz\n"
	.string "HOENN mit seinen POKéMON tanzen?\p"
	.string "Zeig es mir! Hier und jetzt!$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "Ich, der Herausforderer, wurde besiegt…\n"
	.string "Eine erstklassige Leistung!\l"
	.string "Der Ruhm gehört dir, {PLAYER}{KUN}!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "WASSILI: Die POKéMON, die du in den\n"
	.string "Kampf geschickt hast…\p"
	.string "Manchmal wirbelten sie wie eine\n"
	.string "Frühlingsbrise und dann wieder\l"
	.string "schlugen sie ein wie ein Blitz.\p"
	.string "Du hast deine POKéMON mit leichter,\n"
	.string "aber sicherer Eleganz geführt.\p"
	.string "Du hast mich mit deiner meisterhaften\n"
	.string "Vorstellung bezaubert!\p"
	.string "Du bleibst auf dem ruhmreichen Gipfel\n"
	.string "der POKéMON LIGA, {PLAYER}{KUN}.\p"
	.string "Herzlichen Glückwunsch… CHAMP von\n"
	.string "HOENN.$"

EverGrandeCity_ChampionsRoom_Text_RematchMayAdvice:
	.string "MAIKE: {PLAYER}{KUN}!\p"
	.string "Wow! Du hast es geschafft!\n"
	.string "Diesmal kein Rat… nur Glückwünsche!\p"
	.string "Gegen WASSILI anzutreten und zu\n"
	.string "siegen… Das ist unglaublich!$"

EverGrandeCity_ChampionsRoom_Text_RematchBrendanAdvice:
	.string "BRIX: {PLAYER}{KUN}!\p"
	.string "Wow! Du hast es geschafft!\n"
	.string "Diesmal kein Rat… nur Glückwünsche!\p"
	.string "Gegen WASSILI anzutreten und zu\n"
	.string "siegen… Das ist unglaublich!$"

EverGrandeCity_ChampionsRoom_Text_RematchBirchArriveRatePokedex:
	.string "PROF. BIRK: Tja, {RIVAL}, sieht so aus,\n"
	.string "als hätte ich bei {PLAYER}{KUN} Recht\l"
	.string "gehabt!\p"
	.string "Ich habe nie daran gezweifelt, dass du\n"
	.string "deinen Titel verteidigen kannst, und\l"
	.string "nun bist du… immer noch CHAMP!\p"
	.string "Erstaunlich, wie weit du gekommen\n"
	.string "bist! Ich wusste, dass du Talent hast,\l"
	.string "aber das…\p"
	.string "{PLAYER}{KUN}, du hast wirklich\n"
	.string "Geschichte geschrieben.\p"
	.string "Ah, genau! Dein POKéDEX…\n"
	.string "Darf ich mal einen Blick hineinwerfen?\l"
	.string "Ich bin gespannt auf deine Fortschritte.$"

EverGrandeCity_ChampionsRoom_Text_RematchBirchCongratulations:
	.string "PROF. BIRK: Also, dann sage ich:\n"
	.string "Nochmals herzlichen Glückwunsch!\p"
	.string "Nun kannst du wieder mit Stolz den\n"
	.string "letzten Raum betreten!$"

EverGrandeCity_ChampionsRoom_Text_RematchWallaceComeWithMe:
	.string "WASSILI: {PLAYER}{KUN},\n"
	.string "du hast dich erneut bewiesen.\p"
	.string "Verlieren wir keine Zeit.\n"
	.string "CHAMP, folge mir…\p"
	.string "Gehen wir in die RUHMESHALLE, um\n"
	.string "diesen jüngsten Triumph festzuhalten.$"

EverGrandeCity_ChampionsRoom_Text_RematchMayCantGoIn:
	.string "MAIKE: Hey, warte mal!\n"
	.string "WASSILI, du bist nicht der CHAMP.\p"
	.string "Du darfst da nicht rein!$"

EverGrandeCity_ChampionsRoom_Text_RematchBrendanCantGoIn:
	.string "BRIX: Hey, warte mal!\n"
	.string "WASSILI, du bist nicht der CHAMP.\p"
	.string "Du darfst da nicht rein!$"

EverGrandeCity_ChampionsRoom_Text_RematchWallaceChampion::
	.string "WASSILI: Ah, {RIVAL}.\n"
	.string "Weißt du, ich war vor langer Zeit\l"
	.string "CHAMP. In freundschaftlicher Rivalität\l"
	.string "haben TROY und ich uns den Titel\l"
	.string "immer wieder abgejagt.\p"
	.string "Wir beide hielten den Titel viele Male\n"
	.string "und spornten uns ständig gegenseitig\l"
	.string "an, besser zu werden.\p"
	.string "Aber heute… Heute ist der Tag von\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Komm, CHAMP. Halten wir diesen Moment\n"
	.string "in der RUHMESHALLE fest!$"

SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	map_script_2 VAR_TEMP_1, 1, SootopolisCity_Gym_1F_EventScript_TryRematchReward
	.2byte 0

SootopolisCity_Gym_1F_EventScript_TryRematchReward::
	setvar VAR_TEMP_1, 0
	goto_if_set FLAG_GOT_JUAN_REMATCH_REWARD, SootopolisCity_Gym_1F_EventScript_TryRematchRewardEnd
	setvar 0x8005, TRAINER_JUAN_3
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_GiveRematchReward
SootopolisCity_Gym_1F_EventScript_TryRematchRewardEnd::
	ClearTrainerFlag TRAINER_JUAN_5
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_WallaceDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_Wallace::
	trainerbattle_single TRAINER_WALLACE_1, SootopolisCity_Gym_1F_Text_WallaceIntro, SootopolisCity_Gym_1F_Text_WallaceDefeat, SootopolisCity_Gym_1F_EventScript_WallaceDefeated, NO_MUSIC
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_WallaceDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadgeWallace
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	settrainerflag TRAINER_JUAN_1
	setflag FLAG_ENABLE_NORMAN_REMATCH_CALL
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	goto_if_set FLAG_SOOTOPOLIS_CITY_RIVAL_PROFESSOR, SootopolisCity_Gym_1F_EventScript_SootopolisDoneRivalScene1
	setvar VAR_SOOTOPOLIS_CITY_STATE, 7
	goto SootopolisCity_Gym_1F_EventScript_SootopolisDoneRivalScene2
SootopolisCity_Gym_1F_EventScript_SootopolisDoneRivalScene1::
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
SootopolisCity_Gym_1F_EventScript_SootopolisDoneRivalScene2::
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	goto_if_set FLAG_GOT_JUAN_REMATCH_REWARD, SootopolisCity_Gym_1F_EventScript_JuanRematchContinue
	setvar 0x8005, TRAINER_JUAN_3
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_GiveRematchReward
SootopolisCity_Gym_1F_EventScript_JuanRematchContinue::
	setvar VAR_TEMP_1, 1
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	release
	end
SootopolisCity_Gym_1F_EventScript_GiveRematchReward::
	msgbox SootopolisCity_Gym_1F_Text_JuanGiveRematchReward, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_DRAGON_SCALE, 1
	waitfanfare
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_Gym_1F_EventScript_NoRoom
	msgbox SootopolisCity_Gym_1F_Text_GaveReward, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GOT_JUAN_REMATCH_REWARD
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end
SootopolisCity_Gym_1F_EventScript_NoRoom::
	msgbox SootopolisCity_Gym_1F_Text_NoRoomForReward, MSGBOX_DEFAULT
	closemessage
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_1F_EventScript_GymGuidePostGame
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostGame::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostGame, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_1F_EventScript_GymStatueJuanCertified
	msgbox SootopolisCity_Gym_1F_Text_GymStatueWallaceCertified, MSGBOX_DEFAULT
	releaseall
	end
SootopolisCity_Gym_1F_EventScript_GymStatueJuanCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueJuanCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
	.string "Na, CHAMP in spe!\n"
	.string "Unglaublich, wie weit du gekommen bist!\p"
	.string "Bist du bereit, die Sache zu Ende zu\n"
	.string "bringen?\p"
	.string "ARENALEITER WASSILI in XENEROVILLE\n"
	.string "ist der Meister der WASSER-POKéMON\l"
	.string "und aller schönen Dinge.\p"
	.string "Du hast schon gegen WASSER-POKéMON\n"
	.string "gekämpft, aber WASSILI spielt in einer\l"
	.string "ganz anderen Liga.\p"
	.string "Wenn WASSILI kämpft, zeigt er eine\n"
	.string "Anmut, die nur wenige TRAINER\l"
	.string "besitzen.\p"
	.string "Viele halten ihn für so stark wie die\n"
	.string "TOP VIER.\p"
	.string "Manche sagen sogar…\n"
	.string "Ach, das ist nicht wichtig.\p"
	.string "{PLAYER}!\n"
	.string "Ich weiß, dass du das schaffst!$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
	.string "Hui! Du hast WASSILI besiegt, von dem\n"
	.string "man sagt, er sei der Beste in HOENN.\p"
	.string "{PLAYER}! Es war mir eine Ehre!\p"
	.string "Es ist Zeit für dich, die POKéMON LIGA\n"
	.string "herauszufordern!\p"
	.string "Ich kann nicht mitkommen, aber du\n"
	.string "sollst wissen, dass ich dir die Daumen\l"
	.string "drücke!$"

SootopolisCity_Gym_1F_Text_GymGuidePostGame:
	.string "Hui! Du bist so weit gekommen,\n"
	.string "{PLAYER}!\p"
	.string "Als CHAMP von HOENN hast du bereits\n"
	.string "den Gipfel erreicht!\p"
	.string "Ein Kampf gegen JUAN, den neuen LEITER\n"
	.string "dieser ARENA, ist eine echte Prüfung\l"
	.string "deines Könnens!$"

SootopolisCity_Gym_1F_Text_JuanIntro:
	.string "Lass mich dich was fragen.\n"
	.string "Wusstest du das schon? Ach, ich\l"
	.string "sollte nicht so schüchtern sein.\p"
	.string "Ich habe WASSILI alles beigebracht,\n"
	.string "was man über POKéMON wissen muss.\p"
	.string "Und dann habe ich mein Amt als\n"
	.string "ARENALEITER aufgegeben.\p"
	.string "Ich habe die ARENA an WASSILI\n"
	.string "übergeben.\p"
	.string "Doch es gab einen zwingenden Grund für\n"
	.string "mich, zurückzukehren.\p"
	.string "Genug geredet.\n"
	.string "Lass uns kämpfen.\p"
	.string "Du sollst Zeuge unserer\n"
	.string "Kunstfertigkeit werden.\p"
	.string "Eine Illusion aus Wasser, geformt von\n"
	.string "meinen POKéMON und mir.$"

SootopolisCity_Gym_1F_Text_WallaceIntro:
	.string "Gestatte, dass ich mich in aller Form\n"
	.string "vorstelle.\p"
	.string "Ich bin WASSILI.\n"
	.string "Der ARENALEITER von XENEROVILLE.\p"
	.string "Du hast etwas an dir…\n"
	.string "Eine veränderte Ausstrahlung.\p"
	.string "Ich glaube, ich spüre es bei dir.\p"
	.string "Was oben auf dem HIMMELTURM geschehen\n"
	.string "ist und was du getan hast, werde ich\l"
	.string "wohl in unserem Kampf erfahren.\p"
	.string "Nun zeig es mir. Zeig mir die Kraft,\n"
	.string "die du mit deinen POKéMON entfesselst.\p"
	.string "Ich werde dir im Gegenzug eine\n"
	.string "Vorstellung von Illusionen aus Wasser\l"
	.string "darbieten, geformt von meinen POKéMON\l"
	.string "und mir!$"

@ NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for
@ the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs
@ after, as well as the otherwise unused array after that. One wonders if that's the reason for
@ the existence of that unused array of ints.
SootopolisCity_Gym_1F_Text_JuanDefeat:
	.string "Ahahahaha, ausgezeichnet!\n"
	.string "Sehr schön! Du hast gewonnen!\p"
	.string "Ich weiß, dein brillantes Talent wird\n"
	.string "jeden Gegner bezwingen.\p"
	.string "Aber im Vergleich zu mir oder auch\n"
	.string "WASSILI fehlt es dir an Eleganz.\p"
	.string "Vielleicht sollte ich dir ein paar meiner\n"
	.string "Kleidungsstücke leihen?\p"
	.string "… … … … …\n"
	.string "…\l"
	.string "… … … … …\l"
	.string "…\p"
	.string "Hahahaha, ich hab nur Spaß gemacht!\p"
	.string "Statt meiner Kleidung überreiche ich\n"
	.string "dir den SCHAUERORDEN.$"

SootopolisCity_Gym_1F_Text_WallaceDefeat:
	.string "Bravo.\p"
	.string "Nun erkenne ich, wie echt und großartig\n"
	.string "du als POKéMON-TRAINER bist.\p"
	.string "Es erfüllt mich mit großer Freude, dich\n"
	.string "und deine POKéMON getroffen zu haben.\p"
	.string "Du hast dich des SCHAUERORDENs als\n"
	.string "würdig erwiesen. Nimm ihn an.$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
	.string "{PLAYER} erhält den SCHAUERORDEN\n"
	.string "von JUAN.$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadgeWallace:
	.string "{PLAYER} erhält den SCHAUERORDEN\n"
	.string "von WASSILI.$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
	.string "Dieser ORDEN sorgt dafür, dass dir alle\n"
	.string "deine POKéMON gehorchen.\p"
	.string "Der ORDEN befähigt dich außerdem dazu,\n"
	.string "mit der VM KASKADE Wasserfälle in jede\l"
	.string "Richtung zu passieren.\p"
	.string "Und damit du unseren Kampf stets in\n"
	.string "Erinnerung behältst, gebe ich dir dies…$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
	.string "Diese TM enthält AQUAWELLE.\p"
	.string "Damit kann das gegnerische POKéMON\n"
	.string "mit Ultraschallwellen verwirrt werden.\p"
	.string "… … … … … …$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
	.string "ARENALEITER JUAN wurde im POKéNAV-\n"
	.string "Verzeichnis eingetragen.$"

SootopolisCity_Gym_1F_Text_RegisteredWallace:
	.string "ARENALEITER WASSILI wurde im POKéNAV-\n"
	.string "Verzeichnis eingetragen.$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
	.string "TRAINER, die alle ORDEN der ARENen in\n"
	.string "HOENN erhalten haben, sollten sich…\p"
	.string "auf den Weg zur ultimativen Heraus-\n"
	.string "forderung machen. Der POKéMON LIGA!\p"
	.string "Reise zu den östlichsten Gebieten von\n"
	.string "HOENN, zur Insel PRACHTPOLIS CITY.\l"
	.string "Dort findest du die POKéMON LIGA.$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
	.string "In HOENN gibt es nur noch einen ORDEN\n"
	.string "zu verdienen.\p"
	.string "Wenn du die POKéMON LIGA herausfordern\n"
	.string "willst, musst du zuerst den ORDEN der\l"
	.string "ARENA in BAUMHAUSEN CITY bekommen.$"

SootopolisCity_Gym_1F_Text_GymStatue:
	.string "POKéMON ARENA von XENEROVILLE$"

SootopolisCity_Gym_1F_Text_GymStatueWallaceCertified:
	.string "POKéMON ARENA von XENEROVILLE\p"
	.string "WASSILIs ANERKANNTE TRAINER:\n"
	.string "{PLAYER}$"

SootopolisCity_Gym_1F_Text_GymStatueJuanCertified:
	.string "POKéMON ARENA von XENEROVILLE\p"
	.string "JUANS ANERKANNTE TRAINER:\n"
	.string "{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
	.string "JUAN: Ah, diese ARENA strahlt wieder die\n"
	.string "alte Heiterkeit aus…\p"
	.string "Doch da kommt unser junger Wirbelwind,\n"
	.string "um ihr Wasser erneut aufzuwühlen!\p"
	.string "Sicher doch, sicher doch.\p"
	.string "Es ist mir eine Freude, mit dir immer und\n"
	.string "immer wieder über das Wasser zu gleiten.$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
	.string "Ahahaha, du hast gewonnen!\n"
	.string "Du hast mich besiegt.$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
	.string "JUAN: Wenn ich dich frage, ob du mein\n"
	.string "Schüler werden willst, wirst du bestimmt\l"
	.string "ablehnen.\p"
	.string "Ich würde dir stattdessen gerne meinen\n"
	.string "Mantel schenken.\p"
	.string "Aber auch den würdest du bestimmt\n"
	.string "ablehnen.\p"
	.string "Und das, Wirbelwind, ist ein Zeichen\n"
	.string "von hohen Idealen.$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
	.string "JUAN: Ah, diese ARENA strahlt wieder die\n"
	.string "alte Heiterkeit aus…\p"
	.string "Doch da kommt unser junger Wirbelwind,\n"
	.string "um ihr Wasser erneut aufzuwühlen!\p"
	.string "Sicher doch, sicher doch.\p"
	.string "Es ist mir eine Freude, mit dir immer und\n"
	.string "immer wieder über das Wasser zu gleiten.\p"
	.string "Aber nein, nein, nein, nein.\n"
	.string "Du hast ja nur ein einziges POKéMON.\p"
	.string "Ich wünsche, dass du mit mindestens\n"
	.string "zwei POKéMON wiederkommst und dann\l"
	.string "gegen mich antrittst.$"

SootopolisCity_Gym_1F_Text_JuanGiveRematchReward:
	.string "Ah, wahrlich prächtig, {PLAYER}.\n"
	.string "Deine Vorstellung war geradezu\l"
	.string "bezaubernd.\p"
	.string "Zu Ehren dieses bemerkenswerten\n"
	.string "Kampfes möchte ich dir ein seltenes\l"
	.string "Item schenken, das mir sehr am Herzen\l"
	.string "liegt.$"

SootopolisCity_Gym_1F_Text_NoRoomForReward:
	.string "Ah, dein BEUTEL scheint randvoll\n"
	.string "zu sein.\p"
	.string "Keine Sorge, ich bewahre es sicher auf,\n"
	.string "bis du Platz dafür geschaffen hast.$"

SootopolisCity_Gym_1F_Text_GaveReward:
	.string "Diese DRACHENHAUT verkörpert die Würde\n"
	.string "und die Kraft der Drachen, ganz wie\l"
	.string "mein SEEDRAKING, das ich mit viel\l"
	.string "Sorgfalt trainiert habe.\p"
	.string "Möge sie dir auf deiner Reise gute\n"
	.string "Dienste leisten.$"

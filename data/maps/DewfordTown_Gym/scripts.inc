DewfordTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DewfordTown_Gym_OnFrame
	.byte 0

DewfordTown_Gym_OnFrame:
	map_script_2 VAR_TEMP_1, 1, DewfordTown_Gym_EventScript_TryRematchReward
	.2byte 0

DewfordTown_Gym_EventScript_TryRematchReward::
	setvar VAR_TEMP_1, 0
	goto_if_set FLAG_GOT_BRAWLY_REMATCH_REWARD, DewfordTown_Gym_EventScript_TryRematchRewardEnd
	setvar 0x8005, TRAINER_BRAWLY_3
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_GiveRematchReward
DewfordTown_Gym_EventScript_TryRematchRewardEnd::
	ClearTrainerFlag TRAINER_BRAWLY_5
	releaseall
	end

DewfordTown_Gym_OnTransition:
	call DewfordTown_Gym_EventScript_SetFlashLevel
	end

DewfordTown_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
	goto_if_defeated TRAINER_BRAWLY_1_2, DewfordTown_Gym_EventScript_SetLightsOn
	goto_if_defeated TRAINER_BRAWLY_1_3, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
	goto DewfordTown_Gym_EventScript_SetFlashLevel1

DewfordTown_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest
DewfordTown_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

DewfordTown_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

DewfordTown_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

DewfordTown_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

DewfordTown_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

DewfordTown_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest
DewfordTown_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

DewfordTown_Gym_EventScript_BrightenRoom::
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange::
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrendan
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrendan::
	goto_if_not_defeated TRAINER_BRENDAN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers::
	return

DewfordTown_Gym_EventScript_Brawly::
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_DoBrawly1
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, DewfordTown_Gym_EventScript_BeatFlannery
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, DewfordTown_Gym_EventScript_BeatWattson
DewfordTown_Gym_EventScript_DoBrawly1::
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	goto DewfordTown_Gym_EventScript_ContinueBrawly
DewfordTown_Gym_EventScript_BeatWattson::
	trainerbattle_single TRAINER_BRAWLY_1_2, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	goto DewfordTown_Gym_EventScript_ContinueBrawly
DewfordTown_Gym_EventScript_BeatFlannery::
	trainerbattle_single TRAINER_BRAWLY_1_3, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
DewfordTown_Gym_EventScript_ContinueBrawly::
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated::
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	settrainerflag TRAINER_BRAWLY_1
	settrainerflag TRAINER_BRAWLY_1_2
	settrainerflag TRAINER_BRAWLY_1_3
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	return

DewfordTown_Gym_EventScript_GiveBulkUp2:
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch::
	goto_if_set FLAG_GOT_BRAWLY_REMATCH_REWARD, DewfordTown_Gym_EventScript_BrawlyRematchContinue
	setvar 0x8005, TRAINER_BRAWLY_3
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_GiveRematchReward
DewfordTown_Gym_EventScript_BrawlyRematchContinue::
	setvar VAR_TEMP_1, 1
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	release
	end
DewfordTown_Gym_EventScript_GiveRematchReward::
	msgbox DewfordTown_Gym_Text_BrawlyGiveRematchReward, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_BRICK_PIECE, 1
	waitfanfare
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_Gym_EventScript_NoRoom
	msgbox DewfordTown_Gym_Text_GaveReward, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GOT_BRAWLY_REMATCH_REWARD
	release
	end
DewfordTown_Gym_EventScript_NoRoom::
	msgbox DewfordTown_Gym_Text_NoRoomForReward, MSGBOX_DEFAULT
	closemessage
	release
	end

DewfordTown_Gym_Text_BrawlyGiveRematchReward:
	.string "Huihuihui, {PLAYER}!\n"
	.string "Das war ein heftiger Kampf!\p"
	.string "Hinter deinen Attacken steckt echt\n"
	.string "ordentlich Kraft.\p"
	.string "Zu Ehren deiner Stärke möchte ich dir\n"
	.string "diesen ZIEGELSTEIN schenken.$"

DewfordTown_Gym_Text_NoRoomForReward:
	.string "Oh, dein BEUTEL scheint voll zu sein.\p"
	.string "Schaffe etwas Platz, dann bewahre ich\n"
	.string "das für dich auf, bis du wiederkommst.$"

DewfordTown_Gym_Text_GaveReward:
	.string "Das ist ein Stück eines uralten Relikts,\n"
	.string "genau wie die Entschlossenheit, die du\l"
	.string "in unserem Kampf gezeigt hast!$"

DewfordTown_Gym_EventScript_Takao::
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn::
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brendan::
	trainerbattle_single TRAINER_BRENDAN, DewfordTown_Gym_Text_BrendanIntro, DewfordTown_Gym_Text_BrendanDefeat, DewfordTown_Gym_EventScript_BrendanBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendanPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendanBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian::
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Kenji::
	trainerbattle_single TRAINER_KENJI, DewfordTown_Gym_Text_KenjiIntro, DewfordTown_Gym_Text_KenjiDefeat
	msgbox DewfordTown_Gym_Text_KenjiPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Lilith::
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory::
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified::
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue::
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice:
	.string "Na, wie sieht es aus, auf dem Weg zum\n"
	.string "CHAMP, {PLAYER}?\p"
	.string "FAUSTAUHAVENs ARENALEITER KAMILLO\n"
	.string "besitzt KAMPF-POKéMON.\p"
	.string "Wenn du dort NORMAL-POKéMON antreten\n"
	.string "lässt, sind Probleme vorprogrammiert!\p"
	.string "FLUG- und PSYCHO-POKéMON schlagen sich\n"
	.string "gut, sollten aber trotzdem aufpassen!\p"
	.string "Sein erstes POKéMON legt es gleich auf\n"
	.string "ein K.O. an!\p"
	.string "Und auch wenn sein stärkstes POKéMON\n"
	.string "kurze Arme hat, ist es nicht schwach!\p"
	.string "Es dürfte eines der schlagkräftigsten\n"
	.string "POKéMON der ganzen LIGA sein!\p"
	.string "Mit jedem besiegten TRAINER wird die\n"
	.string "ARENA heller! Du schaffst das!$"

DewfordTown_Gym_Text_GymGuidePostVictory:
	.string "Huuh!\n"
	.string "Hier ist es aber hell geworden!\p"
	.string "Deine Zukunft wird strahlend hell sein!$"

DewfordTown_Gym_Text_TakaoIntro:
	.string "Die Macht bestimmt alles!\n"
	.string "Komm schon!$"

DewfordTown_Gym_Text_TakaoDefeat:
	.string "Nicht genug Macht…$"

DewfordTown_Gym_Text_TakaoPostBattle:
	.string "Gegen dein Talent ist meine Macht\n"
	.string "machtlos. Deine Technik ist super!$"

DewfordTown_Gym_Text_JocelynIntro:
	.string "Man muss doch KAMILLO nicht mit so\n"
	.string "etwas Nichtigem belästigen!\p"
	.string "Ich mache dich fertig!$"

DewfordTown_Gym_Text_JocelynDefeat:
	.string "Aber… Wie…?\n"
	.string "Wie konnte ich nur so schnell verlieren?$"

DewfordTown_Gym_Text_JocelynPostBattle:
	.string "Ich werde diese Niederlage nicht ab-\n"
	.string "haken. Sie wird mich beim Training\l"
	.string "motivieren!\p"
	.string "Eines Tages werde ich auch ein\n"
	.string "ARENALEITER sein!\p"
	.string "Nein! Ich werde der CHAMP der\n"
	.string "POKéMON LIGA!$"

DewfordTown_Gym_Text_LauraIntro:
	.string "Du forderst mich heraus? Dann wundere\n"
	.string "dich nicht, wenn du weinst wie ein Baby!$"

DewfordTown_Gym_Text_LauraDefeat:
	.string "Waaaaahaaaaaa!\n"
	.string "Schluchz! Schnief! Ich habe verloooren!$"

DewfordTown_Gym_Text_LauraPostBattle:
	.string "Ich kämpfe im Dunkeln, das macht mich\n"
	.string "mutiger und trainiert mein Herz.\p"
	.string "Weil es hier so dunkel ist, habe ich noch\n"
	.string "nie das Gesicht von KAMILLO gesehen.$"

DewfordTown_Gym_Text_LilithIntro:
	.string "Huhuhu…\n"
	.string "Was stolperst du im Dunklen herum?$"

DewfordTown_Gym_Text_LilithDefeat:
	.string "Ach, du… Ich habe kein\n"
	.string "Interesse, dich kennen zu lernen.$"

DewfordTown_Gym_Text_LilithPostBattle:
	.string "Du verdienst eine Niederlage, damit du\n"
	.string "wieder von vorne anfangen musst.$"

DewfordTown_Gym_Text_BrendanIntro:
	.string "Ich zeige dir, wie viel Köpfchen ein\n"
	.string "Seemann hat!$"

DewfordTown_Gym_Text_BrendanDefeat:
	.string "Wie konnte das nur passieren? Es ist\n"
	.string "nicht meine Art, einfach zu verlieren.$"

DewfordTown_Gym_Text_BrendanPostBattle:
	.string "Ahoi! Du bist es wert, unserem\n"
	.string "ARENALEITER vorgestellt zu werden.$"

DewfordTown_Gym_Text_CristianIntro:
	.string "Wenn du hier vorbei willst, musst du\n"
	.string "erst an mir vorbei!$"

DewfordTown_Gym_Text_CristianDefeat:
	.string "Grrrr!\n"
	.string "Ich wurde einfach überwältigt!$"

DewfordTown_Gym_Text_CristianPostBattle:
	.string "Du hast gewonnen!\n"
	.string "Hol dir den ORDEN!$"

DewfordTown_Gym_Text_KenjiIntro:
	.string "Du wagst es, mich im Dunkeln zu fordern?\n"
	.string "Mal sehen, ob dein Geist hell strahlt!$"

DewfordTown_Gym_Text_KenjiDefeat:
	.string "Argh… Mein Training\n"
	.string "hat nicht gereicht…$"

DewfordTown_Gym_Text_KenjiPostBattle:
	.string "Selbst im Dunkeln spüre ich deine Kraft.\n"
	.string "Du hast dir den Weg nach vorn verdient.$"

DewfordTown_Gym_Text_BrawlyIntro:
	.string "Ich bin KAMILLO!\n"
	.string "Der ARENALEITER von FAUSTAUHAVEN!\p"
	.string "Ich habe die wilden Strudel dieser\n"
	.string "Gegend gemeistert und bin in dieser\l"
	.string "pechschwarzen Höhle stark geworden.\p"
	.string "Du willst mich wirklich herausfordern?\n"
	.string "Dann zeig mir, woraus du gemacht bist!$"

DewfordTown_Gym_Text_BrawlyDefeat:
	.string "Huihuihui! Du hast eine größere Welle\n"
	.string "produziert, als ich dir zugetraut hätte.\p"
	.string "Du hast mich absaufen lassen!\p"
	.string "Okay, du hast mich erwischt!\n"
	.string "Nimm den ORDEN dieser ARENA!$"

DewfordTown_Gym_Text_ReceivedKnuckleBadge:
	.string "{PLAYER} erhält den KNÖCHELORDEN von\n"
	.string "KAMILLO.$"

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
	.string "Dank des KNÖCHELORDENs werden dir alle\n"
	.string "POKéMON bis Level 33 gehorchen, auch\l"
	.string "die, die du durch Tausch erhalten hast.\p"
	.string "Und du kannst die VM BLITZ auch\n"
	.string "außerhalb eines Kampfes anwenden.\p"
	.string "Und wenn du magst, kannst du auch diese\n"
	.string "TECHNISCHE MASCHINE anwenden.$"

DewfordTown_Gym_Text_ExplainBulkUp:
	.string "Die TM08 enthält PROTZER.\p"
	.string "Diese Attacke hebt den Status des\n"
	.string "ANGRIFFs und der VERTEIDIGUNG.\p"
	.string "… … … … … …$"

DewfordTown_Gym_Text_RegisteredBrawly:
	.string "ARENALEITER KAMILLO wurde\n"
	.string "im POKéNAV eingetragen.$"

DewfordTown_Gym_Text_BrawlyPostBattle:
	.string "Ich sehe in dir ein Talent, das eines\n"
	.string "Tages zu einer riesigen Welle wird und\l"
	.string "einen Sturm des Erstaunens bei anderen\l"
	.string "TRAINERn entfachen wird!$"

DewfordTown_Gym_Text_GymStatue:
	.string "POKéMON ARENA von FAUSTAUHAVEN$"

DewfordTown_Gym_Text_GymStatueCertified:
	.string "POKéMON ARENA von FAUSTAUHAVEN\p"
	.string "KAMILLOS ANERKANNTE TRAINER:\n"
	.string "{PLAYER}$"

DewfordTown_Gym_Text_BrawlyPreRematch:
	.string "KAMILLO: Eine Welle kann sich zurück-\n"
	.string "ziehen, wird aber immer wieder an\l"
	.string "Land zurückkommen.\p"
	.string "Ein riesiges Talent wie du…\n"
	.string "Ich wusste, du würdest wiederkommen.\p"
	.string "Zeig mir, wie gut du geworden bist.$"

DewfordTown_Gym_Text_BrawlyRematchDefeat:
	.string "Und wieder wurde ich fortgespült.$"

DewfordTown_Gym_Text_BrawlyPostRematch:
	.string "KAMILLO: Kämpfe sind wild und tief wie\n"
	.string "die See. Du siehst kein Land.\l"
	.string "Wie das Meer um HOENN.$"

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
	.string "KAMILLO: Eine Welle kann sich zurück-\n"
	.string "ziehen, wird aber immer wieder an\l"
	.string "Land zurückkommen.\p"
	.string "Ein riesiges Talent wie du…\n"
	.string "Ich wusste, du würdest wiederkommen.\p"
	.string "Oh, du hast ja nur ein POKéMON, das\n"
	.string "kämpfen kann.\p"
	.string "Tut mir leid, aber ich trete nur gegen\n"
	.string "dich an, wenn du mindestens zwei\l"
	.string "POKéMON hast.$"

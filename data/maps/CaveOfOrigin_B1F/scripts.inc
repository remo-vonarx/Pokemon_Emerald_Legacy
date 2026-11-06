.set LOCALID_WALLACE, 1
.set LOCALID_CRAIG, 2
.set LOCALID_SMITH, 3
.set LOCALID_WEEBRA, 4

CaveOfOrigin_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveOfOrigin_B1F_OnFrame
	.byte 0

CaveOfOrigin_B1F_OnFrame:
	map_script_2 VAR_TEMP_1, 1, CaveOfOrigin_B1F_EventScript_CheckBeatSmith
	map_script_2 VAR_TEMP_1, 2, CaveOfOrigin_B1F_EventScript_CheckBeatCraig
	map_script_2 VAR_TEMP_1, 3, CaveOfOrigin_B1F_EventScript_CheckBeatWeebra
	.2byte 0

CaveOfOrigin_B1F_EventScript_Smith::
	setvar VAR_TEMP_1, 1
	trainerbattle_single TRAINER_SMITH, CaveOfOrigin_B1F_Text_SmithIntro, CaveOfOrigin_B1F_Text_SmithDefeated
CaveOfOrigin_B1F_EventScript_SmithPostBattle::
	msgbox CaveOfOrigin_B1F_Text_SmithPostBattle, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SMITH
	goto_if_set FLAG_RECEIVED_REGIROCK_DOLL CaveOfOrigin_B1F_EventScript_End
	givedecoration DECOR_REGIROCK_DOLL
	goto_if_eq VAR_RESULT, FALSE, CaveOfOrigin_B1F_EventScript_NoRoomForDeco
	msgbox CaveOfOrigin_B1F_Text_SmithPostBattle2, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_REGIROCK_DOLL
	fadescreen FADE_TO_BLACK
	special Script_FadeOutMapMusic
	removeobject LOCALID_SMITH
	setflag FLAG_HIDE_SMITH
	fadescreen FADE_FROM_BLACK
	release
	end
CaveOfOrigin_B1F_EventScript_CheckBeatSmith::
	setvar VAR_TEMP_1, 0
	goto_if_set FLAG_DEFEATED_SMITH, CaveOfOrigin_B1F_EventScript_End
	setvar 0x8005, TRAINER_SMITH
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, CaveOfOrigin_B1F_EventScript_SmithPostBattle
	release
	end

CaveOfOrigin_B1F_EventScript_Craig::
	setvar VAR_TEMP_1, 2
	trainerbattle_single TRAINER_CRAIG, CaveOfOrigin_B1F_Text_CraigIntro, CaveOfOrigin_B1F_Text_CraigDefeated
CaveOfOrigin_B1F_EventScript_CraigPostBattle::
	msgbox CaveOfOrigin_B1F_Text_CraigPostBattle, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_CRAIG
	goto_if_set FLAG_RECEIVED_REGISTEEL_DOLL CaveOfOrigin_B1F_EventScript_End
	givedecoration DECOR_REGISTEEL_DOLL
	goto_if_eq VAR_RESULT, FALSE, CaveOfOrigin_B1F_EventScript_NoRoomForDeco
	setflag FLAG_RECEIVED_REGISTEEL_DOLL
	fadescreen FADE_TO_BLACK
	special Script_FadeOutMapMusic
	removeobject LOCALID_CRAIG
	setflag FLAG_HIDE_CRAIG
	addobject LOCALID_WEEBRA
	clearflag FLAG_HIDE_WEEBRA
	fadescreen FADE_FROM_BLACK
	release
	end
CaveOfOrigin_B1F_EventScript_CheckBeatCraig::
	setvar VAR_TEMP_1, 0
	goto_if_set FLAG_DEFEATED_CRAIG, CaveOfOrigin_B1F_EventScript_End
	setvar 0x8005, TRAINER_CRAIG
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, CaveOfOrigin_B1F_EventScript_CraigPostBattle
	release
	end

CaveOfOrigin_B1F_EventScript_Weebra::
	setvar VAR_TEMP_1, 3
	trainerbattle_single TRAINER_WEEBRA, CaveOfOrigin_B1F_Text_WeebraIntro, CaveOfOrigin_B1F_Text_WeebraDefeated
CaveOfOrigin_B1F_EventScript_WeebraPostBattle::
	msgbox CaveOfOrigin_B1F_Text_WeebraPostBattle, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_WEEBRA
	goto_if_set FLAG_RECEIVED_REGICE_DOLL CaveOfOrigin_B1F_EventScript_End
	givedecoration DECOR_REGICE_DOLL
	goto_if_eq VAR_RESULT, FALSE, CaveOfOrigin_B1F_EventScript_NoRoomForDeco
	setflag FLAG_RECEIVED_REGICE_DOLL
	fadescreen FADE_TO_BLACK
	special Script_FadeOutMapMusic
	removeobject LOCALID_WEEBRA
	setflag FLAG_HIDE_WEEBRA
	addobject LOCALID_SMITH
	clearflag FLAG_HIDE_SMITH
	fadescreen FADE_FROM_BLACK
	release
	end
CaveOfOrigin_B1F_EventScript_CheckBeatWeebra::
	setvar VAR_TEMP_1, 0
	goto_if_set FLAG_DEFEATED_WEEBRA, CaveOfOrigin_B1F_EventScript_End
	setvar 0x8005, TRAINER_WEEBRA
	special HasRematchBeenFought
	goto_if_eq VAR_RESULT, TRUE, CaveOfOrigin_B1F_EventScript_WeebraPostBattle
	release
	end

CaveOfOrigin_B1F_EventScript_NoRoomForDeco::
	msgbox CaveOfOrigin_B1F_Text_NoRoomForDeco, MSGBOX_DEFAULT
CaveOfOrigin_B1F_EventScript_End::
	release
	end

CaveOfOrigin_B1F_Text_SmithIntro:
	.string "Hey! Was geht?\n"
	.string "Zeig mal, wie viel Pep du hast!$"

CaveOfOrigin_B1F_Text_SmithDefeated:
	.string "Du hast den Pep der Götter!$"

CaveOfOrigin_B1F_Text_SmithPostBattle:
	.string "Beeindruckend! Du hast mich trotz all\n"
	.string "meiner Lieblinge besiegt!\p"
	.string "Als Zeichen meines Respekts möchte ich\n"
	.string "dir das hier schenken. Es bringt zwar\l"
	.string "nichts, sieht aber cool aus!$"

CaveOfOrigin_B1F_Text_SmithPostBattle2:
	.string "Peace, du Nerd!$"

CaveOfOrigin_B1F_Text_CraigIntro:
	.string "Es heißt, nur wenige dürfen hier\n"
	.string "eintreten, und doch… Ich durfte es.\p"
	.string "Warum, fragst du?\n"
	.string "Nun, das ist ein Geheimnis.\p"
	.string "Lass uns stattdessen kämpfen. Von dir\n"
	.string "bekomme ich sicher interessante Daten.$"

CaveOfOrigin_B1F_Text_CraigDefeated:
	.string "Das sind gute Daten!\n"
	.string "Die kann ich gebrauchen.$"

CaveOfOrigin_B1F_Text_CraigPostBattle:
	.string "Weißt du, die meisten würden nicht\n"
	.string "glauben, dass ich hier rein durfte.\p"
	.string "Hier, nimm das als Andenken an unseren\n"
	.string "Kampf. Eine Kleinigkeit von…\l"
	.string "verborgenen Orten.$"

CaveOfOrigin_B1F_Text_WeebraIntro:
	.string "Eindringlinge! Schlagt Alarm! So heißt\n"
	.string "der Text doch, oder?$"

CaveOfOrigin_B1F_Text_WeebraDefeated:
	.string "Da ist wohl endlich jemand aus dem\n"
	.string "Käfig ausgebrochen…$"

CaveOfOrigin_B1F_Text_WeebraPostBattle:
	.string "Wie auch immer - so eine coole Socke\n"
	.string "braucht was Passendes…$"

CaveOfOrigin_B1F_Text_NoRoomForDeco:
	.string "Du hast wohl gerade keinen Platz mehr\n"
	.string "für weitere Dekorationen.\p"
	.string "Schaffe etwas Platz und komm später\n"
	.string "wieder!$"

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ah, du bist also {PLAYER}{KUN}?\p"
	.string "Ich habe schon wunderbare Geschichten\n"
	.string "von deinen Heldentaten gehört.\p"
	.string "Ich heiße WASSILI.\p"
	.string "Als ARENALEITER von XENEROVILLE habe\n"
	.string "ich mein Leben lang seine Geheimnisse\l"
	.string "und seine Schönheit ergründet.\p"
	.string "Und nun stehen wir hier…\n"
	.string "inmitten einer Legende.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "GROUDON und KYOGRE… Welch eine Macht!\p"
	.string "Doch laut den uralten Felszeichnungen\n"
	.string "hier in der URZEITHÖHLE gibt es noch\l"
	.string "ein weiteres Wesen.\p"
	.string "Ein heiliges POKéMON, das in den\n"
	.string "Legenden DRACHENGOTT genannt wird.\p"
	.string "Es heißt, in Zeiten der Not sei dieses\n"
	.string "ätherische Wesen vom Himmel\l"
	.string "herabgestiegen, um das Chaos zu beenden.\p"
	.string "Ich glaube, dass die Suche nach diesem\n"
	.string "DRACHENGOTT unsere einzige\l"
	.string "Hoffnung ist.\p"
	.string "Der HIMMELTURM, ein Monument seiner\n"
	.string "Majestät, wartet an der ROUTE 131.\p"
	.string "Ich bin sicher, dass wir dort die\n"
	.string "Antworten finden, die wir suchen.\p"
	.string "Ich habe die Felszeichnungen studiert,\n"
	.string "und endlich…\p"
	.string "Ich glaube, ich weiß nun, wie sich\n"
	.string "seine Geheimnisse lüften lassen.$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "WASSILI: Begleitest du mich,\n"
	.string "{PLAYER}{KUN}?\p"
	.string "Wir dürfen keine Zeit verlieren!\p"
	.string "Lass uns schnell zum HIMMELTURM gehen.\n"
	.string "Die Zeit drängt!\p"
	.string "Ich gehe voraus und bereite alles vor,\n"
	.string "um seinen Eingang zu öffnen.\p"
	.string "Bitte komm nach, so schnell du kannst.$"

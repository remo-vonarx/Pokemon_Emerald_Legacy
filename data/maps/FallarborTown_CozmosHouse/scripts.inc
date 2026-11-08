.set LOCALID_PROFCOZMO, 1

FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	goto_if_set FLAG_RECEIVED_AURORA_TICKET, FallarborTown_CozmosHouse_EventScript_GaveMeteorite_Continued
	setvar 0x8005, SPECIES_RAYQUAZA
	special CheckSpecies
	goto_if_eq VAR_RESULT, TRUE, EventScript_GotRayquaza

FallarborTown_CozmosHouse_EventScript_GaveMeteorite_Continued::
	goto_if_set FLAG_BATTLED_DEOXYS, FallarborTown_CozmosHouse_EventScript_ChangeDeoxysForm
	goto_if_set FLAG_DEFEATED_DEOXYS, FallarborTown_CozmosHouse_EventScript_ChangeDeoxysForm
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_ChangeDeoxysForm::
	goto_if_set FLAG_COZMO_CAUGHT_DEOXYS, FallarborTown_CozmosHouse_EventScript_ChangeDeoxysForm2
	setflag FLAG_COZMO_CAUGHT_DEOXYS
	msgbox FallarborTown_CozmosHouse_Text_CozmoSurprised, MSGBOX_DEFAULT
FallarborTown_CozmosHouse_EventScript_ChangeDeoxysForm2::
	msgbox ChangeDeoxysForm_Text_Beginning, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq ChangeDeoxysForm_Start
ChangeDeoxysForm_End:
	msgbox ChangeDeoxysForm_Text_End, MSGBOX_DEFAULT
	releaseall
	end

ChangeDeoxysForm_Start:
	msgbox ChangeDeoxysForm_Text_Select, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq ChangeDeoxysForm_End
	special TryChangeDeoxysForm
	compare VAR_RESULT, TRUE
	faceplayer
	goto_if_eq ChangeDeoxysForm_Success
	goto ChangeDeoxysForm_End

ChangeDeoxysForm_Success:
	playmoncry SPECIES_DEOXYS, 0
	msgbox ChangeDeoxysForm_Text_Success, MSGBOX_DEFAULT
	waitmoncry
	goto ChangeDeoxysForm_End

ChangeDeoxysForm_Text_Beginning:
	.string "Möchtest du sehen, was passiert, wenn\n"
	.string "wir es diesem METEORITen aussetzen?$"

ChangeDeoxysForm_Text_End:
	.string "Komm jederzeit wieder.$"

ChangeDeoxysForm_Text_Select:
	.string "Zeig mir dein DEOXYS.$"

ChangeDeoxysForm_Text_Success:
	.string "Das Experiment war ein Erfolg!\n"
	.string "Dein DEOXYS hat sich verwandelt!$"

FallarborTown_CozmosHouse_Text_CozmoSurprised:
	.string "PROF. KOSMO: Unglaublich! Du hast\n"
	.string "DEOXYS gefangen, nicht wahr?\p"
	.string "Ich habe den METEORITen untersucht,\n"
	.string "während du weg warst, und ich glaube,\l"
	.string "es gibt eine merkwürdige Verbindung\l"
	.string "zwischen ihm und DEOXYS.\p"
	.string "Spürst du das? Es ist, als ob sie…\n"
	.string "miteinander in Resonanz stünden.$"

EventScript_GotRayquaza::
	msgbox FallarborTown_CozmosHouse_Text_GotRayquaza, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 3   @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 5   @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_PROFCOZMO, LavaridgeTown_Movement_ProfCozmoFaceLeft
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, LavaridgeTown_Movement_ProfCozmoFaceRight
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, LavaridgeTown_Movement_ProfCozmoFaceLeft
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, LavaridgeTown_Movement_ProfCozmoWalkToCabinet
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, LavaridgeTown_Movement_ProfCozmoWalkToPlayer
	waitmovement 0
	applymovement LOCALID_PROFCOZMO, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FallarborTown_CozmosHouse_Text_GotRayquaza2, MSGBOX_DEFAULT
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, FallarborTown_CozmosHouse_EventScript_AuroraTicketBagFull
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_RECEIVED_AURORA_TICKET
	msgbox FallarborTown_CozmosHouse_Text_GotRayquaza3, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_CozmosHouse_EventScript_AuroraTicketBagFull:
	vmessage FallarborTown_CozmosHouse_Text_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_Movement_ProfCozmoWalkToCabinet:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_ProfCozmoWalkToPlayer:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

LavaridgeTown_Movement_ProfCozmoFaceLeft:
	face_left
	step_end

LavaridgeTown_Movement_ProfCozmoFaceRight:
	face_right
	step_end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_unset FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. KOSMO: Oh…\n"
	.string "Ich hätte mich nie dazu verleiten\l"
	.string "lassen dürfen, TEAM MAGMA zu verraten,\l"
	.string "wo METEORITen zu finden sind…\p"
	.string "Der METEORIT von den METEORFÄLLEn…\n"
	.string "Nun wird er niemals mir gehören…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "Oh!\n"
	.string "Oooh?\p"
	.string "Dieses Item…\p"
	.string "Kann es sein?\p"
	.string "Ist das der METEORIT, den TEAM MAGMA\n"
	.string "aus den METEORFÄLLEn entwendet hat?\p"
	.string "Bitte, darf ich den haben?\p"
	.string "Du bekommst auch etwas dafür.\n"
	.string "Was hältst du von dieser TM?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. KOSMO: Mit dieser TM möchte ich\n"
	.string "dir meine Dankbarkeit ausdrücken.\l"
	.string "Bitte, nimm sie an!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. KOSMO: Oh, ich kann es einfach\n"
	.string "nicht glauben! Das ist nett! So nett!!!\p"
	.string "Das wird mir bei meinen Forschungen\n"
	.string "enorm weiterhelfen!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. KOSMO: Oh, aber…\n"
	.string "Das enttäuscht mich jetzt maßlos…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. KOSMO: Bitte, darf ich den\n"
	.string "METEORITen haben?\p"
	.string "Ich möchte ihn nicht umsonst haben! Wie\n"
	.string "wäre es mit dieser TM im Tausch dafür?$"

FallarborTown_CozmosHouse_Text_GotRayquaza:
	.string "PROF. KOSMO: Oh je…\n"
	.string "Ist das… RAYQUAZA?!\p"
	.string "Du bist wirklich immer für eine\n"
	.string "Überraschung gut, {PLAYER}{KUN}.\p"
	.string "Warte, was ist das?\n"
	.string "Der METEORIT… Er reagiert…\l"
	.string "Er bebt! Aber warum?\p"
	.string "Das ist noch nie passiert…\p"
	.string "Kann es sein, dass RAYQUAZAs Gegenwart\n"
	.string "etwas auslöst?\p"
	.string "Moment…$"

FallarborTown_CozmosHouse_Text_GotRayquaza2:
	.string "Meine Geräte messen seismische\n"
	.string "Aktivität aus einem Gebiet namens\l"
	.string "ENTSTEHUNGSINSEL.\p"
	.string "Der Zeitpunkt kann kein Zufall sein…\n"
	.string "RAYQUAZAs Gegenwart muss damit zu\l"
	.string "tun haben.\p"
	.string "Hier, nimm das.$"

FallarborTown_CozmosHouse_Text_GotRayquaza3:
	.string "Dieses TICKET sollte dich zur\n"
	.string "ENTSTEHUNGSINSEL bringen. Du kannst\l"
	.string "es am Hafen von SEEGRASULB CITY\l"
	.string "einsetzen.\p"
	.string "Bitte, {PLAYER}{KUN},\n"
	.string "untersuche das für mich!\p"
	.string "Wir stehen vielleicht kurz vor einer\n"
	.string "bahnbrechenden Entdeckung!$"

FallarborTown_CozmosHouse_Text_AuroraTicketBagFull:
	.string "Oh, es tut mir leid, {PLAYER}! Die\n"
	.string "BASIS-ITEM-TASCHE in deinem\l"
	.string "BEUTEL ist voll.\l"
	.string "Lagere etwas auf deinem PC und\l"
	.string "komme anschließend zurück.$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "PROF. KOSMO ist unterwegs zu\n"
	.string "METEORFÄLLE an der ROUTE 114. Einige\l"
	.string "Leute von TEAM MAGMA begleiten ihn.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Armer PROF. KOSMO…\n"
	.string "Er ist so deprimiert… Er tut mir leid.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Schau dir nur PROF. KOSMO an…\n"
	.string "Er ist so glücklich! Richtig niedlich.$"

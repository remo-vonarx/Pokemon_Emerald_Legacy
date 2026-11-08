MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "Als ich noch jung war, bin ich als\n"
	.string "POKéMON-TRAINER durch die Welt\l"
	.string "gereist.\p"
	.string "Nun, da ich ein alter Knabe geworden\n"
	.string "bin, beobachte ich mit Freuden die\l"
	.string "jungen TRAINER bei ihren Kämpfen.$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "Diese Tür ist verschlossen.$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "Ein TRAINER namens {STR_VAR_1} ist\n"
	.string "bei mir zu Besuch.\p"
	.string "Möchtest du {STR_VAR_1}\n"
	.string "herausfordern?$"

RS_MysteryEventsHouse_Text_YouWontBattle:
	.string "Du willst nicht kämpfen? Schade, ich\n"
	.string "hätte dir gern dabei zugesehen…$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "Oh, gut, gut!\p"
	.string "Aber mein Haus ist nicht sehr stabil.\p"
	.string "Könntet ihr euch bitte auf einen\n"
	.string "Kampf 3 gegen 3 beschränken?$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "Bevor ihr kämpft, solltest du\n"
	.string "dein Spiel speichern.$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "Ich hoffe auf einen guten Kampf!$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "Es ist also unentschieden ausgegangen.\p"
	.string "Ein großartiger Kampf, in dem keine\n"
	.string "Seite einen Schritt zurückgewichen ist!$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "Das war erstklassig!\p"
	.string "Es war, als würde ich mich selbst\n"
	.string "in jungen Jahren sehen!$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "Ah, schade für dich!\p"
	.string "Aber es war ein guter Kampf.\n"
	.string "Vielleicht gewinnst du nächstes Mal.$"

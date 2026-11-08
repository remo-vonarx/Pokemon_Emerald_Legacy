EverGrandeCity_PhoebesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_PhoebesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_PhoebesRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_PhoebesRoom_OnFrame
	.byte 0

EverGrandeCity_PhoebesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_PhoebesRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 1, EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 2
	releaseall
	end

EverGrandeCity_PhoebesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 2, EverGrandeCity_PhoebesRoom_EventScript_CloseDoor
	end

EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_PhoebesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_PhoebesRoom_EventScript_Phoebe::
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematch
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_PhoebesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PHOEBE, EverGrandeCity_PhoebesRoom_Text_Defeat
	goto EverGrandeCity_PhoebesRoom_EventScript_Defeated
	end

EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_PHOEBE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematch::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_PHOEBE, EverGrandeCity_PhoebesRoom_EventScript_RematchPostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_PhoebesRoom_Text_RematchIntroSpeech, MSGBOX_DEFAULT
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematchSingle
	trainerbattle_no_intro TRAINER_PHOEBE_2, EverGrandeCity_PhoebesRoom_Text_RematchDefeat
	goto EverGrandeCity_PhoebesRoom_EventScript_RematchDefeated
	end

EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematchSingle::
	trainerbattle_no_intro TRAINER_PHOEBE_2_SINGLE, EverGrandeCity_PhoebesRoom_Text_RematchDefeat
	goto EverGrandeCity_PhoebesRoom_EventScript_RematchDefeated
	end

EverGrandeCity_PhoebesRoom_EventScript_RematchPostBattleSpeech::
	msgbox EverGrandeCity_PhoebesRoom_Text_RematchPostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_EventScript_RematchDefeated::
	setflag FLAG_DEFEATED_ELITE_4_PHOEBE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_PhoebesRoom_Text_RematchPostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_Text_IntroSpeech:
	.string "Ahahahahaha!\p"
	.string "Ich bin ANTONIA von den TOP VIER.\n"
	.string "Ich habe am PYROBERG trainiert.\p"
	.string "Während des Trainings habe ich die\n"
	.string "Fähigkeit erworben, mit GEIST-POKéMON\l"
	.string "zu kommunizieren.\p"
	.string "In der Tat ist das Band zwischen mir und\n"
	.string "den POKéMON sehr stark.\p"
	.string "Komm und schau, ob du irgendetwas\n"
	.string "gegen meine POKéMON ausrichten kannst.$"

EverGrandeCity_PhoebesRoom_Text_Defeat:
	.string "Oh, verdammt.\n"
	.string "Aus und vorbei. Verloren.$"

EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech:
	.string "Das Band zwischen dir und deinen\n"
	.string "POKéMON ist ebenfalls sehr stark.\p"
	.string "Das habe ich gar nicht bemerkt, daher\n"
	.string "konnte ich nur verlieren.\p"
	.string "Ja, jetzt möchte ich sehen, wie weit\n"
	.string "dieses Band euch bringt.\p"
	.string "Geh und betritt den nächsten Raum.$"

EverGrandeCity_PhoebesRoom_Text_RematchIntroSpeech:
	.string "ANTONIA: Ahahahahaha! Du bist zurück!\n"
	.string "Ich konnte dich wohl nicht fernhalten!\p"
	.string "Mein Band zu den GEIST-POKéMON ist\n"
	.string "noch tiefer geworden.\p"
	.string "Ich bin gespannt, wie weit auch dein\n"
	.string "Band gewachsen ist.\p"
	.string "Tanzen wir mit den Geistern!$"

EverGrandeCity_PhoebesRoom_Text_RematchDefeat:
	.string "Ooooh… Schon wieder verloren, was?\n"
	.string "Du bist echt gewachsen, oder?$"

EverGrandeCity_PhoebesRoom_Text_RematchPostBattleSpeech:
	.string "Deine Verbindung zu deinen POKéMON…\n"
	.string "Sie ist so stark wie eh und je.\p"
	.string "Schön, dass wir noch mal gekämpft\n"
	.string "haben. Geh weiter und zeig, was du\l"
	.string "draufhast!$"

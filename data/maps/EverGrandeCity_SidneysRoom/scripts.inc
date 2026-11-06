EverGrandeCity_SidneysRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_SidneysRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_SidneysRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_SidneysRoom_OnFrame
	.byte 0

EverGrandeCity_SidneysRoom_OnTransition:
	setflag FLAG_MET_SCOTT_IN_EVERGRANDE
	setflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	end

EverGrandeCity_SidneysRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 1, EverGrandeCity_SidneysRoom_EventScript_CloseDoor
	end

EverGrandeCity_SidneysRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_SidneysRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_SidneysRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_SidneysRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_SidneysRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_SidneysRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 0, EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 1
	releaseall
	end

EverGrandeCity_SidneysRoom_EventScript_Sidney::
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_SidneysRoom_EventScript_SidneyRematch
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_SidneysRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SIDNEY, EverGrandeCity_SidneysRoom_Text_Defeat
	goto EverGrandeCity_SidneysRoom_EventScript_Defeated
	end

EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SidneysRoom_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_SIDNEY
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SidneysRoom_EventScript_SidneyRematch::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_RematchPostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_SidneysRoom_Text_RematchIntroSpeech, MSGBOX_DEFAULT
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EverGrandeCity_SidneysRoom_EventScript_SidneyRematchOnePokemon
	trainerbattle_no_intro TRAINER_SIDNEY_2, EverGrandeCity_SidneysRoom_Text_RematchDefeat
	goto EverGrandeCity_SidneysRoom_EventScript_RematchDefeated
	end

EverGrandeCity_SidneysRoom_EventScript_SidneyRematchOnePokemon::
	trainerbattle_no_intro TRAINER_SIDNEY_2_SINGLE, EverGrandeCity_SidneysRoom_Text_RematchDefeat
	goto EverGrandeCity_SidneysRoom_EventScript_RematchDefeated
	end

EverGrandeCity_SidneysRoom_EventScript_RematchPostBattleSpeech::
	msgbox EverGrandeCity_SidneysRoom_Text_RematchPostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SidneysRoom_EventScript_RematchDefeated::
	setflag FLAG_DEFEATED_ELITE_4_SIDNEY
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_SidneysRoom_Text_RematchPostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_SidneysRoom_Text_IntroSpeech:
	.string "Willkommen, Herausforderer!\n"
	.string "Ich bin ULRICH von den TOP VIER.\p"
	.string "Ich mag deinen herausfordernden Blick.\n"
	.string "Ich denke, das wird ein guter Kampf.\l"
	.string "Gut! Das sieht gut aus!\p"
	.string "Schön! Dann lass uns beide einen Kampf\n"
	.string "erleben, wie man ihn nur hier in der\l"
	.string "POKéMON LIGA erleben kann!$"

EverGrandeCity_SidneysRoom_Text_Defeat:
	.string "Ich habe verloren! Ich, ULRICH von den\n"
	.string "TOP VIER. Macht nichts, es war lustig.$"

EverGrandeCity_SidneysRoom_Text_PostBattleSpeech:
	.string "Nun, hör dir an, was dieser Verlierer\n"
	.string "zu sagen hat.\p"
	.string "Du bist bestens ausgerüstet.\n"
	.string "Daher solltest du nun in den nächsten\l"
	.string "Raum gehen - zum nächsten Kampf.$"

EverGrandeCity_SidneysRoom_Text_RematchIntroSpeech:
	.string "ULRICH: Hey, CHAMP! Noch nicht genug?\n"
	.string "Ich wusste, dass du Feuer im Blut hast!\p"
	.string "Tja, diesmal will WASSILI deinen\n"
	.string "Titel.\l"
	.string "Sieh uns einfach als Aufwärmrunde!\p"
	.string "Zeig mir das Feuer von damals!\n"
	.string "Machen wir einen denkwürdigen Kampf\l"
	.string "daraus!$"

EverGrandeCity_SidneysRoom_Text_RematchDefeat:
	.string "Du hast es echt drauf…\n"
	.string "Sieht aus, als wärst du schon warm!$"

EverGrandeCity_SidneysRoom_Text_RematchPostBattleSpeech:
	.string "Du bist so zäh wie eh und je!\n"
	.string "Meinst du, du kannst den Titel halten?\p"
	.string "Los, der nächste Raum wartet!\n"
	.string "Bleib schön heiß!$"

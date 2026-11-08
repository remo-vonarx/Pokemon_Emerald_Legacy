.set LOCALID_ATTENDANT, 1

VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "An welchem WETTBEWERB nimmst du teil?\n"
	.string "Möchtest du einen Rat?\p"
	.string "Bei jedem WETTBEWERB, zum Beispiel\n"
	.string "einem ANMUTWETTBEWERB, zählt in der\l"
	.string "ersten Bewertung wohl nicht nur die\l"
	.string "Anmut.\p"
	.string "Du musst herausfinden, wie du deine\n"
	.string "POKéMON besser aufziehen kannst.$"

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "Ich habe mein POKéMON so aufgezogen,\n"
	.string "dass es niedlich ist.\p"
	.string "Und dann habe ich erfahren, dass es\n"
	.string "einen WETTBEWERB für Anmut gibt!\p"
	.string "Wie gut, dass ich es so liebevoll\n"
	.string "aufgezogen habe…$"

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "Mein POKéMON ist der Hammer!\p"
	.string "Es ist cool, stark, schön, süß und\n"
	.string "klug. Es ist perfekt!\p"
	.string "Da kann ich gleich bei jedem\n"
	.string "WETTBEWERB auf Sieg gehen.$"

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "POKéMON-WETTBEWERBE\n"
	.string "BÜHNE DER NORMAL-KLASSE!$"


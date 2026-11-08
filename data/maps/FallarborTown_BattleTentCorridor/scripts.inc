.set LOCALID_ATTENDANT, 1

FallarborTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FallarborTown_BattleTentCorridor_OnFrame
	.byte 0

FallarborTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, FallarborTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

FallarborTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_FALLARBOR_TOWN_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	releaseall
	end

FallarborTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
FallarborTown_ContestHall_Text_DoAllRightInPreliminary:
	.string "Im ersten Durchlauf läuft es ganz gut,\n"
	.string "aber im zweiten gewinnen wir nie…\p"
	.string "Vielleicht muss ich mal darauf achten,\n"
	.string "was die anderen Kontrahenten machen…$"

@ Unused
FallarborTown_ContestHall_Text_MonAllTheseRibbons:
	.string "Schau!\n"
	.string "Mein POKéMON hat all diese BÄNDER\l"
	.string "gewonnen!\p"
	.string "Haben deine POKéMON auch BÄNDER?\n"
	.string "Du kannst sie im POKéNAV ansehen.$"

@ Unused
FallarborTown_ContestHall_Text_CantWinEverywhere:
	.string "Ich kann keine ARENALEITER besiegen…\p"
	.string "Ich kann keine WETTBEWERBE gewinnen…\p"
	.string "Ich war schon überall, und alles\n"
	.string "war umsonst…$"

@ Unused
FallarborTown_ContestHall_Text_SuperRankStage:
	.string "POKéMON-WETTBEWERBE\n"
	.string "BÜHNE DER SUPER-KLASSE!$"


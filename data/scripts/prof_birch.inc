ProfBirch_EventScript_UpdateLocation::
	@ If the Johto-starter quest needs Birch in the lab (state >= 4 = "all
	@ Hoenn mons caught, choose a Johto starter"), force him to the lab
	@ regardless of whether the Mossdeep Jirachi sidequest has been done.
	@ Mossdeep Birch is a separate object event with its own hide flag, so
	@ this does not affect the Jirachi quest.
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, ProfBirch_EventScript_MoveToLab
	goto_if_unset FLAG_HIDE_MOSSDEEP_CITY_BIRCH, Common_EventScript_NopReturn
	goto_if_eq VAR_PETALBURG_GYM_STATE, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 0, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 1, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 2, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 3, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 4, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 5, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 6, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 7, ProfBirch_EventScript_MoveToLab
	return

ProfBirch_EventScript_MoveToLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfBirch_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch

ProfBirch_EventScript_AskRatePokedex::
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfBirch_EventScript_DeclineRating
	call ProfBirch_EventScript_RatePokedex
	release
	end

ProfBirch_EventScript_DeclineRating::
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfBirch_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfBirch_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, TRUE, ProfBirch_EventScript_CompletedNationalDex
	return

ProfBirch_EventScript_CompletedNationalDex::
	goto_if_set FLAG_RECEIVED_OLD_SEA_MAP, Common_EventScript_NopReturn
	msgbox gBirchDexRatingText_DexCompletedNationwide, MSGBOX_DEFAULT
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, ProfBirch_EventScript_OldSeaMapBagFull
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	msgbox gBirchDexRatingText_JourneyNotOverYet, MSGBOX_DEFAULT
	releaseall
	return

ProfBirch_EventScript_OldSeaMapBagFull:
	vmessage ProfBirch_Text_OldSeaMapBagFull
	waitmessage
	waitbuttonpress
	releaseall
	return

gBirchDexRatingText_DexCompletedNationwide::
	.string "Nun, {PLAYER}{KUN},\n"
	.string "das ist wirklich bemerkenswert!\p"
	.string "Du hast den POKéDEX auf nationaler\n"
	.string "Ebene vervollständigt…\p"
	.string "Ich hätte nie gedacht, dass ich diesen\n"
	.string "Tag erleben würde! Dein Einsatz ist\l"
	.string "inspirierend.\p"
	.string "Ach, das erinnert mich an etwas…\n"
	.string "Es gibt da etwas, das ich aufbewahrt\l"
	.string "habe. Es ist eine ALTE KARTE.\p"
	.string "Ich habe sie vor Jahren auf einer\n"
	.string "meiner Forschungsreisen gefunden,\l"
	.string "aber ich wusste nie so recht, was ich\l"
	.string "davon halten sollte.\p"
	.string "Eine merkwürdige Sache, wirklich. Ich\n"
	.string "war mir nie ganz sicher, woher sie\l"
	.string "stammt.\p"
	.string "Die Karte scheint auf eine geheimnis-\n"
	.string "volle Insel hinzuweisen…\p"
	.string "Aber als ich ihr folgen wollte, war dort\n"
	.string "nichts, nur endloses Meer.\p"
	.string "Ich begann zu glauben, es sei nur\n"
	.string "Seemannsgarn, und vielleicht habe ich\l"
	.string "die Sache deshalb nicht weiterverfolgt.\p"
	.string "Aber bei deinem Einsatz und Können\n"
	.string "glaube ich, dass gerade du dieses\l"
	.string "Rätsel lösen könntest.\p"
	.string "Wer weiß, vielleicht ist dort etwas\n"
	.string "Unglaubliches verborgen.\p"
	.string "Nimm diese ALTE KARTE, {PLAYER}{KUN}.$"

ProfBirch_Text_OldSeaMapBagFull:
	.string "Oh, es tut mir leid, {PLAYER}! Die\n"
	.string "BASIS-ITEM-TASCHE in deinem\l"
	.string "BEUTEL ist voll.\l"
	.string "Lagere etwas auf deinem PC und\l"
	.string "komme anschließend zurück.$"

gBirchDexRatingText_JourneyNotOverYet:
	.string "Vielleicht ist deine Reise noch nicht\n"
	.string "ganz vorbei.$"

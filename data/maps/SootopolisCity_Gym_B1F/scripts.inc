SootopolisCity_Gym_B1F_MapScripts::
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_B1F_EventScript_CrissyPostGame
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end
SootopolisCity_Gym_B1F_EventScript_CrissyPostGame::
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle2, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_B1F_EventScript_BriannaPostGame
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end
SootopolisCity_Gym_B1F_EventScript_BriannaPostGame::
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle2, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_B1F_EventScript_ConniePostGame
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end
SootopolisCity_Gym_B1F_EventScript_ConniePostGame::
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle2, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	goto_if_set FLAG_IS_CHAMPION, SootopolisCity_Gym_B1F_EventScript_AnnikaPostGame
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end
SootopolisCity_Gym_B1F_EventScript_AnnikaPostGame::
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle2, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "Ich zeige dir die sublimen Techniken,\n"
	.string "die ich vom ARENALEITER WASSILI\l"
	.string "gelernt habe.$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "Bitte verzeih mir, WASSILI…$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "Pass auf, was passiert, wenn du alle\n"
	.string "Bodenfliesen betreten hast…$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "Du bist den ganzen Weg hierherge-\n"
	.string "kommen, aber bis zu WASSILI dringst\l"
	.string "du nicht vor.\p"
	.string "Weil du gegen mich verlieren wirst!$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "Du bist stark! Ich habe mich durch dein\n"
	.string "unschuldiges Aussehen täuschen\l"
	.string "lassen.$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "Du bist gut genug, um nicht sofort von\n"
	.string "WASSILI hinweggefegt zu werden.$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle2:
	.string "Du bist gut genug, um nicht sofort von\n"
	.string "JUAN hinweggefegt zu werden.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "Die Art, wie WASSILI kämpft…\p"
	.string "Dieser wunderbare Anblick hat mich dazu\n"
	.string "inspiriert, TRAINER zu werden.$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "Du kämpfst mit mehr Anmut als ich…$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "Die Ästhetik, die du in den Kampf ein-\n"
	.string "bringst, ist unbeschreiblich.\p"
	.string "Oh… Ich bin so glücklich, dass ich mich\n"
	.string "für POKéMON entschieden habe.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "Ich werde dir beibringen, dass Kämpfe\n"
	.string "kein Zuckerschlecken sind!$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "Oh.\n"
	.string "Du bist stark.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "Ich verrate dir etwas.\p"
	.string "Wenn du zu WASSILI willst, dann darfst\n"
	.string "du auf jede Fliese nur ein Mal treten.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle2:
	.string "Ich verrate dir etwas.\p"
	.string "Wenn du zu JUAN willst, dann darfst\n"
	.string "du auf jede Fliese nur ein Mal treten.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "Die POKéMON ARENA mit den höchsten\n"
	.string "Anforderungen in der HOENN-Region…\p"
	.string "Das ist die ARENA von XENEROVILLE.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "Du kämpfst aber auf einem hohen\n"
	.string "Niveau!$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "Statt damit zufrieden zu sein, zur\n"
	.string "besten ARENA zu gehören, würde ich\l"
	.string "gerne auch an anderen Orten trainieren.\l"
	.string "Aber hier ist es so lustig!$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "Ich trainiere meine POKéMON zusammen\n"
	.string "mit WASSILI.\p"
	.string "Kennst du ihn?$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "Da wurde ich glatt überrollt…$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "JUAN war WASSILIs Mentor. Er hat ihm\n"
	.string "vieles von dem beigebracht, was er\l"
	.string "weiß.$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "Anmutig über das Eis zu gleiten, ohne\n"
	.string "die Linien zu berühren…\p"
	.string "Ein TRAINER, der das beherrscht, wird\n"
	.string "auch in anderen Dingen elegant wirken.$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "Äh, entschuldige mich…$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "Es ist offensichtlich: Die Stärke eines\n"
	.string "TRAINERs hat nichts mit seinem Alter\l"
	.string "zu tun!$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "Wenn ich mit meinen POKéMON zusammen\n"
	.string "bin, vergeht die Zeit so schnell, dass\l"
	.string "ich noch nicht mal “Uuups” sagen kann.$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "Uuups!$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "Ich wollte, ich könnte meine\n"
	.string "Niederlagen vergessen, bevor ich\l"
	.string "“Uuups” ausgesprochen habe.$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "Wenn du magst, setze ich im Kampf viele\n"
	.string "seltene POKéMON ein.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "Und? Hast du dir meine POKéMON\n"
	.string "gut angesehen?$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "Ich bin zu dieser ARENA gekommen, weil\n"
	.string "JUAN meine geliebten POKéMON gelobt\l"
	.string "hat.\l"
	.string "Jetzt trainiere ich bei WASSILI!$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle2:
	.string "Ich bin zu dieser ARENA gekommen, weil\n"
	.string "JUAN meine geliebten POKéMON gelobt\l"
	.string "hat.$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "Kicher…\n"
	.string "Dein grimmiger Ausdruck ist total\l"
	.string "niedlich.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "Oh je.\n"
	.string "Ich habe es dir viel zu leicht gemacht.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "Du kannst WASSILI kein Härchen krümmen,\n"
	.string "wetten? Kicher…$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle2:
	.string "Du kannst JUAN kein Härchen krümmen,\n"
	.string "wetten? Kicher…$"

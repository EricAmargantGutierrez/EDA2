#include "battles.c"

Skill skills[4] = {
        {"Deceit Attack", "Use your deception skills to inflict sudden damage to your enemy. Note that this attack works well against certain types of enemies.", false, 5, 0, 0},
        {"Agile Attack", "Use your youth and agility to surprise your enemy. Note that this attack works well against certain types of enemies.", false, 5, 0, 0},
        {"Berserk", "You picture the emperor (he who is responsible for the death of your loved ones) as your enemy, you go crazy and inflict lots of damage on your enemy. Note that this attack works well against certain types of enemies.", false, 5, 0, 0},
        {"Heal", "Use your medicinal knowledge to heal yourself (+100 HP). Note that this ability can only be used once.", true, 0, 0, 100}
    };

// Define the characters' stats
Character c1 = {"Arnaus Decimus Meridius",100, 1, 1}; // Arnaus Decimus Meridius
Character c2 = {"Ericus Carpophorus", 100, 0.9, 1.1}; // Ericus Carpophorus
Character c3 = {"Paullus Acilius Glabrio", 100, 1.2, 0.8}; // Paullus Acilius Glabrio

// Initialize enemies
Enemy decimus = {"Decimus Brutus", 80, 0.4, 0.5, skills}; //cambiar pq no puguin fer servir totes les skills
Enemy cult = {"Cult of Bacchus", 90, 0.7, 0.6, skills};
Enemy mercenaries = {"The Mercenaries", 100, 0.7, 0.9, skills};
Enemy Sulla = {"Lucius Cornelius Sulla", 120, 1, 1.1, skills};



// Initialize options
Option opt1_rome = {"Forge Alliances", "You form alliances with other gladiators, pooling your strengths to overcome rivals together.", "Your alliances prove beneficial, leading to an increase in your characters attack points by 1.", 0, 0.1, 0};

Option opt2_rome = {"Face Adversaries", "You confront your adversaries directly, relying on your individual skills to prevail in combat.", "Your prowess in combat impresses both allies and rivals, solidifying your reputation as a formidable gladiator. Your HP and defense are increased by 1. Nevertheless, you got slightly injured, so your attack is reduced by 2 point", 10, -0.2, 0.1};

Option opt1_pompeii = {"Ally with Caesar", "You decide to ally yourself with Julius Caesar, intrigued by the potential benefits of such a powerful connection.", "Your alliance with Julius Caesar opens doors to new opportunities and grants you access to influential circles in Pompeii. You exploit those connections and gain 2 attack points but your defense is reduced by 1 as powerful enemies have spotted some of your weak points.", 0, 0.2, -0.1};

Option opt2_pompeii = {"Exercise Caution", "You choose to tread cautiously, wary of Julius Caesar's motives and the risks associated with such a partnership.", "Your cautious approach safeguards you from potential pitfalls and allows you to navigate the political landscape of Pompeii with prudence. You gain 2 HP points.", 0, 0, 0.2};

Option opt1_thermal = {"Investigate Argument", "You decide to investigate the heated argument, intrigued by the involvement of powerful figures.", "Your investigation uncovers valuable information and earns you the respect of influential individuals in the city. Additionally, Maximus Kratos invited you to a self-defense masterclass, earning you 3 defense points!", 0, 0, 0.3};

Option opt2_thermal = {"Mind Your Own Business", "You choose to mind your own business and enjoy the tranquility of the thermal baths, avoiding unnecessary entanglements.", "Your decision to stay out of the argument preserves your peace of mind and allows you to focus on your own goals. Your lack of implication loses you 2 attack points.", 0, -0.2, 0};

Option opt1_colosseum = {"Stand Your Ground", "You choose to stand your ground and face your opponent head-on, relying on your skills and courage to emerge victorious.", "Your bravery and skill in combat earn you the admiration of the crowd and the respect of your opponent. You gain 2 points on defense and 1 HP.", 10, 0, 0.1};

Option opt2_colosseum = {"Analyze Weaknesses", "You opt to analyze your opponent's weaknesses and exploit them strategically, seeking any advantage you can find.", "Your strategic approach seems to pay off as you exploit your opponent's weaknesses, you gain 3 attack points.", 0.3, 0};


// Initialize decisions
Decision rome_dec = {"You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?", {&opt1_rome, &opt2_rome}};

Decision pompeii_dec = {"At the designated rendezvous point, you come face to face with the enigmatic Julius Caesar, this still young and mysterious figure who summoned you. Their identity shrouded in secrecy, he offers you a proposition that could tip the balance of power in Pompeii. Will you ally yourself with this mysterious benefactor, or will you tread cautiously, wary of hidden agendas and ulterior motives?", {&opt1_pompeii, &opt2_pompeii}};

Decision thermal_dec = { "As you soak in the rejuvenating waters, you notice a heated argument unfolding nearby. A group of powerful and influential figures of the city are engaged in a fierce debate, their voices echoing off the marble walls of the baths. Intrigued, you consider whether to investigate further or to mind your own business and enjoy the tranquility of the surroundings.", {&opt1_thermal, &opt2_thermal}};

Decision colosseum_dec = {"As you await your turn in the arena, a hush falls over the crowd, and the gate opens to reveal your opponent: a fierce and imposing gladiator known for their ruthless efficiency in combat. In this moment of truth, will you stand your ground and face your opponent head-on, or will you seek a strategic advantage by analyzing their weaknesses and exploiting them?", {&opt1_colosseum, &opt2_colosseum}};



// Initialize scenarios, we initialize them in reverse order so we can link the "next" item in the list
Scenario colosseum_showdown = {"The Colosseum Showdown", "Whatever happens, you end up detained at the hands of the praetorian guard. You are brought back to Rome where a trial is set to begin. After a couple of sessions, it is already clear that the magistrate, the Optimate Dictator Lucius Cornelius Sulla, wants to condemn you whatever the cost may be, and that the sentence is likely set from the beginning of the trial: death at the Tarpeian Rock!", &Sulla, &colosseum_dec, NULL};

Scenario thermal_baths = {"The Thermal Baths", "After the tumultuous events in Pompeii, you seek respite and refuge in the tranquil surroundings of the thermal baths. Here, amidst the soothing waters and opulent surroundings, you contemplate your next move in the ever-shifting game of power and intrigue.", &mercenaries, &thermal_dec, &colosseum_showdown};

Scenario shadows_of_pompeii = {"Shadows of Pompeii", "In the twilight of Pompeii's ruins, mysteries lurk beneath ash-covered streets. Navigate shadows fraught with intrigue and danger. Will you unravel secrets or become entangled in deceit? Choose wisely; in Pompeii, history's whispers echo loudest", &cult, &pompeii_dec, &thermal_baths};

Scenario rome = {"Rome", "In the heart of ancient Rome, your journey begins. In a context of post-civil war between the Optimates and Populares factions in the senate, the roman plebs live under the yoke of Optimate tyranny, and the Dictatorship of Lucius Cornelius Sulla. Navigate the streets wisely, for every choice shapes your destiny. Adventure awaits in the arena and beyond. Let the games begin! \n\n", &decimus, &rome_dec, &shadows_of_pompeii};

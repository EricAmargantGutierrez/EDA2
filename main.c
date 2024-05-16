#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

// Define the characters' stats
// Arnaus Decimus Meridius
// Ericus Carpophorus
// Paullus Acilius Glabrio

/*
void init_skills(Skill *ability, char* name, char* descript, bool type, int atk, int def, int hp){
    strcpy(ability->name, name);    
    strcpy(ability->description, descript);
    ability->type=type;
    ability->mod_atk=atk;
    ability->mod_def=def;
    ability->mod_hp=hp;
}

void init_option(Option* option, char* initial_text, char* response, char* final_text){
    strcpy(option->narrative_text_i, initial_text);    
    strcpy(option->response_text, response);
    strcpy(option->narrative_text_f, final_text);
}

void init_decision(Decision* decision, char* question, int num_options, Option* options){
    strcpy(decision->question_text, question);
    decision->number_options = num_options;
    decision->options = options; //change if it doesnt work
}

void init_enemy(Enemy* enemy, char* name, int hp, int atk, int def, Skill skills[3]){ //canviar
    strcpy(enemy->name, name);
    enemy->hp = hp;
    enemy->atk = atk;
    enemy->def = def;
    memcpy(enemy->skills, skills, sizeof(enemy->skills));
}

void init_scenario(Scenario* scene, char* name, char* descript, Enemy enemies[3], Decision* choice, Scenario *next){ //canviar
    strcpy(scene->name, name);
    strcpy(scene->description, descript);
    memcpy(scene->enemies, enemies, sizeof(scene->enemies));
    scene->choice = choice;
    scene->next = next;
}

*/


void configure_character(Character *player) {
    printf("Character selection:\n");
    printf("1. Arnaus Decimus Meridius\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 5\n");
    printf("   * Defense Points: 5\n");
    printf("2. Ericus Carpophorus\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 3\n");
    printf("   * Defense Points: 7\n");
    printf("3. Paullus Acilius Glabrio\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 6\n");
    printf("   * Defense Points: 4\n");

    int choice;
    printf("Choose your character (1, 2, or 3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(player->name, "Arnaus Decimus Meridius");    
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            int temp_skills[]={1, 2, 3, 4};
            memcpy(player->skills, temp_skills, sizeof(temp_skills));
            break;
        case 2:
            strcpy(player->name, "Ericus Carpophorus");    
            player->HP = 100;
            player->atk_pts = 4;
            player->def_pts = 6;
            memcpy(player->skills, temp_skills, sizeof(temp_skills));
            break;
        case 3:
            strcpy(player->name, "Paullus Acilius Glabrio");
            player->HP = 100;
            player->atk_pts = 7;
            player->def_pts = 3;
            memcpy(player->skills, temp_skills, sizeof(temp_skills));
            break;
        default:
            printf("Invalid choice. Defaulting to Arnaus Decimus Meridius.\n");
            strcpy(player->name, "Arnaus Decimus Meridius");
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            memcpy(player->skills, temp_skills, sizeof(temp_skills));
            break;
    }
}


void start_game(Character *player){
    printf("We have started");
}


void display_menu(Character *player) {
    int choice;
    bool chosen_character = false;

    do {
        printf("\n----- Gladiator RPG Menu -----\n");
        printf("1. Start New Game\n");
        printf("2. Configure Character before playing\n");
        printf("3. View Game Structure\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                if(chosen_character == false){
                    printf("Since you have not configured your character yet, you will be redirected to 'Configure Character'");
                    choice = 2;
                }
                start_game(player); //this is the function that leads character through the different scenarios in the game
                break;
            case 2:
                configure_character(player); //this is the function that configures the players character
                chosen_character = true;
                break;
            case 3:
                printf("Game structure:\n");
                printf("Scenarios:\n");
                printf("1. Rome\n");
                printf("2. Shadows of PompeII\n");
                printf("3. The thermal baths\n");
                printf("4. Colosseum Showdown\n");
                break;
            case 4:
                printf("Exiting the game. Guess you couldn't handle the pressure!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
}



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
Option opt1_rome = {"Forge Alliances", "You form alliances with other gladiators, pooling your strengths to overcome rivals together.", "Your alliances prove beneficial, leading to an increase in your characters attack points by 1."};

Option opt2_rome = {"Face Adversaries", "You confront your adversaries directly, relying on your individual skills to prevail in combat.", "Your prowess in combat impresses both allies and rivals, solidifying your reputation as a formidable gladiator. Your HP and defense are increased by 2. Nevertheless, you got slightly injured, so your attack is reduced by 1 point"};

Option opt1_pompeii = {"Ally with Caesar", "You decide to ally yourself with Julius Caesar, intrigued by the potential benefits of such a powerful connection.", "Your alliance with Julius Caesar opens doors to new opportunities and grants you access to influential circles in Pompeii. You exploit those connections and gain 2 attack points but your defense is reduced by 1 as powerful enemies have spotted some of your weak points."};

Option opt2_pompeii = {"Exercise Caution", "You choose to tread cautiously, wary of Julius Caesar's motives and the risks associated with such a partnership.", "Your cautious approach safeguards you from potential pitfalls and allows you to navigate the political landscape of Pompeii with prudence. You gain 2 HP points."};

Option opt1_thermal = {"Investigate Argument", "You decide to investigate the heated argument, intrigued by the involvement of powerful figures.", "Your investigation uncovers valuable information and earns you the respect of influential individuals in the city. Additionally, Maximus Kratos invited you to a self-defense masterclass, earning you 3 defense points!"};

Option opt2_thermal = {"Mind Your Own Business", "You choose to mind your own business and enjoy the tranquility of the thermal baths, avoiding unnecessary entanglements.", "Your decision to stay out of the argument preserves your peace of mind and allows you to focus on your own goals. Your lack of implication loses you 2 attack points."};

Option opt1_colosseum = {"Stand Your Ground", "You choose to stand your ground and face your opponent head-on, relying on your skills and courage to emerge victorious.", "Your bravery and skill in combat earn you the admiration of the crowd and the respect of your opponent. You gain 2 points on defense and 1 HP."};

Option opt2_colosseum = {"Analyze Weaknesses", "You opt to analyze your opponent's weaknesses and exploit them strategically, seeking any advantage you can find.", "Your strategic approach seems to pay off as you exploit your opponent's weaknesses, you gain 3 attack points."};


// Initialize decisions
Decision rome_dec = {"You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?", 2, {&opt1_rome, &opt2_rome}};

Decision pompeii_dec = {"At the designated rendezvous point, you come face to face with the enigmatic Julius Caesar, this still young and mysterious figure who summoned you. Their identity shrouded in secrecy, he offers you a proposition that could tip the balance of power in Pompeii. Will you ally yourself with this mysterious benefactor, or will you tread cautiously, wary of hidden agendas and ulterior motives?", 2, {&opt1_pompeii, &opt2_pompeii}};

Decision thermal_dec = { "As you soak in the rejuvenating waters, you notice a heated argument unfolding nearby. A group of powerful and influential figures of the city are engaged in a fierce debate, their voices echoing off the marble walls of the baths. Intrigued, you consider whether to investigate further or to mind your own business and enjoy the tranquility of the surroundings.", 2, {&opt1_thermal, &opt2_thermal}};

Decision colosseum_dec = {"As you await your turn in the arena, a hush falls over the crowd, and the gate opens to reveal your opponent: a fierce and imposing gladiator known for their ruthless efficiency in combat. In this moment of truth, will you stand your ground and face your opponent head-on, or will you seek a strategic advantage by analyzing their weaknesses and exploiting them?", 2, {&opt1_colosseum, &opt2_colosseum}};



// Initialize scenarios, we initialize them in reverse order so we can link the "next" item in the list
Scenario colosseum_showdown = {"The Colosseum Showdown", "Whatever happens, you end up detained at the hands of the praetorian guard. You are brought back to Rome where a trial is set to begin. After a couple of sessions, it is already clear that the magistrate, the Optimate Dictator Lucius Cornelius Sulla, wants to condemn you whatever the cost may be, and that the sentence is likely set from the beginning of the trial: death at the Tarpeian Rock!", &Sulla, &colosseum_dec, NULL};

Scenario thermal_baths = {"The Thermal Baths", "After the tumultuous events in Pompeii, you seek respite and refuge in the tranquil surroundings of the thermal baths. Here, amidst the soothing waters and opulent surroundings, you contemplate your next move in the ever-shifting game of power and intrigue.", &mercenaries, &thermal_dec, &colosseum_showdown};

Scenario shadows_of_pompeii = {"Shadows of Pompeii", "In the twilight of Pompeii's ruins, mysteries lurk beneath ash-covered streets. Navigate shadows fraught with intrigue and danger. Will you unravel secrets or become entangled in deceit? Choose wisely; in Pompeii, history's whispers echo loudest", &cult, &pompeii_dec, &thermal_baths};

Scenario rome = {"Rome", "In the heart of ancient Rome, your journey begins. In a context of post-civil war between the Optimates and Populares factions in the senate, the roman plebs live under the yoke of Optimate tyranny, and the Dictatorship of Lucius Cornelius Sulla. Navigate the streets wisely, for every choice shapes your destiny. Adventure awaits in the arena and beyond. Let the games begin! \n\n", &decimus, &rome_dec, &shadows_of_pompeii};



void print_enemy_info(Enemy* enemy) {
    printf("Enemy Name: %s\n", enemy->name);
    printf("Enemy Attack: %d\n", enemy->atk);
    printf("Enemy HP: %d\n", enemy->hp);
    printf("Enemy Defense: %d\n", enemy->def);
}

// Function to print information of a player (Character)
void print_player_info(Character* player) {
    printf("Player Name: %s\n", player->name);
    printf("Player Attack Points: %d\n", player->atk_pts);
    printf("Player HP: %d\n", player->HP);
    printf("Player Defense Points: %d\n", player->def_pts);
}
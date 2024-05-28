#include "structures.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdbool.h>

// Insert the skills on the dictionary
void insert(Character *player, const char *key, int value) {
    if (player->dict.size >= MAX_ITEMS) {
        printf("Dictionary is full\n");
        return;
    }

    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            player->dict.entries[i].value = value;
            return;
        }
    }

    strncpy(player->dict.entries[player->dict.size].key, key, MAX_LENGTH - 1);
    player->dict.entries[player->dict.size].key[MAX_LENGTH - 1] = '\0';
    player->dict.entries[player->dict.size].value = value;
    player->dict.size++;
}

// Initialize an empty dictionary
void init_dictionary(Character *player) {
    player->dict.size = 0;
    player->dict.initialized = true;
}

// Get element from the dictionary
int get(Character *player, const char *key) {
    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            return player->dict.entries[i].value;
        }
    }
    return -1; // Key not found
}

// Reinitialize the dictionary in the case that it was already initialized, but we have re-configured the character's skills
void reinit_dictionary(Character *player) {
    if (player->dict.initialized) {
        player->dict.size = 0;
    }
}

// Increment by one the number of times a skill has been used
void increment(Character *player, const char *key) {
    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            player->dict.entries[i].value += 1;
            return;
        }
    }
    printf("Key '%s' not found in dictionary\n", key);
}


// initialize an empty battle queue
void init_battle_queue(BattleQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->elements = 0;
}


// self-explanatory
void enqueue_battle_move(BattleQueue* q, int move, Character *character, bool player) {
    q->elements += 1;

    // reserve space for the battle turn we want to enqueue
    BattleTurn *node = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (node == NULL) {
        return;
    }

    // set the necessary parameters of the battle turn
    node->move_used = move;
    node->player = player;
    node->character = character;
    node->next = NULL;

    if (q->tail == NULL) {
        q->head = node;
    } else {
        q->tail->next = node;
    }

    q->tail = node;
}


// also self-explanatory
BattleTurn dequeue_battle_move(BattleQueue* q) {

    // declare the battle turn we will return
    BattleTurn *temp = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (q->head == NULL) {
        return *temp;
    }

    // move the head to the next turn in the queue
    temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    q->elements -= 1;

    // return battle turn
    return *temp;
}


// initialize an empty battle stack
void init_battle_stack(BattleStack *s) {
    s->head = NULL;
    s->elements = 0;
}


// self-explanatory
void push_battle_move(BattleStack *s, int move, Character *character) {
    s->elements += 1;

    BattleTurn *node = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (node == NULL) {
        return;
    }

    node->move_used = move;
    node->character = character;
    node->next = s->head;

    s->head = node;
}


// also self-explanatory
BattleTurn pop_battle_move(BattleStack *s) {
    BattleTurn result;

    if (s->head == NULL) {
        return result;
    }

    BattleTurn *temp = s->head;
    s->head = s->head->next;

    result.move_used = temp->move_used;
    result.character = temp->character;

    free(temp);

    s->elements -= 1;

    return result;
}


// Initialize the different arrays of skills
Skill weapons[3] = {
    {"Shield", "Utilize your defensive prowess to absorb enemy attacks, significantly reducing damage taken while being able to stay close and deal critical damage", true, 5, 10, 5}, 
    {"Bow and Arrow", "Use your archery skills to damage the enemy from far away, while minimizing your exposure to their attack.", true, 0, 10, 10},
    {"Invisible Knife (Cool Down)", "This attack can be used to quickly and silently eliminate a single enemy.", true, 20, 0, 10}  // cool_down period?
};

Skill hero_skills[3] = {
        {"Deceit Attack", "Use your deception skills to inflict sudden damage to your enemy.", true, 10, 5, 5},
        {"Agile Attack", "Use your youth and agility to surprise your enemy.", true, 5, 5, 10},
        {"Berserk", "You remember the loss of your loved ones years ago, you go crazy and inflict lots of damage on your enemy. Note that this attack exposes you to counter-attacks from the enemy.", true, 15, 0, 0},
        };

Skill special_skills[2] = {
    {"Regenerate", "Use your medicinal knowledge to heal yourself (+100 HP). Note that this ability can only be used once.", true, 0, 0, 100},
    {"Time Strike", "Harness the power of time to unleash one of the previously used skills (except 'Regenerate'), and duplicate the attack, defense, and HP bonus of the skill selected at random. Note that this ability can only be used once.", true, 0, 0, 0}
};

Skill skills_enemy[2] = {
    {"Backstab", "A sneaky attack from behind, dealing moderate damage.", true, 10, 5, 0},
    {"Rage", "Enter a furious state, increasing attack power but reducing defense.", true, 15, 0, 0}
};

Skill particular_enemy_skills[4] = {
    {"Brutus' Gambit", "Execute a calculated maneuver inspired by Brutus' betrayal, delivering a powerful blow. This attack works well against certain types of enemies.", true, 18, 0, 0},
    {"Ritual Fury", "Harness the dark energy of your cult to unleash a powerful attack on your enemy. This attack works well against certain types of enemies.", true, 18, 0, 0},
    {"Poisonous Strike", "Deliver a single strike laced with poison, causing additional damage for one turn. This attack works well against certain types of enemies.", true, 12, 0, 0},
    {"Dictator's Wrath", "Invoke the ruthless spirit of Sulla to execute a powerful attack. This attack works well against certain types of enemies.", true, 20, 0, 0}

};

// Initialize options
Option opt1_rome = {"Forge Alliances", "You form alliances with other gladiators, pooling your strengths to overcome rivals together.", "Your alliances prove beneficial, leading to an increase in your characters attack points by 1.", 0, 1, 0};

Option opt2_rome = {"Face Adversaries", "You confront your adversaries directly, relying on your individual skills to prevail in combat.", "Your prowess in combat impresses both allies and rivals, solidifying your reputation as a formidable gladiator. You gain +10HP and +1 defense points. Nevertheless, you got slightly injured, reducing your mobility and agility, so your attack is reduced by 2 points", 10, -2, 1};

Option opt1_pompeii = {"Ally with Caesar", "You decide to ally yourself with Julius Caesar, intrigued by the potential benefits of such a powerful connection.", "Your alliance with Julius Caesar opens doors to new opportunities and grants you access to influential circles in Pompeii. You exploit those connections and gain 2 attack points but your defense is reduced by 1 as powerful enemies have spotted some of your weak points.", 0, 2, -1};

Option opt2_pompeii = {"Exercise Caution", "You choose to tread cautiously, wary of Julius Caesar's motives and the risks associated with such a partnership.", "Your cautious approach safeguards you from potential pitfalls and allows you to navigate the political landscape of Pompeii with prudence. You gain 20 HP points.", 20, 0, 0};

Option opt1_thermal = {"Investigate Argument", "You decide to investigate the heated argument, intrigued by the involvement of powerful figures.", "Your investigation uncovers valuable information and earns you the respect of influential individuals in the city. Additionally, Maximus Kratos invited you to a self-defense masterclass, earning you 3 defense points!", 0, 0, 3};

Option opt2_thermal = {"Mind Your Own Business", "You choose to mind your own business and enjoy the tranquility of the thermal baths, avoiding unnecessary entanglements.", "Your decision to stay out of the argument preserves your peace of mind and allows you to focus on your own goals. Your lack of implication loses you 2 attack points.", 0, -2, 0};

Option opt1_colosseum = {"Stand Your Ground", "You choose to stand your ground and face your opponent head-on, relying on your skills and courage to emerge victorious.", "Your bravery and skill in combat earn you the admiration of the crowd and the respect of your opponent. You gain 1 point on defense and 10 HP.", 10, 0, 1};

Option opt2_colosseum = {"Analyze Weaknesses", "You opt to analyze your opponent's weaknesses and exploit them strategically, seeking any advantage you can find.", "Your strategic approach seems to pay off as you exploit your opponent's weaknesses, you gain 3 attack points.", 0, 3, 0};



// Initialize the decisions
Decision rome_dec = {"You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?", {&opt1_rome, &opt2_rome}, 0};

Decision pompeii_dec = {"At the designated rendezvous point, you come face to face with the enigmatic Julius Caesar, this still young and mysterious figure who summoned you. Their identity shrouded in secrecy, he offers you a proposition that could tip the balance of power in Pompeii. Will you ally yourself with this mysterious benefactor, or will you tread cautiously, wary of hidden agendas and ulterior motives?", {&opt1_pompeii, &opt2_pompeii}, 0};

Decision thermal_dec = { "As you soak in the rejuvenating waters, you notice a heated argument unfolding nearby. A group of powerful and influential figures of the city are engaged in a fierce debate, their voices echoing off the marble walls of the baths. Intrigued, you consider whether to investigate further or to mind your own business and enjoy the tranquility of the surroundings.", {&opt1_thermal, &opt2_thermal}, 0};

Decision colosseum_dec = {"As you await your turn in the arena, a hush falls over the crowd, and the gate opens to reveal your opponent: a fierce and imposing gladiator known for their ruthless efficiency in combat. In this moment of truth, will you stand your ground and face your opponent head-on, or will you seek a strategic advantage by analyzing their weaknesses and exploiting them?", {&opt1_colosseum, &opt2_colosseum}, 0};
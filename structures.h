#include <stdio.h>
#include <stdbool.h>
#define MAX_LENGTH 50
#define MAX_ITEMS 5


// Define constants
#define MAX_SKILLS 4
#define MAX_ENEMIES 3
#define OPTIONS 2

// Define the structs

typedef struct {
    char name[50];
    char description[300];
    bool can_be_used;
    float mod_atk;
    float mod_def;
    float mod_hp;
} Skill;

// Dictionary structs
typedef struct {
    char key[MAX_LENGTH];
    int value;
} Entry;

typedef struct {
    Entry entries[MAX_ITEMS];
    int size;
    bool initialized;
} Dictionary;

typedef struct {
    char name[50];
    float HP;
    float atk_pts;
    float def_pts;
    int first_skill;
    int second_skill;
    int weapon;
    int character_num;
    bool difficult;
    Skill skills[5];
    Dictionary dict;
} Character;


void insert(Character *player, const char *key, int value) {
    if (player->dict.size >= MAX_ITEMS) {
        printf("Dictionary is full\n");
        return;
    }

    // Check for duplicate keys and update value if found
    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            player->dict.entries[i].value = value;
            return;
        }
    }

    // Otherwise, insert the new key-value pair
    strncpy(player->dict.entries[player->dict.size].key, key, MAX_LENGTH - 1);
    player->dict.entries[player->dict.size].key[MAX_LENGTH - 1] = '\0'; // Ensure null-termination
    player->dict.entries[player->dict.size].value = value;
    player->dict.size++;
}

void init_dictionary(Character *player) {
    player->dict.size = 0;
    player->dict.initialized = true;
}

int get(Character *player, const char *key) {
    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            return player->dict.entries[i].value;
        }
    }
    return -1; // Key not found
}

void reinit_dictionary(Character *player) {
    if (player->dict.initialized) {
        player->dict.size = 0;
        // Reinitialization logic can be added here if needed
        printf("Dictionary reinitialized.\n");
    } else {
        printf("Dictionary is not initialized yet.\n");
    }
}

void increment(Character *player, const char *key) {
    for (int i = 0; i < player->dict.size; i++) {
        if (strncmp(player->dict.entries[i].key, key, MAX_LENGTH) == 0) {
            player->dict.entries[i].value += 1;
            return;
        }
    }
    printf("Key '%s' not found in dictionary\n", key);
}

typedef struct {
    char name[50];
    float hp;
    float initial_hp;
    float atk;
    float def;
    Skill skills[3]; //enemies cannot heal themselves
}Enemy;

typedef struct{
    char narrative_text_i[400];
    char response_text[200];
    char narrative_text_f[400];
    float hp_incr;
    float atk_incr;
    float def_incr;
} Option;

typedef struct {
    char question_text[400];
    Option *options[2];
    int option_number;
} Decision;

typedef struct  scen {
    char name[50];
    char description[400];
    Enemy *enemies;
    Decision *choice;
    int life;
    int order;
    struct scen *next;
    struct scen *prev;
} Scenario;


typedef struct BattleTurn {
    int move_used;
    Character *character;
    struct BattleTurn *next;
} BattleTurn;

// Queue
typedef struct {
    BattleTurn *head;
    BattleTurn *tail;
    int elements;
} BattleQueue;

void init_battle_queue(BattleQueue *q){
    q->head=NULL;
    q->tail=NULL;
    q->elements=0;
}

void enqueue_battle_move(BattleQueue* q, int move, Character *character){
    q->elements+=1;

    BattleTurn *node = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (node == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new node
    node->move_used = move;
    node->character = character;
    node->next = NULL;

    // If the queue is empty, set head to the new node
    if (q->tail == NULL) {
        q->head = node;
    } else {
        // Link the new node to the end of the queue
        q->tail->next = node;
    }

    // Update the tail pointer to the new node
    q->tail = node;

}

BattleTurn dequeue_battle_move(BattleQueue* q) {
    BattleTurn *temp= (BattleTurn *)malloc(sizeof(BattleTurn));
;
    // Check if the queue is empty
    if (q->head == NULL) {
        // Queue is empty, nothing to dequeue
        return *temp;
    }

    // Store the current head node in a temporary variable
    temp = q->head;

    // Move the head pointer to the next node
    q->head = q->head->next;

    // If the queue is now empty, update the tail to NULL as well
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // Decrease the count of elements in the queue
    q->elements -= 1;

    // Return the first turn
    return *temp;
}

// Stack
typedef struct {
    BattleTurn *head;
    int elements;
} BattleStack;

void init_battle_stack(BattleStack *s) {
    s->head = NULL;
    s->elements = 0;
}

void push_battle_move(BattleStack *s, int move, Character *character) {
    s->elements += 1;

    BattleTurn *node = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (node == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new node
    node->move_used = move;
    node->character = character;
    node->next = s->head;

    // Update the head pointer to the new node
    s->head = node;
}

BattleTurn pop_battle_move(BattleStack *s) {
    BattleTurn result;

    // Check if the stack is empty
    if (s->head == NULL) {
        // Stack is empty, nothing to pop
        // Handle the error as appropriate
        // Returning an uninitialized result here; you may want to handle this case differently
        return result;
    }

    // Store the current head node in a temporary variable
    BattleTurn *temp = s->head;

    // Move the head pointer to the next node
    s->head = s->head->next;

    // Copy the data from the node to the result before freeing it
    result.move_used = temp->move_used;
    result.character = temp->character;

    // Free the memory of the popped node
    free(temp);

    // Decrease the count of elements in the stack
    s->elements -= 1;

    // Return the popped turn
    return result;
}


typedef struct Chapter {    // We will use this as the nodes in the scenario queues
    int life;               // we can use this in case we want to go back in the game, to remember the amount of life we had at that point
    Scenario *scene;
    struct Chapter *next;
} Chapter;

// Queue
typedef struct {
    Chapter *head;
    Chapter *tail;
    int elements;
} ScenarioQueue;

void init_scene_queue(ScenarioQueue *q){
    q->head=NULL;
    q->tail=NULL;
    q->elements=0;
}

void enqueue_scenario(ScenarioQueue* q, Scenario *scene){
    q->elements+=1;

    Chapter *node = (Chapter *)malloc(sizeof(Chapter));
    if (node == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new node
    node->life = 100;
    node->scene = scene;
    node->next = NULL;

    // If the queue is empty, set head to the new node
    if (q->tail == NULL) {
        q->head = node;
    } else {
        // Link the new node to the end of the queue
        q->tail->next = node;
    }

    // Update the tail pointer to the new node
    q->tail = node;

}

Chapter dequeue_scenario(ScenarioQueue* q) {
    Chapter *temp= (Chapter *)malloc(sizeof(Chapter));
;
    // Check if the queue is empty
    if (q->head == NULL) {
        // Queue is empty, nothing to dequeue
        return *temp;
    }

    // Store the current head node in a temporary variable
    temp = q->head;

    // Move the head pointer to the next node
    q->head = q->head->next;

    // If the queue is now empty, update the tail to NULL as well
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // Decrease the count of elements in the queue
    q->elements -= 1;

    // Return the first turn
    return *temp;
}



Skill weapons[3] = {
        {"Shield", "Use your deception skills to inflict sudden damage to your enemy. Note that this attack works well against certain types of enemies.", true, 10, 5, 5},
        {"Bow and Arrow", "Use your youth and agility to surprise your enemy and dodge the enemy (extra defence). Note that this attack works well against certain types of enemies.", true, 5, 10, 5},
        {"Hammer", "You picture the emperor (he who is responsible for the death of your loved ones) as your enemy, you go crazy and inflict lots of damage on your enemy. Note that this attack works well against certain types of enemies.", true, 15, 0, 0}
};


Skill hero_skills[3] = {
        {"Deceit Attack", "Use your deception skills to inflict sudden damage to your enemy. Note that this attack works well against certain types of enemies.", true, 10, 5, 5},
        {"Agile Attack", "Use your youth and agility to surprise your enemy and dodge the enemy (extra defence). Note that this attack works well against certain types of enemies.", true, 5, 10, 5},
        {"Berserk", "You picture the emperor (he who is responsible for the death of your loved ones) as your enemy, you go crazy and inflict lots of damage on your enemy. Note that this attack works well against certain types of enemies.", true, 15, 0, 0},
        };

Skill special_skills[2] = {
        {"Regenerate", "Use your medicinal knowledge to heal yourself (+100 HP). Note that this ability can only be used once.", true, 0, 0, 100},
        {"Time Strike", "Time Strike /***********ADD DESCRIPT************/ Note that this ability can only be used once.", true, 0, 0, 0}
};
// cambiar les skills que hi han aqui
Skill enemy_skills[3] = {
        {"Deceit Attack", "Use your deception skills to inflict sudden damage to your enemy. Note that this attack works well against certain types of enemies.", false, 10, 0, 0},
        {"Agile Attack", "Use your youth and agility to surprise your enemy. Note that this attack works well against certain types of enemies.", false, 5, 0, 0},
        {"Berserk", "You picture the emperor (he who is responsible for the death of your loved ones) as your enemy, you go crazy and inflict lots of damage on your enemy. Note that this attack works well against certain types of enemies.", false, 15, 0, 0},
    };    

// Initialize options
Option opt1_rome = {"Forge Alliances", "You form alliances with other gladiators, pooling your strengths to overcome rivals together.", "Your alliances prove beneficial, leading to an increase in your characters attack points by 1.", 0, 1, 0};

Option opt2_rome = {"Face Adversaries", "You confront your adversaries directly, relying on your individual skills to prevail in combat.", "Your prowess in combat impresses both allies and rivals, solidifying your reputation as a formidable gladiator. Your HP and defense are increased by 1. Nevertheless, you got slightly injured, so your attack is reduced by 2 point", 10, -2, 1};

Option opt1_pompeii = {"Ally with Caesar", "You decide to ally yourself with Julius Caesar, intrigued by the potential benefits of such a powerful connection.", "Your alliance with Julius Caesar opens doors to new opportunities and grants you access to influential circles in Pompeii. You exploit those connections and gain 2 attack points but your defense is reduced by 1 as powerful enemies have spotted some of your weak points.", 0, 2, -1};

Option opt2_pompeii = {"Exercise Caution", "You choose to tread cautiously, wary of Julius Caesar's motives and the risks associated with such a partnership.", "Your cautious approach safeguards you from potential pitfalls and allows you to navigate the political landscape of Pompeii with prudence. You gain 2 HP points.", 0, 0, 2};

Option opt1_thermal = {"Investigate Argument", "You decide to investigate the heated argument, intrigued by the involvement of powerful figures.", "Your investigation uncovers valuable information and earns you the respect of influential individuals in the city. Additionally, Maximus Kratos invited you to a self-defense masterclass, earning you 3 defense points!", 0, 0, 3};

Option opt2_thermal = {"Mind Your Own Business", "You choose to mind your own business and enjoy the tranquility of the thermal baths, avoiding unnecessary entanglements.", "Your decision to stay out of the argument preserves your peace of mind and allows you to focus on your own goals. Your lack of implication loses you 2 attack points.", 0, -2, 0};

Option opt1_colosseum = {"Stand Your Ground", "You choose to stand your ground and face your opponent head-on, relying on your skills and courage to emerge victorious.", "Your bravery and skill in combat earn you the admiration of the crowd and the respect of your opponent. You gain 2 points on defense and 1 HP.", 10, 0, 1};

Option opt2_colosseum = {"Analyze Weaknesses", "You opt to analyze your opponent's weaknesses and exploit them strategically, seeking any advantage you can find.", "Your strategic approach seems to pay off as you exploit your opponent's weaknesses, you gain 3 attack points.", 0, 3, 0};


// Initialize decisions
Decision rome_dec = {"You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?", {&opt1_rome, &opt2_rome}, 0};

Decision pompeii_dec = {"At the designated rendezvous point, you come face to face with the enigmatic Julius Caesar, this still young and mysterious figure who summoned you. Their identity shrouded in secrecy, he offers you a proposition that could tip the balance of power in Pompeii. Will you ally yourself with this mysterious benefactor, or will you tread cautiously, wary of hidden agendas and ulterior motives?", {&opt1_pompeii, &opt2_pompeii}, 0};

Decision thermal_dec = { "As you soak in the rejuvenating waters, you notice a heated argument unfolding nearby. A group of powerful and influential figures of the city are engaged in a fierce debate, their voices echoing off the marble walls of the baths. Intrigued, you consider whether to investigate further or to mind your own business and enjoy the tranquility of the surroundings.", {&opt1_thermal, &opt2_thermal}, 0};

Decision colosseum_dec = {"As you await your turn in the arena, a hush falls over the crowd, and the gate opens to reveal your opponent: a fierce and imposing gladiator known for their ruthless efficiency in combat. In this moment of truth, will you stand your ground and face your opponent head-on, or will you seek a strategic advantage by analyzing their weaknesses and exploiting them?", {&opt1_colosseum, &opt2_colosseum}, 0};
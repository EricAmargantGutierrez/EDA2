#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_LENGTH 50
#define MAX_ITEMS 5
#define MAX_SKILLS 4
#define MAX_ENEMIES 3
#define OPTIONS 2

#include <stdbool.h>
// Define structs

// skills that the player or enemy can use in combat
typedef struct {
    char name[50];
    char description[300];
    bool can_be_used;
    float mod_atk;
    float mod_def;
    float mod_hp;
} Skill;


// entries in the dictionary that counts the usage of skills
typedef struct {
    char key[MAX_LENGTH];
    int value;
} Entry;


// dictionary that counts the usage of skills
typedef struct {
    Entry entries[MAX_ITEMS];
    int size;
    bool initialized;
} Dictionary;


// our player and its attributes
typedef struct {
    char name[50];
    float HP;
    float atk_pts;
    float def_pts;
    // these will be the choices the player has made in choosing skills
    // they will later be uploaded to the .txt file
    int first_skill;
    int second_skill;
    int weapon;
    int character_num;
    bool difficult;
    Skill skills[5];
    Dictionary dict;
} Character;

// enemy data structure
typedef struct {
    char name[50];
    float hp;
    float initial_hp;
    float atk;
    float def;
    Skill skills[3]; //enemies cannot heal themselves
} Enemy;


// different options that the player can choose in each scenario
typedef struct{
    char narrative_text_i[400];
    char response_text[200];
    char narrative_text_f[400];
    float hp_incr;
    float atk_incr;
    float def_incr;
} Option;


// the decision the player will face in each scenario
typedef struct {
    char question_text[400];
    Option *options[2];
    int option_number;
} Decision;


// the scenario
typedef struct scen {
    char name[50];
    char description[400];
    Enemy *enemies;
    Decision *choice;
    int life;
    int order;
    struct scen *next;
} Scenario;




// Data structure for the battle moves
typedef struct BattleTurn {
    int move_used;
    bool player;
    Character *character;
    struct BattleTurn *next;
} BattleTurn;

// queue for the battle moves
typedef struct {
    BattleTurn *head;
    BattleTurn *tail;
    int elements;
} BattleQueue;



// Data structure for the turns
typedef struct Turn {    // We will use this as the nodes in the scenario queues
    int which_player;
    struct Turn *next;
} Turn;

// Queue for the turns
typedef struct {
    Turn *head;
    Turn *tail;
    int elements;
} TurnQueue;


// stack for the battle turns
typedef struct {
    BattleTurn *head;
    int elements;
} BattleStack;


// Function declarations
void insert(Character *player, const char *key, int value);
void init_dictionary(Character *player);
int get(Character *player, const char *key);
void reinit_dictionary(Character *player);
void increment(Character *player, const char *key);

void init_battle_queue(BattleQueue *q);
void enqueue_battle_move(BattleQueue* q, int move, Character *character, bool player);
BattleTurn dequeue_battle_move(BattleQueue* q);

void init_battle_stack(BattleStack *s);
void push_battle_move(BattleStack *s, int move, Character *character);
BattleTurn pop_battle_move(BattleStack *s);

// declare initialized data structures we will use

extern Skill weapons[3];
extern Skill hero_skills[3];
extern Skill special_skills[2];
extern Skill enemy_skills[3];

extern Option opt1_rome;
extern Option opt2_rome;
extern Option opt1_pompeii;
extern Option opt2_pompeii;
extern Option opt1_thermal;
extern Option opt2_thermal;
extern Option opt1_colosseum;
extern Option opt2_colosseum;

extern Decision rome_dec;
extern Decision pompeii_dec;
extern Decision thermal_dec;
extern Decision colosseum_dec;

#endif // STRUCTURES

#include <stdio.h>
#include <stdbool.h>


// Define constants
#define MAX_SKILLS 4
#define MAX_ENEMIES 3
#define MAX_OPTIONS 2

// Define the structs

typedef struct {
    char name[50];
    char description[300];
    bool type;
    int mod_atk;
    int mod_def;
    int mod_hp;
} Skill;

typedef struct {
    char name[50];
    int HP;
    int atk_pts;
    int def_pts;
    Skill skills[4];
} Character;

typedef struct {
    char name[50];
    int hp;
    int atk;
    int def;
    Skill* skills[3]; //enemies cannot heal themselves
}Enemy;

typedef struct{
    char narrative_text_i[400];
    char response_text[200];
    char narrative_text_f[400];
} Option;

typedef struct {
    char question_text[400];
    int number_options; // always 2, we will use the macro declared as MAX_OPTIONS
    Option *options[2];
} Decision;

typedef struct  scen {
    char name[50];
    char description[400];
    Enemy *enemies;
    Decision *choice;
    struct scen *next;
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

BattleQueue* init_queue(BattleQueue *q){
    q->head=NULL;
    q->tail=NULL;
    q->elements=0;
    return q;
}

void enqueue_move(BattleQueue* q, int move, Character *character){
    q->elements+=1;
    BattleTurn node = {move, character, NULL};
    q->tail->next=&node;
    q->tail=q->tail->next;
}

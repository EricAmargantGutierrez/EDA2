#include <stdio.h>
#include <stdbool.h>

// Define the structs
typedef struct {
    char name[50];
    int HP;
    int atk_pts;
    int def_pts;
    char chosen_path;
    int skills[4];
} Character;

typedef struct {
    char name[50];
    char description[100];
} Skill;

typedef struct {
    char name[50];
    int atk;
    int hp;
    int def;
    int skill_IDS[4];
}Enemy;

typedef struct{
    char response_text[100];
    char narrative_text_i[200];
    Enemy enemies[3];
    char narrative_text_f[200];
}Option;

typedef struct {
    char question_text[200];
    int number_options;
    Option *what_happens;
}Decision;

typedef struct {
    char name[50];
    char description[200];
    Decision *choice;
}Scenario;

typedef struct QueueNode {
    int move_used;
    struct QueueNode *next;
} QueueNode;

// Queue
typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int elements;
} Queue;

Queue* init_queue(Queue *q){
    q->head=NULL;
    q->tail=NULL;
    q->elements=0;
    return q;
}

void enqueue(Queue* q, int move){
    q->elements+=1;
    QueueNode* node={move, NULL};
    q->tail->next=node;
    q->tail=q->tail->next;
}
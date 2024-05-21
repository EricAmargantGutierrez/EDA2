#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

void Enqueue_Battle(BattleQueue *queue, Character *character, Enemy* enemy) {
    // Create a new node
    BattleTurn *newNode = (BattleTurn *)malloc(sizeof(BattleTurn));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to enqueue.\n");
        return;
    }
    newNode->character = character;
    newNode->next = NULL;

    // If the queue is empty, set both head and tail to the new node
    if (queue->head == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        // Otherwise, add the new node to the end and update the tail
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    // Increment the number of elements in the queue
    queue->elements++;
}

void init_enemy(Enemy* enemy, char* name, int hp, int atk, int def){
    strcpy(enemy->name, name);
    enemy->hp = hp;
    enemy->atk = atk;
    enemy->def = def;
    memcpy(enemy->skills, enemy_skills, sizeof(enemy_skills));
}


void init_scenario(Scenario* scene, char* name, char* descript, Enemy* enemy, Decision* choice, Scenario *next){ //canviar
    strcpy(scene->name, name);
    strcpy(scene->description, descript);
    scene->enemies=enemy;
    scene->choice = choice;
    scene->next = next;
}


// Queue for the turns

typedef struct Turn {    // We will use this as the nodes in the scenario queues
    int which_player;
    struct Turn *next;
} Turn;

// Queue
typedef struct {
    Turn *head;
    Turn *tail;
    int elements;
} TurnQueue;

void init_turn_queue(TurnQueue* q){
    q->head=NULL;
    q->tail=NULL;
    q->elements=0;
}

void enqueue_turn(TurnQueue* q, int player_move){
    q->elements+=1;

    Turn *node = (Turn *)malloc(sizeof(Turn));
    if (node == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new node
    node->which_player = player_move;
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

int dequeue_turn(TurnQueue* q) {
    Turn *temp= (Turn *)malloc(sizeof(Turn));
;
    // Check if the queue is empty
    if (q->head == NULL) {
        // Queue is empty, nothing to dequeue
        return temp->which_player;
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
    return temp->which_player;
}
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



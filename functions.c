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
    enemy->initial_hp = hp;
    enemy->atk = atk;
    enemy->def = def;
    memcpy(enemy->skills, enemy_skills, sizeof(enemy_skills));
}


void init_scenario(Scenario* scene, char* name, char* descript, Enemy* enemy, Decision* choice, Scenario *next, Scenario *prev, int order){ //canviar
    strcpy(scene->name, name);
    strcpy(scene->description, descript);
    scene->enemies=enemy;
    scene->choice = choice;
    scene->next = next;
    scene->prev = prev;
    if(scene->prev==NULL){
        scene->life=100;
    }
    scene->order = order;
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


// Sorting algorithms
// Quicksort, which we will use to return in order how many times each skill has been carried out

void swap(Entry *a, Entry *b) {
    Entry temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Entry arr[], int low, int high) {
    int pivot = arr[high].value;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].value >= pivot) {  // Change comparison to sort in descending order
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(Entry arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

char** get_sorted_keys(Character* player) {
    // Sort the entries based on their values
    quicksort(player->dict.entries, 0, player->dict.size - 1);

    // Allocate memory for the array of keys
    char **sorted_keys = malloc(player->dict.size * sizeof(char*));
    if (!sorted_keys) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Extract the keys from the sorted entries
    for (int i = 0; i < player->dict.size; i++) {
        sorted_keys[i] = strdup(player->dict.entries[i].key);
    }

    return sorted_keys;
}

// Function to print information of a player (Character)
void print_player_info(Character* player) {
    printf("Player Name: %s\n", player->name);
    printf("Player Attack Points: %.2f\n", player->atk_pts);
    printf("Player HP: %.2f\n", player->HP);
    printf("Player Defense Points: %.2f\n\n", player->def_pts);
}


int read_decision(){
        char input[100];  // Buffer to hold the input
        int success;
        int choice;

        if (fgets(input, sizeof(input), stdin) != NULL) {
        // Attempt to parse the input as an integer
        success = sscanf(input, "%d", &choice);

        // Check if the parsing was successful
        if (success != 1) {
            return -1;
        }
        } else {
            printf("Error reading input.\n");
        }
        return choice;

}
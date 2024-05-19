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

void increment_characteristics(Character *player, Option *opt) {
    player->HP += opt->hp_incr;
    player->atk_pts += opt->atk_incr;
    player->def_pts += opt->def_incr;
}


void handle_scenario(Scenario* scenario, Character *player) {
    Decision* decision = scenario->choice;
    Option *opt1=scenario->choice->options[0];
    Option *opt2=scenario->choice->options[1];
    printf("%s\n\n", scenario->name);
    printf("%s\n\n", scenario->description);
    printf("%s\n", decision->question_text); // Print the decision question

    int option;
    bool valid_input = false;

    do {
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("%c\n\n", opt1->narrative_text_i);
                printf("%c\n\n", opt1->narrative_text_f);
                increment_characteristics(player, opt1);
                valid_input = true;
                break;
            case 2:
                printf("%c\n\n", opt2->narrative_text_i);
                printf("%c\n\n", opt2->narrative_text_f);
                increment_characteristics(player, opt2);
                valid_input = true;
                break;
            default:
                printf("Invalid Choice. There are only two options (1 & 2)\n");
                break;
        }
    } while (!valid_input);
}

void recover_player_hp(Character* player, int max_HP) {
    // Set the player's current HP to its maximum HP
    player->HP = max_HP;
}
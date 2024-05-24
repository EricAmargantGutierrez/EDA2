#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "structures.h"

int read_int() {
    int res, val;
    do {
        res = scanf("%d", &val);
        while (getchar() != '\n'); // Clear the input buffer
    } while (res != 1);
    return val;
}

void read_filename(char* filename) {
    int res;
    do {
        res = scanf("%s", filename);
    } while (res != 1);
}

int max(int a, int b) {
    return (a > b ? a : b);
}

// Function to save the game state to a file
void save_game(Scenario* scenario, Character* player) {
    // @brief Writes session sequence to a FILE
    // @Returns: nothing

    // 1. Checks for Sequence errors
    int life = player->HP;
    int enemy_life = scenario->enemies->hp;

    // 2. Set filename variable from standard input
    char filename[] = "saved_info.txt";

    // 3. Opens the filename FILE in writing-mode and
    //    checks that no errors are produced
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file\n");
        return; // Exit the function
    }

    // 4. Prints data to opened file as follows:
    //     - print the score of the first step and jump 
    //       to the next line,
    //     - for each row in the board matrix, print all
    //       numbers for that row separated by blank spaces
    //       and jump to next line for each new row
    //     - move to the next step in the sequence
    //    
    fprintf(fp, "%d\n", scenario->order);
    fprintf(fp, "%d\n", life);
    fprintf(fp, "%d\n", enemy_life);

    // 5. Closes the file
    fclose(fp);
}

// Function to load the game state from a file
void load_game(Scenario* scenario) {
    // @brief Reads a session sequence from a FILE
    // @Returns: the updated scenario pointer

    // 1. Sets filename variable from standard input
    
    // 2. Opens the filename FILE in reading-mode and
    //    checks that no errors are produced
    FILE *fp = fopen("saved_info.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file\n");
        return; // Exit the function
    }
    
    // 3. Restarts session sequence and game state
    // 4. Reads data from file with the same structure
    //    as it was saved, then adds the game state to
    //    the sequence
    int current_scenario;
    int life;
    int enemy_life;

    if (fscanf(fp, "%d%d%d", &current_scenario, &life, &enemy_life) != 3) {
        printf("Error reading data from file\n");
        fclose(fp);
        return;
    }
    
    // Navigate to the correct scenario
    while (scenario->order < current_scenario && scenario->next != NULL) {
        scenario = scenario->next;
    }
    while (scenario->order > current_scenario && scenario->prev != NULL) {
        scenario = scenario->prev;
    }
    
    // Update the scenario's data
    scenario->life = life;
    scenario->enemies->hp = enemy_life;
    
    // Close the file
    fclose(fp);
    return;
}

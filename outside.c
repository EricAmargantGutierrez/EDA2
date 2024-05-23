#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "structures.h"

int read_int(){
    int res, val;
    do{
        res = scanf("%d", &val);
    }while(res != 1);
    return val;
}

void read_filename(char* filename){
    int res;
    do{
        res = scanf("%s", filename);
    }while(res != 1);
}

int max(int a, int b){
    return (a>b?a:b);
}

int read_int(); 

void read_filename(char* filename); 

int max(int a, int b); 




// aqui estaria be començar ja amb les linked LISTS pels scenarios del JOC DE GLADIADORS


void save_game(Scenario* scenario, Character* player){
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
    if (fp == NULL){
        printf("Error");
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
    fprintf(fp, "%d ", enemy_life);

    // 5. Closes the file
    fclose(fp);
}

Scenario* load_game(Scenario* scenario){
    // @brief Reads a session sequence from a FILE
    // @Returns: nothing

    // 1. Sets filename variable from standard input
    char filename[] = "saved_info.txt";
    read_filename(filename);
    
    // 2. Opens the filename FILE in reading-mode and
    //    checks that no errors are produced
    // 3. Restarts session sequence and game state
    // 4. Reads data from file with the same structure
    //    as it was saved, then adds the game state to
    //    the sequence

    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error opening the file");
        return scenario; // Exit the function
    }
    int current_scenario=0;
    int life;
    int enemy_life;
    while (!feof(fp)){
        fscanf(fp, "%d", &current_scenario);
        fscanf(fp, "%d", &life);
        fscanf(fp, "%d", &enemy_life);
                }
    while(scenario->order<current_scenario && scenario->next!=NULL){
        scenario = scenario->next;
    }
    while(scenario->order>current_scenario && scenario->prev!=NULL){
        scenario = scenario->prev;
    }
    scenario->life=life;
    scenario->enemies->hp=enemy_life;
    fclose(fp);
    return scenario;
}
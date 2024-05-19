#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battles.c"

// Define the characters' stats
// Arnaus Decimus Meridius
// Ericus Carpophorus
// Paullus Acilius Glabrio

/*
void init_skills(Skill *ability, char* name, char* descript, bool type, int atk, int def, int hp){
    strcpy(ability->name, name);    
    strcpy(ability->description, descript);
    ability->type=type;
    ability->mod_atk=atk;
    ability->mod_def=def;
    ability->mod_hp=hp;
}

void init_option(Option* option, char* initial_text, char* response, char* final_text){
    strcpy(option->narrative_text_i, initial_text);    
    strcpy(option->response_text, response);
    strcpy(option->narrative_text_f, final_text);
}

void init_decision(Decision* decision, char* question, int num_options, Option* options){
    strcpy(decision->question_text, question);
    decision->number_options = num_options;
    decision->options = options; //change if it doesnt work
}

void init_enemy(Enemy* enemy, char* name, int hp, int atk, int def, Skill skills[3]){ //canviar
    strcpy(enemy->name, name);
    enemy->hp = hp;
    enemy->atk = atk;
    enemy->def = def;
    memcpy(enemy->skills, skills, sizeof(enemy->skills));
}

void init_scenario(Scenario* scene, char* name, char* descript, Enemy enemies[3], Decision* choice, Scenario *next){ //canviar
    strcpy(scene->name, name);
    strcpy(scene->description, descript);
    memcpy(scene->enemies, enemies, sizeof(scene->enemies));
    scene->choice = choice;
    scene->next = next;
}

*/


void configure_character(Character *player) {
    printf("Character selection:\n");
    printf("1. Arnaus Decimus Meridius\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 5\n");
    printf("   * Defense Points: 5\n");
    printf("2. Ericus Carpophorus\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 3\n");
    printf("   * Defense Points: 7\n");
    printf("3. Paullus Acilius Glabrio\n");
    printf("   * HP: 100\n");
    printf("   * Attack Points: 6\n");
    printf("   * Defense Points: 4\n");

    int choice;
    printf("Choose your character (1, 2, or 3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(player->name, "Arnaus Decimus Meridius");    
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            memcpy(player->skills, hero_skills, sizeof(hero_skills));
            break;
        case 2:
            strcpy(player->name, "Ericus Carpophorus");    
            player->HP = 100;
            player->atk_pts = 4;
            player->def_pts = 6;
            memcpy(player->skills, hero_skills, sizeof(hero_skills));
            
            break;
        case 3:
            
            strcpy(player->name, "Paullus Acilius Glabrio");
            player->HP = 100;
            player->atk_pts = 7;
            player->def_pts = 3;
            memcpy(player->skills, hero_skills, sizeof(hero_skills));
            
            break;
        default:
            printf("Invalid choice. Defaulting to Arnaus Decimus Meridius.\n");
            strcpy(player->name, "Arnaus Decimus Meridius");
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            memcpy(player->skills, hero_skills, sizeof(hero_skills));
            
            break;
    }
}


void start_game(Character *player){
    printf("Test %.2f, %.2f, %.2f", player->skills[1].mod_def, player->skills[1].mod_hp, player->skills[1].mod_atk);
    Enemy decimus;
    strcpy(decimus.name, "Decimus Brutus");
    decimus.hp = 80;
    decimus.atk = 5;
    decimus.def = 5;
    memcpy(decimus.skills, enemy_skills, sizeof(enemy_skills));
    battle1(player, &decimus);
}


void display_menu(Character *player) {
    int choice;
    bool chosen_character = false;

    do {
        printf("\n----- Gladiator RPG Menu -----\n");
        printf("1. Start New Game\n");
        printf("2. Configure Character before playing\n");
        printf("3. View Game Structure\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                if(chosen_character == false){
                    printf("Since you have not configured your character yet, you will be redirected to 'Configure Character'");
                    choice = 2;
                    break;
                }
                start_game(player); //this is the function that leads character through the different scenarios in the game
                break;
            case 2:
                configure_character(player); //this is the function that configures the players character
                chosen_character = true;
                break;
            case 3:
                printf("Game structure:\n");
                printf("Scenarios:\n");
                printf("1. Rome\n");
                printf("2. Shadows of PompeII\n");
                printf("3. The thermal baths\n");
                printf("4. Colosseum Showdown\n");
                break;
            case 4:
                printf("Exiting the game. Guess you couldn't handle the pressure!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
}


void print_enemy_info(Enemy* enemy) {
    printf("Enemy Name: %s\n", enemy->name);
    printf("Enemy Attack: %d\n", enemy->atk);
    printf("Enemy HP: %d\n", enemy->hp);
    printf("Enemy Defense: %d\n", enemy->def);
}

// Function to print information of a player (Character)
void print_player_info(Character* player) {
    printf("Player Name: %s\n", player->name);
    printf("Player Attack Points: %d\n", player->atk_pts);
    printf("Player HP: %d\n", player->HP);
    printf("Player Defense Points: %d\n", player->def_pts);
}

void main(){
    Character player;
    display_menu(&player);
}
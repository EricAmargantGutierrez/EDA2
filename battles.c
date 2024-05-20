#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "functions.c"
#define TURNS 15

void turn(Character* player, Enemy *enemy1, int move){
    // calculate the attack damage arithmetically
    //printf("Player \tatk %.2f, mod %.2f \n", player->atk_pts, player->skills[move-1].mod_atk);
    float damage=(player->skills[move-1].mod_atk+player->atk_pts);
    
    // subtract to the damage the defense of the enemy
    damage-=(enemy1->def)/2;
    // as this is still an RPG, there is some luck component associated to the result
    float odds=(rand()%31);
    odds/=100;
    odds+=0.8;
    // multiply the damage by the "luck factor"
    float attack_damage=damage*odds;
    player->HP+=player->skills[move-1].mod_hp;
   // printf("player dmg %.2f\t odds_dmg %.2f\t hp added %.2f \n", damage, odds, player->skills[move-1].mod_hp);
    enemy1->hp-=attack_damage;
}

void counter_Attack(Enemy* enemy1, Character* player, int enemy_move, int player_move){
    // calculate the attack damage arithmetically
    //printf("atk %.2f, mod %.2f \n", enemy1->atk, enemy1->skills[enemy_move].mod_atk);
    float damage=(enemy1->skills[enemy_move].mod_atk+enemy1->atk);
    // subtract to the damage the defense of the enemy
    damage-=(player->def_pts + player->skills[player_move-1].mod_def)/2;
    // same as in the "turn" function, we add a luck component to the result
    float odds=(rand()%21);
    odds/=100;
    odds+=0.7;
    // multiply the damage by the "luck factor"
    float attack_damage=damage*odds;
    
   // printf("enemy dmg %.2f\t odds_dmg %.2f \n", damage, attack_damage);
    player->HP-=attack_damage;
}

void battle(Character* player, Enemy* enemy){
    // Initialize the Queue where we will store the movements
    BattleQueue q;
    BattleStack stack;
    init_battle_stack(&stack);
    init_battle_queue(&q);
    srand(time(NULL));
    printf("FIGHT:\t%s VS %s \n\n", enemy->name, player->name);
    printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
    for(int i=0; i<15; i++){
        int move=0;
        // Read the integer input from the user
        int check=0;
        // Use a do-while loop to make sure the input is correct


        while (enemy->hp > 0.0 && player->HP > 0.0){
        printf("Enter your move: \n");
        printf("1. %s\n2. %s\n3. %s\n", player->skills[0].name, player->skills[1].name, player->skills[2].name);
        if(player->skills[3].can_be_used){printf("4. %s\n", player->skills[3].name);}
        printf("5. Info\n\n...\n");
        check=scanf("%d", &move);
        float enemy_attack;
        switch (move) {
            case 1:
                // Call function to inflict damage on the enemy
                turn(player, enemy, move);
                // enqueue the move used
                enqueue_battle_move(&q, move, player);
                // push the move used
                push_battle_move(&q, move, player);
                //enemy's turn
                enemy_attack=rand()%3;
                counter_Attack(enemy, player, enemy_attack, move);
                printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
                break;
            case 2:
                // Call function to inflict damage on the enemy
                turn(player, enemy, move);
                // enqueue the move used
                enqueue_battle_move(&q, move, player);
                // push the move used
                push_battle_move(&q, move, player);
                //enemy's turn
                enemy_attack=rand()%3;
                counter_Attack(enemy, player, enemy_attack, move);
                printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
                break;
            case 3:
                // Call function to inflict damage on the enemy
                turn(player, enemy, move);
                // enqueue the move used
                enqueue_battle_move(&q, move, player);
                // push the move used
                push_battle_move(&q, move, player);
                //enemy's turn
                enemy_attack=rand()%3;
                counter_Attack(enemy, player, enemy_attack, move);
                printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
                break;
            case 4:
                if(!player->skills[3].can_be_used){
                    printf("Already used this skill the maximum number of times");
                    break;}
                // Call function to inflict damage on the enemy
                turn(player, enemy, move);
                // enqueue the move used
                enqueue_battle_move(&q, move, player);
                // push the move used
                push_battle_move(&q, move, player);
                //enemy's turn
                enemy_attack=rand()%3;
                counter_Attack(enemy, player, enemy_attack, move);
                printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
                player->skills[3].can_be_used=false;
                break;
            case 5:
                printf("1. %s\n2. %s\n3. %s\n", player->skills[0].description, player->skills[1].description, player->skills[2].description);
                if(player->skills[3].can_be_used){printf("4. %s\n", player->skills[3].description);}
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } 
    }
    BattleTurn move_struct;
    int i=0;
    while(q.elements>0){
        i++;
        move_struct=dequeue_battle_move(&q);
        printf("The %d move we used was: %s \n", i, player->skills[move_struct.move_used-1].name);
    }
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
    printf("Player Attack Points: %.2f\n", player->atk_pts);
    printf("Player HP: %.2f\n", player->HP);
    printf("Player Defense Points: %.2f\n\n", player->def_pts);
}

void implement_option(Character* player, Scenario* scene){
    int choice;
    bool valid_input=false;
    do{
    printf("%s\n\n", scene->choice->question_text);
    printf("1. %s\n", scene->choice->options[0]->narrative_text_i);
    printf("2. %s\n", scene->choice->options[1]->narrative_text_i);
    printf("3. Info\n\n");    
    scanf("%d", &choice);
    switch (choice) {
            case 1:
                printf("%s\n\n", scene->choice->options[0]->response_text);
                printf("%s\n\n", scene->choice->options[0]->narrative_text_f);
                printf("New stats:\n");
                printf("Player Attack Points: %.2f + (%.2f)\n", player->atk_pts, scene->choice->options[0]->atk_incr);
                printf("Player Defense Points: %.2f + (%.2f)\n\n", player->def_pts, scene->choice->options[0]->def_incr);
                printf("Player HP: %.2f + (%.2f)\n", player->HP, scene->choice->options[0]->hp_incr);
                player->atk_pts+=scene->choice->options[0]->atk_incr;
                player->def_pts+=scene->choice->options[0]->def_incr;
                player->HP+=scene->choice->options[0]->hp_incr;
                valid_input=true;
                break;
            case 2:
                printf("%s\n\n", scene->choice->options[1]->response_text);
                printf("%s\n\n", scene->choice->options[1]->narrative_text_f);
                printf("New stats:\n");                
                printf("Player Attack Points: %.2f + (%.2f)\n", player->atk_pts, scene->choice->options[1]->atk_incr);
                printf("Player Defense Points: %.2f + (%.2f)\n\n", player->def_pts, scene->choice->options[1]->def_incr);
                printf("Player HP: %.2f + (%.2f)\n", player->HP, scene->choice->options[1]->hp_incr);
                player->atk_pts+=scene->choice->options[1]->atk_incr;
                player->def_pts+=scene->choice->options[1]->def_incr;
                player->HP+=scene->choice->options[1]->hp_incr;
                valid_input=true;
                break;
            case 3:
                print_player_info(player);
                printf("Choice 1:\n\tAttack increment:\t%.2f\n\tDefensive increment:\t%.2f\n\tHP increment:\t%.2f\n", scene->choice->options[0]->atk_incr, scene->choice->options[0]->def_incr, scene->choice->options[0]->hp_incr);
                printf("Choice 2:\n\tAttack increment:\t%.2f\n\tDefensive increment:\t%.2f\n\tHP increment:\t%.2f\n\n", scene->choice->options[1]->atk_incr, scene->choice->options[1]->def_incr, scene->choice->options[1]->hp_incr);
                break;
            default:
                printf("Invalid option, repeat your selection!");
                break;
    }}while(!valid_input);
}




void game(ScenarioQueue *Q, Character *player){
    Scenario *scene;
    Chapter temp;
    while(Q->elements>0){
        player->HP=Q->head->life;
        temp=dequeue_scenario(Q);
        scene=temp.scene;
        printf("\nYou are now in %s\n\n", scene->name);
        printf("%s\n\n", scene->description);
        implement_option(player, scene);
        battle(player, scene->enemies);
        if(Q->elements>0){Q->head->life=player->HP;}
    }
}
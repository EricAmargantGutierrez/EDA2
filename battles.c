#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "functions.c"
#define TURNS 15


void battle1(Character* player, Enemy *enemy){
    // Initialize the Queue where we will store the movements
    BattleQueue *q;
    q=init_queue(q);
    for(int i=0; i<15; i++){
        srand(time(NULL));
        int move=0;
        // Read the integer input from the user
        int check=0;
        // Use a do-while loop to make sure the input is correct
        do{
        printf("Enter your move (integer from 1-4): ");
        check=scanf("%d", &move);;
        }while(move<1 || move>4 || check!=0);
        // Call function to inflict damage on the enemy
        turn(player, enemy, move);
        printf("%d\n", enemy->hp);
        // enqueue the move used
        enqueue_move(q, move, player);

        //enemy's turn
        int enemy_attack=rand()%4;
        counter_Attack(enemy, player, enemy_attack);
    }
}

void turn(Character* player, Enemy *enemy1, int move){
    // calculate the attack damage arithmetically
    int damage=(player->skills[move].mod_atk+player->atk_pts);
    // subtract to the damage the defense of the enemy
    damage-=enemy1->def;
    // as this is still an RPG, there is some luck component associated to the result
    int odds=(rand()%31)/100;
    odds+=0.8;
    // multiply the damage by the "luck factor"
    int attack_damage=damage*odds;
    enemy1->hp-=attack_damage;
}

void counter_Attack(Enemy *enemy1, Character* player, int move){
    // calculate the attack damage arithmetically
    int damage=(enemy1->skills[move]+enemy1->atk);
    // subtract to the damage the defense of the enemy
    damage-=player->def_pts;
    // same as in the "turn" function, we add a luck component to the result
    int odds=(rand()%21)/100;
    odds+=0.8;
    // multiply the damage by the "luck factor"
    int attack_damage=damage*odds;
    enemy1->hp-=attack_damage;
}
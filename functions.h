#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structures.h"
#include "structures.c"

void Enqueue_Battle(BattleQueue *queue, Character *character, Enemy* enemy);
void init_enemy(Enemy* enemy, char* name, int hp, int atk, int def);
void init_scenario(Scenario* scene, char* name, char* descript, Enemy* enemy, Decision* choice, Scenario *next, int order);
void init_turn_queue(TurnQueue* q);
void enqueue_turn(TurnQueue* q, int player_move);
int dequeue_turn(TurnQueue* q);
char** get_sorted_keys(Character* player);
void print_player_info(Character* player);
int read_decision();

#endif // BATTLE_OPERATIONS_H

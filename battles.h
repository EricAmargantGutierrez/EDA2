#ifndef BATTLES_H
#define BATTLES_H

#include "structures.h"
#include "functions.h"
#include "functions.c"

// Function declarations
TurnQueue create_turns();
void turn(Character* player, Enemy *enemy1, int move);
void counter_Attack(Enemy* enemy1, Character* player, int enemy_move, int player_move);
bool battle(Character* player, Scenario* scen);
void implement_option(Character* player, Scenario* scene, int prev_choice);
void game(Scenario *scenario, Character *player, bool loaded);
void save_game(Scenario* scenario, Character* player, int turns);
Scenario* load_game(Scenario* scenario, Character *player);

#endif // BATTLES_H

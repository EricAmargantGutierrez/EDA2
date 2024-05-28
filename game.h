#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "battles.h"


// declare the functions from game.c
void configure_character(Character *player, int charact);
void start_game(Character *player, bool load_scenario);
void configure_skills(Character* player);
void play(Character *player);

#endif // GLADIATOR_H
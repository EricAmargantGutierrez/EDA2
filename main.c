#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game.c"

void main(){
    Character player;
    init_dictionary(&player);
    display_menu(&player);
}


// controlar els bounds dels valors llegits del .txt amb un %3
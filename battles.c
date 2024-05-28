#include "battles.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TURNS 15

// Declare the save game and load game functions
void save_game(Scenario* scenario, Character* player, int turns);
Scenario* load_game(Scenario* scenario, Character *player);


// Function to initialize the full queue of turns for the battle
// Some of the turns will be for the enemy and some for us, with 50/50 chances
// However it is possible that either us or the enemy will have several throws in a row
// Nevertheless, because each queue will have 16 turns, the total turn number will stabilise
TurnQueue create_turns(){
    // Create the queue with the turns
    TurnQueue queue;

    // Initialize an EMPTY queue of turns
    init_turn_queue(&queue);
    int number;
    //we want the player to always start, so that there is a smoother transition from the scenario text to the battle
    enqueue_turn(&queue, 1); 
    // Loop 15 times
    for(int i=0; i<TURNS; i++){
        // Pick a random number between 1 and 0, 1 will mean it's the user's turn, and 0 will mean it's the enemy's turn
        number=(int)rand()%2;
        // Enqueue whichever number we have
        enqueue_turn(&queue, number);
    }
    return queue;
}




void turn(Character* player, Enemy *enemy1, int move){
    // calculate the attack damage arithmetically

    // total damage = player attack + skill attack modifier - (enemy defense)/2
    float damage=(player->skills[move-1].mod_atk+player->atk_pts);
    damage-=(enemy1->def)/2;

    // as this is still an RPG, there is some luck component associated to the result
    float odds=(rand()%31);

    // there is a multiplier of damage which ranges randomly from 0.8 - 1.1
    odds/=100;
    odds+=0.8;

    // multiply the damage by the "luck factor"
    float attack_damage=damage*odds;
    player->HP+=player->skills[move-1].mod_hp;
    // subtract the damage from the HP of the enemy
    enemy1->hp-=attack_damage;
}

void counter_Attack(Enemy* enemy1, Character* player, int enemy_move, int player_move){
    // calculate the attack damage of the enemy arithmetically
    
    // total damage = enemy attack + enemy skill attack modifier - (player defense + player skill defense modifier)/2
    float damage=(enemy1->skills[enemy_move].mod_atk+enemy1->atk);
    damage-=(player->def_pts + player->skills[player_move-1].mod_def)/2;

    // same as in the "turn" function, we add a luck component to the result
    // ranges from 0.7 - 0.9   Slight advantage for the player in terms of luck
    float odds=(rand()%21);
    odds/=100;
    odds+=0.7;

    // multiply the damage by the "luck factor"
    float attack_damage=damage*odds;
    printf("You are hit with: %s\n", enemy1->skills[enemy_move].name);
    // subtract the damage from the HP of the player
    player->HP-=attack_damage;
}

int combat(Character* player, Scenario* scen){
    // Assign a pointer to the scenario's enemy for further simplification
    Enemy *enemy=scen->enemies;
    
    // Initialize the Queue where we will store the movements
    TurnQueue qturns = create_turns();

    // We will use the BattleQueue q, so that we can later print in order all of the moves in the battle
    BattleQueue q;
    // This stack will be used to store all our moves, so we can access them with the time strike
    BattleStack stack;
    // Initialize both data structures
    init_battle_stack(&stack);
    init_battle_queue(&q);
    srand(time(NULL));
    printf("FIGHT:\t%s VS %s \n\n", enemy->name, player->name);
    printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
    bool next_turn=true;
    int current_turn = 1;

    // in the case that we are loading a game, we have already played several turns, so we will dequeue as man turns from the queue, as turns we have played previously
    for(int i=0; i<player->turns_played; i++){
        dequeue_turn(&qturns);
    }
    player->turns_played=0;
    // While the conditions for us to keep playing are true
    while (enemy->hp > 0.0 && player->HP > 0.0 && qturns.elements>0){
    int move=0;
    // Read the integer input from the user

    // next turn will tell us if we can go forward because a valid move has been used
    // for example if we want info, or to save the game, we will not loose a turn, because this bool will be set to false
    if(next_turn){
        current_turn = dequeue_turn(&qturns);
        next_turn=false;
        }
    if(current_turn==1){

    // Print which moves can be used in each turn
    printf("Player's Turn \n\n");
    printf("1. %s\n2. %s\n", player->skills[0].name, player->skills[1].name);
    if(player->skills[2].can_be_used){printf("3. %s\n", player->skills[2].name);}
    if(player->skills[3].can_be_used){printf("4. %s\n", player->skills[3].name);}
    if(player->skills[4].can_be_used){printf("5. %s\n", player->skills[4].name);}
    printf("6. Info\n");
    printf("7. Save game\n");
    printf("8. Leave game\n\n...\n");
    move=read_decision();
    float enemy_attack;
    // Use a do-while loop to make sure the input is correct
    switch (move) {
        case 1:
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player, true);
            // push the move used
            push_battle_move(&stack, move, player);
            // increment the number of times used in the dictionary
            increment(player, player->skills[move-1].name);
            if(enemy->hp<0){enemy->hp=0;}
            if(player->HP<0){player->HP=0;}
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 2:
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player, true);
            // push the move used
            push_battle_move(&stack, move, player);   
            // increment the number of times used in the dictionary         
            increment(player, player->skills[move-1].name);
            if(enemy->hp<0){enemy->hp=0;}
            if(player->HP<0){player->HP=0;}
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 3:
            if(!player->skills[2].can_be_used){
                printf("Cool off period\n");
                break;}
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player, true);
            // push the move used
            push_battle_move(&stack, move, player);
            // increment the number of times used in the dictionary
            increment(player, player->skills[move-1].name);
            if(enemy->hp<0){enemy->hp=0;}
            if(player->HP<0){player->HP=0;}
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 4:
            if(!player->skills[3].can_be_used){
                printf("Already used this skill the maximum number of times\n");
                break;}
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player, true);
            // increment the number of times used in the dictionary
            increment(player, player->skills[move-1].name);
            // push the move used
            push_battle_move(&stack, move, player);
            if(enemy->hp<0){enemy->hp=0;}
            if(player->HP<0){player->HP=0;}
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            player->skills[3].can_be_used=false;
            next_turn=true;
            break;
        case 5:
            if(!player->skills[4].can_be_used){
                printf("Already used this skill the maximum number of times\n");
                break;}
                
            // we want to make sure that we will pop at least one element
            if(stack.elements<1){ printf("Can't be used, too few previous moves\n");
                break;};
            // we use the modulo, so that the turns we pop from the stack are in a range smaller or equal than the total number of elements in the stack
            int turns=rand()%(stack.elements);
            // increment the number of times used in the dictionary
            increment(player, player->skills[move-1].name);
            turns++;
            BattleTurn result;
            for(int i=0; i<turns; i++){
                result=pop_battle_move(&stack);
            }
            // Calculate the turn and inflict the damage

            // Make sure that we are not repeating a move that can only be used once (eg. HEALING)
            // as that would give a huge advantage of potentially +300HP
            if(!player->skills[result.move_used-1].can_be_used){
                result.move_used--;
            }
            // calculate the attack damage arithmetically, but give 2x the weight to the skill used
            printf("The time move is...\n%s\n\n", player->skills[result.move_used-1].name);
            float damage=2*(player->skills[result.move_used-1].mod_atk)+player->atk_pts;
            // subtract to the damage the defense of the enemy
            damage-=(enemy->def)/2;
            // as this is still an RPG, there is some luck component associated to the result
            float odds=(rand()%31);
            odds/=100;
            odds+=0.8;
            // multiply the damage by the "luck factor"
            float attack_damage=damage*odds;
            player->HP+=2*player->skills[result.move_used-1].mod_hp;
            enemy->hp-=attack_damage;
            // enqueue the move used
            enqueue_battle_move(&q, move, player, true);
            player->skills[4].can_be_used=false;
            if(enemy->hp<0){enemy->hp=0;}
            if(player->HP<0){player->HP=0;}
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 6:
            print_player_info(player);
            printf("1. %s\n2. %s\n3. %s\n", player->skills[0].description, player->skills[1].description, player->skills[2].description);
            if(player->skills[3].can_be_used){printf("4. %s\n", player->skills[3].description);}
            if(player->skills[4].can_be_used){printf("5. %s\n", player->skills[4].description);}
            next_turn = false;
            break;
        case 7:
            save_game(scen, player, (16-qturns.elements));
            printf("\nYour game was saved. Press '8' to leave the game\n");
            next_turn = false;
            break;
        case 8:
            // return -1 means we have left the game without either winning nor loosing
            return -1;
        default:
            // set the next turn to true, so that a turn is lost, and next time the user will be more careful
            printf("Invalid choice. (Your blunder lost you a turn)\n");
            next_turn=true;
            break;
    }
    // apply the cooldown period if necessary on the Invisible Knife
    if(strcmp(player->skills[2].name, "Invisible Knife (Cool Down)")==0){
        if(move==3){
            player->skills[2].can_be_used=false;
        }
        else{
            player->skills[2].can_be_used=true;
        }
    }
    else{
        player->skills[2].can_be_used=true;
    }
    }

    // If it is the enemies turn
    if(current_turn==0){
        printf("%s's Turn:\n\n", enemy->name);
        // Enemy counter_attack
        // generate a random move for the enemy
        int enemy_attack=rand()%3;

        // use the counter attack function
        counter_Attack(enemy, player, enemy_attack, move);
        // log the move so we can later have a summary of all the moves
        enqueue_battle_move(&q, enemy_attack, player, false);
        if(enemy->hp<0){enemy->hp=0;}
        if(player->HP<0){player->HP=0;}
        printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
        next_turn=true;
    }

    if(player->HP<1){

        // LOST THE BATTLE
        printf("Battle summary!\n");
        BattleTurn move_struct;
        int i=0;
        while(q.elements>0){
            i++;
            move_struct=dequeue_battle_move(&q);
            if(move_struct.player){
                printf("%d. You used was: %s \n", i, player->skills[move_struct.move_used-1].name);
                }
            if(!move_struct.player){
                printf("%d. %s used: %s \n", i, enemy->name, enemy->skills[move_struct.move_used].name);
            }
        }
        // return 0 means the battle is lost
        return 0;
    }
    else if(enemy->hp<1){
        // WON THE BATTLE
        printf("Battle summary!\n");
        BattleTurn move_struct;
        int i=0;
        while(q.elements>0){
            i++;
            move_struct=dequeue_battle_move(&q);
            if(move_struct.player){
                printf("%d. You used was: %s \n", i, player->skills[move_struct.move_used-1].name);
                }
            if(!move_struct.player){
                printf("%d. %s used: %s \n", i, enemy->name, enemy->skills[move_struct.move_used].name);
            }
        }
        // 
        // return 1 means the battle is won
        return 1;
    }
    if(qturns.elements<1){
        // LOST THE BATTLE
        printf("You are out of turns\n");
        printf("Battle summary!\n");

        BattleTurn move_struct;
        int i=0;
        while(q.elements>0){
            i++;
            move_struct=dequeue_battle_move(&q);
            if(move_struct.player){
                printf("%d. You used was: %s \n", i, player->skills[move_struct.move_used-1].name);
                }
            if(!move_struct.player){
                printf("%d. %s used: %s \n", i, enemy->name, enemy->skills[move_struct.move_used].name);
            }
        }
        // return 0 means the battle is lost
        return 0;
    }
} 
    
}

// self-explanatory
void print_enemy_info(Enemy* enemy) {
    printf("Enemy Name: %s\n", enemy->name);
    printf("Enemy Attack: %d\n", enemy->atk);
    printf("Enemy HP: %d\n", enemy->hp);
    printf("Enemy Defense: %d\n", enemy->def);
}


// Implement the option chosen in each decision
void implement_option(Character* player, Scenario* scene, int prev_choice){
    int choice=prev_choice;
    bool valid_input=false;
    do{
        // print the 2 options and an info
    if(choice==-1){
    printf("%s\n\n", scene->choice->question_text);
    printf("1. %s\n", scene->choice->options[0]->narrative_text_i);
    printf("2. %s\n", scene->choice->options[1]->narrative_text_i);
    printf("3. Info\n\n");    
    choice=read_decision();
    choice--;
    }

    // modify the stats as it pertains to each decision
    // print how the stats are modified for a better user experience
    switch (choice) {
            case 0:
                printf("%s\n\n", scene->choice->options[0]->response_text);
                printf("%s\n\n", scene->choice->options[0]->narrative_text_f);
                scene->choice->option_number=0;
                printf("New stats:\n");
                printf("Player Attack Points: %.2f + (%.2f)\n", player->atk_pts, scene->choice->options[0]->atk_incr);
                printf("Player Defense Points: %.2f + (%.2f)\n\n", player->def_pts, scene->choice->options[0]->def_incr);
                printf("Player HP: %.2f + (%.2f)\n", player->HP, scene->choice->options[0]->hp_incr);
                player->atk_pts+=scene->choice->options[0]->atk_incr;
                player->def_pts+=scene->choice->options[0]->def_incr;
                player->HP+=scene->choice->options[0]->hp_incr;
                valid_input=true;
                break;
            case 1:
                printf("%s\n\n", scene->choice->options[1]->response_text);
                printf("%s\n\n", scene->choice->options[1]->narrative_text_f);
                scene->choice->option_number=1;
                printf("New stats:\n");                
                printf("Player Attack Points: %.2f + (%.2f)\n", player->atk_pts, scene->choice->options[1]->atk_incr);
                printf("Player Defense Points: %.2f + (%.2f)\n\n", player->def_pts, scene->choice->options[1]->def_incr);
                printf("Player HP: %.2f + (%.2f)\n", player->HP, scene->choice->options[1]->hp_incr);
                player->atk_pts+=scene->choice->options[1]->atk_incr;
                player->def_pts+=scene->choice->options[1]->def_incr;
                player->HP+=scene->choice->options[1]->hp_incr;
                valid_input=true;
                break;
            case 2:
                print_player_info(player);
                printf("Choice 1:\n\tAttack increment:\t%.2f\n\tDefensive increment:\t%.2f\n\tHP increment:\t%.2f\n", scene->choice->options[0]->atk_incr, scene->choice->options[0]->def_incr, scene->choice->options[0]->hp_incr);
                printf("Choice 2:\n\tAttack increment:\t%.2f\n\tDefensive increment:\t%.2f\n\tHP increment:\t%.2f\n\n", scene->choice->options[1]->atk_incr, scene->choice->options[1]->def_incr, scene->choice->options[1]->hp_incr);
                break;
            default:
                printf("Invalid option, repeat your selection!");
                break;
    }
    choice=-1;
    }while(!valid_input);
}



// main game function
void game(Scenario *scenario, Character *player, bool loaded){
    while(true){
        // put the scenario's life to the value of the player's life when he first enters a scenario
        // this will serve us when we revive, so that we start with the life we had at the beginning
        player->HP=scenario->life;
        printf("\nYou are now in %s\n\n", scenario->name);
        printf("%s\n\n", scenario->description);

        // if we have loaded the game, then the choice is already taken
        if(!loaded){
            // we pass -1 as an argument so that the program knows this is not a loaded game
        implement_option(player, scenario, -1);
        }
        else{  
            // if we are in a loaded game, then we can already pass which choice we want
        implement_option(player, scenario, scenario->choice->option_number);
        loaded=false;
        }

        // call the combat
        // as the combat returns an int, we will know if we have won (1), lost (0), or left (-1)
        int result=combat(player, scenario);
        // if we are not yet at the last scenario, and we have won
        if(scenario->next!=NULL && result==1){
            // we pass to the next scenario, and set the life of the next scenario to the current life of the player
            scenario=scenario->next;
            scenario->life=player->HP;
            }
            // if we have lost
        else if(result==0){
            // either if we are at the last scenario, or if we are in difficult mode, we DIE permanently
            if(scenario->next==NULL || player->difficult){
                printf("FATALITY\n\n");
                scenario=scenario->next;
                return;
            }
            else{
                // if we have lost, but are in one of the first 3 scenarios, and are in easy mode, then we start over the scenario
                printf("YOU HAVE FAILED!\nLUCKY FOR YOU, THE GODDESS FORTUNE HAS GRANTED YOU ANOTHER CHANCE! \n\n");
                // set the hp of the enemy to its initial value
                scenario->enemies->hp = scenario->enemies->initial_hp;
                // we are given the choice to choose our option again, so we must subtract the modifiers
                player->atk_pts-=scenario->choice->options[scenario->choice->option_number]->atk_incr;
                player->def_pts-=scenario->choice->options[scenario->choice->option_number]->def_incr;
                player->HP-=scenario->choice->options[scenario->choice->option_number]->hp_incr;
            }
        }
        else if(result==-1){
            // if we have simply left the game using that option, then we return to the main menu
                return;
        }
        else{
            // if we have won, and are in the last scenario, then we HAVE WON the GAME!!!
            // YAAAAY
            printf("YOU HAVE WON!\n\n");
            return;
        }
    }
}


////////////////////////////


// function to save the game
void save_game(Scenario* scenario, Character* player, int turns){

    int life = player->HP;
    int enemy_life = scenario->enemies->hp;

    // Set filename variable from standard input
    char filename[] = "saved_info.txt";

    // Opens the filename FILE in writing-mode and checks that no errors are produced
    FILE *fp = fopen(filename, "w");
    if (fp == NULL){
        printf("Error");
        return; // Exit the function
    }


    int difficulty;
    if(player->difficult){
        difficulty=1;
    }
    else{
        difficulty=0;
    }

    int used_regenerate;
    if(player->skills[3].can_be_used){
        used_regenerate=1;
    }
    else{
        used_regenerate=0;
    }

    int used_timestrike;
    if(player->skills[3].can_be_used){
        used_timestrike=1;
    }
    else{
        used_timestrike=0;
    }



    // Prints data to opened file

    fprintf(fp, "%d\n", scenario->order);
    fprintf(fp, "%d\n", ((int)(player->HP - scenario->choice->options[scenario->choice->option_number]->hp_incr)));
    fprintf(fp, "%d\n", scenario->choice->option_number);
    fprintf(fp, "%d\n", ((int)(player->atk_pts - scenario->choice->options[scenario->choice->option_number]->atk_incr)));
    fprintf(fp, "%d\n", ((int)(player->def_pts - scenario->choice->options[scenario->choice->option_number]->def_incr)));
    fprintf(fp, "%d\n", (int)enemy_life);
    fprintf(fp, "%d\n", player->first_skill);
    fprintf(fp, "%d\n", player->second_skill);
    fprintf(fp, "%d\n", player->weapon);
    fprintf(fp, "%d\n", player->character_num);
    fprintf(fp, "%d\n", difficulty);
    fprintf(fp, "%d\n", used_regenerate);
    fprintf(fp, "%d\n", used_timestrike);
    fprintf(fp, "%d\n", turns);

    // Closes the file
    fclose(fp);
}

Scenario* load_game(Scenario* scenario, Character *player){

    
    //  Opens the filename FILE in reading-mode and checks that no errors are produced
    // 4. Reads data from file with the same structure as it was saved

    FILE *fp = fopen("saved_info.txt", "r");
    if (fp == NULL){
        printf("You still haven't saved any game! Defaulting to base attributes");
        // Initialize default values so we don't get an error
        player->atk_pts = 5;  
        player->def_pts = 5;
        player->first_skill = 0;
        player->second_skill = 1;
        player->weapon = 0;
        player->character_num = 0;
        return scenario; // Exit the function
    }

    // Declare local variables in which we will use to save the data loaded from the .txt files 
    int current_scenario=0;
    int life;
    int enemy_life;
    int atk;
    int def;
    int first;
    int second;
    int weapon;
    int charact;
    int option_number;
    int difficulty;
    int used_regenerate;
    int used_timestrike;
    int turns;

  while (fscanf(fp, "%d", &current_scenario) != EOF) {
        if (fscanf(fp, "%d", &life) != 1 ||
            fscanf(fp, "%d", &option_number) != 1 ||
            fscanf(fp, "%d", &atk) != 1 ||
            fscanf(fp, "%d", &def) != 1 ||
            fscanf(fp, "%d", &enemy_life) != 1 ||
            fscanf(fp, "%d ", &first) != 1 ||
            fscanf(fp, "%d ", &second) != 1 ||
            fscanf(fp, "%d ", &weapon) != 1 ||
            fscanf(fp, "%d ", &charact) != 1 ||
            fscanf(fp, "%d ", &difficulty) != 1 ||
            fscanf(fp, "%d ", &used_regenerate) != 1 ||
            fscanf(fp, "%d ", &used_timestrike) != 1 ||
            fscanf(fp, "%d ", &turns) != 1){
            printf("You still haven't saved any game! Defaulting to base attributes");
            // Check for errors
            
        // Initialize default values so we don't get an error
        player->atk_pts = 5;  
        player->def_pts = 5;
        player->first_skill = 0;
        player->second_skill = 1;
        player->weapon = 0;
        player->character_num = 0;
        return scenario; // Exit the function
        }
        }

    // Run thorugh the linked lists of the scenarios until we have reached the desired scenario
    while(scenario->order<current_scenario && scenario->next!=NULL){
        scenario = scenario->next;
    }



    
    // Keep the values inside the desired range so we don't get segmentation errors or unreasonable values
    atk%=10;
    def%=10;
    life%=300;
    enemy_life%=150;
    first%=3;
    second%=3;
    weapon%=3;
    charact%=3;
    option_number%=4;
    difficulty%=2;
    used_regenerate%=2;
    used_timestrike%=2;
    turns%=16;

    if(difficulty==1){
        player->difficult=true;
    }
    else{
        player->difficult=false;
    }

    if(used_regenerate==1){
        player->skills[3].can_be_used=true;
    }
    else{
        player->skills[3].can_be_used=false;
    }

    if(used_regenerate==1){
        player->skills[4].can_be_used=true;
    }
    else{
        player->skills[4].can_be_used=false;
    }

    // save the values we have retrieved from the .txt file to the palyer and scenario attributes
    player->atk_pts = atk;  
    player->def_pts = def;
    scenario->life=life;
    scenario->enemies->hp=enemy_life;
    player->first_skill=first;
    player->second_skill=second;
    player->weapon=weapon;
    player->character_num=charact;  
    scenario->choice->option_number=option_number;  
    player->turns_played=turns;

    // close the file    
    fclose(fp);
    return scenario;
}
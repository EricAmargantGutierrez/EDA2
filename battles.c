#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "functions.c"

#define TURNS 15


TurnQueue create_turns(){
    // Create the queue with the turns
    TurnQueue queue;
    init_turn_queue(&queue);
    int number;
    enqueue_turn(&queue, 1); //we want the player to always start, so that there is a smoother transition
    for(int i=0; i<TURNS; i++){
        number=(int)rand()%2;
        enqueue_turn(&queue, number);
    }
    return queue;
}




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

bool battle(Character* player, Scenario* scen){
    // Initialize the Queue where we will store the movements
    Enemy *enemy=scen->enemies;
    TurnQueue turns = create_turns();
    BattleQueue q;
    BattleStack stack;
    init_battle_stack(&stack);
    init_battle_queue(&q);
    srand(time(NULL));
    printf("FIGHT:\t%s VS %s \n\n", enemy->name, player->name);
    printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
    bool next_turn=true;
    int current_turn = 1;
    while (enemy->hp > 0.0 && player->HP > 0.0 && turns.elements>0){
    int move=0;
    // Read the integer input from the user
    if(next_turn){
        current_turn = dequeue_turn(&turns);
        printf("%d\n", current_turn);
        next_turn=false;
        }
    if(current_turn==1){
    printf("Player's Turn \n\n");
    printf("1. %s\n2. %s\n3. %s\n", player->skills[0].name, player->skills[1].name, player->skills[2].name);
    if(player->skills[3].can_be_used){printf("4. %s\n", player->skills[3].name);}
    if(player->skills[4].can_be_used){printf("5. %s\n", player->skills[4].name);}
    printf("6. Info\n");
    printf("7. Save game\n\n...\n");
    scanf("%d", &move);
    float enemy_attack;
    // Use a do-while loop to make sure the input is correct
    switch (move) {
        case 1:
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player);
            // push the move used
            push_battle_move(&stack, move, player);
            increment(player, player->skills[move-1].name);
            //enemy's turn
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 2:
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player);
            // push the move used
            push_battle_move(&stack, move, player);            
            increment(player, player->skills[move-1].name);
            //enemy's turn
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 3:
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player);
            // push the move used
            push_battle_move(&stack, move, player);
            increment(player, player->skills[move-1].name);
            //enemy's turn
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            next_turn=true;
            break;
        case 4:
            if(!player->skills[3].can_be_used){
                printf("Already used this skill the maximum number of times");
                break;}
            // Call function to inflict damage on the enemy
            turn(player, enemy, move);
            // enqueue the move used
            enqueue_battle_move(&q, move, player);
            increment(player, player->skills[move-1].name);
            // push the move used
            push_battle_move(&stack, move, player);
            printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
            player->skills[3].can_be_used=false;
            next_turn=true;
            break;
        case 5:
            if(!player->skills[4].can_be_used){
                printf("Already used this skill the maximum number of times");
                break;}
            if(stack.elements<1){ printf("Can't be used, too few previous moves");
                break;};
            // we want to make sure that we will pop at least one element
            int turns=rand()%(stack.elements);
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
            enqueue_battle_move(&q, move, player);
            player->skills[4].can_be_used=false;
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
            save_game(scen, player);
            next_turn = false;
            break;
        default:
            printf("Invalid choice. Please enter a valid option. (Your blunder lost you a turn)\n");
            break;
    }}
    if(current_turn==0){
        printf("%s's Turn:\n\n", enemy->name);
        // Enemy counter_attack
        int enemy_attack=rand()%3;
        counter_Attack(enemy, player, enemy_attack, move);
        printf("HP:\t%s: %.2f \t%s: %.2f \n", enemy->name, enemy->hp, player->name, player->HP);
        next_turn=true;
    }

    if(player->HP<0 || turns.elements<0){
        return false;
    }
    else if(enemy->hp<0){
        return true;
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

void implement_option(Character* player, Scenario* scene, int prev_choice){
    int choice=0;
    bool valid_input=false;
    do{
    if(prev_choice==-1){printf("%s\n\n", scene->choice->question_text);
    printf("1. %s\n", scene->choice->options[0]->narrative_text_i);
    printf("2. %s\n", scene->choice->options[1]->narrative_text_i);
    printf("3. Info\n\n");    
    scanf("%d", &choice);
    choice--;
    }
    else{
        //choice=prev_choice;
        printf("LOL");
        choice=0;
    }
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
    }}while(!valid_input);
}




void game(Scenario *scenario, Character *player, bool loaded){
    Chapter temp;
    while(true){
        player->HP=scenario->life;
        printf("\nYou are now in %s\n\n", scenario->name);
        printf("%s\n\n", scenario->description);
        if(!loaded){
        implement_option(player, scenario, -1);
        }
        else{  
        implement_option(player, scenario, scenario->choice->option_number);
        }
        bool won=battle(player, scenario);
        if(scenario->next!=NULL && won){
            scenario=scenario->next;
            scenario->life=player->HP;
            }
        else if(!won){
            if(scenario->next==NULL){
                printf("FATALITY\n\n");
                scenario=scenario->next;
                return;
            }
            else{
                printf("WOMP WOMP, TOU HAVE LOST! REPEAT THE SCENARIO\n\n");
                scenario->enemies->hp = scenario->enemies->initial_hp;
            }
        }
        else{
            printf("YOU HAVE WON!\n\n");
            return;
        }
    }
}


////////////////////////////
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
    fprintf(fp, "%d\n", ((int)(player->HP - scenario->choice->options[scenario->choice->option_number]->hp_incr)));
    fprintf(fp, "%d\n", scenario->choice->option_number);
    fprintf(fp, "%d\n", ((int)(player->atk_pts - scenario->choice->options[scenario->choice->option_number]->atk_incr)));
    fprintf(fp, "%d\n", ((int)(player->def_pts - scenario->choice->options[scenario->choice->option_number]->def_incr)));
    fprintf(fp, "%d\n", (int)enemy_life);
    fprintf(fp, "%d\n", player->first_skill);
    fprintf(fp, "%d\n", player->second_skill);
    fprintf(fp, "%d\n", player->weapon);
    fprintf(fp, "%d\n", player->character_num);

    // 5. Closes the file
    fclose(fp);
}

Scenario* load_game(Scenario* scenario, Character *player){
    // @brief Reads a session sequence from a FILE
    // @Returns: nothing

    
    // 2. Opens the filename FILE in reading-mode and
    //    checks that no errors are produced
    // 3. Restarts session sequence and game state
    // 4. Reads data from file with the same structure
    //    as it was saved, then adds the game state to
    //    the sequence

    FILE *fp = fopen("saved_info.txt", "r");
    if (fp == NULL){
        printf("You still haven't saved any game!");
        return scenario; // Exit the function
    }
    int current_scenario=0;
    int life;
    int enemy_life;
    int atk;
    int def;
    int first;
    int second;
    int weapon;
    int charact;
    while (!feof(fp)){
        fscanf(fp, "%d", &current_scenario);
        fscanf(fp, "%d", &life);     
        fscanf(fp, "%d", scenario->choice->option_number);
        fscanf(fp, "%d", &atk);
        fscanf(fp, "%d", &def);
        fscanf(fp, "%d", &enemy_life);
        fscanf(fp, "%d ", &first);
        fscanf(fp, "%d ", &second);
        fscanf(fp, "%d ", &weapon);
        fscanf(fp, "%d ", &charact);
                }
    while(scenario->order<current_scenario && scenario->next!=NULL){
        scenario = scenario->next;
    }
    while(scenario->order>current_scenario && scenario->prev!=NULL){
        scenario = scenario->prev;
    }
    player->atk_pts = atk;  
    player->def_pts = def;
    scenario->life=life;
    scenario->enemies->hp=enemy_life;
    player->first_skill=first;
    player->second_skill=second;
    player->weapon=weapon;
    player->character_num=charact;        
    fclose(fp);
    return scenario;
}
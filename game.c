#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battles.c"


void configure_character(Character *player, int charact) {
    int choice;
    int level;
    printf("Choose difficulty!\n\t1. Medium (Revives allowed)\n\t2. Legendary\n\t");
    level=read_decision();
    if(level==2){
        player->difficult=true;
    }
    else{
        player->difficult=false;
    }
    if(charact!=-1){
        choice=charact;
        }
    else{
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

    printf("Choose your character (1, 2, or 3): ");
    
    choice=read_decision();
}

    switch (choice) {
        case 1:
            strcpy(player->name, "Arnaus Decimus Meridius");    
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            player->character_num = 1;
            break;
        case 2:
            strcpy(player->name, "Ericus Carpophorus");    
            player->HP = 100;
            player->atk_pts = 4;
            player->def_pts = 6;
            player->character_num = 2;
            break;
        case 3:
            
            strcpy(player->name, "Paullus Acilius Glabrio");
            player->HP = 100;
            player->atk_pts = 7;
            player->def_pts = 3;
            player->character_num = 3;
            break;
        default:
            printf("Invalid choice. Defaulting to Arnaus Decimus Meridius.\n");
            strcpy(player->name, "Arnaus Decimus Meridius");
            player->HP = 100;
            player->atk_pts = 5;
            player->def_pts = 5;
            player->character_num = 1;
            break;
    }
}


void start_game(Character *player, bool load_scenario){
    Enemy decimus;
    Enemy cult;
    Enemy mercenaries;
    Enemy Sulla;
    Scenario rome;
    Scenario shadows_of_pompeii;
    Scenario thermal_baths;
    Scenario colosseum_showdown;
    init_enemy(&decimus, "Decimus Brutus", 80, 4, 5);
    init_enemy(&cult, "Cult of Bacchus", 90, 5, 5);
    init_enemy(&mercenaries, "The Mercenaries", 100, 5, 6);
    init_enemy(&Sulla, "Lucius Cornelius Sulla", 120, 6, 6);
    decimus.skills[2]=particular_enemy_skills[0];
    cult.skills[2]=particular_enemy_skills[1];
    mercenaries.skills[2]=particular_enemy_skills[2];
    Sulla.skills[2]=particular_enemy_skills[3];
    init_scenario(&rome, "Rome", "In the heart of ancient Rome, your journey begins. In a context of post-civil war between the Optimates and Populares factions in the senate, the roman plebs live under the yoke of Optimate tyranny, and the Dictatorship of Lucius Cornelius Sulla. Navigate the streets wisely, for every choice shapes your destiny. Adventure awaits in the arena and beyond. Let the games begin! \n\n", &decimus, &rome_dec, &shadows_of_pompeii, NULL, 1);
    init_scenario(&shadows_of_pompeii, "Shadows of Pompeii", "In the twilight of Pompeii's ruins, mysteries lurk beneath ash-covered streets. Navigate shadows fraught with intrigue and danger. Will you unravel secrets or become entangled in deceit? Choose wisely; in Pompeii, history's whispers echo loudest", &cult, &pompeii_dec, &thermal_baths, &rome, 2);
    init_scenario(&thermal_baths, "The Thermal Baths", "After the tumultuous events in Pompeii, you seek respite and refuge in the tranquil surroundings of the thermal baths. Here, amidst the soothing waters and opulent surroundings, you contemplate your next move in the ever-shifting game of power and intrigue.", &mercenaries, &thermal_dec, &colosseum_showdown, &shadows_of_pompeii, 3);
    init_scenario(&colosseum_showdown, "The Colosseum Showdown", "Whatever happens, you end up detained at the hands of the praetorian guard. You are brought back to Rome where a trial is set to begin. After a couple of sessions, it is already clear that the magistrate, the Optimate Dictator Lucius Cornelius Sulla, wants to condemn you whatever the cost may be, and that the sentence is likely set from the beginning of the trial: death at the Tarpeian Rock!", &Sulla, &colosseum_dec, NULL, &thermal_baths, 4);
    Scenario* scen = &rome;
    if(load_scenario){
        // incr, character_num
        scen = load_game(scen, player);
        // normal data
        configure_character(player, player->character_num);
        player->skills[0]=hero_skills[player->first_skill];
        player->skills[1]=hero_skills[player->second_skill];
        player->skills[2]=weapons[player->weapon];
        player->skills[3]=special_skills[0];
        player->skills[4]=special_skills[1];
        insert(player, player->skills[0].name, 0);
        insert(player, player->skills[1].name, 0);
        insert(player, player->skills[2].name, 0);
        insert(player, player->skills[3].name, 0);
        insert(player, player->skills[4].name, 0);
    }
    game(scen, player, load_scenario);
    for(int i=0; i<5; i++){
        printf("%s has been used %d times\n", player->skills[i].name, get(player, player->skills[i].name));
    }
    printf("\n\n");
    char **sorted_keys = get_sorted_keys(player);
    if (sorted_keys) {
        printf("\nSorted keys based on values:\n");
        for (int i = 0; i < player->dict.size; i++) {
            printf("%d.\t%s\n", (i+1), sorted_keys[i]);
            free(sorted_keys[i]); // Free each allocated string
        }
        free(sorted_keys); // Free the array itself
    }

}

void configure_skills(Character* player){
    int choice;
    int already_chosen=0;
    printf("\n\nSelect 2 skills which you will use throughout the game!\n");
    for(int i=0; i<2; i++){
        if(already_chosen!=1){
        printf("1. %s\n", hero_skills[0].name);
        printf("   * HP modifier: %.2f\n", hero_skills[0].mod_hp);
        printf("   * Attack Points: %.2f\n", hero_skills[0].mod_atk);
        printf("   * Defense Points: %.2f\n", hero_skills[0].mod_def);}
        if(already_chosen!=2){
        printf("2. %s\n", hero_skills[1].name);
        printf("   * HP modifier: %.2f\n", hero_skills[1].mod_hp);
        printf("   * Attack Points: %.2f\n", hero_skills[1].mod_atk);
        printf("   * Defense Points: %.2f\n", hero_skills[1].mod_def);}
        if(already_chosen!=3){
        printf("3. %s\n", hero_skills[2].name);
        printf("   * HP modifier: %.2f\n", hero_skills[2].mod_hp);
        printf("   * Attack Points: %.2f\n", hero_skills[2].mod_atk);
        printf("   * Defense Points: %.2f\n\n", hero_skills[2].mod_def);}
        printf("Choose your skill number %d/2\n", (i+1));
        choice=read_decision();



        if(choice==already_chosen){choice=4;}
        switch (choice) {
            case 1:
                player->skills[i]=hero_skills[choice-1];
                already_chosen=1;
                printf("You have chosen: %s\n\n", player->skills[i]);
                //memcpy(player->skills, hero_skills, sizeof(hero_skills)); 
                insert(player, player->skills[i].name, 0);
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }
                break;
            case 2:
                player->skills[i]=hero_skills[choice-1];
            // memcpy(player->skills, hero_skills, sizeof(hero_skills));
                already_chosen=2;
                printf("You have chosen: %s\n\n", player->skills[i]);
                insert(player, player->skills[i].name, 0);
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }
                break;
            case 3:
                player->skills[i]=hero_skills[choice-1];
            //  memcpy(player->skills, hero_skills, sizeof(hero_skills));
                already_chosen=3;
                printf("You have chosen: %s\n\n", player->skills[i]);
                insert(player, player->skills[i].name, 0);
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }
                break;
            default:
                printf("Invalid choice.\n");
                i--;
            //  memcpy(player->skills, hero_skills, sizeof(hero_skills));
                break;
        }}
        bool check=false;
        while(!check){printf("Weapon selection:\n");
        printf("1. %s\n", weapons[0].name);
        printf("   * HP modifier: %.2f\n", weapons[0].mod_hp);
        printf("   * Attack Points: %.2f\n", weapons[0].mod_atk);
        printf("   * Defense Points: %.2f\n", weapons[0].mod_def);
        printf("2. %s\n", weapons[1].name);
        printf("   * HP modifier: %.2f\n", weapons[1].mod_hp);
        printf("   * Attack Points: %.2f\n", weapons[1].mod_atk);
        printf("   * Defense Points: %.2f\n", weapons[1].mod_def);
        printf("3. %s\n", weapons[2].name);
        printf("   * HP modifier: %.2f\n", weapons[2].mod_hp);
        printf("   * Attack Points: %.2f\n", weapons[2].mod_atk);
        printf("   * Defense Points: %.2f\n\n", weapons[2].mod_def);

        printf("Choose your weapon:\n");
        
        choice=read_decision();

        switch (choice) {
            case 1:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
                //memcpy(player->skills, hero_skills, sizeof(hero_skills));
                insert(player, player->skills[2].name, 0);
                player->weapon=choice-1;
                break;
            case 2:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
            // memcpy(player->skills, hero_skills, sizeof(hero_skills));
                insert(player, player->skills[2].name, 0); 
                player->weapon=choice-1;               
                break;
            case 3:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
                insert(player, player->skills[2].name, 0);  
                player->weapon=choice-1;              
                break;
            default:
                printf("Invalid choice.\n");
                break;}
            printf("You also get 2 special skills which can only be used ONCE throughout the game! These will be:\n");
            player->skills[3]=special_skills[0];
            player->skills[4]=special_skills[1];
            insert(player, player->skills[3].name, 0);
            insert(player, player->skills[4].name, 0);                
            printf("· %s\n· %s\n\n\n", player->skills[3].name, player->skills[4].name);
        }
        
        
        }




void display_menu(Character *player) {
    int choice;
    bool chosen_character = false;
    bool finished=false;

    do {
        printf("\n----- Gladiator RPG Menu -----\n");
        printf("1. Start New Game\n");
        printf("2. Configure Character before playing\n");
        printf("3. View Game Structure\n");
        printf("4. Load Game\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice=read_decision();

        switch (choice) {
            case 1:
                if(chosen_character == false){
                    printf("You have not configured your character yet. Go to '2. Configure Character'");
                    break;
                }
                start_game(player, false); //this is the function that leads character through the different scenarios in the game
                break;
            case 2:
                reinit_dictionary(player);
                configure_character(player, -1); //this is the function that configures the players character
                configure_skills(player);
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
                printf("Loading Game...\n");
                Character loaded_player;
                init_dictionary(&loaded_player);
                start_game(&loaded_player, true);
                break;
            case 5:
                printf("Exiting the game. Guess you couldn't handle the pressure!\n");
                finished=true;
                break;
            
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (!finished);
}
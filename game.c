#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battles.c"



// function to set up the character's basic attributes (name, hp, attack points, etc)
void configure_character(Character *player, int charact) {
    int choice;

    // If there is a number 1-2-3 in the arguments passed, then we are loading a saved game, and we already have decided our choice
    // If the argument we pass is -1, it means we still have to choose
    if(charact!=-1){
        choice=charact;
        }
    // Print the info for each character
    else{
        // A "level" integer which asks us to set up the difficulty of the game 
    player->turns_played=0;
    int level;
    printf("Choose difficulty!\n\t1. Medium (Revives allowed)\n\t2. Legendary\n\t");
    // Use read_decision() function, which asks input from the user, and controls errors from invalid inputs (eg. inputting a char instead of an int)
    level=read_decision();
    // If the player chooses to select "legendary" difficulty by entering int 2, then there will be no revives during the game
    if(level==1){
        // Use of a boolean to select the level in order to save memory space
        player->difficult=false;
    }
    // If the player enters 1, then revives are allowed
    // Also by default, any non 2 number will set the difficulty to low
    else if(level==2){
        player->difficult=true;
    }
    else{
        printf("Your input was invalid. You have been defaulted to the Medium path");
        player->difficult=false;
    }


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
    // Read input from user with the read_decision() function, which also controls errors of missmatching inputs
    choice=read_decision();
}
    // Using the choice (either from input, or from the loaded game), we assign the attributes to our player
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

// Function to start the game
// Parameters are: the character, and a bool which lets us know if we are loading a game or stting up the game for the first time
void start_game(Character *player, bool load_scenario){
    // Declare the enemies
    Enemy decimus;
    Enemy cult;
    Enemy mercenaries;
    Enemy Sulla;
    // Declare the scenarios we will run through
    Scenario rome;
    Scenario shadows_of_pompeii;
    Scenario thermal_baths;
    Scenario colosseum_showdown;
    // We declare them like this instead of using pointers, because this way we take advantage of c's memory allocation algorithms

    // Initialize the enemies with the init_enemies function defined in the functions.c file
    init_enemy(&decimus, "Decimus Brutus", 80, 4, 5);
    init_enemy(&cult, "Cult of Bacchus", 90, 5, 5);
    init_enemy(&mercenaries, "The Mercenaries", 100, 5, 6);
    init_enemy(&Sulla, "Lucius Cornelius Sulla", 120, 6, 6);
    // Give each enemy their particular skill
    decimus.skills[2]=particular_enemy_skills[0];
    cult.skills[2]=particular_enemy_skills[1];
    mercenaries.skills[2]=particular_enemy_skills[2];
    Sulla.skills[2]=particular_enemy_skills[3];

    // Initialize the scenarios with the init_scenario() function defined in the functions.c file
    init_scenario(&rome, "Rome", "In the heart of ancient Rome, your journey begins. In a context of post-civil war between the Optimates and Populares factions in the senate, the roman plebs live under the yoke of Optimate tyranny, and the Dictatorship of Lucius Cornelius Sulla. Navigate the streets wisely, for every choice shapes your destiny. Adventure awaits in the arena and beyond. Let the games begin! \n\n", &decimus, &rome_dec, &shadows_of_pompeii, 1);
    init_scenario(&shadows_of_pompeii, "Shadows of Pompeii", "In the twilight of Pompeii's ruins, mysteries lurk beneath ash-covered streets. Navigate shadows fraught with intrigue and danger. Will you unravel secrets or become entangled in deceit? Choose wisely; in Pompeii, history's whispers echo loudest", &cult, &pompeii_dec, &thermal_baths, 2);
    init_scenario(&thermal_baths, "The Thermal Baths", "After the tumultuous events in Pompeii, you seek respite and refuge in the tranquil surroundings of the thermal baths. Here, amidst the soothing waters and opulent surroundings, you contemplate your next move in the ever-shifting game of power and intrigue.", &mercenaries, &thermal_dec, &colosseum_showdown, 3);
    init_scenario(&colosseum_showdown, "The Colosseum Showdown", "Whatever happens, you end up detained at the hands of the praetorian guard. You are brought back to Rome where a trial is set to begin. After a couple of sessions, it is already clear that the magistrate, the Optimate Dictator Lucius Cornelius Sulla, wants to condemn you whatever the cost may be, and that the sentence is likely set from the beginning of the trial: death at the Tarpeian Rock!", &Sulla, &colosseum_dec, NULL, 4);
    // The scenarios form a Linked List, and we use pointer scen to traverse through the list
    Scenario* scen = &rome;
    
    // Using the bool load_scenario given in the parameters of this function, we differentiate the 2 cases
    // If we are loading a scenario we will remain in this first if-condition
    if(load_scenario){
        // Using the load_game function, which returns a scenario pointer, we set up the player and the scenario with the correct
        // specificities we have saved
        player->skills[3]=special_skills[0];
        player->skills[4]=special_skills[1];
        scen = load_game(scen, player);
        // Use the configure character function we have declared previously
        // Here we pass the integer player->character_num, which is a number 1-2-3 that sets up the player attributes and name as explained in the definition of the function
        configure_character(player, player->character_num);
        // Set the player's skills according to what was is in the saved game info
        player->skills[0]=hero_skills[player->first_skill];
        player->skills[1]=hero_skills[player->second_skill];
        player->skills[2]=weapons[player->weapon];
        // Initialize the values of the Dictionary we use to store all the skills, and how many times they have been used
        for(int i=0; i<5; i++){
        insert(player, player->skills[i].name, 0);
        }
    }
    // Call the game function defined in game.c, which starts the play
    game(scen, player, load_scenario);
    // Once the game is over, we print how many times each skill has been used using the dictionary
    for(int i=0; i<5; i++){
        printf("%s has been used %d times\n", player->skills[i].name, get(player, player->skills[i].name));
    }
    printf("\n\n");
    // Use the quicksort algorithm defined in the functions.c file, to sort the skills in descending order of usage
    char **sorted_keys = get_sorted_keys(player);
    // If the skills have been correctly sorted
    if (sorted_keys) {
        // Print the skills
        printf("\nSorted skills based on usage:\n");
        for (int i = 0; i < player->dict.size; i++) {
            printf("%d.\t%s\n", (i+1), sorted_keys[i]);
            free(sorted_keys[i]); // Free each allocated string
        }
        free(sorted_keys); // Free the array itself
    }

}


// function to set up the character's attributes
void configure_skills(Character* player){
    // Declare the variable we will use to store the user's choice of skills each time
    int choice;
    // This variable will indicate which of the skills has already been chosen, so that we don't choose it twice
    int already_chosen=0;
    printf("\n\nSelect 2 skills which you will use throughout the game!\n");
    
    // as we have to choose 2 skills, we will use a loop of 2 
    for(int i=0; i<2; i++){
        // If the skill hasn't been chosen, print its data on the screen
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
        // Get input from the user
        choice=read_decision();


        // If, for whatever reason, the player chooses the number of a skill which has already been chosen
        // even though the skill has not been shown on screen... then we set the choice to 4, which will make the program ask for a skill again
        if(choice==already_chosen){choice=4;}
        switch (choice) {
            // set the skills to whatever the user has chosen
            case 1:
                player->skills[i]=hero_skills[choice-1];
                already_chosen=1;
                printf("You have chosen: %s\n\n", player->skills[i]);
                // Insert the key value to the dictionary
                insert(player, player->skills[i].name, 0);
                
                // Save the skill number so that we can later save it on the .txt file
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }


                break;
            case 2:
                player->skills[i]=hero_skills[choice-1];
                already_chosen=2;
                printf("You have chosen: %s\n\n", player->skills[i]);
                // Insert the key value to the dictionary
                insert(player, player->skills[i].name, 0);
                
                // Save the skill number so that we can later save it on the .txt file
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }
                break;
            case 3:
                player->skills[i]=hero_skills[choice-1];
                already_chosen=3;
                printf("You have chosen: %s\n\n", player->skills[i]);
                // Insert the key value to the dictionary
                insert(player, player->skills[i].name, 0);
                
                // Save the skill number so that we can later save it on the .txt file
                if(i==0){
                    player->first_skill=choice-1;
                }
                else if(i==1){
                    player->second_skill=choice-1;
                }
                break;
            default:
                printf("Invalid choice.\n");

                // If the coice is invalid, we subtract 1 from our iteration variable i, so that we hvae to ask again for the skill
                i--;
               break;
        }}


        // Use a bool to check until when we have correctly selected the new weapon
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
        // Get input from user
        choice=read_decision();

        switch (choice) {
            case 1:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
                // Insert the key value to the dictionary
                insert(player, player->skills[2].name, 0);

                // save the weapon choice so we can later save it on the .txt file
                player->weapon=choice-1;
                break;
            case 2:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
                // Insert the key value to the dictionary
                insert(player, player->skills[2].name, 0); 

                // save the weapon choice so we can later save it on the .txt file
                player->weapon=choice-1;               
                break;
            case 3:
                player->skills[2]=weapons[choice-1];
                check=true;
                printf("You have chosen: %s\n\n", player->skills[2]);
                // Insert the key value to the dictionary
                insert(player, player->skills[2].name, 0);  
                
                // save the weapon choice so we can later save it on the .txt file
                player->weapon=choice-1;              
                break;
            default:
                printf("Invalid choice.\n");
                break;}

            // Add the final 2 obligatory skills which everyone gets
            printf("You also get 2 special skills which can only be used ONCE throughout the game! These will be:\n");
            player->skills[3]=special_skills[0];
            player->skills[4]=special_skills[1];
            insert(player, player->skills[3].name, 0);
            insert(player, player->skills[4].name, 0);                
            printf("· %s\n· %s\n\n\n", player->skills[3].name, player->skills[4].name);
        }
        
        
        }



// Function
void play(Character *player) {
    // Init the dictionary we will use to save the skills and their usage statistics (how many times we have used each skill)
    init_dictionary(player);
    // Where we will store the choice inputted by the user
    int choice;
    // Boolean to check if we have chosen the character
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

        // Get input from the user
        choice=read_decision();

        switch (choice) {
            case 1:
                if(chosen_character){
                //this is the function that leads character through the different scenarios in the game
                start_game(player, false); 
                chosen_character=false;
                break;
                }
                printf("You have not configured your character yet. You will be redirected to '2. Configure Character'\n\n");
            case 2:
                // reinitialize the dictionary just in case this is the 2nd+ time we have chosen skills in this run of the program
                reinit_dictionary(player);
                //this is the function that configures the players character
                configure_character(player, -1); 
                // configure the skills of the player
                configure_skills(player);
                // set the chosen character to true, so that we can initialize the game the next time
                chosen_character = true;
                break;
            case 3:
                // Print the different scenarios... not much more to it
                printf("Game structure:\n");
                printf("Scenarios:\n");
                printf("1. Rome\n");
                printf("2. Shadows of PompeII\n");
                printf("3. The thermal baths\n");
                printf("4. Colosseum Showdown\n");
                break;
            case 4:
                printf("Loading Game...\n");
                // Initialize a new character, which will have different attributes than the one created in this same game
                Character loaded_player;
                // Initialize a dictionary for this new player
                init_dictionary(&loaded_player);
                // Start the game with this new player
                start_game(&loaded_player, true);
                break;
            case 5:
                // EXIT THE GAME
                printf("Exiting the game. Guess you couldn't handle the pressure!\n");
                finished=true;
                break;
            
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (!finished);
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "battles.h"

//OJOOO, CAL CORREGIR ERRORS I A MÉS, FER SERVIR LES STRUCT ja que NO hem fet servir skill, decision, scenario, etc!!!!!


// Define constants
#define MAX_SKILLS 4
#define MAX_ENEMIES 3

// Define the characters' stats
Character c1 = {100, 5, 5}; // Arnaus Decimus Meridius
Character c2 = {100, 3, 7}; // Ericus Carpophorus
Character c3 = {100, 6, 4}; // Paullus Acilius Glabrio

// Function prototypes
void initialize_scenarios(Scenario *scenarios);
void start_game();
void display_menu(Character *player);
void narrate_scenario_one(Character *player);
void narrate_scenario_two(Character *player);
void narrate_scenario_three(Character *player);
void enqueue(Queue *queue, Character *character);
void confront_mercenaries(Character *player);
void coliseum_showdown(Character *player);
Character *dequeue(Queue *queue);

int main() {
    printf("In the heart of ancient Rome, your journey begins. In a context of post-civil war between the Optimates and Populares factions in the senate, the roman plebs live under the yoke of Optimate tyranny, and the Dictatorship of Lucius Cornelius Sulla. Navigate the streets wisely, for every choice shapes your destiny. Adventure awaits in the arena and beyond. Let the games begin! \n\n");
    
    // Initialize scenarios
    Scenario scenarios[4];
    initialize_scenarios(scenarios);
    // Create a character for the player
    Character player;
    // Display menu
    display_menu(&player);

    //the adventure (game) starts
    narrate_scenario_one(&player);
    narrate_scenario_two(&player);
    narrate_scenario_three(&player);
    coliseum_showdown(&player);
    return 0;
}

void narrate_scenario_one(Character *player) {
    printf("As you embark on your journey, you come across two distinct paths, each presenting its own set of challenges and opportunities:\n");
    printf("Option A: The Path of Valor\n");
    printf("Option B: The Path of Deception\n");

    char choice;
    printf("Choose your path (A or B): ");
    scanf(" %c", &choice);

    // Handle player's choice
    switch (choice) {
        case 'A':
        case 'a':
            printf("\nYou have chosen the Path of Valor.\n");
            printf("Embrace the honorable path of the warrior. Train diligently in the gladiatorial schools, honing your combat skills and earning the respect of your peers. Face your opponents in the arena with courage and determination.\n");
            
            // Situation 1: Training at the Ludus Magnus
            printf("\nSituation 1: Training at the Ludus Magnus\n");
            printf("You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?\n");

            // Handle player's choice in Situation 1
            char choice_situation_1;
            printf("Choose your approach (A: Forge alliances, B: Confront adversaries): ");
            scanf(" %c", &choice_situation_1);

            // Perform actions based on player's choice
            switch (choice_situation_1) {
                case 'A':
                case 'a':
                    // Player forges alliances
                    printf("\nYou choose to forge alliances. You gain valuable allies who provide support during battles, gaining 2 attack points.\n");
                    // Adjust player's stats or progress story as necessary
                    player->atk_pts += 2; // Increase attack points by 2
                    break;
                case 'B':
                case 'b':
                    // Player confronts adversaries
                    printf("\nYou choose to confront your adversaries. You engage in intense sparring matches, gaining 2 defense points and 10 HP and honing your combat skills 2 points. However, injuries sustained during these conflicts may reduce your attack points.\n");
                    // Adjust player's stats or progress story as necessary
                    player->def_pts += 2; // Increase defense points by 2
                    player->HP += 10; // Increase HP by 10
                    player->atk_pts -= 2; // Reduce attack points by 2
                    break;
                default:
                    printf("\nInvalid choice. Defaulting to forging alliances.\n");
                    // Default action: Player forges alliances
                    printf("You gain valuable allies who provide support during battles, gaining attack points.\n");
                    // Adjust player's stats or progress story as necessary
            }

            // Situation 2: The Arena Challenge
            printf("\nSituation 2: The Arena Challenge\n");
            printf("Your training culminates in a grand spectacle at a small amphitheater, where you face off against formidable opponents in front of cheering crowds. The roar of the crowd echoes through the arena as you step into the sands, ready to prove your worth as a gladiator. Will you emerge victorious, earning glory and renown, or will you fall in defeat before the eyes of the Roman populace?\n");

            //AQUÍ S'HA DE FER LA 1a BATALLA, CONTRA DECIMUS BRUTUS i posar que passa si guanyes o perds
            //// CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
            printf("\nWhen you finish your battle, the organizer of the games decides to send you to Pompeii, where the next celebration in honor of Vulcan will take place. There, great gladiatorial combats will be held in honor of the god of forge and fire.\n");

            break;
        case 'B':
        case 'b':
            // Option B: The Path of Deception
            printf("\nYou have chosen the Path of Deception.\n");
            printf("Navigate the intricate web of assassinations and intrigue that permeates the city. Carry out the dirty work for influential political agents, manipulate events to your advantage, and climb the social ladder through cunning and guile.\n");

            // Situation 1: Training at the Ludus Magnus
            printf("\nSituation 1: Training at the Ludus Magnus\n");
            printf("You spend your days honing your combat skills under the watchful eye of seasoned gladiators. Your dedication earns you the respect of your peers and the admiration of your trainers. However, tensions rise within the Ludus as rivalries emerge among the gladiators. Will you forge alliances to overcome your adversaries, or will you face them head-on in combat?\n");

            // Handle player's choice in Situation 1
            char choice_situation_1_B;
            printf("Choose your approach (A: Forge alliances, B: Confront adversaries): ");
            scanf(" %c", &choice_situation_1_B);

            // Perform actions based on player's choice in Situation 1
            switch (choice_situation_1_B) {
                case 'A':
                case 'a':
                    // Player forges alliances
                    printf("\nYou choose to forge alliances. You gain valuable allies who provide support during battles, gaining 2 attack points.\n");
                    // Adjust player's stats or progress story as necessary
                    player->atk_pts += 2; // Increase attack points by 2
                    break;
                case 'B':
                case 'b':
                    // Player confronts adversaries
                    printf("\nYou choose to confront your adversaries. You engage in intense sparring matches, gaining 2 defense points and 10 HP and honing your combat skills 2 points. However, injuries sustained during these conflicts may reduce your attack points.\n");
                    // Adjust player's stats or progress story as necessary
                    player->def_pts += 2; // Increase defense points by 2
                    player->HP += 10; // Increase HP by 10
                    player->atk_pts -= 2; // Reduce attack points by 2
                    break;
                default:
                    printf("\nInvalid choice. Defaulting to forging alliances.\n");
                    // Default action: Player forges alliances
                    printf("You gain valuable allies who provide support during battles, gaining attack points.\n");
                    // Adjust player's stats or progress story as necessary
            }

            // Situation 2: The Arena Challenge
            printf("\nSituation 2: The Arena Challenge\n");
            printf("Your training culminates in a grand spectacle at a small amphitheater, where you face off against formidable opponents in front of cheering crowds. The roar of the crowd echoes through the arena as you step into the sands, ready to prove your worth as a gladiator. Will you emerge victorious, earning glory and renown, or will you fall in defeat before the eyes of the Roman populace?\n");

            //AQUÍ S'HA DE FER LA 1a BATALLA, CONTRA DECIMUS BRUTUS i posar que passa si guanyes o perds
            //// CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
            printf("\nAfter the battle, a mysterious figure by the name of Julius Caesar has been impressed by your abilities. He urges your master to send you to a clandestine meeting in the heart of Pompeii, where he will make use of your talents.\n");

            break;
        default:
            printf("\nInvalid choice. Defaulting to the Path of Valor.\n");
            printf("Embrace the honorable path of the warrior. Train diligently in the gladiatorial schools, honing your combat skills and earning the respect of your peers. Face your opponents in the arena with courage and determination.\n");
    }
    //UN COP ACABA EL ESCENARI HEM DE FER QUE EL PERSONATGE RECUPERA TOT EL SEU HP
}

void start_game(){}

void narrate_scenario_two(Character *player) {
    printf("Scenario 2: Shadows of Pompeii\n");

    if (player->chosen_path == 'A' || player->chosen_path == 'a') {
        // Path of Valor
        printf("Path of Valor:\n");
        printf("You arrive in Pompeii amid the celebrations and festivals of Vulcanalia. You are amazed by the fire spectacles and dances, as well as the opulent sacrifices made to the god Vulcan. Some say that this god lives in the same city you are in, given that the mountain they call Vesuvius, near the city of Pompeii, can sometimes be heard roaring during the night.\n");
        printf("As you traverse the colored streets of the city, you notice a thief stealing a toy from a kid. Despite the warnings of your master not to chase after the thief, you dive into the maze of corridors of the inner city of Pompeii.\n");

        // Proceed with the thief situation
        printf("You chase after the thief, weaving through the labyrinthine alleys of Pompeii. As you close in on the thief, you confront them, demanding they return the stolen toy. The thief, caught off guard by your sudden appearance, hesitates for a moment before reluctantly handing over the toy and fleeing into the shadows.\n");
        printf("Your act of bravery earns you the gratitude of the child's family and the admiration of the nearby townsfolk. They whisper among themselves, impressed by your valor and sense of justice.\n");

        // Adjust player's stats or progress story as necessary
        player->HP += 10; // Increase HP by 10
        player->atk_pts += 2; // Increase attack points by 2
    } else {
        // Path of Deception
        printf("Path of Deception:\n");
        printf("You arrive in the ancient city of Pompeii under the cover of darkness, where whispers of conspiracy and betrayal echo through the cobblestone streets. The air is thick with tension as you navigate the labyrinthine alleys, wary of unseen dangers lurking in the shadows.\n");

        // Proceed with the meeting situation
        printf("Situation: The Meeting\n");
        printf("At the designated rendezvous point, you come face to face with the enigmatic Julius Caesar, this still young and mysterious figure who summoned you. Their identity shrouded in secrecy, he offers you a proposition that could tip the balance of power in Pompeii. Will you ally yourself with this mysterious benefactor, or will you tread cautiously, wary of hidden agendas and ulterior motives?\n");

        char choice_situation_2;
        printf("Choose your approach (A: Form an Alliance, B: Proceed with Caution): ");
        scanf(" %c", &choice_situation_2);

        switch (choice_situation_2) {
            case 'A':
            case 'a':
                // Form an Alliance
                printf("\nYou choose to form an alliance. Align yourself with the mysterious figure, embracing the opportunity to gain influence and leverage within Pompeii's intricate network of power. Forge a pact with your newfound ally and navigate the treacherous waters of politics with their support.\n");
                // YOU ACQUIRE A NEW SKILL (AIXÒ HO PODEM CANVIAR I SINO, HAURÍEM DE MIRAR COM FER-HO)             
                break;
            case 'B':
            case 'b':
                // Proceed with Caution
                printf("\nYou choose to proceed with caution. Opt for caution and skepticism, wary of the potential risks and consequences of aligning yourself with unknown forces. Choose to investigate further before committing to any alliances, trusting in your own instincts to navigate the dangers of Pompeii's shadowy underworld.\n");
                // YOU ACQUIRE A NEW (DIFFERENT) SKILL (AIXÒ HO PODEM CANVIAR I SINO, HAURÍEM DE MIRAR COM FER-HO)       
                break;
            default:
                printf("\nInvalid choice. Defaulting to proceeding with caution.\n");
                // Proceed with Caution
                printf("Opt for caution and skepticism, wary of the potential risks and consequences of aligning yourself with unknown forces. Choose to investigate further before committing to any alliances, trusting in your own instincts to navigate the dangers of Pompeii's shadowy underworld.\n");
                // You acquire a different skill
                printf("You acquire a new skill: Stealth.\n");
                // Adjust player's stats or progress story as necessary
                // For now, let's just print that the player gained a skill
        }
    }

    // Regardless of choice, proceed to the battle
    printf("\nAs you prepare to depart from the meeting or finish dealing with the thief, you are ambushed by a group of shadowy figures lurking in the alleyways.\n");
    printf("Battle: Ambush in the Shadows (OBLIGATORY)\n");
    printf("You find yourself outnumbered and surrounded by adversaries intent on thwarting your plans. With no option for escape, you must fight for your life against these unknown assailants. Will you emerge victorious, or will the shadows of Pompeii claim you as their latest victim?\n");
    
    // AQUÍ HAURÍEM DE PLANIFICAR LA 2a BATALLA
    //// CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
    printf("You emerge victorious from the ambush, gaining attack, defense, and HP.\n");
    //UN COP ACABA EL ESCENARI HEM DE FER QUE EL PERSONATGE RECUPERA TOT EL SEU HP
}

void narrate_scenario_three(Character *player) {
    // Scenario introduction
    printf("\nAfter the tumultuous events in Pompeii, you seek respite and refuge in the tranquil surroundings of the thermal baths. Here, amidst the soothing waters and opulent surroundings, you contemplate your next move in the ever-shifting game of power and intrigue.\n");

    // Situation: The Serenity of the Baths (obligatory)
    printf("\nSituation: The Serenity of the Baths\n");
    printf("As you soak in the rejuvenating waters, you notice a heated argument unfolding nearby. A group of powerful and influential figures of the city are engaged in a fierce debate, their voices echoing off the marble walls of the baths. Intrigued, you consider whether to investigate further or to mind your own business and enjoy the tranquility of the surroundings.\n");

    // Player's choice in Situation: The Serenity of the Baths
    char choice_baths;
    printf("Choose your approach (A: Ignore the argument, B: Approach the argument): ");
    scanf(" %c", &choice_baths);

    // Perform actions based on player's choice
    switch (choice_baths) {
        case 'A':
        case 'a':
            // Choice 1: Ignore the Argument
            printf("\nYou choose to ignore the confrontation and focus on your own relaxation. You lean back in the soothing waters, closing your eyes and letting the tensions of the day melt away.\n");
            // No further action needed for ignoring the argument
            break;
        case 'B':
        case 'b':
            // Choice 2: Approach the Argument
            printf("\nCuriosity piqued, you decide to approach the group and listen in on their conversation. As you draw nearer, you catch snippets of their discussion, hinting at political intrigue and power struggles within the city.\n");

            // Player's sub-choice in approaching the argument
            char sub_choice_argument;
            printf("Do you want to interfere? (Y/N): ");
            scanf(" %c", &sub_choice_argument);

            if (sub_choice_argument == 'Y' || sub_choice_argument == 'y') {
                // Player interferes
                printf("\nOne of the powerful figures notices your presence and invites you to join them. Will you seize the opportunity to gain insight into the inner workings of Pompeii's elite?\n");

                // Handle player's decision after interference
                char decision_interference;
                printf("Do you want to accept the invitation? (Y/N): ");
                scanf(" %c", &decision_interference);

                if (decision_interference == 'Y' || decision_interference == 'y') {
                    // Player accepts the invitation
                    printf("\nYou step out of the thermal baths, feeling rejuvenated and invigorated, deciding it's time to leave the tranquil oasis behind and return to the bustling streets of Pompeii.\n");
                    // Offer the player the chance to change the previously obtained skill
                    // AIXÒ CALDRIA PROGRAMAR-HO!!!!
                } else {
                    // Player declines the invitation
                    printf("\nYou politely decline the invitation, choosing to maintain a safe distance from the drama.\n");
                    // No further action needed if the player declines the invitation
                }
            } else {
                // Player chooses not to interfere
                printf("\nYou decide to listen from a distance, choosing not to interfere with the heated debate.\n");
                // No further action needed if the player chooses not to interfere
            }
            break;
        default:
            printf("\nInvalid choice. Defaulting to ignoring the argument.\n");
            // Default action: Ignore the Argument
            printf("You choose to ignore the confrontation and focus on your own relaxation. You lean back in the soothing waters, closing your eyes and letting the tensions of the day melt away.\n");
            // No further action needed for default choice
            break;
    }

    // Common part for both choices after leaving the thermal baths and encountering the mercenaries
    printf("\nAs you step out of the thermal baths, feeling rejuvenated and invigorated, you decide it's time to leave the tranquil oasis behind and return to the bustling streets of Pompeii. However, as you make your way towards the exit, a sudden commotion erupts nearby.\n");
    printf("Turning towards the source of the disturbance, you find yourself confronted by a group of armed mercenaries, their expressions stern and unwelcoming. It seems you've stumbled into the midst of a city-wide crackdown on dissent, and you're now faced with a difficult choice: submit to them and become a slave for the rest of your life or attempt to evade capture and escape into the winding alleyways of Pompeii.\n");

    // Confrontation with the mercenaries (hi ha una funció ja que és llarg...)
    confront_mercenaries(player);

    // CAL QUE EL JUGADOR RECUPERI EL HP
}

void confront_mercenaries(Character *player) {
    printf("\nAs you step out of the thermal baths, feeling rejuvenated and invigorated, you decide it's time to leave the tranquil oasis behind and return to the bustling streets of Pompeii. However, as you make your way towards the exit, a sudden commotion erupts nearby.\n");
    printf("Turning towards the source of the disturbance, you find yourself confronted by a group of armed mercenaries, their expressions stern and unwelcoming. It seems you've stumbled into the midst of a city-wide crackdown on dissent, and you're now faced with a difficult choice: submit to them and become a slave for the rest of your life or attempt to evade capture and escape into the winding alleyways of Pompeii.\n");

    // Player's choice in confronting the mercenaries
    char choice_confront;
    printf("Choose your approach (A: Face them head on, B: Evade capture): ");
    scanf(" %c", &choice_confront);

    // Perform actions based on player's choice
    switch (choice_confront) {
        case 'A':
        case 'a':
            // Choice 1: Face them head on
            printf("\nYou decide to face the mercenaries head on, refusing to submit to their demands.\n");
            // Perform battle with the mercenaries
            // CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
            break;
        case 'B':
        case 'b':
            // Choice 2: Evade capture
            printf("\nOpting for a daring escape, you dart down a nearby alleyway, weaving through the labyrinthine streets of Pompeii with agility and stealth.\n");
            printf("You loose 10 HP for demonstrationg lack of bravery");
            // Player loses HP for demonstrating lack of bravery
            player->HP -= 10; // Example HP deduction, adjust as needed
            printf("The sounds of pursuit echo behind you as you navigate the city's winding passages, determined to outmaneuver your pursuers and reach safety.\n");
            // Since the player loses HP, they end up having to face the mercenaries anyway
            printf("\nHowever, you stumble, and the mercenaries catch up to you before you can make a clean escape. You find yourself cornered, forced to confront them head-on.\n");
            // Perform battle with the mercenaries
            // CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
            break;
        default:
            printf("\nInvalid choice. Defaulting to facing them head on.\n");
            // Default action: Face them head on
            printf("You decide to face the mercenaries head on, refusing to submit to their demands.\n");
            // Perform battle with the mercenaries
            // CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)
            break;
    }
}

void coliseum_showdown(Character *player) {
    printf("\nAfter navigating the trials and tribulations of Pompeii, you find yourself standing at the threshold of the legendary Colosseum, the grand arena where gladiators clash and legends are born. Here, amidst the roar of the crowd and the dust of ancient battles, you prepare to face your ultimate challenge: a showdown against the mighty himself.\n");
    printf("As you step onto the blood-stained sands of the arena, you can feel the weight of history bearing down upon you. The eyes of Rome are upon you, awaiting the outcome of this epic confrontation between two titans of power and ambition.\n");

    // Perform battle with Lucius Cornelius Sulla
    // Code to handle battle with Lucius Cornelius Sulla
    // CAL FER EL CODI DE LA BATALLA AMB QUEUES O DICTIONARIES(TAMBÉ CAL POSAR LA EXPLICACIO DE PUNTS FORTS I FEBLES DE L'ENEMIC)

    // Outcome based on battle result
    if (player->HP > 0) { // If player wins
        printf("\nWith a display of unparalleled skill and determination, you emerge victorious in the epic showdown against Sulla. Your triumph reverberates throughout the Colosseum, earning you the adulation of the crowd and the respect of your peers.\n");
        printf("As the dust settles, you stand as the undisputed champion, a beacon of hope and inspiration for the people of Rome. Your victory sends shockwaves through the corridors of power, shaking the foundations of the empire to its core.\n");
        printf("With Sulla defeated, you ascend to the pinnacle of fame and popularity, gaining the unwavering gratitude of a rising star in the senate by the name of Julius Caesar. With his help, you get appointed a governorship in the provinces, which gives you vast amounts of wealth and prestige. Rome enters a new era of prosperity and enlightenment, its citizens united after decades of Optimate Dictatorship. YOU WIN!\n");
    } else { // If player loses
        printf("\nDespite your valiant efforts, victory eludes you in the final moments of the showdown against Sulla. As the crowd watches in stunned silence, you fall before the might of the legendary general, your dreams of leadership shattered on the blood-stained sands of the Colosseum.\n");
        printf("Your defeat sends shockwaves through the empire, casting doubt upon the future of Rome and the stability of its leadership. With Julius Caesar reaffirming his dominance, the people of Rome brace themselves for a reign of tyranny and oppression, their hopes for a brighter tomorrow dashed by the specter of defeat. YOU LOSE...\n");
    }
}

void configure_character(Character *player) {
    printf("Character selection:\n");
    printf("1. Arnaus Decimus Meridius\n");
    printf("   - HP: 100\n");
    printf("   - Attack Points: 5\n");
    printf("   - Defense Points: 5\n");
    printf("2. Ericus Carpophorus\n");
    printf("   - HP: 100\n");
    printf("   - Attack Points: 3\n");
    printf("   - Defense Points: 7\n");
    printf("3. Paullus Acilius Glabrio\n");
    printf("   - HP: 100\n");
    printf("   - Attack Points: 6\n");
    printf("   - Defense Points: 4\n");

    int choice;
    printf("Choose your character (1, 2, or 3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            *player = (Character){
                .name = "Arnaus Decimus Meridius",
                .HP = 100,
                .atk_pts = 5,
                .def_pts = 5,
                .skills = {1, 2, 3, 4} // Skill IDs (if applicable) 
            };
            break;
        case 2:
            *player = (Character){
                .name = "Ericus Carpophorus",
                .HP = 100,
                .atk_pts = 3,
                .def_pts = 7,
                .skills = {1, 2, 3, 4} // Skill IDs (if applicable) 
            };
            break;
        case 3:
            *player = (Character){
                .name = "Paullus Acilius Glabrio",
                .HP = 100,
                .atk_pts = 6,
                .def_pts = 4,
                .skills = {1, 2, 3, 4} // Skill IDs (if applicable) 
            };
            break;
        default:
            printf("Invalid choice. Defaulting to Arnaus Decimus Meridius.\n");
            *player = (Character){
                .name = "Arnaus Decimus Meridius",
                .HP = 100,
                .atk_pts = 5,
                .def_pts = 5,
                .skills = {1, 2, 3, 4} // Skill IDs (if applicable) 
            };
    }

    printf("\nCharacter %s configured successfully!\n", player->name);
    printf("Selected Skills:\n");
    printf("Skill 1: Deceit Attack\n"); // Art of deception (hurts mercenaries, decimus)
    printf("Skill 2: Agile Attack\n"); // Extremely quick attack (hurts lucius, cult)
    printf("Skill 3: Heal\n"); // can only be used once in the entire game (HP = 100)
    printf("Skill 4: Berserk\n"); //Rage attack (mercenaries, decimus, cult)
}

void display_menu(Character *player) {
    int choice;

    do {
        printf("\n----- Gladiator RPG Menu -----\n");
        printf("1. Start New Game\n");
        printf("2. Configure Character\n");
        printf("3. View Game Structure\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                start_game(player);
                break;
            case 2:
                configure_character(player);
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
                printf("Exiting the game. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
}

void enqueue(Queue *queue, Character *character) {
    // Create a new node
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to enqueue.\n");
        return;
    }
    newNode->character = character;
    newNode->next = NULL;

    // If the queue is empty, set both head and tail to the new node
    if (queue->head == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        // Otherwise, add the new node to the end and update the tail
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    // Increment the number of elements in the queue
    queue->elements++;
}

Character *dequeue(Queue *queue) {
    // Check if the queue is empty
    if (queue->head == NULL) {
        printf("Queue is empty. Unable to dequeue.\n");
        return NULL;
    }

    // Remove the character from the front of the queue
    QueueNode *temp = queue->head;
    Character *dequeuedCharacter = temp->character;
    queue->head = temp->next;
    free(temp);

    // If the queue becomes empty, update the tail
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    // Decrement the number of elements in the queue
    queue->elements--;

    return dequeuedCharacter;
}

//to use during the game (ENCARA NO ELS HE FET SERVIR)

Enemy decimus_brutus = {
    "Decimus Brutus",
    100, // Initial HP
    4,  // Attack points
    2,  // Defense points
    {1, 2, 3, 4} // Skill IDs (if applicable) //quan fer codi brutus no te ni 1 ni 3 (aplicar do-while)
};

Enemy cult = {
    "Cult of Bacchus",
    100, // Initial HP
    3,  // Attack points
    5,  // Defense points
    {1, 2, 3, 4} // Skill IDs (if applicable) // quan fer codi, cult no te ni 4 ni 3
};

Enemy mercenaries = {
    "The Mercenaries",
    100, // Initial HP
    6,  // Attack points
    3,  // Defense points
    {1, 2, 3, 4} // Skill IDs (if applicable) // quan fer codi, mercenaries no te ni 1 ni 3
};

Enemy lucius = {
    "Lucius Cornelius Sulla",
    100, // Initial HP
    5,  // Attack points
    7,  // Defense points
    {1, 2, 3, 4} // Skill IDs (if applicable) // quan fer codi, lucius no te 3
};
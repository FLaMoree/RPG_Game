#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"

int main()
{
    srand(time(NULL));
    
    Entity player;
    player.potions = 3;
    player.max_hp = 100;
    player.min_dmg = 8;
    player.max_dmg = 15;
    player.crit_chance = 5;
    player.hp = 100;
    player.armr = 0;

    Entity current_enemy;

    char turn;
    int chance = 10, max_floor = 5, max_number_of_rooms = 5, room = 1;
    int game_status;

    for ( int floor = 1; floor <= max_floor; floor++)
    {
        for ( room = 1; room <= max_number_of_rooms; room++)
        {
            spawn_enemy(&current_enemy, floor);
            game_status = processing_turn(&player, &current_enemy, chance);
            if ( game_status == GAME_QUIT )
            {
                return GAME_FINISHED;
            }

            if ( current_enemy.hp == 0 )
            {
                printf("You have cleared the room №%d\n", room);
                loot(&chance, &player, &current_enemy);
                free_mem(&current_enemy);
            }
            if ( player.hp == 0 )
            {
                printf("Ooooops. Skill issue! GG\n");
                free_mem(&current_enemy);
                return GAME_SKILLISSUE;
            }
            if ( room == max_number_of_rooms )
            {   
                max_number_of_rooms = 3 + (floor * 1) + (rand() % 3); 
                break;
            }
        }
    }
    printf("Oh, you win, just like a hero...\n");
    free_mem(&current_enemy);
    return GAME_FINISHED;
}
    
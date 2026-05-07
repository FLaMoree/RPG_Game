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

    for ( int floor = 1; floor <= max_floor; floor++)
    {
        for ( room = 1; room <= max_number_of_rooms; room++)
        {
            spawn_enemy(&current_enemy, floor);
            while ( player.hp != 0 && current_enemy.hp != 0 )
            {
                printf("\nPlayer:\n");
                printf("Hp:%d\n", player.hp);
                printf("Min damage:%d\nMax damage:%d\n", player.min_dmg, player.max_dmg);
                printf("Armor:%d\n", player.armr);
                printf("Potions:%d\n", player.potions);
                printf("Player lucky is %d\n\n", chance);
                for ( int i = 0; i < strlen(current_enemy.name); i++)
                {
                    printf("%c", current_enemy.name[i]);
                }
                printf(":\n");
                printf("Hp:%d\n", current_enemy.hp);
                printf("Min damage:%d\nMax damage:%d\n", current_enemy.min_dmg, current_enemy.max_dmg);
                printf("Armor:%d\n", current_enemy.armr);
                printf("\nChoose turn type(A - attack, H - heal, Q - quit):\n");
                scanf(" %c", &turn);
    
                if ( turn == 'a' || turn == 'A')
                {
                    printf("Chosen attack turn type\n");
                    attack(&player, &current_enemy);
                    if ( current_enemy.hp != 0 )
                    {
                        attack(&current_enemy, &player);
                    }
                }
                if ( turn == 'Q' || turn == 'q')
                {
                    printf("Good bye!\n");
                    return 0;
                }
                if ( turn == 'H' || turn == 'h')
                {
                    if ( player.potions == 0 )
                    {
                        printf("You drunk all potions. Do you have addiction?\n");
                        printf("While you trying find the potion, ");
                        for ( int i = 0; i < strlen(current_enemy.name); i++)
                        {
                            printf("%c", current_enemy.name[i]);
                        }
                        printf(" with pleasure damaged you :D(You didn`t find the potion)\n\n");
                        attack(&current_enemy, &player);
                        continue;
                    }
                    printf("Chosen a drink potion turn type\n");
                    player.potions--;
                    if ( player.potions < 0 )
                    {
                        player.potions = 0;
                    }
                    player.hp += 30;
                    if ( player.hp > player.max_hp )
                    {
                       player.hp = player.max_hp;
                    }
                    printf("You was damaged by ");
                    for ( int i = 0; i < strlen(current_enemy.name); i++)
                    {
                        printf("%c", current_enemy.name[i]);
                    }
                    printf(", while you drinking potion\n");
                    attack(&current_enemy, &player);
                }
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
                return SKILLISSUE;
            }
            if ( room == max_number_of_rooms )
            {   
                max_number_of_rooms = 3 + (floor * 1) + (rand() % 3); 
                break;
            }
        }
    }
    printf("Oh, you win, just like a hero...\n");
    return 0;
}
    
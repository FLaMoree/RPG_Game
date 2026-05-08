#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void attack(Entity *attacker, Entity *target)
{
    int possible_crit_chance = (rand() % 100) + 1;
    int temporary_max_dmg = attacker->max_dmg;
    int temporary_min_dmg = attacker->min_dmg;

    if ( possible_crit_chance <= attacker->crit_chance )
    {
        attacker->max_dmg *= 2;
        attacker->min_dmg *= 2;
        printf("CCCCCC CRRRIIIIIT!!\n");
    }
    else
    {
        attacker->crit_chance += 1;
    }
    int clear_damage = (rand() % (attacker->max_dmg - attacker->min_dmg + 1 ) + attacker->min_dmg) - target->armr;
    if ( clear_damage < 0 )
    {
        clear_damage = 0;
    }
    target->hp -= clear_damage;
    if ( target->hp < 0 )
    {
        target->hp = 0;
    }
    attacker->max_dmg = temporary_max_dmg;
    attacker->min_dmg = temporary_min_dmg;
}

void free_mem(Entity *target)
{
    free(target->name);
}

void print_status(Entity *player, Entity *current_enemy, int chance)
{
    printf("\nPlayer:\n");
    printf("Hp:%d\n", player->hp);
    printf("Min damage:%d\nMax damage:%d\n", player->min_dmg, player->max_dmg);
    printf("Armor:%d\n", player->armr);
    printf("Potions:%d\n", player->potions);
    printf("Player lucky is %d\n\n", chance);
    for ( int i = 0; i < strlen(current_enemy->name); i++)
    {
        printf("%c", current_enemy->name[i]);
    }
    printf(":\n");
    printf("Hp:%d\n", current_enemy->hp);
    printf("Min damage:%d\nMax damage:%d\n", current_enemy->min_dmg, current_enemy->max_dmg);
    printf("Armor:%d\n", current_enemy->armr);
}

int processing_turn(Entity *player, Entity *current_enemy, int chance)
{
    while (player->hp != 0 && current_enemy->hp != 0)
    {
        print_status(player, current_enemy, chance);

        char turn;
        printf("\nChoose turn type(A - attack, H - heal, Q - quit):\n");
        scanf(" %c", &turn);

        if (turn == 'a' || turn == 'A')
        {
            printf("Chosen attack turn type\n");
            attack(player, current_enemy);
            if (current_enemy->hp != 0)
            {
                attack(current_enemy, player);
            }
        }
        if (turn == 'Q' || turn == 'q')
        {
            printf("Good bye!\n");
            return GAME_QUIT;
        }
        if (turn == 'H' || turn == 'h')
        {
            if (player->potions == 0)
            {
                printf("You drunk all potions. Do you have addiction?\n");
                printf("While you trying find the potion, ");
                for (int i = 0; i < strlen(current_enemy->name); i++)
                {
                    printf("%c", current_enemy->name[i]);
                }
                printf(" with pleasure damaged you :D(You didn`t find the potion)\n\n");
                attack(current_enemy, player);
                continue;
            }
            printf("Chosen a drink potion turn type\n");
            player->potions--;
            if (player->potions < 0)
            {
                player->potions = 0;
            }
            player->hp += 30;
            if (player->hp > player->max_hp)
            {
                player->hp = player->max_hp;
            }
            printf("You was damaged by ");
            for (int i = 0; i < strlen(current_enemy->name); i++)
            {
                printf("%c", current_enemy->name[i]);
            }
            printf(", while you drinking potion\n");
            attack(current_enemy, player);
        }
    }
    return FUNCTION_FINISHED;
}
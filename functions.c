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


int loot(int *chance, Entity *player, Entity *enemy)
{
    int basic_chance = 10, potions_amount;

    if ( (rand() % 100) + 1 <= *chance ) // rand() % 100) + 1 - from 1 to *chance. Without '+ 1' it might be from 0 to *chance - 1
    {
        player->potions++;
        printf("You got 1 potion");
        *chance = basic_chance;

        if ( *chance < basic_chance )
        {
            *chance = basic_chance;
        }
        return 0;
    }
    else
    {
        *chance += enemy->loot_weight;
        return 1;
    }
}


void spawn_enemy(Entity *enemy, int floor)
{
    int pick_type_of_enemy;
    pick_type_of_enemy = 1;
    switch (pick_type_of_enemy)
    {
        case SPIDER: 
            enemy->hp = 35;
            enemy->base_hp = 35;
            enemy->armr = 0;
            enemy->crit_chance = 0;
            enemy->base_armr = 0;
            enemy->loot_weight = 5;
            enemy->max_dmg = 14;
            enemy->base_max_dmg = 14;
            enemy->min_dmg = 8;
            enemy->base_min_dmg = 8;
            enemy->name = (char*)malloc(7 * sizeof(char));
            strcpy(enemy->name, "Spider");
            break;
        case SLIME:
            enemy->hp = 60;
            enemy->base_hp = 60;
            enemy->armr = 5;
            enemy->crit_chance = 0;
            enemy->base_armr = 5;
            enemy->min_dmg = 4;
            enemy->base_min_dmg = 4;
            enemy->max_dmg = 8;
            enemy->base_max_dmg = 8;
            enemy->loot_weight = 20;
            enemy->name = (char*)malloc(6 * sizeof(char));
            strcpy(enemy->name, "Slime");
        break;
    }
    enemy->hp = enemy->base_hp + (enemy->base_hp * (floor - 1) * 15 / 100); // Every floor enemy`s hp is increasing by 15% 
    enemy->min_dmg = enemy->base_min_dmg + (2 * (floor - 1)); // Every floor enemy`s damage is increasing 
    enemy->max_dmg = enemy->base_max_dmg + (2 * (floor - 1)); //                      by 2 for each floor
    enemy->armr = enemy->base_armr + (floor / 2); // Every 2 floors armor is increasing by 1
}

void free_mem(Entity *target)
{
    free(target->name);
}
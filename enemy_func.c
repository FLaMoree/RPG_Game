#include "functions.h"
#include <string.h>
#include <stdlib.h>

void spawn_enemy(Entity *enemy, int floor)
{
    int pick_type_of_enemy;
    pick_type_of_enemy = rand() % 2;
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
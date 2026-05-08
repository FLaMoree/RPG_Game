#include "functions.h"
#include <stdio.h>
#include <time.h>

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
        return FUNCTION_FINISHED;
    }
    else
    {
        *chance += enemy->loot_weight;
        return LOOT_NOT_GOT;
    }
}
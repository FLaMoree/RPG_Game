#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SKILLISSUE 1

typedef struct 
{
    int hp, max_hp, base_hp;
    int min_dmg, base_min_dmg;
    int max_dmg, base_max_dmg;
    int armr, base_armr;
    int potions;
    int loot_weight;

} Entity;

enum EnemyType
{
    SPIDER,
    SLIME
};

void attack(Entity *attacker, Entity *target);
int loot(int *chance, Entity *player, Entity *current_enemy);
void spawn_enemy(Entity *enemy, int floor);

int main()
{
    srand(time(NULL));

    Entity player;
    player.potions = 3;
    player.max_hp = 100;
    player.min_dmg = 8;
    player.max_dmg = 15;
    player.hp = 100;
    player.armr = 0;

    Entity current_enemy;

    char turn;
    int chance = 10, floor = 1, number_of_rooms = 4;

    for ( int room = 1; room < number_of_rooms; room++)
    {
        while ( player.hp != 0 && current_enemy.hp != 0 )
        {
            spawn_enemy(&current_enemy, floor);

            printf("\nPlayer:\n");
            printf("Hp:%d\n", player.hp);
            printf("Min damage:%d\nMax damage:%d\n", player.min_dmg, player.max_dmg);
            printf("Armor:%d\n", player.armr);
            printf("Potions:%d\n", player.potions);
            printf("Player lucky is %d", chance);
            printf("\ncurrent_enemy:\n");
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
                    printf("While you trying find the potion, current_enemy with pleasure damaged you :D(You didn`t find the potion)\n");
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
                printf("You was damaged by current_enemy, while you drinking potion\n");
                attack(&current_enemy, &player);
            }
        }
        if ( current_enemy.hp == 0 )
        {
            printf("Congratulations! You Win the room №%d\n", room);
            loot(&chance, &player, &current_enemy);
        }
        if ( player.hp == 0 )
        {
            printf("Ooooops. Skill issue! GG\n");
            return SKILLISSUE;
        }
        if ( room == 3 )
        {
            number_of_rooms += 2;
            floor++; 
        }
        if ( floor == 5)
        {
            printf("You win, nice");
            return 0;
        }
        
    }
    return 0;
}
    
    

void attack(Entity *attacker, Entity *target)
{
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
    pick_type_of_enemy = rand() % 2;
    switch (pick_type_of_enemy)
    {
        case 'SPIDER': 
            enemy->hp = 35;
            enemy->base_hp = 35;
            enemy->armr = 0;
            enemy->base_armr = 0;
            enemy->loot_weight = 5;
            enemy->max_dmg = 14;
            enemy->base_max_dmg = 14;
            enemy->min_dmg = 8;
            enemy->base_min_dmg = 8;
            break;
        case 'SLIME':
            enemy->hp = 60;
            enemy->base_hp = 60;
            enemy->armr = 5;
            enemy->min_dmg = 4;
            enemy->base_min_dmg = 4;
            enemy->max_dmg = 8;
            enemy->base_max_dmg = 8;
            enemy->loot_weight = 15;
        break;
    }
    enemy->hp = enemy->base_hp + (enemy->base_hp * (floor - 1) * 15 / 100); // Every floor enemy`s hp is increasing by 15% 
    enemy->min_dmg = enemy->base_min_dmg + (2 * (floor - 1)); // Every floor enemy`s damage is increasing 
    enemy->max_dmg = enemy->base_max_dmg + (2 * (floor - 1)); //                by 2 times for each floor
    enemy->armr = enemy->base_armr + (floor / 2); // Every 2 floors armor is increasing by 1

}
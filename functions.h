#ifndef functions
#define functions

#define SKILLISSUE 1

typedef struct 
{
    // For enemy
    char *name;
    int loot_weight;
    int base_hp;
    int base_min_dmg;
    int base_max_dmg;
    int base_armr;
    // For player
    int max_hp;
    int potions;
    int crit_chance;
    //For both
    int min_dmg;
    int max_dmg;
    int armr;
    int hp;
    

} Entity;

enum EnemyType
{
    SPIDER,
    SLIME
};

void attack(Entity *attacker, Entity *target);
int loot(int *chance, Entity *player, Entity *current_enemy);
void spawn_enemy(Entity *enemy, int floor);
void free_mem(Entity *target);

#endif
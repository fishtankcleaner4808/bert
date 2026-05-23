#ifndef ENEMY_H
#define ENEMY_H

#include "../tilemap/tilemap.h"

#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float x_velocity;
    float y_velocity;
    bool on_ground;
    float direction;
} Enemy;

void enemy_init(Enemy *enemy);
void enemy_update(Enemy *enemy, Tilemap *map);
bool player_enemy_collision(void *player_ptr, Enemy *enemy);

#endif

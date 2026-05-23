#ifndef PLAYER_H
#define PLAYER_H

#include "../tilemap/tilemap.h"

#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float x_velocity;
    float y_velocity;
    float prev_x;
    float prev_y;
    bool on_ground;
    bool jump_pressed;
    bool jump_released;
    float input_x;
} Player;

void player_init(Player *player);
void player_update(Player *player, Tilemap *map);

#endif

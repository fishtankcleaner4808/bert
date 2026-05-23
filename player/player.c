#include "player.h"
#include <math.h>

#define FIXED_DT (1.0f / 60.0f)
#define TILE_SIZE 50
#define SPRITE_SIZE 50.0f

#define MOVE_ACCEL 2000.0f
#define MAX_SPEED_X 300.0f
#define FRICTION 1800.0f

#define GRAVITY 2500.0f
#define MAX_FALL_SPEED 1000.0f

#define JUMP_VELOCITY -1050.0f
#define JUMP_CUT_MULT 0.4f

static float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

void player_init(Player *player) {
    player->x = 100;
    player->y = 100;
    player->x_velocity = 0;
    player->y_velocity = 0;
    player->prev_x = player->x;
    player->prev_y = player->y;
    player->on_ground = false;
    player->jump_pressed = false;
    player->jump_released = false;
    player->input_x = 0.0f;
}

void player_update(Player *p, Tilemap *map) {
    if (p->input_x != 0.0f)
        p->x_velocity += p->input_x * MOVE_ACCEL * FIXED_DT;
    else if (p->x_velocity > 0) {
        p->x_velocity -= FRICTION * FIXED_DT;

        if (p->x_velocity < 0)
            p->x_velocity = 0;

    } else if (p->x_velocity < 0) {
        p->x_velocity += FRICTION * FIXED_DT;

        if (p->x_velocity > 0)
            p->x_velocity = 0;
    }

    p->x_velocity = clamp(p->x_velocity, -MAX_SPEED_X, MAX_SPEED_X);

    float new_x = p->x + p->x_velocity * FIXED_DT;
    int tile_top = (int)(p->y / TILE_SIZE);
    int tile_bottom = (int)((p->y + SPRITE_SIZE - 1) / TILE_SIZE);

    if (p->x_velocity > 0) {
        int tile_right = (int)((new_x + SPRITE_SIZE) / TILE_SIZE);

        for (int y = tile_top; y <= tile_bottom; y++)
            if (tilemap_is_solid(map, tile_right, y)) {
                new_x = tile_right * TILE_SIZE - SPRITE_SIZE;
                p->x_velocity = 0;
                break;
            }
    }

    if (p->x_velocity < 0) {
        int tile_left = (int)(new_x / TILE_SIZE);
        for (int y = tile_top; y <= tile_bottom; y++)
            if (tilemap_is_solid(map, tile_left, y)) {
                new_x = (tile_left + 1) * TILE_SIZE;
                p->x_velocity = 0;
                break;
            }
    }

    p->x = new_x;
    p->y_velocity += GRAVITY * FIXED_DT;
    p->y_velocity = clamp(p->y_velocity, -INFINITY, MAX_FALL_SPEED);

    float new_y = p->y + p->y_velocity * FIXED_DT;
    int tile_left = (int)(p->x / TILE_SIZE);
    int tile_right = (int)((p->x + SPRITE_SIZE - 1) / TILE_SIZE);

    p->on_ground = false;

    if (p->y_velocity > 0) {
        int tile_bottom = (int)((new_y + SPRITE_SIZE) / TILE_SIZE);

        for (int x = tile_left; x <= tile_right; x++)
            if (tilemap_is_solid(map, x, tile_bottom)) {
                new_y = tile_bottom * TILE_SIZE - SPRITE_SIZE;
                p->y_velocity = 0;
                p->on_ground = true;
                break;
            }
    }

    p->y = new_y;

    if (p->jump_pressed && p->on_ground) {
        p->y_velocity = JUMP_VELOCITY;
        p->on_ground = false;
        p->jump_pressed = false;
    }

    if (p->jump_released && p->y_velocity < 0) {
        p->y_velocity *= JUMP_CUT_MULT;
        p->jump_released = false;
    }
}

#include "enemy.h"

#include "../player/player.h"

#include <SDL2/SDL.h>
#include <math.h>

#define FIXED_DT (1.0f / 60.0f)

#define TILE_SIZE 50
#define SPRITE_SIZE 50.0f

#define GRAVITY 2500.0f
#define MAX_FALL_SPEED 1000.0f

static float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

void enemy_init(Enemy *enemy) {
    enemy->x = 500;
    enemy->y = 0;
    enemy->x_velocity = 120.0f;
    enemy->y_velocity = 0;
    enemy->on_ground = false;
    enemy->direction = -1.0f;
}

void enemy_update(Enemy *enemy, Tilemap *map) {
    if (enemy->on_ground) {

        float next_x =
            enemy->x +
            enemy->direction *
            enemy->x_velocity *
            FIXED_DT;

        int edge_x;

        if (enemy->direction > 0)
            edge_x = (int)((next_x + SPRITE_SIZE) / TILE_SIZE);
        else
            edge_x = (int)(next_x / TILE_SIZE);

        int foot_y = (int)((enemy->y + SPRITE_SIZE) / TILE_SIZE);
        bool floor_ahead = tilemap_is_solid(map, edge_x, foot_y);

        if (!floor_ahead)
            enemy->direction *= -1.0f;
        else
            enemy->x = next_x;

    } else {

        enemy->y_velocity += GRAVITY * FIXED_DT;
        enemy->y_velocity = clamp(enemy->y_velocity, -INFINITY, MAX_FALL_SPEED);

        float new_y = enemy->y + enemy->y_velocity * FIXED_DT;
        int tile_left = (int)(enemy->x / TILE_SIZE);
        int tile_right = (int)((enemy->x + SPRITE_SIZE - 1) / TILE_SIZE);
        int tile_bottom = (int)((new_y + SPRITE_SIZE) / TILE_SIZE);

        for (int x = tile_left; x <= tile_right; x++)
            if (tilemap_is_solid(map, x, tile_bottom)) {
                new_y = tile_bottom * TILE_SIZE - SPRITE_SIZE;
                enemy->y_velocity = 0;
                enemy->on_ground = true;
                break;
            }

        enemy->y = new_y;
    }
}

bool player_enemy_collision(void *player_ptr, Enemy *enemy) {
    Player *player = (Player *)player_ptr;

    SDL_FRect a = {
        player->x,
        player->y,
        SPRITE_SIZE,
        SPRITE_SIZE
    };

    SDL_FRect b = {
        enemy->x,
        enemy->y,
        SPRITE_SIZE,
        SPRITE_SIZE
    };

    return SDL_HasIntersectionF(&a, &b);
}

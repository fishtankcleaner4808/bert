#ifndef RENDER_H
#define RENDER_H

#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../tilemap/tilemap.h"
#include "../camera/camera.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void render_game(SDL_Renderer *renderer,
    Tilemap *map,
    Player *player,
    Enemy *enemy,
    Camera *cam,
    float alpha);

void render_menu(SDL_Renderer *renderer, TTF_Font *font);

#endif

#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

void render_game(SDL_Renderer *renderer,
    Tilemap *map,
    Player *player,
    Enemy *enemy,
    Camera *cam,
    float alpha);

void render_menu(SDL_Renderer *renderer, TTF_Font *font);

#endif

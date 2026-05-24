#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "constants.h"

static float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

static void draw_text(SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    int x,
    int y)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render_game(SDL_Renderer *renderer,
    Tilemap *map,
    Player *player,
    Enemy *enemy,
    Camera *cam,
    float alpha)
{
    float render_x = lerp(player->prev_x, player->x, alpha);
    float render_y = lerp(player->prev_y, player->y, alpha);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            if (map->tiles[y * map->width + x]) {
                SDL_Rect tile = {
                    (int)(x * TILE_SIZE - cam->x),
                    (int)(y * TILE_SIZE - cam->y),
                    TILE_SIZE,
                    TILE_SIZE
                };

                SDL_SetRenderDrawColor(renderer,
                    100,
                    100,
                    255,
                    255);

                SDL_RenderFillRect(renderer, &tile);
            }

    SDL_Rect enemy_rect = {
        (int)(enemy->x - cam->x),
        (int)(enemy->y - cam->y),
        SPRITE_SIZE,
        SPRITE_SIZE
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &enemy_rect);

    SDL_Rect player_rect = {
        (int)(render_x - cam->x),
        (int)(render_y - cam->y),
        SPRITE_SIZE,
        SPRITE_SIZE
    };

    SDL_SetRenderDrawColor(renderer, 255, 220, 0, 255);
    SDL_RenderFillRect(renderer, &player_rect);
    SDL_RenderPresent(renderer);
}

void render_menu(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    draw_text(renderer, font,
        "1) Start a game",
        250,
        240);

    draw_text( renderer, font,
        "2) Quit",
        250,
        300);

    SDL_RenderPresent(renderer);
}

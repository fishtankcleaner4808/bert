#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "constants.h"
#include "player.h"
#include "enemy.h"
#include "tilemap.h"
#include "camera.h"
#include "render.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING
} GameState;

int game_run(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Bert (phase 1)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!window) {
        SDL_Log("Window Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        SDL_Log("Renderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    if (TTF_Init() != 0) {
        SDL_Log("TTF_Init Error: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    TTF_Font *font = TTF_OpenFont("assets/byte.ttf", 36);

    if (!font) {
        SDL_Log("Failed to load font file: byte.ttf: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 5;
    }

    Tilemap map = tilemap_load("assets/map.txt");

    Player player;
    Enemy enemy;
    Camera cam;

    player_init(&player);
    enemy_init(&enemy);
    camera_init(&cam, &map);

    GameState state = GAME_STATE_MENU;
    Uint64 prev = SDL_GetPerformanceCounter();
    float freq = (float)SDL_GetPerformanceFrequency();
    float accumulator = 0.0f;
    bool running = true;
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    while (running) {
        Uint64 now = SDL_GetPerformanceCounter();
        float frame_dt = (float)(now - prev) / freq;
        prev = now;

        if (frame_dt > 0.25f)
            frame_dt = 0.25f;

        accumulator += frame_dt;

        player.jump_pressed = false;
        player.jump_released = false;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN && !event.key.repeat) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;

                if (state == GAME_STATE_MENU) {
                    if (event.key.keysym.sym == SDLK_1 ||
                        event.key.keysym.sym == SDLK_RETURN) {

                        player_init(&player);
                        enemy_init(&enemy);
                        state = GAME_STATE_PLAYING;
                    }

                    if (event.key.keysym.sym == SDLK_2)
                        running = false;
                }

                if (state == GAME_STATE_PLAYING)
                    if (event.key.keysym.sym == SDLK_SPACE)
                        player.jump_pressed = true;
            }

            if (event.type == SDL_KEYUP)
                if (event.key.keysym.sym == SDLK_SPACE)
                    player.jump_released = true;
        }

        if (state == GAME_STATE_PLAYING) {
            player.input_x = 0.0f;
            if (keys[SDL_SCANCODE_LEFT])  player.input_x -= 1.0f;
            if (keys[SDL_SCANCODE_RIGHT]) player.input_x += 1.0f;

            while (accumulator >= FIXED_DT) {
                player.prev_x = player.x;
                player.prev_y = player.y;

                player_update(&player, &map);
                enemy_update(&enemy, &map);

                if (player_enemy_collision(&player, &enemy))
                    state = GAME_STATE_MENU;

                accumulator -= FIXED_DT;
            }

            camera_follow(&cam, &player);
                //player.x,
                //player.y);

            render_game(renderer,
                &map,
                &player,
                &enemy,
                &cam,
                accumulator / FIXED_DT);

        } else
            render_menu(renderer, font);
    }

    free(map.tiles);
    map.tiles = NULL;
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

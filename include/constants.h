#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define FIXED_DT (1.0f / 60.0f)

#define TILE_SIZE   50
#define SPRITE_SIZE 50.0f
#define CAMERA_SMOOTHING 10.0f

#define MOVE_ACCEL 2000.0f
#define MAX_SPEED_X 300.0f
#define FRICTION   1800.0f

#define GRAVITY        2500.0f
#define MAX_FALL_SPEED 1000.0f

#define JUMP_VELOCITY -1050.0f
#define JUMP_CUT_MULT     0.4f

typedef struct {
    int width;
    int height;
    int *tiles;
} Tilemap;

typedef struct {
    float x;
    float y;
    float x_max;
    float y_max;
    float x_margin;
    float y_margin;
} Camera;

typedef struct {
    float x;
    float y;
    float x_velocity;
    float y_velocity;
    bool on_ground;
    float direction;
} Enemy;

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

#endif

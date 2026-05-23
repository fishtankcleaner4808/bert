#ifndef CAMERA_H
#define CAMERA_H
#include "../tilemap/tilemap.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    float x;
    float y;
    float x_max;
    float y_max;
    float x_margin;
    float y_margin;
} Camera;

void camera_init(Camera *cam, Tilemap *map);

void camera_follow(Camera *cam,
    float target_x,
    float target_y);

#endif

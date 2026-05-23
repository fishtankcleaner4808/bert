#include "camera.h"

#define TILE_SIZE 50
#define CAMERA_SMOOTHING 10.0f
#define FIXED_DT (1.0f / 60.0f)

static float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

static float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void camera_init(Camera *cam, Tilemap *map) {
    cam->x = 0;
    cam->y = 0;

    cam->x_max = map->width * TILE_SIZE - 800;
    cam->y_max = map->height * TILE_SIZE - 600;

    cam->x_margin = 200.0f;
    cam->y_margin = 150.0f;
}

void camera_follow(Camera *cam,
    float target_x,
    float target_y)
{
    float cam_target_x = cam->x;
    float cam_target_y = cam->y;

    if (target_x - cam_target_x < cam->x_margin)
        cam_target_x = target_x - cam->x_margin;

    if (target_x - cam_target_x > WINDOW_WIDTH - cam->x_margin)
        cam_target_x = target_x - (WINDOW_WIDTH - cam->x_margin);

    if (target_y - cam_target_y < cam->y_margin)
        cam_target_y = target_y - cam->y_margin;

    if (target_y - cam_target_y > WINDOW_HEIGHT - cam->y_margin)
        cam_target_y = target_y - (WINDOW_HEIGHT - cam->y_margin);

    cam_target_x = clamp(cam_target_x, 0.0f, cam->x_max);
    cam_target_y = clamp(cam_target_y, 0.0f, cam->y_max);

    cam->x = lerp(cam->x, cam_target_x, CAMERA_SMOOTHING * FIXED_DT);
    cam->y = lerp(cam->y, cam_target_y, CAMERA_SMOOTHING * FIXED_DT);
}

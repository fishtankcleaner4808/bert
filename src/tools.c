#include <stdbool.h>
#include "constants.h"

float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

bool is_px_solid(Tilemap *map, int x, int y) {
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return true;

    return map->tiles[y * map->width + x] == 1;
}

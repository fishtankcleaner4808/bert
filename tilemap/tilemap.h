#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int *tiles;
} Tilemap;

Tilemap tilemap_load(const char *filename);
bool tilemap_is_solid(Tilemap *map, int x, int y);

#endif

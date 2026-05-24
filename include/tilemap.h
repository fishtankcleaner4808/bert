#ifndef TILEMAP_H
#define TILEMAP_H

Tilemap tilemap_load(const char *filename);
bool tilemap_is_solid(Tilemap *map, int x, int y);

#endif

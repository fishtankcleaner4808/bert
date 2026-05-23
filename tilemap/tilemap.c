#include "tilemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tilemap tilemap_load(const char *filename) {
    Tilemap map = {0};
    FILE *f = fopen(filename, "r");

    if (!f)
        return map;

    char line[1024];

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);

        if (line[len - 1] == '\n')
            len--;

        if (len > map.width)
            map.width = len;

        map.height++;
    }

    rewind(f);

    map.tiles = malloc(map.width * map.height * sizeof(int));

    int y = 0;

    while (fgets(line, sizeof(line), f)) {
        int line_len = strlen(line);

        for (int x = 0; x < map.width; x++)
            if (x < line_len && line[x] == '1')
                map.tiles[y * map.width + x] = 1;
            else
                map.tiles[y * map.width + x] = 0;

        y++;
    }

    fclose(f);
    return map;
}

bool tilemap_is_solid(Tilemap *map, int x, int y) {
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return true;

    return map->tiles[y * map->width + x] == 1;
}

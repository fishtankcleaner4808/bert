#ifndef TOOLS_H
#define TOOLS_H
static float clamp(float v, float min, float max);
static float lerp(float a, float b, float t);
bool is_px_solid(Tilemap *map, int x, int y);
#endif

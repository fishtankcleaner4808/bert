#ifndef CAMERA_H
#define CAMERA_H
void camera_init(Camera *cam, Tilemap *map);
void camera_follow(Camera *cam, Player *player);
#endif

#ifndef PLAYER_H
#define PLAYER_H
void player_init(Player *player);
void player_move_x(Player *player, Tilemap *map);
void player_move_y(Player *player, Tilemap *map);
#endif

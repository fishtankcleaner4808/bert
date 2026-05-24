#ifndef ENEMY_H
#define ENEMY_H

void enemy_init(Enemy *enemy);
void enemy_update(Enemy *enemy, Tilemap *map);
bool player_enemy_collision(void *player_ptr, Enemy *enemy);

#endif

#ifndef PLAYER_OPERATION_H
# define PLAYER_OPERATION_H

void	rotate_player(int key_code, t_player *player);
void	move_player(int key_code, t_player *player, t_map_element **map);

#endif
#ifndef MOVE_PLAYER_HELPER_H
# define MOVE_PLAYER_HELPER_H

# include "cub3d_structs.h"

t_map_element	get_maged_ele(const t_map_element **map, const int y,
					const int x);
bool	can_enter(const t_map_element **map, const int maged_y, const int maged_x);
t_point			assign_point(const int x, const int y);

#endif

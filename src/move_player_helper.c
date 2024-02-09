#include "cub3d_structs.h"

t_map_element	get_maged_ele(const t_map_element **map, const int y,
		const int x)
{
	return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION]);
}

t_point	assign_point(const int x, const int y)
{
	t_point	result;

	result.x = x;
	result.y = y;
	return (result);
}

#include "cub3d_structs.h"

static t_map_element	get_maged_ele(const t_map_element **map, const int y,
		const int x)
{
	return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION]);
}

bool	can_enter(const t_map_element **map, const int maged_y,
		const int maged_x)
{
	const int	collision_distance = ((double)(PLAYER_MAGFICATION)) * (0.1); // この値でどの程度壁に近づけるか決めてる //

	return (
		get_maged_ele(map, maged_y + collision_distance, maged_x) != WALL && \
		get_maged_ele(map, maged_y - collision_distance, maged_x) != WALL && \
		get_maged_ele(map, maged_y, maged_x + collision_distance) != WALL && \
		get_maged_ele(map, maged_y, maged_x - collision_distance) != WALL);
}

t_point	assign_point(const int x, const int y)
{
	t_point	result;

	result.x = x;
	result.y = y;
	return (result);
}

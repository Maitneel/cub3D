#include <stdbool.h>

#include "cub3d_structs.h"


static bool is_not_using_incorrect_element(const t_map_element **map)
{
	// TODO
	return (true);
}
static bool is_surrounded_by_wall(const t_map_element **map)
{
	// TODO
	return (true);
}
static bool is_connected_all_element(const t_map_element **map)
{
	// TODO
	return (true);
}

bool	is_correct_map(const t_map_element **map)
{
	return (
		is_not_using_incorrect_element(map) && \
		is_surrounded_by_wall(map) && \
		is_connected_all_element(map)
	);
}

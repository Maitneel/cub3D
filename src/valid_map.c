#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "cub3d_structs.h"

static bool	is_not_using_incorrect_element(const t_map_element **map)
{
	size_t i;
	size_t j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != END_OF_LINE)
		{
			if (map[i][j] == INCORRECTED_MAP_CHAR)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	is_surrounded_by_wall(const t_map_element **map)
{
	// TODO
	return (true);
}

static bool	is_connected_all_element(const t_map_element **map)
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

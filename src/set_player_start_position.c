#include "cub3d_structs.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>


static bool	is_start_element(t_map_element element)
{
	return (
		element == START_N || element == START_S || \
		element == START_E || element == START_W
	);
}

static double	get_start_direction(t_map_element element)
{
	if (element == START_N)
	{
		return (M_PI_2 * 0);
	}
	else if (element == START_E)
	{
		return (M_PI_2 * 1);
	}
	else if (element == START_S)
	{
		return (M_PI_2 * 2);
	}
	else if (element == START_W)
	{
		return (M_PI_2 * 3);
	}
	else
	{
		return (-1);
	}
}

void	set_player_start_position(t_player *player, t_map_element **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != END_OF_LINE)
		{
			if (is_start_element(map[i][j]))
			{
				player->point.x_hoge = j * PLAYER_MAGFICATION + (PLAYER_MAGFICATION / 2);
				player->point.y_hoge = i * PLAYER_MAGFICATION + (PLAYER_MAGFICATION / 2);
				player->direction = get_start_direction(map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

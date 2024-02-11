/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:03:14 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:30:25 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "cub3d_structs.h"
#include <stdio.h>

static bool	is_not_using_incorrect_element(const t_map_element **map)
{
	size_t	i;
	size_t	j;
	size_t	start_count;

	start_count = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != END_OF_LINE)
		{
			if (map[i][j] == INCORRECTED_MAP_ELEMENT)
				return (false);
			if (map[i][j] == START_N || map[i][j] == START_S || \
				map[i][j] == START_E || map[i][j] == START_W)
				start_count++;
			j++;
		}
		i++;
	}
	if (start_count != 1)
		return (false);
	return (true);
}

static bool	is_there_only_wall_next_to(const t_map_element **map,
		const int point_i, const int point_j)
{
	int	i;
	int	j;

	i = point_i - 1 - 1;
	while (++i <= point_i + 1)
	{
		if (i < 0 || map[i] == NULL)
			continue ;
		j = point_j - 1 - 1;
		while (++j <= point_j + 1)
		{
			if (j < 0 || map[i][j] == END_OF_LINE)
				continue ;
			if (map[i][j] != WALL && map[i][j] != OUT_OF_MAP)
				return (false);
		}
	}
	return (true);
}

static bool	is_surrounded_by_wall(const t_map_element **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != END_OF_LINE)
		{
			if (map[i][j] == OUT_OF_MAP)
			{
				if (!is_there_only_wall_next_to(map, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_correct_map(const t_map_element **map)
{
	return (
		is_not_using_incorrect_element(map) && \
		is_surrounded_by_wall(map)
	);
}

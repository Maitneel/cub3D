/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:25:24 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 22:25:25 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

bool	is_wall(t_cub3d *cub3d, int y, int x)
{
	t_map_element	**map;

	map = cub3d->map;
	if (!(0 < y && y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= x
			&& x < cub3d->map_width * PLAYER_MAGFICATION))
	{
		return (true);
	}
	return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == WALL || map[y
		/ PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == OUT_OF_MAP);
}

double	get_distance(t_point *start, t_point *end)
{
	if (start->x == INT_MAX || start->y == INT_MAX || end->x == INT_MAX
		|| end->y == INT_MAX)
		return (INFINITY);
	return (sqrt(pow(end->y - start->y, 2) + pow(end->x - start->x, 2)));
}

double	get_adj_dis(t_player *player, double ray_dir, t_point *start,
		t_point *end)
{
	double	dtheta;

	dtheta = ray_dir - player->direction - M_PI_2;
	return (cos(dtheta) * get_distance(start, end));
}

double	get_wall_ratio(double wall_distance)
{
	return ((double)WALL_HEIGHT / (tan(VERT_FOV_ANGLE)
			* (double)wall_distance));
}

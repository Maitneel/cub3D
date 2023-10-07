/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:45:29 by taksaito          #+#    #+#             */
/*   Updated: 2023/10/07 18:28:59 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"

static t_vector2d get_next_pos(t_cub3d *cub3d, double direction);

t_vector2d	get_intersection_with_wall(t_cub3d *cub3d, double direction)
{
	t_vector2d	player_pos;
	t_vector2d	dir;

	player_pos.y = cub3d->player.point.y;
	player_pos.x = cub3d->player.point.x;

	int map_y = player_pos.y;
	int map_x = player_pos.x;

	dir = unit_vector(cub3d->player.direction);
	
	return (player_pos);
}

bool	is_wall(t_vector2d *vec)
{
	return (true);
}
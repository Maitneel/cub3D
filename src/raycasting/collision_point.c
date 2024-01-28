/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:38:06 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 22:41:19 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_point	hz_collition_point(t_cub3d *cub3d, double dir)
{
	int	side_x;
	int	side_y;
	int	step;

	if (is_north(dir))
		set_hz_step_if_north(cub3d->player, &step, &side_y);
	else if (is_south(dir))
		set_hz_step_if_sourth(cub3d->player, &step, &side_y);
	else
		return (new_point_struct(INT_MAX, INT_MAX));
	side_x = tan(dir + M_PI_2) * side_y * -1;
	while (!is_wall(cub3d, cub3d->player.point.y + side_y, cub3d->player.point.x
			+ side_x))
	{
		side_y += step;
		side_x = tan(dir + M_PI_2) * side_y * -1;
	}
	return (new_point_struct(cub3d->player.point.y + side_y,
			cub3d->player.point.x + side_x));
}

t_point	vert_collition_point(t_cub3d *cub3d, double dir)
{
	int	side_x;
	int	side_y;
	int	step;

	if (is_east(dir))
		set_ver_step_if_east(cub3d->player, &step, &side_x);
	else if (is_west(dir))
		set_ver_step_if_west(cub3d->player, &step, &side_x);
	else
		return (new_point_struct(INT_MAX, INT_MAX));
	side_y = side_x * tan(dir);
	while (!is_wall(cub3d, cub3d->player.point.y + side_y, cub3d->player.point.x
			+ side_x))
	{
		side_x += step;
		side_y = side_x * tan(dir);
	}
	return (new_point_struct(cub3d->player.point.y + side_y,
			cub3d->player.point.x + side_x));
}

t_coll_point	get_collision_point(t_cub3d *cub3d, double dir)
{
	int		n;
	int		before_x;
	int		before_y;
	t_point	hz_point;
	t_point	vert_point;

	n = 1;
	before_x = cub3d->player.point.x;
	before_y = cub3d->player.point.y;
	hz_point = hz_collition_point(cub3d, dir);
	vert_point = vert_collition_point(cub3d, dir);
	if (get_distance(&(cub3d->player.point),
			&hz_point) < get_distance(&(cub3d->player.point), &vert_point))
		return (new_coll_pt_struct(hz_point, false));
	else
		return (new_coll_pt_struct(vert_point, true));
}

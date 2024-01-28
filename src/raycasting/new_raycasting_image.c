/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:28:17 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 17:50:15 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "libft.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	is_wall(t_cub3d *cub3d, int y, int x)
{
	const t_map_element	**map = cub3d->map;

	if (!(0 < y && y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= x
			&& x < cub3d->map_width * PLAYER_MAGFICATION))
	{
		return (true);
	}
	return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == WALL || map[y
		/ PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == OUT_OF_MAP);
}

t_point			new_point_struct(int y, int x);

t_point	hz_collition_point(t_cub3d *cub3d, double dir)
{
	int	side_x;
	int	side_y;
	int	step;

	if (is_north(dir))
	{
		side_y = -1 * cub3d->player.point.y % PLAYER_MAGFICATION - 1;
		step = -PLAYER_MAGFICATION;
	}
	else if (is_south(dir))
	{
		side_y = PLAYER_MAGFICATION - (cub3d->player.point.y
				% PLAYER_MAGFICATION);
		step = PLAYER_MAGFICATION;
	}
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
	{
		side_x = PLAYER_MAGFICATION - (cub3d->player.point.x
				% PLAYER_MAGFICATION);
		side_y = side_x * tan(dir);
		step = PLAYER_MAGFICATION;
	}
	else if (is_west(dir))
	{
		// ここの初期値うまう動かないかも //
		side_x = -1 * cub3d->player.point.x % PLAYER_MAGFICATION - 1;
		side_y = side_x * tan(dir);
		step = -PLAYER_MAGFICATION;
	}
	else
	{
		return (new_point_struct(INT_MAX, INT_MAX));
	}
	while (!is_wall(cub3d, cub3d->player.point.y + side_y, cub3d->player.point.x
			+ side_x))
	{
		side_x += step;
		side_y = side_x * tan(dir);
	}
	return (new_point_struct(cub3d->player.point.y + side_y,
			cub3d->player.point.x + side_x));
}

double	get_distance(t_point *start, t_point *end)
{
	if (start->x == INT_MAX || start->y == INT_MAX || end->x == INT_MAX
		|| end->y == INT_MAX)
		return (INFINITY);
	return (sqrt(pow(end->y - start->y, 2) + pow(end->x - start->x, 2)));
}

t_coll_point	new_coll_pt_struct(t_point pt, bool is_vert);

t_coll_point	get_collision_point2(t_cub3d *cub3d, double dir)
{
	int		n;
	int		y;
	int		x;
	int		before_x;
	int		before_y;
	t_point	hz_point;
	t_point	vert_point;

	n = 1;
	y = cub3d->player.point.y;
	x = cub3d->player.point.x;
	before_x = x;
	before_y = y;
	hz_point = hz_collition_point(cub3d, dir);
	vert_point = vert_collition_point(cub3d, dir);
	if (get_distance(&(cub3d->player.point),
			&hz_point) < get_distance(&(cub3d->player.point), &vert_point))
	{
		return (new_coll_pt_struct(hz_point, false));
	}
	else
	{
		return (new_coll_pt_struct(vert_point, true));
	}
}

t_point	*get_collision_point(t_cub3d *cub3d, double dir)
{
	int	n;
	int	y;
	int	x;
	int	before_x;
	int	before_y;

	n = 1;
	y = cub3d->player.point.y;
	x = cub3d->player.point.x;
	before_x = x;
	before_y = y;
	while (true)
	{
		before_x = x;
		before_y = y;
		y = cub3d->player.point.y + sin(dir) * n;
		x = cub3d->player.point.x + cos(dir) * n;
		if (is_wall(cub3d, y, x))
		{
			break ;
		}
		n++;
	}
	return (new_point(before_y, before_x));
}

double	get_adj_dis(t_player *player, double ray_dir, t_point *start,
		t_point *end)
{
	double	dtheta;

	dtheta = ray_dir - player->direction - M_PI_2;
	return (cos(dtheta) * get_distance(start, end));
}

double	get_wall_ratio(double wall_distance, const double dir)
{
	return ((double)WALL_HEIGHT / (tan(VERT_FOV_ANGLE)
			* (double)wall_distance));
}

t_graphic_info	*get_graphic_info_by_point(t_cub3d *cub3d,
		t_coll_point *coll_pt)
{
	const t_map_element	**map = cub3d->map;
	const int			x = coll_pt->pt.x / PLAYER_MAGFICATION;
	const int			y = coll_pt->pt.y / PLAYER_MAGFICATION;

	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
	{
		return (cub3d->graphic_info->north_texture);
	}
	if (!is_wall(cub3d, coll_pt->pt.y, coll_pt->pt.x))
	{
		return (cub3d->graphic_info->west_texture);
	}
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
	{
		return (cub3d->graphic_info->east_texture);
	}
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
	{
		return (cub3d->graphic_info->west_texture);
	}
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
	{
		return (cub3d->graphic_info->south_texture);
	}
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
	{
		return (cub3d->graphic_info->north_texture);
	}
	return (cub3d->graphic_info->east_texture);
}

double	get_texture_position(t_cub3d *cub3d, t_coll_point *coll_pt)
{
	const t_map_element	**map = cub3d->map;
	const int			y = coll_pt->pt.y / PLAYER_MAGFICATION;
	const int			x = coll_pt->pt.x / PLAYER_MAGFICATION;

	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
	{
		return (0.0);
	}
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
	{
		return ((double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	}
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
	{
		return (1.0 - (double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	}
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
	{
		return (1.0 - (double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	}
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
	{
		return ((double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	}
	return (0.0);
}

#define SCREEN_MAGFICATION 100000

t_point	get_screen_point(const t_point focus_point, const double direction)
{
	t_point	screen_point;

	screen_point.x = sin(direction) * SCREEN_MAGFICATION + focus_point.x;
	screen_point.y = cos(direction) * SCREEN_MAGFICATION + focus_point.y;
	return (screen_point);
}

double	get_direction_across_screen_position(const t_point player_position,
		const t_point screen_left, const t_point screen_right,
		const int screen_position)
{
	double	position_x;
	double	position_y;
	double	direction;
	double	diff_x;
	double	diff_y;

	position_x = (screen_left.x + ((screen_right.x - screen_left.x)
				* (double)(screen_position) / WINDOW_WIDTH));
	position_y = (screen_left.y + ((screen_right.y - screen_left.y)
				* (double)(screen_position) / WINDOW_WIDTH));
	diff_x = position_x - player_position.x;
	diff_y = position_y - player_position.y;
	// ここ問題ないかわからない //
	// atan func は ＋- inf が与えられた時 +- pi/2 を返すが //
	// float のゼロ除算が inf を返すかがわからない //
	direction = (atan(diff_y / diff_x)) * -1.0;
	if (position_x < player_position.x)
	{
		direction += M_PI * 2.0;
	}
	else
	{
		direction += M_PI;
	}
	return (direction);
}

t_mlx_image	*new_raycasting_image(const t_cub3d *cub3d, const t_mlx *mlx,
		const int width, const int height)
{
	t_mlx_image		*image;
	t_coll_point	coll_pt;
	double			wall_raito;
	t_point			screen_left;
	t_point			screen_right;
	double			ray_dir;
	double			wall_dis;

	screen_left = get_screen_point(cub3d->player.point, cub3d->player.direction
			- (HN_FOV_ANGLE / 2.0));
	screen_right = get_screen_point(cub3d->player.point, cub3d->player.direction
			+ (HN_FOV_ANGLE / 2.0));
	image = new_image_struct(mlx, width, height);
	if (is_wall(cub3d, cub3d->player.point.y, cub3d->player.point.x))
	{
		ft_bzero(image->data_addr, image->width * image->height
			* (image->bit_per_pixel / CHAR_BIT));
		return (image);
	}
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		ray_dir = get_direction_across_screen_position(cub3d->player.point,
				screen_left, screen_right, x);
		coll_pt = get_collision_point2(cub3d, ray_dir);
		wall_dis = get_adj_dis(&cub3d->player, ray_dir, &(coll_pt.pt),
				&(cub3d->player.point));
		wall_raito = get_wall_ratio(wall_dis, ray_dir);
		paste_texture(cub3d, image, wall_raito, get_texture_position(cub3d,
				&coll_pt), get_graphic_info_by_point(cub3d, &coll_pt.pt), x);
	}
	return (image);
}

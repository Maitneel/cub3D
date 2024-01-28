/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:28:17 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 21:53:59 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "libft.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
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

t_texture	*get_graphic_info_by_point(t_cub3d *cub3d, t_coll_point *coll_pt)
{
	t_map_element	**map;

	map = cub3d->map;
	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
		return (cub3d->graphic_info->north_texture);
	if (!is_wall(cub3d, coll_pt->pt.y, coll_pt->pt.x))
		return (cub3d->graphic_info->west_texture);
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
		return (cub3d->graphic_info->east_texture);
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
		return (cub3d->graphic_info->west_texture);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
		return (cub3d->graphic_info->south_texture);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
		return (cub3d->graphic_info->north_texture);
	return (cub3d->graphic_info->east_texture);
}

double	get_texture_position(t_cub3d *cub3d, t_coll_point *coll_pt)
{
	t_map_element	**map;

	map = cub3d->map;
	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
		return (0.0);
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
		return ((double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
		return (1.0 - (double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
		return (1.0 - (double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
		return ((double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	return (0.0);
}

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
		direction += M_PI * 2.0;
	else
		direction += M_PI;
	return (direction);
}

t_mlx_image	*paste_black_image(t_mlx_image *image)
{
	ft_bzero(image->data_addr, image->width * image->height
		* (image->bit_per_pixel / CHAR_BIT));
	return (image);
}

t_mlx_image	*draw_world(t_cub3d *cub3d, t_mlx_image *image, t_point screen_left,
		t_point screen_right)
{
	t_coll_point	coll_pt;
	double			ray_dir;
	double			wall_dis;
	double			wall_raito;
	int				x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_dir = get_direction_across_screen_position(cub3d->player.point,
				screen_left, screen_right, x);
		coll_pt = get_collision_point(cub3d, ray_dir);
		wall_dis = get_adj_dis(&cub3d->player, ray_dir, &(coll_pt.pt),
				&(cub3d->player.point));
		wall_raito = get_wall_ratio(wall_dis);
		paste_texture(cub3d, image, wall_raito, get_texture_position(cub3d,
				&coll_pt), get_graphic_info_by_point(cub3d,
				(t_coll_point *)&(coll_pt.pt)), x);
		x++;
	}
	return (image);
}

t_mlx_image	*new_raycasting_image(t_cub3d *cub3d, t_mlx *mlx,
	const int width, const int height)
{
	t_mlx_image		*image;
	t_point			screen_left;
	t_point			screen_right;

	screen_left = get_screen_point(cub3d->player.point, cub3d->player.direction
			- (HN_FOV_ANGLE / 2.0));
	screen_right = get_screen_point(cub3d->player.point, cub3d->player.direction
			+ (HN_FOV_ANGLE / 2.0));
	image = new_image_struct(mlx, width, height);
	if (is_wall(cub3d, cub3d->player.point.y, cub3d->player.point.x))
		return (paste_black_image(image));
	return (draw_world(cub3d, image, screen_left, screen_right));
}

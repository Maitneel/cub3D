/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:32:32 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/03 17:48:12 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "libft.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
#include "raycasting.h"

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
	if (diff_x == 0.0)
		direction = (atan(INFINITY)) * -1.0;
	else
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

t_paste_texture_info	new_paste_texxture_info(double mag, double texture_pos,
		size_t image_x)
{
	t_paste_texture_info	info;

	info.mag = mag;
	info.texture_pos = texture_pos;
	info.image_x = image_x;
	return (info);
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
		paste_texture(cub3d, image, get_texture(cub3d, &coll_pt),
			new_paste_texxture_info(wall_raito, get_texture_position(cub3d,
					&coll_pt), x));
		x++;
	}
	return (image);
}

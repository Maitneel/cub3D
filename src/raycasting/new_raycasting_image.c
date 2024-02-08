/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:28:17 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/03 17:29:55 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "libft.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
#include "raycasting.h"

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

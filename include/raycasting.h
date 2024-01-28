/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:41:53 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 21:10:50 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d_structs.h"
# include <math.h>

t_mlx_image	*new_raycasting_image(t_cub3d *cub3d, t_mlx *mlx,
	const int width, const int height);

// util
double norm_dir(double dir);
bool is_west(double ray_dir);
bool is_east(double ray_dir);
bool is_south(double ray_dir);
bool is_north(double ray_dir);

#endif // RAYCASTING_H

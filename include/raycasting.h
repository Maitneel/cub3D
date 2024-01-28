/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:41:53 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 21:38:20 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d_structs.h"
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

t_mlx_image	*new_raycasting_image(t_cub3d *cub3d, t_mlx *mlx,
	const int width, const int height);
bool	is_wall(t_cub3d *cub3d, int y, int x);
double	get_distance(t_point *start, t_point *end);

// util
double norm_dir(double dir);
bool is_west(double ray_dir);
bool is_east(double ray_dir);
bool is_south(double ray_dir);
bool is_north(double ray_dir);

// collistion_point
t_coll_point	get_collision_point(t_cub3d *cub3d, double dir);

#endif // RAYCASTING_H

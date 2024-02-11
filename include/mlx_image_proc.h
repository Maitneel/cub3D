/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_proc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:41 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:42 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IMAGE_PROC_H
# define MLX_IMAGE_PROC_H

# include "cub3d_structs.h"

t_mlx_image	*new_image_struct(t_mlx *mlx, int width, int height);
int			put_pixel_to_mlx_image(t_mlx_image *image, \
				const int x, const int y, const int color);

#endif

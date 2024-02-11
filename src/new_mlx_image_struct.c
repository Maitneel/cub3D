/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mlx_image_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:48 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:48 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"

#include "cub3d_structs.h"
#include "util_lib.h"
#include "print_lib.h"

t_mlx_image	*new_image_struct(t_mlx *mlx, int width, int height)
{
	t_mlx_image	*mlx_image;

	mlx_image = ft_xcalloc(1, sizeof(t_mlx_image));
	mlx_image->image_ptr = mlx_new_image(mlx->mlx, width, height);
	if (mlx_image->image_ptr == NULL)
	{
		print_error(false, "mlx_new_image failed\n");
		exit(1);
	}
	mlx_image->width = width;
	mlx_image->height = height;
	mlx_image->data_addr = mlx_get_data_addr(mlx_image->image_ptr, \
		&(mlx_image->bit_per_pixel), &(mlx_image->size_line), \
		&(mlx_image->endian));
	return (mlx_image);
}

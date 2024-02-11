/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:03:11 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:03:12 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "free_lib.h"
#include "mlx.h"
#include <stdlib.h>

void	free_cub3d(t_cub3d *cub3d)
{
	if (cub3d == NULL)
		return ;
	free_graphic_info(cub3d->graphic_info);
	free_map(cub3d->map);
	free(cub3d);
}

void	free_mlx_struct(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	// TODO
}

void	free_mlx_hook_arg(t_mlx_hook_arg *mlx_hook_arg)
{
	if (mlx_hook_arg == NULL)
		return ;
	free_mlx_struct(mlx_hook_arg->mlx);
	free_cub3d(mlx_hook_arg->cub3d);
	free(mlx_hook_arg);
	return ;
}

void	free_and_detroy_mlx_image(t_mlx_image *image, const t_mlx *mlx)
{
	if (image == NULL)
		return ;
	mlx_destroy_image(mlx->mlx, image->image_ptr);
	free(image);
}

void	free_uint_array_array(unsigned int **array, const size_t height)
{
	size_t	i;

	if (array == NULL)
	{
		return ;
	}
	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

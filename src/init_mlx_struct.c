/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:31 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:31 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "mlx.h"
#include "util_lib.h"
#include "free_lib.h"

t_mlx	*init_mlx_struct(char *title)
{
	t_mlx	*mlx;

	mlx = ft_xcalloc(1, sizeof(t_mlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (NULL);
	mlx->window = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	if (mlx->window == NULL)
	{
		free_mlx_struct(mlx);
		return (NULL);
	}
	return (mlx);
}

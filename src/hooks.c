/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:23 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:31:22 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"

#include "free_lib.h"
#include "minimap.h"
#include "mlx.h"
#include "mlx_defines.h"
#include "player_operation.h"
#include "raycasting.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>

#define DEBUGGING

int	key_hook(int key_code, void *arg)
{
	const t_mlx_hook_arg	*mlx_hook_arg = arg;

	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
		rotate_player(key_code, &(mlx_hook_arg->cub3d->player));
	if (key_code == KEY_A || key_code == KEY_S || \
		key_code == KEY_D || key_code == KEY_W)
		move_player(key_code, &(mlx_hook_arg->cub3d->player), \
			mlx_hook_arg->cub3d->map);
	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	return (0);
}

int	loop_hook(void *arg)
{
	const t_mlx_hook_arg	*mlx_hook_arg = arg;
	t_mlx					*arg_mlx;
	t_mlx_image				*image[IMAGE_SIZE];
	size_t					i;

	i = -1;
	while (++i < IMAGE_SIZE)
		image[i] = NULL;
	arg_mlx = mlx_hook_arg->mlx;
	image[0] = new_raycasting_image(mlx_hook_arg->cub3d, arg_mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	image[1] = new_minimap(mlx_hook_arg->cub3d, arg_mlx, 160, 120);
	i = 0;
	while (i < IMAGE_SIZE)
	{
		free_and_detroy_mlx_image(arg_mlx->image[i], arg_mlx);
		if (image[i] != NULL)
			mlx_put_image_to_window(arg_mlx->mlx, arg_mlx->window,
				image[i]->image_ptr, 0, 0);
		arg_mlx->image[i] = image[i];
		i++;
	}
	return (0);
}

void	add_hooks(t_mlx_hook_arg *mlx_hook_arg)
{
	mlx_key_hook(mlx_hook_arg->mlx->window, key_hook, mlx_hook_arg);
	mlx_loop_hook(mlx_hook_arg->mlx->mlx, loop_hook, mlx_hook_arg);
}

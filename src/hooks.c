#include "cub3d_structs.h"
#include "debug.h"
#include "free_lib.h"
#include "minimap.h"
#include "mlx.h"
#include "mlx_defines.h"
#include "player_operation.h"
#include "raycasting.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "debug.h"
#include <stdbool.h>

#define DEBUGGING

int	key_hook(int key_code, void *arg)
{
	const t_mlx_hook_arg	*mlx_hook_arg = arg;

	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
		rotate_player(key_code, &(mlx_hook_arg->cub3d->player));
	if (key_code == KEY_A || key_code == KEY_S || \
		key_code == KEY_D || key_code == KEY_W)
		move_player(key_code, &(mlx_hook_arg->cub3d->player), mlx_hook_arg->cub3d->map);
	if (key_code == KEY_ESC)
	{
		// TODO
		exit(0);
	}
	print_key_code(key_code);
	print_player(mlx_hook_arg->cub3d->player);
	return (0);
}

/******************  TEST FUNCTION ******************/
// #include "mlx_image_proc.h"
// #include "paste_texture.h"
// t_mlx_image *paste_texture_test(t_mlx *mlx, t_texture *texture) {
// 	t_mlx_image *image;
// 	image = new_image_struct(mlx, 200, 200);

// 	for(size_t i = 0; i < 200; i++) {
// 		// if (i < 100)
// 		// 	paste_texture(image, (double)(i) / 100.0f, (double)(i)
					// / (double)(200), texture, i);
// 		// else
// 		// 	paste_texture(image,  (1.0f - (double)(i) / 200.0f), (double)(i)
					// / (double)(200), texture, i);
// 			// paste_texture(image, 0.5f + ((double)(i) / 400.0f), (double)(i)
					// / (double)(200), texture, i);
// 	}
// 	usleep(100);
// 	return (image);
// }
/****************************************************/

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
	image[1] = new_minimap(mlx_hook_arg->cub3d, arg_mlx, 160, 120);
	image[0] = new_raycasting_image(mlx_hook_arg->cub3d, arg_mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	image[2] = NULL;
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

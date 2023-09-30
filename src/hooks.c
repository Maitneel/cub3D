#include <stdlib.h>

#include "mlx.h"
#include "cub3d_structs.h"
#include "mlx_defines.h"
#include "player_operation.h"
#include "minimap.h"
#include "free_lib.h"

#include <stdio.h>
#include <unistd.h>
#include "debug.h"

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

int	loop_hook(void *arg)
{
	const t_mlx_hook_arg *mlx_hook_arg = arg;
	t_mlx *mlx;
	size_t i;
	static int count;

	mlx = mlx_hook_arg->mlx;
	free_and_detroy_mlx_image(mlx->image[0], mlx);
	mlx->image[0] = new_minimap(mlx_hook_arg->cub3d, mlx, 160, 120);	
	i = 0;
	while (i < IMAGE_SIZE)
	{
		if (mlx->image[i] != NULL)
			mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image[i]->image_ptr, 10, 10);
		i++;
	}
	// fprintf(stderr, "count : '%d'\n", count);
	count++;
	usleep(1 * 1000);
	// system("leaks cub3D");
	return (0);
}

void	add_hooks(t_mlx_hook_arg *mlx_hook_arg)
{
	mlx_key_hook(mlx_hook_arg->mlx->window, key_hook, mlx_hook_arg);
	mlx_loop_hook(mlx_hook_arg->mlx->mlx, loop_hook, mlx_hook_arg);
}

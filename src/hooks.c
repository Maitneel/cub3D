#include <stdlib.h>

#include "mlx.h"
#include "cub3d_structs.h"
#include "mlx_defines.h"

#include <stdio.h>

int	key_hook(int key_code)
{
	if (key_code == ARROW_UP)
		printf("UP\n");
	if (key_code == ARROW_DOWN)
		printf("DOWN\n");
	if (key_code == ARROW_LEFT)
		printf("LEFT\n");
	if (key_code == ARROW_RIGHT)
		printf("RIGHT\n");

	if (key_code == KEY_A)
		printf("KEY_A\n");
	if (key_code == KEY_S)
		printf("KEY_S\n");
	if (key_code == KEY_D)
		printf("KEY_D\n");
	if (key_code == KEY_W)
		printf("KEY_W\n");

	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	return (0);
}

void	add_hooks(t_mlx_hook_arg *mlx_hook_arg)
{
	mlx_key_hook(mlx_hook_arg->mlx->window, key_hook, mlx_hook_arg);
}

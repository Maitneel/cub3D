#include "mlx.h"
#include "cub3d_structs.h"

#include <stdio.h>

int	key_hook(int key_code)
{
	fprintf(stderr, "key_code : '%d'\n", key_code);
	return (0);
}

void	add_hooks(t_mlx_hook_arg *mlx_hook_arg)
{
	mlx_key_hook(mlx_hook_arg->mlx->window, key_hook, mlx_hook_arg);
}

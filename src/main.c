#include "cub3d_structs.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "print_lib.h"
#include "free_lib.h"
#include "util_lib.h"
#include "mlx_related.h"
#include "mlx_image_proc.h"

#include "debug.h"
// /*
int	main(const int argc, const char **argv)
{
	t_mlx_hook_arg	*mlx_hook_arg;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, "few argument\n", 14);
		return (1);
	}
	mlx_hook_arg = ft_xcalloc(1, sizeof(t_mlx_hook_arg));
	mlx_hook_arg->mlx = init_mlx_struct("hogehoge");
	if (mlx_hook_arg->mlx == NULL)
		return (1);
	mlx_hook_arg->cub3d = init_cub3d(mlx_hook_arg->mlx->mlx, argv[1]);
	if (mlx_hook_arg->cub3d == NULL)
	{
		free_mlx_hook_arg(mlx_hook_arg);
		return (1);
	}
	add_hooks(mlx_hook_arg);
	mlx_loop(mlx_hook_arg->mlx->mlx);
	return (0);
}
// */

// __attribute__((destructor))
// void destructor() {
// 	system("leaks cub3D");
// }

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
	mlx_hook_arg->cub3d = init_cub3d(argv[1]);
	// mlx_hook_arg->mlx = init_mlx_struct("hogehoge");
	// if (mlx_hook_arg->cub3d == NULL || mlx_hook_arg->mlx == NULL)
	// {
	// 	free_mlx_hook_arg(mlx_hook_arg);
	// 	return (1);
	// }

	print_map(mlx_hook_arg->cub3d->map);
	printf("y: %lf, x: %lf\n", mlx_hook_arg->cub3d->player.point.y, mlx_hook_arg->cub3d->player.point.x);

	// add_hooks(mlx_hook_arg);
	// mlx_hook_arg->mlx->image[0] = new_image_struct(mlx_hook_arg->mlx, 100, 100);
	// t_mlx_image *image = mlx_hook_arg->mlx->image[0];
	// for (size_t i = 0; i < image->width; i++)
	// {
	// 	for (size_t j = 0; j < image->height; j++)
	// 	{
	// 		if (i % 10 == 0 || j % 10 == 0) {
	// 			put_pixel_to_mlx_image(image, i, j, 0xffffff);
	// 		}
	// 	}
	// }
	// mlx_put_image_to_window(mlx_hook_arg->mlx->mlx, mlx_hook_arg->mlx->window, image->image_ptr, 10, 10);
	// //
	// mlx_loop(mlx_hook_arg->mlx->mlx);
	return (0);
}

// __attribute__((destructor))
// void destructor() {
// 	system("leaks cub3D");
// }

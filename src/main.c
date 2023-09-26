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

#include "debug.h"

int	main(const int argc, const char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_cub3d	*cub3d;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, "few argument\n", 14);
		return (1);
	}
	cub3d = init_cub3d(argv[1]);
	if (cub3d == NULL)
		return 1;
	print_cub3d(cub3d);
	free_cub3d(cub3d);
	return (0);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 200, 200, "Hello world!");
	mlx_loop(mlx);
}

// __attribute__((destructor))
// void destructor() {
// 	system("leaks cub3D");
// }
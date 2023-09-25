#include "cub3d_structs.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "print_lib.h"

int	main(const int argc, const char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, "few argument\n", 14);
		return (1);
	}
	init_cub3d(argv[1]);
	return (0);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 200, 200, "Hello world!");
	mlx_loop(mlx);
}

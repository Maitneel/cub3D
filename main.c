#include "cub3d_structs.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "print_lib.h"

bool	is_valid_filename(char *filename)
{
	size_t			filename_length;
	const char		*extension = ".cub";
	const size_t	extension_length = ft_strlen(extension);
	size_t			i;

	if (filename == NULL)
	{
		return (false);
	}
	filename_length = ft_strlen(filename);
	if (filename_length < extension_length + 1)
	{
		return (false);
	}
	i = 0;
	while (i < extension_length)
	{
		if (filename[filename_length - extension_length + i] != extension[i])
		{
			return (false);
		}
		i++;
	}
	return (true);
}

t_cub3d	*init_cub3d(char *filename)
{
	int	fd;
	t_cub3d *cub3d;

	if (!is_valid_filename(filename))
	{
		write(STDERR_FILENO, "Error\n", 6);
		write(STDERR_FILENO, "file is not .cub file\n", 23);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		perror(NULL);
		return (NULL);
	}
	cub3d = malloc(sizeof(t_cub3d));
	if (cub3d == NULL) {
		write(STDERR_FILENO, "Error\n", 6);
		perror(NULL);
		return NULL;
	}
	// cub3d->texture = get_texture(fd); TODO
	// cub3d->map = get_map(fd); TODO
	close(fd);
	if (cub3d->texture == NULL || cub3d->map == NULL) {
		// free_cub3d(cub3d); TODO
		return NULL;
	}
	return (cub3d);
}

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

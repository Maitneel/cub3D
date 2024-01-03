#include <stdlib.h>
#include <stdbool.h>
#include <sys/fcntl.h>

#include "libft.h"
#include "util_lib.h"
#include "free_lib.h"
#include "cub3d_structs.h"
#include "print_lib.h"
#include "get_cub3d_info.h"

#include <stdio.h>
#include "debug.h"

static bool	is_valid_filename(const char *filename)
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

static int get_map_width(t_map_element **map)
{
	int i;
	if (map == NULL)
		return -1;
	if (map[0] == NULL)
		return 0;
	i = 0;
	while (map[0][i] != END_OF_LINE)
		i++;
	return i;
}

static int get_map_height(t_map_element **map)
{
	int i;
	if (map == NULL)
		return (-1);
	i = 0;
	while (map[i] != NULL)
		i++;
	return i;
}

static t_cub3d	*get_cub3d_data(const void *mlx_ptr, const int fd)
{
	t_cub3d	*cub3d;

	cub3d = ft_xcalloc(1, sizeof(t_cub3d));
	cub3d->graphic_info = get_graphic_info(mlx_ptr, fd);
	cub3d->map = get_map(fd);
	if (cub3d->graphic_info == NULL || cub3d->map == NULL)
	{
		print_error(false, "inccorect map\n");
		free_cub3d(cub3d);
		return (NULL);
	}
	cub3d->map_width = get_map_width(cub3d->map);
	cub3d->map_height = get_map_height(cub3d->map);
	set_player_start_position(&(cub3d->player), cub3d->map);
	return (cub3d);
}

t_cub3d	*init_cub3d(const void *mlx_ptr, const char *filename)
{
	int		fd;
	t_cub3d	*cub3d;

	if (!is_valid_filename(filename))
	{
		print_error(false, "file is not .cub file\n");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error(true, filename);
		return (NULL);
	}
	cub3d = get_cub3d_data(mlx_ptr, fd);
	close(fd);
	return (cub3d);
}

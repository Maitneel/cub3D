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

static t_cub3d	*get_cub3d_data(const int fd)
{
	t_cub3d	*cub3d;

	cub3d = ft_xcalloc(1, sizeof(t_cub3d));
	cub3d->graphic_info = get_graphic_info(fd);
	cub3d->map = get_map(fd);
	if (cub3d->graphic_info == NULL || cub3d->map == NULL)
	{
		print_error(false, "inccorect map\n");
		free_cub3d(cub3d);
		return (NULL);
	}
	set_player_start_position(&(cub3d->player), cub3d->map);
	return (cub3d);
}

t_cub3d	*init_cub3d(const char *filename)
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
	cub3d = get_cub3d_data(fd);
	close(fd);
	return (cub3d);
}

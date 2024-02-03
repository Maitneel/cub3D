#include "cub3d_structs.h"
#include "free_lib.h"
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

bool	is_graphic_info_element_filled(const t_graphic_info *graphic_info)
{
	return (
		graphic_info->north_texture != NULL && \
		graphic_info->south_texture != NULL && \
		graphic_info->west_texture != NULL && \
		graphic_info->east_texture != NULL && \
		graphic_info->floor_color != NULL && \
		graphic_info->ceiling_color != NULL);
}

bool	is_texture_line(const char *line)
{
	const char		*texture_identifier[4] = {"NO ", "SO ", "WE ", "EA "};
	const size_t	texture_identifier_size = 4;
	size_t			i;

	i = 0;
	while (i < texture_identifier_size)
	{
		if (ft_strncmp(line, texture_identifier[i], 3) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_color_line(const char *line)
{
	const char		*texture_identifier[2] = {"F ", "C "};
	const size_t	texture_identifier_size = 2;
	size_t			i;

	i = 0;
	while (i < texture_identifier_size)
	{
		if (ft_strncmp(line, texture_identifier[i], 2) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_correct_texture_format(const char *line)
{
	size_t	i;

	i = 3;
	while (ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (false);
	while (ft_isascii(line[i]) && !ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (false);
	while (ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] != '\0')
		return (false);
	return (true);
}

bool	is_within_0_to_255(const char *front)
{
	size_t	i;
	int		converted;

	converted = 0;
	i = 0;
	while (ft_isdigit(front[i]) && converted < 256)
	{
		converted *= 10;
		converted += front[i] - '0';
		i++;
	}
	if (converted < 256)
		return (true);
	return (false);
}

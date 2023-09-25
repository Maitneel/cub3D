#include "cub3d_structs.h"
#include "get_next_line.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static bool	is_graphic_info_element_filled(const t_graphic_info *graphic_info)
{
	return (
		graphic_info->north_texture != NULL && \
		graphic_info->south_texture != NULL && \
		graphic_info->west_texture != NULL && \
		graphic_info->east_texture != NULL);
}

static bool	is_texture_line(char *line)
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

static bool	is_color_line(char *line)
{
	const char		*texture_identifier[2] = {"F ", "c "};
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

bool	is_correct_texture_format(char *line)
{
	size_t	i;

	if (!ft_isspace(line[3]))
		return (false);
	i = 4;
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

bool	is_within_0_to_255(char *front)
{
	size_t	i;
	size_t	front_index;
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

bool	is_correct_color_format(const char *line)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 2;
	while (j < 3)
	{
		while (ft_isspace(line[i]) && line[i] != '\0')
			i++;
		if (!ft_isdigit(line[i]) || !is_within_0_to_255(&line[i]))
			return (false);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == '\0')
			return (false);
		while (ft_isspace(line[i]) && line[i] != '\0')
			i++;
		if (line[i] != ',' && j != 2)
			return (false);
		i++;
		j++;
	}
	if (line[i - 1] != '\0')
		return (false);
	return (true);
}

static bool	is_correct_format(char *line)
{
	size_t	i;

	if (line == NULL)
		return (false);
	if (line[0] == '\0')
		return (true);
	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (is_texture_line(&line[i]))
		return (is_correct_texture_format(&line[i]));
	if (is_color_line(&line[i]))
		return (is_correct_color_format(&line[i]));
	else
		return (false);
}

static void	set_to_appropriate_element(t_graphic_info *graphic_info, char *line)
{
	// TODO
}

void	free_graphic_info(t_graphic_info *graphic_info)
{
	// TODO
}

t_graphic_info	*get_graphic_info(const int fd)
{
	t_graphic_info	*graphic_info;
	char			*line;

	graphic_info = ft_xcalloc(1, sizeof(t_graphic_info));
	while (is_graphic_info_element_filled(graphic_info))
	{
		line = get_next_line(fd);
		if (line == NULL || !is_correct_format(line))
		{
			if (errno != 0)
				print_error(true, "read");
			else
				print_error(false, "inccorect map\n");
			free_graphic_info(graphic_info);
			return (NULL);
		}
		set_to_appropriate_element(graphic_info, line);
		free(line);
	}
	return (graphic_info);
}

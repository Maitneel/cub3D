#include "cub3d_structs.h"
#include "get_next_line.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include "free_lib.h"
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
		graphic_info->east_texture != NULL && \
		graphic_info->floor_color != NULL && \
		graphic_info->ceiling_color != NULL
	);
}

static bool	is_texture_line(const char *line)
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

static bool	is_color_line(const char *line)
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

static bool	is_correct_format(const char *line)
{
	size_t	i;

	if (line == NULL)
		return (false);
	if (line[0] == '\n')
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

static bool	is_texture_empty(const t_graphic_info *graphic_info, const char identifier)
{
	t_texture	*target;

	if (identifier == 'N')
		target = graphic_info->north_texture;
	else if (identifier == 'S')
		target = graphic_info->south_texture;
	else if (identifier == 'W')
		target = graphic_info->west_texture;
	else if (identifier == 'E')
		target = graphic_info->east_texture;
	else
		return (false);
	if (target == NULL)
		return (true);
	else
		return (false);
}

static bool	is_color_empty(const t_graphic_info *graphic_info, const char identifier)
{
	t_color	*target;

	if (identifier == 'F')
		target = graphic_info->floor_color;
	else if (identifier == 'C')
		target = graphic_info->ceiling_color;
	else
		return (false);
	if (target == NULL)
		return (true);
	else
		return (false);
}

// なんかいい感じの関数名が思いつかない //
static bool	is_element_empyt(
	const t_graphic_info *graphic_info,
	const char *line
)
{
	if (line[0] == '\n')
		return (true);
	else if (is_texture_line(line))
		return (is_texture_empty(graphic_info, line[0]));
	else if (is_color_line(line))
		return (is_color_empty(graphic_info, line[0]));
	else
		return (false);
}

char	*get_texture_file_name(const char *line)
{
	char	*file_name;
	size_t	file_name_start_index;
	size_t	i;

	file_name_start_index = 2;
	while (ft_isspace(line[file_name_start_index]))
		file_name_start_index++;
	file_name = ft_strdup(&line[file_name_start_index]);
	if (file_name == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	i = 0;
	while (!ft_isspace(file_name[i]) && file_name[i] != '\0')
		i++;
	file_name[i] = '\0';
	return (file_name);
}

t_texture	*new_texture(const char *file_name)
{
	t_texture	*texture;

	texture = ft_xcalloc(1, sizeof(t_texture));
	texture->file_name = ft_strdup(file_name);
	if (texture->file_name == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	return (texture);
}

static void	set_texture(t_graphic_info *graphic_info, const char *line)
{
	char		*file_name;
	const char	identifier = line[0];

	file_name = get_texture_file_name(line);
	if (identifier == 'N')
		graphic_info->north_texture = new_texture(file_name);
	else if (identifier == 'S')
		graphic_info->south_texture = new_texture(file_name);
	else if (identifier == 'W')
		graphic_info->west_texture = new_texture(file_name);
	else if (identifier == 'E')
		graphic_info->east_texture = new_texture(file_name);
	free(file_name);
}

static t_color	*new_color(const char *line)
{
	size_t	i;
	size_t	line_index;
	t_color	*color;

	color = ft_xcalloc(1, sizeof(t_color));
	i = 0;
	line_index = 0;
	while (i < 3)
	{
		while (!ft_isdigit(line[line_index]))
			line_index++;
		if (i == 0)
			color->red = ft_atoi(&line[line_index]);
		else if (i == 1)
			color->green = ft_atoi(&line[line_index]);
		else if (i == 2)
			color->blue = ft_atoi(&line[line_index]);
		while (ft_isdigit(line[line_index]))
			line_index++;
		i++;
	}
	return (color);
}

static void	set_color(t_graphic_info *graphic_info, const char *line)
{
	const char	identifier = line[0];

	if (identifier == 'F')
		graphic_info->floor_color = new_color(line);
	else if (identifier == 'C')
		graphic_info->ceiling_color = new_color(line);
}

static void	set_to_appropriate_element(t_graphic_info *graphic_info,
	const char *line
)
{
	if (is_texture_line(line))
	{
		set_texture(graphic_info, line);
	}
	else if (is_color_line(line))
	{
		set_color(graphic_info, line);
	}
}

t_graphic_info	*get_graphic_info(const int fd)
{
	t_graphic_info	*graphic_info;
	char			*line;

	graphic_info = ft_xcalloc(1, sizeof(t_graphic_info));
	while (!is_graphic_info_element_filled(graphic_info))
	{
		line = get_next_line(fd);
		if (line == NULL || !is_correct_format(line) || \
				!is_element_empyt(graphic_info, line))
		{
			print_error(false, "inccorect map\n");
			free_graphic_info(graphic_info);
			return (NULL);
		}
		set_to_appropriate_element(graphic_info, line);
		free(line);
	}
	return (graphic_info);
}

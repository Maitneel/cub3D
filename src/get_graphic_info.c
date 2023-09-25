#include <sys/errno.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cub3d_structs.h"
#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"

static bool	is_graphic_info_element_filled(const t_graphic_info *graphic_info)
{
	return (
		graphic_info->north_texture != NULL && \
		graphic_info->south_texture != NULL && \
		graphic_info->west_texture != NULL && \
		graphic_info->east_texture != NULL);
}

static bool is_texture_line(char *line)
{
	// TODO;
	return false;
}

static bool is_color_line(char *line)
{
	// TODO;
	return false;
}

static bool is_correct_texture_format(char *line)
{
	// TODO
	return true;
}

static bool is_correct_color_format(char *line)
{
	// TODO
	return true;
}

static bool is_correct_format(char *line)
{
	size_t i;

	if (line == NULL)
		return false;
	if (line[0] == '\0')
		return true;
	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (is_texture_line(&line[i]))
		return is_correct_texture_format(&line[i]);
	if (is_color_line(&line[i]))
		return is_correct_color_format(&line[i]);
	else 
		return false;
}

static void set_to_appropriate_element(t_graphic_info *graphic_info, char *line)
{
	// TODO
}

void free_graphic_info(t_graphic_info *graphic_info)
{
	// TODO
}

t_graphic_info	*get_graphic_info(const int fd)
{
	t_graphic_info *graphic_info;
	char *line;

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

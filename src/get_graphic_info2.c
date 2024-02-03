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

bool	is_correct_format(const char *line)
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

bool	is_texture_empty(
	const t_graphic_info *graphic_info, const char identifier)
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

bool	is_color_empty(
	const t_graphic_info *graphic_info, const char identifier)
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

bool	is_element_empyt(
	const t_graphic_info *graphic_info,
	const char *line)
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

#include <stdlib.h>

#include "libft.h"
#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"
#include "free_lib.h"
#include "cub3d_structs.h"

#include <stdio.h>
#include "debug.h"

char **read_map(const int fd)
{
	char **map;
	char *line;
	size_t alloc_size;
	size_t map_index;

	alloc_size = 2;
	map = ft_xcalloc(alloc_size, sizeof(char *));
	map_index = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map_index == alloc_size - 1)
		{
			map = expand_str_array_memory(&map, alloc_size * 2);
			alloc_size *= 2;
		}
		map[map_index] = line;
		map_index++;
		line = get_next_line(fd);
	}
	return (map);
}

bool is_correct_map(const char **map)
{
	// TODO
	return true;
}

static size_t get_max_length(const char **map)
{
	size_t max_length;
	size_t length;
	size_t i;

	max_length = 0;
	i = 0;
	while (map[i] != NULL)
	{
		length = ft_strlen(map[i]);
		if (max_length < length)
			max_length = length;
		i++;
	}
	return (max_length);
}

static t_map_element get_element_type(const char c)
{
	if (c == ' ')
		return (OUT_OF_MAP);
	else if (c == '0')
		return (EMPTY);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (START_N);
	else if (c == 'S')
		return (START_S);
	else if (c == 'E')
		return (START_E);
	else if (c == 'W')
		return (START_W);
	return (OUT_OF_MAP);
}

t_map_element *convert_line_to_map_element(const char *line, const size_t width)
{
	t_map_element *converted_line;
	size_t i;

	converted_line = ft_xcalloc(width + 3, sizeof(t_map_element));
	i = 0;
	while (line[i] != '\0')
	{
		converted_line[i + 1] = get_element_type(line[i]);
		i++;
	}
	while (i < width + 2)
	{
		converted_line[i] = OUT_OF_MAP;
		i++;
	}
	converted_line[width + 2] = END_OF_LINE;
	return (converted_line);
}

t_map_element **convert_to_map_element(const char **char_map)
{
	const size_t height = string_array_size(char_map);
	const size_t width = get_max_length(char_map);
	size_t i;
	t_map_element **converted_map;

	converted_map = ft_xcalloc((height + 3), sizeof(t_map_element *));
	converted_map[0] = convert_line_to_map_element("", width);
	i = 0;
	while (i < height)
	{
		converted_map[i + 1] = convert_line_to_map_element(char_map[i], width);
		i++;
	}
	converted_map[height + 1] = convert_line_to_map_element("", width);
	return (converted_map);
}

t_map_element **get_map(const int fd_of_move_to_end_of_graphic_info)
{
	char **char_map;
	t_map_element	**converted_map;

	char_map = read_map(fd_of_move_to_end_of_graphic_info);
	if (!is_correct_map((const char **)(char_map)))
	{
		print_error(false, "inccorect map");
		free_string_array(char_map);
		return (NULL);
	}
	converted_map = convert_to_map_element((const char **)(char_map));
	free_string_array(char_map);
	print_map(converted_map);
	return (converted_map);
}
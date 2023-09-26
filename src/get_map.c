#include <stdlib.h>

#include "libft.h"
#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"
#include "free_lib.h"

#include <stdio.h>

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

bool is_correct_map(char **map)
{
	// TODO
	return true;
}

static size_t get_max_length(char **map)
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

int *convert_line_to_int(char *line, size_t width)
{
	// TODO;
	return NULL;
}



int **convert_to_int_map(char **char_map)
{
	const size_t height = string_array_size(char_map);
	const size_t width = get_max_length(char_map);
	size_t i;
	int **int_map;

	int_map = ft_xcalloc((height + 1), sizeof(int *));
	i = 0;
	while (i < height)
	{
		int_map[i] = convert_line_to_int(char_map[i], width);
		i++;
	}
	return (int_map);
}

int **get_map(const int fd_of_move_to_end_of_graphic_info)
{
	const char **char_map = read_map(fd_of_move_to_end_of_graphic_info);
	int	**int_map;

	if (!is_correct_map(char_map))
	{
		print_error(false, "inccorect map");
		free_string_array(char_map);
		return (NULL);
	}
	int_map = convert_to_int_map(char_map);
	free_string_array(char_map);
	return (int_map);
}
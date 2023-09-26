#include <stdlib.h>

#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"

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

int **convert_to_int_map(char **char_map)
{
	// TODO;
	return NULL;
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
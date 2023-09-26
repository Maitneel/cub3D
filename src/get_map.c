#include <stdlib.h>

#include "get_next_line.h"
#include "util_lib.h"


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

int **get_map(const int fd_of_move_to_end_of_graphic_info)
{
	char **char_map = read_map(fd_of_move_to_end_of_graphic_info);


	size_t i;
	i = 0;
	while (char_map[i] != NULL)
	{
		fprintf(stderr, "char_map[i] : '%s", char_map[i]);
		i++;
	}
	

	return NULL;
}
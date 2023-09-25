#include <sys/errno.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cub3d_structs.h"
#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"

bool	is_graphic_info_element_filled(const t_graphic_info *graphic_info)
{
	return (
		graphic_info->north_texture != NULL && \
		graphic_info->south_texture != NULL && \
		graphic_info->west_texture != NULL && \
		graphic_info->east_texture != NULL);
}

void set_to_appropriate_element(t_graphic_info *graphic_info, char *line)
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
		if (line == NULL)
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

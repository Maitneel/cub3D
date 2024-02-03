#include "cub3d_structs.h"
#include "free_lib.h"
#include "get_next_line.h"
#include "get_xpm_data.h"
#include "libft.h"
#include "mlx.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

t_graphic_info	*get_graphic_info(const void *mlx_ptr, const int fd)
{
	t_graphic_info	*graphic_info;
	char			*line;

	graphic_info = ft_xcalloc(1, sizeof(t_graphic_info));
	while (!is_graphic_info_element_filled(graphic_info))
	{
		line = get_next_line(fd);
		if (
			line == NULL || !is_correct_format(line) || \
			!is_element_empyt(graphic_info, line))
		{
			free_graphic_info(graphic_info);
			return (NULL);
		}
		set_to_appropriate_element(mlx_ptr, graphic_info, line);
		free(line);
	}
	return (graphic_info);
}

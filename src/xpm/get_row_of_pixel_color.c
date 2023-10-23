#include "cub3d_structs.h"

#include <stdio.h>

t_color	*get_row_of_pixel_color(const char *line,
								const t_color_index_pair *color_map,
								const size_t height, const size_t width)
{
	size_t i;

	i = 0;
	while (i < height) {
		fprintf(stderr, "'%s' 0x%02X%02X%02X\n", color_map[i].key, color_map[i].color.red, color_map[i].color.green, color_map[i].color.blue);
		i++;
	}
}

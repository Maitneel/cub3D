#include "cub3d_structs.h"
#include "print_lib.h"
#include "util_lib.h"
#include "get_xpm_data.h"
#include <stdlib.h>

t_color_index_pair	*get_color_map(const char **file_content)
{
}

t_color	*get_row_of_pixel_color(const char *line,
		const t_color_index_pair *color_map, const size_t width)
{
}

t_color	**get_xpm_pixel_color(const char **file_content, const size_t height,
		const size_t width)
{
	t_color				**pixel_color;
	t_color_index_pair	*color_map;
	size_t				i;
	size_t				front_of_pixel_info;

	front_of_pixel_info = get_xpm_number_of_color(file_content) + 1;
	pixel_color = ft_xcalloc(height + 1, sizeof(t_color *));
	color_map = get_color_map(file_content);
	i = 0;
	while (i < height && file_content[front_of_pixel_info + i] != NULL)
	{
		pixel_color[i] = get_row_of_pixel_color(file_content[front_of_pixel_info
				+ i], color_map, width);
		i++;
	}
	if (i != height || file_content[front_of_pixel_info + i] != NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(1); // eixt していい? //
	}
	free(color_map);
	return (pixel_color);
}

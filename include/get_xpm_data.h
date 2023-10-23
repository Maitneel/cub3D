#ifndef GET_XPM_DATA_H
# define GET_XPM_DATA_H

# include <stddef.h>

# include "cub3d_structs.h"

char	**get_xpm_file_content(const char *filename);
size_t	get_xpm_height(const char **file_content);
size_t	get_xpm_width(const char **file_content);
size_t	get_xpm_number_of_color(const char **file_content);
size_t	get_xpm_char_per_pixel(const char **file_content);
t_color_index_pair	get_color_index_pair(const char *line,
		const size_t char_per_pixel);
t_color	**get_xpm_pixel_color(const char **file_content, const size_t height,
			const size_t width);

#endif
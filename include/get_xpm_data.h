#ifndef GET_XPM_DATA_H
# define GET_XPM_DATA_H

# include <stddef.h>

# include "cub3d_structs.h"

char	**get_xpm_file_content(const char *filename);
size_t	get_xpm_height(const char **file_content);
size_t	get_xpm_width(const char **file_content);
t_color	**get_xpm_pixel_color(const char **file_content, const size_t height,
			const size_t width);

#endif
#ifndef FREE_LIB_H
# define FREE_LIB_H

# include "cub3d_structs.h"

void	free_string_array(char **array);
void	free_texture(t_texture *texture);
void	free_color(t_color *color);
void	free_graphic_info(t_graphic_info *graphic_info);
void	free_map(t_map_element **map);

void	free_cub3d(t_cub3d *cub3d);
#endif

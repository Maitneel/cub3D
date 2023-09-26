#ifndef GET_CUB3D_INFO_H
# define GET_CUB3D_INFO_H

# include "cub3d_structs.h"

t_graphic_info	*get_graphic_info(const int fd);
t_map_element	**get_map(const int fd_of_move_to_end_of_graphic_info);

#endif

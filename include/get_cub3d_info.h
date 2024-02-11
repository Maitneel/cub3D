/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub3d_info.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:29 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:30 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CUB3D_INFO_H
# define GET_CUB3D_INFO_H

# include "cub3d_structs.h"

t_graphic_info	*get_graphic_info(const void *mlx_ptr, const int fd);
t_map_element	**get_map(const int fd_of_move_to_end_of_graphic_info);
void			set_player_start_position( \
					t_player *player, t_map_element **map);

#endif

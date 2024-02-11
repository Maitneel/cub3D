/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:26 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:27 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_LIB_H
# define FREE_LIB_H

# include "cub3d_structs.h"

void	free_string_array(char **array);
void	free_texture(t_texture *texture);
void	free_color(t_color *color);
void	free_graphic_info(t_graphic_info *graphic_info);
void	free_map(t_map_element **map);

void	free_cub3d(t_cub3d *cub3d);
void	free_mlx_struct(t_mlx *mlx);
void	free_mlx_hook_arg(t_mlx_hook_arg *mlx_hook_arg);
void	free_and_detroy_mlx_image(t_mlx_image *image, const t_mlx *mlx);
void	free_uint_array_array(unsigned int **array, const size_t height);
#endif

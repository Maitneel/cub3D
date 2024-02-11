/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:35 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:36 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

t_mlx_image	*new_minimap(const t_cub3d *cub3d, const t_mlx *mlx,
				const int width, const int height);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:37:54 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 22:37:55 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_texture	*get_texture(t_cub3d *cub3d, t_coll_point *coll_pt)
{
	t_map_element	**map;

	map = cub3d->map;
	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
		return (cub3d->graphic_info->north_texture);
	if (!is_wall(cub3d, coll_pt->pt.y, coll_pt->pt.x))
		return (cub3d->graphic_info->west_texture);
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
		return (cub3d->graphic_info->east_texture);
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
		return (cub3d->graphic_info->west_texture);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
		return (cub3d->graphic_info->south_texture);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
		return (cub3d->graphic_info->north_texture);
	return (cub3d->graphic_info->east_texture);
}

double	get_texture_position(t_cub3d *cub3d, t_coll_point *coll_pt)
{
	t_map_element	**map;

	map = cub3d->map;
	if (!(0 < coll_pt->pt.y && coll_pt->pt.y < cub3d->map_height
			* PLAYER_MAGFICATION) || !(0 <= coll_pt->pt.x
			&& coll_pt->pt.x < cub3d->map_width * PLAYER_MAGFICATION))
		return (0.0);
	if (coll_pt->pt.x % PLAYER_MAGFICATION == 0 && coll_pt->is_vert)
		return ((double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& coll_pt->is_vert)
		return (1.0 - (double)(coll_pt->pt.y % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == 0 && !coll_pt->is_vert)
		return (1.0 - (double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	else if (coll_pt->pt.y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1
		&& !coll_pt->is_vert)
		return ((double)(coll_pt->pt.x % PLAYER_MAGFICATION)
			/ (double)PLAYER_MAGFICATION);
	return (0.0);
}

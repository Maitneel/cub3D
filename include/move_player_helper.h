/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_helper.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:50 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:51 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_PLAYER_HELPER_H
# define MOVE_PLAYER_HELPER_H

# include "cub3d_structs.h"

bool	can_enter(const t_map_element **map, const int maged_y,
			const int maged_x);
t_point	assign_point(const int x, const int y);

#endif

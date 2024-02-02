/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_point_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:40:59 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/03 04:08:08 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	set_ver_step_if_east(t_player player, int *step, int *side_x)
{
	*side_x = PLAYER_MAGFICATION - (player.point.x % PLAYER_MAGFICATION);
	*step = PLAYER_MAGFICATION;
}

void	set_ver_step_if_west(t_player player, int *step, int *side_x)
{
	*side_x = -1 * player.point.x % PLAYER_MAGFICATION - 1;
	*step = -PLAYER_MAGFICATION;
}

void	set_hz_step_if_north(t_player player, int *step, int *side_y)
{
	*side_y = -1 * player.point.y % PLAYER_MAGFICATION - 1;
	*step = -PLAYER_MAGFICATION;
}

void	set_hz_step_if_south(t_player player, int *step, int *side_y)
{
	*side_y = PLAYER_MAGFICATION - (player.point.y % PLAYER_MAGFICATION);
	*step = PLAYER_MAGFICATION;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:45 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:46 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "mlx_defines.h"
#include "move_player_helper.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static const long long	g_moving_coefficient = 0.5f * \
							(float)(PLAYER_MAGFICATION);

double	get_moving_dir(const int key_code, const double player_direction)
{
	if (key_code == KEY_W)
		return (player_direction);
	else if (key_code == KEY_S)
		return (player_direction - M_PI);
	else if (key_code == KEY_A)
		return (player_direction - M_PI_2);
	else if (key_code == KEY_D)
		return (player_direction + M_PI_2);
	else
		return (INFINITY);
}

void	add_diff(const t_map_element **map, const t_point before,
	t_point now, t_point *diff)
{
	if (!can_enter(map, now.y, now.x + diff->x))
		diff->y += before.y - now.y;
	if (!can_enter(map, now.y + diff->y, now.x))
		diff->x += before.x - now.x;
}

void	move_player_bonus(int key_code, t_player *player,
		const t_map_element **map)
{
	const double	moving_dir = get_moving_dir(key_code, player->direction);
	t_point			now;
	t_point			before;
	t_point			diff;
	int				i;

	now = player->point;
	diff = assign_point(0, 0);
	i = -1;
	while (++i <= g_moving_coefficient)
	{
		before = now;
		now.x = player->point.x - (long long)(sin(moving_dir) * (double)(i));
		now.y = player->point.y + (long long)(cos(moving_dir) * (double)(i));
		if (!can_enter(map, now.y + diff.y, before.x + diff.x) && \
			!can_enter(map, before.y + diff.y, now.x + diff.x))
		{
			now = before;
			break ;
		}
		add_diff(map, before, now, &diff);
	}
	player->point = assign_point(now.x + diff.x, now.y + diff.y);
}

void	move_player_mandantory(int key_code, t_player *player)
{
	const double	moving_direction = \
						get_moving_dir(key_code, player->direction);

	player->point.x -= (long long)((sin(moving_direction)
				* g_moving_coefficient));
	player->point.y += (long long)((cos(moving_direction)
				* g_moving_coefficient));
}

void	move_player(int key_code, t_player *player, const t_map_element **map)
{
	if (BONUS)
		move_player_bonus(key_code, player, map);
	else
		move_player_mandantory(key_code, player);
}

/*
int	main(void) {
	t_point from = {-1, -1};
	t_point to = {0, 0};
	bool before = true;
	bool now;
	for (long long  i = 0; i < PLAYER_MAGFICATION; i++)
	{
		from.x = i;
		for (long long  j = -1 * PLAYER_MAGFICATION * 3; j < PLAYER_MAGFICATION
				* 3; j++)
		{
			to.x = j;
			for (long long k = 0; k < PLAYER_MAGFICATION * 2; k++)
			{
				to.y = k;
				now = dose_we_colides_first(from, to, 0.0);
				if (now != before ) {
					before = now;
					fprintf(stdout, "now : %d, from : '%lld, %lld' ", now,
							from.x, from.y);
					fprintf(stdout, "to : '%lld, %lld'\n", to.x, to.y);
				}
			}
			
		}
	}
}
// */
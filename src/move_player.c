#include "cub3d_structs.h"
#include "mlx_defines.h"
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

#define MAKE_BONUS

#ifdef MAKE_BONUS
# define BONUS true
#else
# define BONUS false
#endif

t_map_element	get_maged_ele(t_map_element **map, int y, int x)
{
	return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION]);
}

void	move_player_bonus(int key_code, t_player *player, t_map_element **map)
{
	const double	moving_dir = get_moving_dir(key_code, player->direction);
	t_point			from;
	t_point			before;
	int				i;

	from = player->point;
	i = -1;
	while (++i <= g_moving_coefficient)
	{
		before = player->point;
		player->point.x = from.x - (long long)(sin(moving_dir) * (double)(i));
		player->point.y = from.y + (long long)(cos(moving_dir) * (double)(i));
		if (get_maged_ele(map, before.y, player->point.x) == WALL || \
				get_maged_ele(map, player->point.y, before.x) == WALL)
			player->point = before;
		else if (get_maged_ele(map, player->point.y, player->point.x) == WALL)
		{
			if (get_maged_ele(map, before.y, player->point.x) == WALL)
				player->point.x = before.x;
			if (get_maged_ele(map, player->point.y, before.x) == WALL)
				player->point.y = before.y;
		}
		from.x = player->point.x + (long long)(sin(moving_dir) * (double)(i));
		from.y = player->point.y - (long long)(cos(moving_dir) * (double)(i));
	}
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

void	move_player(int key_code, t_player *player, t_map_element **map)
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
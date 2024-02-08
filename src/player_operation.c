#include <math.h>
#include <stdbool.h>

#include "cub3d_structs.h"
#include "mlx_defines.h"
#include <math.h>
#include <stdio.h>

static const long long 	g_moving_coefficient = 0.5f * (float)(PLAYER_MAGFICATION);
static const double		g_rotate_angle = (M_PI_2 / 9.0f);

void	rotate_player(int key_code, t_player *player)
{
	if (key_code == ARROW_LEFT)
	{
		player->direction -= g_rotate_angle;
		if (player->direction < 0.0f)
			player->direction += 2 * M_PI;
	}
	else if (key_code == ARROW_RIGHT)
	{
		player->direction += g_rotate_angle;
		if (2.0f * M_PI <= player->direction)
			player->direction -= 2.0f * M_PI;
	}
}

double	get_moving_direction(const int key_code, const double player_direction)
{;
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

void	move_player(int key_code, t_player *player, t_map_element **map)
{
	const double	moving_direction = get_moving_direction(key_code, player->direction);
	t_point from;
	t_point before_point;
	int i;
	from = player->point;
#ifdef BONUS
	i = 1;
	fprintf(stderr, "g_moving_coefficient : '%d'\n", g_moving_coefficient);
	while (i < g_moving_coefficient)
	{
		before_point = player->point;
		player->point.x = from.x + (long long)(sin(moving_direction) * (double)(i));
		player->point.y = from.y - (long long)(cos(moving_direction) * (double)(i));
		if (map[before_point.y / PLAYER_MAGFICATION][player->point.x / PLAYER_MAGFICATION] == WALL && map[player->point.y / PLAYER_MAGFICATION][before_point.x / PLAYER_MAGFICATION] == WALL)
			player->point = before_point;
		else if (map[player->point.y / PLAYER_MAGFICATION][player->point.x / PLAYER_MAGFICATION] == WALL) {
			if (map[before_point.y / PLAYER_MAGFICATION][player->point.x / PLAYER_MAGFICATION] == WALL)
				player->point.x = before_point.x;
			if (map[player->point.y / PLAYER_MAGFICATION][before_point.x / PLAYER_MAGFICATION] == WALL)
				player->point.y = before_point.y;
		}
		from.x = player->point.x - (long long)(sin(moving_direction) * (double)(i));
		from.y = player->point.y + (long long)(cos(moving_direction) * (double)(i));
		i++;
	}
	
	fprintf(stderr, "======================================================================\n");
	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "moving_direction : '%f'\n", moving_direction);
	fprintf(stderr, "cos(moving_direction) : '%+f'\n", cos(moving_direction));
	fprintf(stderr, "sin(moving_direction) : '%+f'\n", sin(moving_direction));
#else
	player->point.x -= (long long)((sin(moving_direction)
				* g_moving_coefficient));
	player->point.y += (long long)((cos(moving_direction)
				* g_moving_coefficient));
#endif
}

/*
int main() {
	t_point from = {-1, -1};
	t_point to = {0, 0};
	bool before = true;
	bool now;
	for (long long  i = 0; i < PLAYER_MAGFICATION; i++)
	{
		from.x = i;
		for (long long  j = -1 * PLAYER_MAGFICATION * 3; j < PLAYER_MAGFICATION * 3; j++)
		{
			to.x = j;
			for (long long k = 0; k < PLAYER_MAGFICATION * 2; k++)
			{
				to.y = k;
				now = dose_we_colides_first(from, to, 0.0);
				if (now != before ) {
					before = now;
					fprintf(stdout, "now : %d, from : '%lld, %lld' ", now, from.x, from.y);
					fprintf(stdout, "to : '%lld, %lld'\n", to.x, to.y);
				}
			}
			
		}
	}
}
// */
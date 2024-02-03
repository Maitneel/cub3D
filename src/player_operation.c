#include "cub3d_structs.h"
#include "mlx_defines.h"
#include <math.h>
#include <stdio.h>

static const double	g_rotate_angle = (M_PI_2 / 9.0f);
static const double	g_moving_coefficient = 0.5f;

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

void	move_player(int key_code, t_player *player)
{
	double	moving_direction;

	moving_direction = 0;
	if (key_code == KEY_W)
		moving_direction = player->direction;
	else if (key_code == KEY_S)
		moving_direction = player->direction + M_PI;
	else if (key_code == KEY_A)
		moving_direction = player->direction - M_PI_2;
	else if (key_code == KEY_D)
		moving_direction = player->direction + M_PI_2;
	player->point.x -= (long long)((sin(moving_direction)
				* g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
	player->point.y += (long long)((cos(moving_direction)
				* g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
}

#include <math.h>

#include "cub3d_structs.h"
#include "mlx_defines.h"

#include <stdio.h>

const double	g_rotate_angle = (M_PI_2 / 9.0f);
const double	g_moving_coefficient = 0.5f;

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

void	move_player(int key_code, t_player *player, t_map_element **map)
{
	double	moving_direction;

	moving_direction = 0;
	if (key_code == KEY_W)
		moving_direction = player->direction;
	else if (key_code == KEY_S)
		moving_direction = player->direction - M_PI;
	else if (key_code == KEY_A)
		moving_direction = player->direction - M_PI_2;
	else if (key_code == KEY_D)
		moving_direction = player->direction + M_PI_2;
	player->point.x_hoge += (long long)((sin(moving_direction) * g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
	player->point.y_hoge -= (long long)((cos(moving_direction) * g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "moving_direction : '%f'\n", moving_direction);
	fprintf(stderr, "cos(moving_direction) : '%+f'\n", cos(moving_direction));
	fprintf(stderr, "sin(moving_direction) : '%+f'\n", sin(moving_direction));
}

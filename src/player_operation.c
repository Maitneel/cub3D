#include <math.h>

#include "cub3d_structs.h"
#include "mlx_defines.h"

#include <stdio.h>

#define ROTATE_ANGLE (M_PI_2)
#define MOVING_COEFFICIENT (0.5)

void	rotate_player(int key_code, t_player *player)
{
	if (key_code == ARROW_LEFT)
	{
		player->direction -= ROTATE_ANGLE;
		if (player->direction < 0.0f)
			player->direction += 2 * M_PI;
	} else if (key_code == ARROW_RIGHT)
	{
		player->direction += ROTATE_ANGLE;
		if (2.0f * M_PI <= player->direction)
			player->direction -= 2.0f * M_PI;
	}
}

void	move_player(int key_code, t_player *player)
{
	double moving_direction;

	moving_direction = 0;
	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "player->direction : '%f'\n", player->direction);
	if (key_code == KEY_W)
		moving_direction = player->direction;
	else if (key_code == KEY_S)
		moving_direction = player->direction - M_PI;
	else if (key_code == KEY_A)
		moving_direction = player->direction - M_PI_2;
	else if (key_code == KEY_D)
		moving_direction = player->direction + M_PI_2;
	fprintf(stderr, "moving_direction : '%f'\n", moving_direction);
	fprintf(stderr, "cos(moving_direction) : '%f'\n", cos(moving_direction));
	fprintf(stderr, "sin(moving_direction) : '%fm'\n", sin(moving_direction));
	player->point.x += sin(moving_direction) * MOVING_COEFFICIENT;
	player->point.y -= cos(moving_direction) * MOVING_COEFFICIENT;
}

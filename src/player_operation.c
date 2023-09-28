#include <math.h>

#include "cub3d_structs.h"
#include "mlx_defines.h"

#include <stdio.h>

#define ROTATE_ANGLE (M_PI / 18.0f);

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

}

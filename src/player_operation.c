#include <math.h>
#include <stdbool.h>

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

bool	is_div_mag_equal_coord(const t_point a, const t_point b, const char coord)
{
	if (coord == 'x')
		return (a.x / PLAYER_MAGFICATION == b.x / PLAYER_MAGFICATION);
	else if (coord == 'y') 
		return (a.y / PLAYER_MAGFICATION == b.y / PLAYER_MAGFICATION);
	else 
		return (false);
}

int get_boundary(const int before, const int after)
{
	if (before == after)
		return before;
	if (before < after)
		return ((after / PLAYER_MAGFICATION) * PLAYER_MAGFICATION - 1);
	else 
		return ((before / PLAYER_MAGFICATION) * PLAYER_MAGFICATION);
}


/*--------------------------------------------------*/
/*                         N                        */
/*                    o---------o                   */
/*                    |         |                   */
/*                W   |         |   E               */
/*                    |         |                   */
/*                    o---------o                   */
/*                         S                        */
/*--------------------------------------------------*/
bool dose_we_colides_first(const t_point from, const t_point to)
{
	const double line_angle = atan((double)(to.y - from.y) / (double)(to.x - from.x));
	const double left_top_angle = atan((double)((from.y - (from.y % PLAYER_MAGFICATION)) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION)) - from.x));
	const double right_top_angle = atan((double)((from.y - (from.y % PLAYER_MAGFICATION)) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.x));
	const double left_bottom_angle = atan((double)((from.y - (from.y % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION)) - from.x));
	const double right_bottom_angle = atan((double)((from.y - (from.y % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.x));

	if (from.x == to.x)
		return false;
	else if (to.x < from.x)
		return (right_top_angle < line_angle && line_angle < right_bottom_angle);
	else
		return (left_bottom_angle < line_angle && line_angle < left_top_angle);
}

void	collision_correction(t_point *to, t_point *from, const t_map_element **map)
{
	if (is_div_mag_equal_coord(*to, *from, 'x') && is_div_mag_equal_coord(*to, *from, 'y'))
		return ;
	// ここ衝突判定が常に正しくできていて、かつマップがすべて壁に囲まれている場合は問題ないが、どれか一つでも満たせないとout_of_rangeする //
	if (is_div_mag_equal_coord(*to, *from, 'x') || is_div_mag_equal_coord(*to, *from, 'y')) {
		if (map[to->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] == WALL)
		{
			if (is_div_mag_equal_coord(*to, *from, 'x'))
				to->y = get_boundary(from->y, to->y);
			else if (is_div_mag_equal_coord(*to, *from, 'y'))
				to->x = get_boundary(from->x, to->x);
		}
	}
	else 
	{
		// TODO 
		fprintf(stderr, "%s\n", (dose_we_colides_first(*from, *to) ? "west east first" : "north south first"));
		if (map[to->y / PLAYER_MAGFICATION][from->x / PLAYER_MAGFICATION] == WALL && map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] == WALL)
		{
			to->y = get_boundary(from->y, to->y);
			to->x = get_boundary(from->x, to->x);
			fprintf(stderr, "x and y collision\n");
		}
	}
}

void	move_player(int key_code, t_player *player, t_map_element **map)
{
	double	moving_direction;
	t_point from;

	moving_direction = 0;
	from = player->point;
	if (key_code == KEY_W)
		moving_direction = player->direction;
	else if (key_code == KEY_S)
		moving_direction = player->direction - M_PI;
	else if (key_code == KEY_A)
		moving_direction = player->direction - M_PI_2;
	else if (key_code == KEY_D)
		moving_direction = player->direction + M_PI_2;
	player->point.x += (long long)((sin(moving_direction) * g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
	player->point.y -= (long long)((cos(moving_direction) * g_moving_coefficient) * (double)(PLAYER_MAGFICATION));
	collision_correction(&player->point, &from, map);
	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "moving_direction : '%f'\n", moving_direction);
	fprintf(stderr, "cos(moving_direction) : '%+f'\n", cos(moving_direction));
	fprintf(stderr, "sin(moving_direction) : '%+f'\n", sin(moving_direction));
}

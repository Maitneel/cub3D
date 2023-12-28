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
// こいつうまく動いてない //
bool dose_we_colides_first(const t_point from, const t_point to, double direction)
{
	const double line_angle = ((double)(to.y - from.y) / (double)(to.x - from.x));
	// double line_angle;
	const double left_top_angle = ((double)((from.y - (from.y % PLAYER_MAGFICATION)) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) - 1) - from.x));
	const double right_top_angle = ((double)((from.y - (from.y % PLAYER_MAGFICATION)) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.x));
	const double left_bottom_angle = ((double)((from.y - (from.y % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) - 1) - from.x));
	const double right_bottom_angle = ((double)((from.y - (from.y % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.y) / (double)((from.x - (from.x % PLAYER_MAGFICATION) + PLAYER_MAGFICATION) - from.x));

	// if (direction < 0) {
	// 	direction += M_PI * 2;
	// }

	// line_angle = tan(direction);
	// if (direction < 0) {
	// 	line_angle += M_PI;
	// }
	fprintf(stderr, "direction          : '%f'\n", direction * 180 / M_PI);
	fprintf(stderr, "line_angle         : '%f'\n", line_angle);
	fprintf(stderr, "left_top_angle     : '%f'\n", left_top_angle);
	fprintf(stderr, "left_bottom_angle  : '%f'\n", left_bottom_angle);
	fprintf(stderr, "right_top_angle    : '%f'\n", right_top_angle);
	fprintf(stderr, "right_bottom_angle : '%f'\n", right_bottom_angle);

	if (from.x == to.x)
		fprintf(stderr, "stat %d flag1\n", false);
	else if (from.x < to.x)
		fprintf(stderr, "stat %d flag2\n", (right_top_angle < line_angle && line_angle < right_bottom_angle));
	else
		fprintf(stderr, "stat %d flag3\n", (left_bottom_angle < line_angle && line_angle < left_top_angle));

	fprintf(stderr, "hogehoge------------------------------------------\n");
	if (from.x == to.x)
		return false;
	else if (from.x < to.x)
		return (right_top_angle < line_angle && line_angle < right_bottom_angle);
	else
		return (left_bottom_angle < line_angle && line_angle < left_top_angle);
}

void correct_misalingment(const t_point *from, t_point *to, const t_point *misalingment_from, const char coord)
{
	long long diff;
	double raito;

	fprintf(stderr, "before-----------------------------------\n");
	fprintf(stderr, "to->x : '%lld'\n", to->x);
	fprintf(stderr, "to->y : '%lld'\n", to->y);
	if (coord == 'x')
	{
		if (from->y == to->y)
			return;
		raito = fabs((double)(from->y) - (double)(misalingment_from->y)) /fabs((double)(from->y) - (double)(to->y));
		diff = (int)((double)(to->x - from->x) * raito);
		to->x -= diff;
	}
	else if (coord == 'y')
	{
		if (from->x == to->x)
			return;
		raito = fabs((double)(from->x) - (double)(misalingment_from->x)) /fabs((double)(from->x) - (double)(to->x));
		diff = (int)((double)(to->y - from->y) * raito);
		to->y -= diff;
	}
	fprintf(stderr, "after------------------------------------\n");
	fprintf(stderr, "to->x : '%lld'\n", to->x);
	fprintf(stderr, "to->y : '%lld'\n", to->y);
}

void	collision_correction(t_point *to, t_point *from, const double direction, const t_map_element **map)
{
	// fprintf(stderr,  "callied ------------------------------\n");
	t_point misalingment;
	if (is_div_mag_equal_coord(*to, *from, 'x') && is_div_mag_equal_coord(*to, *from, 'y'))
		return ;
	// ここ衝突判定が常に正しくできていて、かつマップがすべて壁に囲まれている場合は問題ないが、どれか一つでも満たせないとout_of_rangeする //
	fprintf(stderr, "from->x : '%d' ", from->x);
	fprintf(stderr, "from->y : '%d'\n", from->y);

	fprintf(stderr, "to->x : '%d' ", to->x);
	fprintf(stderr, "to->y : '%d'\n", to->y);

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
		// fprintf(stderr, "%s\n", (dose_we_colides_first(*from, *to, direction) ? "west east first" : "north south first"));
		// else if (dose_we_colides_first(*from, *to, direction) || (from->x % PLAYER_MAGFICATION == 0 || from->x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1))

		fprintf(stderr, "dose_we_colides_first(*from, *to, direction) : '%d'\n", dose_we_colides_first(*from, *to, direction));
		fprintf(stderr, "map[to->y / PLAYER_MAGFICATION][from->x / PLAYER_MAGFICATION] != WALL : '%d'\n", map[to->y / PLAYER_MAGFICATION][from->x / PLAYER_MAGFICATION] != WALL);
		fprintf(stderr, "map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] != WALL : '%d'\n", map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] != WALL);

		// この条件だとワンチャン積む //
		if (dose_we_colides_first(*from, *to, direction) && map[to->y / PLAYER_MAGFICATION][from->x / PLAYER_MAGFICATION] != WALL || map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] == WALL)
		{	
			misalingment.x = get_boundary(from->x, to->x);
			misalingment.y = get_boundary(to->y, from->y);
			if (map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] == WALL)
			{
				correct_misalingment(from, to, &misalingment, 'x');
			}
			*from = misalingment;
			// fprintf(stderr, "we'\n");
			// fprintf(stderr, "misalingment.x : '%d'\n", misalingment.x);
			// fprintf(stderr, "misalingment.y : '%d'\n", misalingment.y);
			collision_correction(to, from, direction, map);
		}
		else if (map[from->y / PLAYER_MAGFICATION][to->x / PLAYER_MAGFICATION] != WALL)
		{
			if (dose_we_colides_first(*from, *to, direction)) {
				fprintf(stderr, "error----------------------------\n");
			}
			// fprintf(stderr, "\x1b[47m\x1b[30m");
			// fprintf(stderr ,"NS                          ");
			// fprintf(stderr, "\x1b[39m");
			// fprintf(stderr, "\x1b[49m");
			// fprintf(stderr, "\n");

			misalingment.x = get_boundary(to->x, from->x);
			misalingment.y = get_boundary(from->y, to->y);
			if (map[to->y / PLAYER_MAGFICATION][from->x / PLAYER_MAGFICATION] == WALL)
			{
				correct_misalingment(from, to, &misalingment, 'y');
			}
			*from = misalingment;
			// fprintf(stderr, "ns'\n");
			// fprintf(stderr, "misalingment.x : '%d'\n", misalingment.x);
			// fprintf(stderr, "misalingment.y : '%d'\n", misalingment.y);
			collision_correction(to, from, direction, map);
		}
		else
		{
			to->y = get_boundary(from->y, to->y);
			to->x = get_boundary(from->x, to->x);
			// fprintf(stderr, "x and y collision\n");
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
	fprintf(stderr, "======================================================================\n");
	collision_correction(&player->point, &from, moving_direction, map);
	fprintf(stderr, "------------------------------------------------------\n");
	fprintf(stderr, "moving_direction : '%f'\n", moving_direction);
	fprintf(stderr, "cos(moving_direction) : '%+f'\n", cos(moving_direction));
	fprintf(stderr, "sin(moving_direction) : '%+f'\n", sin(moving_direction));
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
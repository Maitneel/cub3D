#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

bool is_wall(t_cub3d *cub3d, int y, int x)
{
    const t_map_element **map = cub3d->map;
    if (!(0 < y && y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= x && x < cub3d->map_width * PLAYER_MAGFICATION))
    {
        return true;
    }
    return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == WALL);
}

double normDir(double dir)
{
    return fmod(fabs(dir + 2 * M_PI), 2 * M_PI);
}

bool is_west(double ray_dir)
{
    double dir = normDir(ray_dir - M_PI_2);
    if (0 < dir && dir < M_PI)
        return true;
    return false;
}

bool is_east(double ray_dir)
{
    double dir = normDir(ray_dir - M_PI_2);
    if (dir > M_PI && dir < 2 * M_PI)
        return true;
    return false;
}

bool is_south(double ray_dir)
{
    double dir = normDir(ray_dir - M_PI_2);
    if (dir < M_PI_2 || dir > M_PI_2 * 3)
        return true;
    return false;
}

bool is_north(double ray_dir)
{
    double dir = normDir(ray_dir - M_PI_2);
    if (dir > M_PI_2 && dir < M_PI_2 * 3)
        return true;
    return false;
}

void print_dir(double);

t_point *hz_collition_point(t_cub3d *cub3d, double dir)
{
    int side_x;
    int side_y;
    int step;
    if (is_north(dir))
    {
        side_y = -1 * cub3d->player.point.y % PLAYER_MAGFICATION - 1;
        step = -PLAYER_MAGFICATION;
    }
    else if (is_south(dir))
    {
        side_y =  PLAYER_MAGFICATION - (cub3d->player.point.y % PLAYER_MAGFICATION);
        step = PLAYER_MAGFICATION;
    }
     else {
        return (new_point(INT_MAX, INT_MAX));
    }
    side_x = tan(dir + M_PI_2) * side_y * -1;
    if (!(-100000 < side_x && side_x < 100000)) {
        // fprintf(stderr, "side_x : %d\n", side_x);
    }
    while(!is_wall(cub3d, cub3d->player.point.y + side_y,cub3d->player.point.x + side_x))
    {
        side_y += step;
        side_x = tan(dir + M_PI_2) * side_y * -1;
    }
    return new_point(cub3d->player.point.y + side_y, cub3d->player.point.x + side_x);
}

t_point *vert_collition_point(t_cub3d *cub3d, double dir)
{
    int side_x;
    int side_y;
    int step;
    if (is_east(dir))
    {
        side_x = PLAYER_MAGFICATION - (cub3d->player.point.x % PLAYER_MAGFICATION);
        side_y = side_x * tan(dir);
        step = PLAYER_MAGFICATION;
    } else if (is_west(dir))
    {
        // ここの初期値うまう動かないかも //
        side_x = -1 * cub3d->player.point.x % PLAYER_MAGFICATION - 1;
        side_y = side_x * tan(dir);
        step = -PLAYER_MAGFICATION;
    } else {
        return (new_point(INT_MAX, INT_MAX));
    }
    if (!(-100000 < side_y && side_y < 100000)){
        // fprintf(stderr, "side_y : %d\n", side_y);
    }
    while(!is_wall(cub3d, cub3d->player.point.y + side_y,cub3d->player.point.x + side_x))
    {
        side_x += step;
        side_y = side_x * tan(dir);
    }
    return new_point(cub3d->player.point.y + side_y, cub3d->player.point.x + side_x);
}

double get_distance(t_point *start, t_point *end)
{
    if (start->x == INT_MAX || start->y == INT_MAX || end->x == INT_MAX || end->y == INT_MAX)
        return INFINITY;
    return (sqrt(pow(end->y - start->y,2) + pow(end->x - start->x, 2)));
}

// TODO: 直行したベクトルの場合、壁をすり抜ける
t_point *get_collision_point2(t_cub3d *cub3d, double dir)
{
    int n = 1;
    int y = cub3d->player.point.y;
    int x = cub3d->player.point.x;
    int before_x = x;
    int before_y = y;

    t_point *hz_point = hz_collition_point(cub3d, dir);
    t_point *vert_point = vert_collition_point(cub3d, dir);

    // return hz_point;
    // return vert_point;


    if (get_distance(&(cub3d->player.point), hz_point) < get_distance(&(cub3d->player.point), vert_point))
    {
        return hz_point;
    }
    else
    {
        return vert_point;
    }
}

t_point *get_collision_point(t_cub3d *cub3d, double dir)
{
    int n = 1;
    int y = cub3d->player.point.y;
    int x = cub3d->player.point.x;
    int before_x = x;
    int before_y = y;

    while (true)
    {
        before_x = x;
        before_y = y;
        y = cub3d->player.point.y + sin(dir) * n;
        x = cub3d->player.point.x + cos(dir) * n;
        if (is_wall(cub3d, y, x)) {
            break;
        }
        n++;
    }
    return new_point(before_y, before_x);
}

double get_adj_dis(t_player *player, double ray_dir, t_point* start, t_point *end)
{
    double dtheta = ray_dir - player->direction - M_PI_2; 
    return cos(dtheta) * get_distance(start, end);
}

double get_wall_ratio(double wall_distance, const double dir)
{
    return ((double)WALL_HEIGHT / (tan(VERT_FOV_ANGLE) * (double)wall_distance));
}

t_graphic_info *get_graphic_info_by_point(t_cub3d *cub3d, t_point *point)
{
    if (!(0 < point->y && point->y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= point->x && point->x < cub3d->map_width * PLAYER_MAGFICATION))
    {
        return cub3d->graphic_info->north_texture;   
        fprintf(stderr, "dose not wall\n");
    }

    const t_map_element **map = cub3d->map;
    const int x = point->x / PLAYER_MAGFICATION;
    const int y = point->y / PLAYER_MAGFICATION;
    
    if (!is_wall(cub3d, point->y, point->x))
    {
        // fprintf(stderr, "dose not wall\n");
        return cub3d->graphic_info->west_texture;
    }

    if (point->x % PLAYER_MAGFICATION == 0)
    {
        return cub3d->graphic_info->west_texture;
    }
    else if (point->x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1)
    {
        return cub3d->graphic_info->east_texture;
    }
    else if (point->y % PLAYER_MAGFICATION == 0)
    {
        return cub3d->graphic_info->north_texture;
    }
    else if (point->y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1)
    {
        return cub3d->graphic_info->south_texture;
    }
    // TODO: 未到達なはず...
    return cub3d->graphic_info->east_texture;
}

double get_texture_position(t_cub3d *cub3d, t_point *point)
{
    const t_map_element **map = cub3d->map;
    const int y = point->y / PLAYER_MAGFICATION;
    const int x = point->x / PLAYER_MAGFICATION;
    // fprintf(stderr, "x : %d  ", x);
    // fprintf(stderr, "y : %d\n", y);

    if (!(0 < point->y && point->y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= point->x && point->x < cub3d->map_width * PLAYER_MAGFICATION))
    {
        return 0.0;
    }




    if (point->x % PLAYER_MAGFICATION == 0 )
    {
        return 1.0 - (double)(point->y % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    }
    else if (point->x % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1 )
    {
        return (double)(point->y % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    }
    else if (point->y % PLAYER_MAGFICATION == 0 )
    {
        return (double)(point->x % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;   
    }
    else if (point->y % PLAYER_MAGFICATION == PLAYER_MAGFICATION - 1)
    {
        return 1.0 - (double)(point->x % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    }
    // TODO: 未到達なはず...
    return 0.0;
}

void print_point(t_point *point)
{
    printf("y: %d, x: %d\n", point->y, point->x);
}

void print_dir(double dir)
{
    printf(
        "north: %d, south: %d, east: %d, west: %d, dir: %.20f\n",
        is_north(dir),
        is_south(dir),
        is_east(dir),
        is_west(dir),
        180 * dir / M_PI
    );
}

#define SCREEN_MAGFICATION 100000

t_point get_screen_point(const t_point focus_point, const double direction)
{
    t_point screen_point;

    screen_point.x = sin(direction) * SCREEN_MAGFICATION + focus_point.x;
    screen_point.y = cos(direction) * SCREEN_MAGFICATION + focus_point.y;
    return screen_point;
}

double get_direction_across_screen_position(const t_point player_position, const t_point screen_left, const t_point screen_right, const int screen_position)
{
    double position_x;
    double position_y;
    double direction;
    double diff_x;
    double diff_y;

    position_x = (screen_left.x + ((screen_right.x - screen_left.x) * (double)(screen_position) / WINDOW_WIDTH));
    position_y = (screen_left.y + ((screen_right.y - screen_left.y) * (double)(screen_position) / WINDOW_WIDTH));

    diff_x = position_x - player_position.x;
    diff_y = position_y - player_position.y;

    // ここ問題ないかわからない //
    // atan func は ＋- inf が与えられた時 +- pi/2 を返すが //
    // float のゼロ除算が inf を返すかがわからない //
    direction = (atan(diff_y / diff_x)) * -1.0;
    if (position_x < player_position.x) {
        direction += M_PI * 2.0;
    } else {
        direction += M_PI;
    }
    return direction;
}

t_mlx_image	*new_raycasting_image(
	const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height)
{
    t_mlx_image		*image;
    t_point         *collision_point;
    double          wall_raito;
    t_point         screen_left;
    t_point         screen_right;

    screen_left = get_screen_point(cub3d->player.point, cub3d->player.direction - (HN_FOV_ANGLE / 2.0));
    screen_right = get_screen_point(cub3d->player.point, cub3d->player.direction + (HN_FOV_ANGLE / 2.0));
    image = new_image_struct(mlx, width, height);

    // print_dir(cub3d->player.direction);
    for (int x=0; x<WINDOW_WIDTH; x++)
    {
        double ray_dir = get_direction_across_screen_position(cub3d->player.point, screen_left, screen_right, x );
        // double ray_dir = cub3d->player.direction;
        collision_point = get_collision_point2(cub3d, ray_dir);
        t_point *cp = get_collision_point(cub3d, ray_dir);
        double wall_dis = get_adj_dis(&cub3d->player, ray_dir, collision_point, &(cub3d->player.point));
        wall_raito = get_wall_ratio(wall_dis, ray_dir);

        // fprintf(stderr, "wrong_point.x : %d  ", collision_point->x);
        // fprintf(stderr, " y : %d  ", collision_point->y);
        // fprintf(stderr, "ray_dir : %f\n", ray_dir);
        // fprintf(stderr, "correct_point.x  : %d  ", cp->x);
        // fprintf(stderr, "y : %d\n", cp->y);
        // fprintf(stderr, "diff        .x : %d  ", collision_point->x - cp->x);
        // fprintf(stderr, "y : %d\n", collision_point->y - cp->y);

        paste_texture(cub3d, image, wall_raito, get_texture_position(cub3d, collision_point), get_graphic_info_by_point(cub3d, collision_point), x);
        free(collision_point);
    }
    // exit(0);m
    return (image);
}

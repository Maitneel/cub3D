#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include "paste_texture.h"
#include <math.h>
#include <stdbool.h>

#include <stdio.h>

//TODO: あとでヘッダーに移す(他で同じような定義がありそうな予感)
#define HN_FOV_ANGLE (90 * M_PI / 180)
#define WALL_HEIGHT 10
#define VERT_FOV_ANGLE (10 * M_PI / 180)

bool is_wall(t_cub3d *cub3d, int y, int x)
{
    const t_map_element **map = cub3d->map;
    if (!(0 < y && y < cub3d->map_height * PLAYER_MAGFICATION) || !(0 <= x && x < cub3d->map_width * PLAYER_MAGFICATION))
    {
        return true;
    }
    return (map[y / PLAYER_MAGFICATION][x / PLAYER_MAGFICATION] == WALL);
}

// TODO: 直行したベクトルの場合、壁をすり抜ける
t_point *get_collision_point(t_cub3d *cub3d, double dir)
{
    int n = 1;
    int y = cub3d->player.point.y;
    int x = cub3d->player.point.x;
    while (!is_wall(cub3d, y, x))
    {
        y = cub3d->player.point.y + sin(dir) * n;
        x = cub3d->player.point.x + cos(dir) * n;
        n++;
    }
    return new_point(y, x);
}

double get_distance(t_player *player, double ray_dir, t_point* start, t_point *end)
{
    double dtheta = ray_dir - player->direction - M_PI_2; 
    return cos(dtheta) * sqrt(pow(end->y - start->y,2) + pow(end->x - start->x, 2));
}

double get_wall_ratio(double wall_distance)
{
    return (WALL_HEIGHT / (tan(VERT_FOV_ANGLE) * wall_distance));
}

t_graphic_info *get_graphic_info_by_point(t_cub3d *cub3d, t_point *point)
{
    if (point->x % PLAYER_MAGFICATION == 0)
        return cub3d->graphic_info->east_texture;
    else if (point->x % PLAYER_MAGFICATION == 99)
        return cub3d->graphic_info->west_texture;
    else if (point->y % PLAYER_MAGFICATION == 0)
        return cub3d->graphic_info->south_texture;
    else if (point->y % PLAYER_MAGFICATION == 99)
        return cub3d->graphic_info->north_texture;
    // TODO: 未到達なはず...
    return cub3d->graphic_info->east_texture;
}

double get_texture_position(t_point *point)
{
    if (point->x % PLAYER_MAGFICATION == 0)
        return (double)(point->y % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    else if (point->x % PLAYER_MAGFICATION == 99)
        return 1.0 - (double)(point->y % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    else if (point->y % PLAYER_MAGFICATION == 0)
        return 1.0 - (double)(point->x % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;
    else if (point->y % PLAYER_MAGFICATION == 99)
        return (double)(point->x % PLAYER_MAGFICATION) / (double)PLAYER_MAGFICATION;    
    // TODO: 未到達なはず...
    return 0.0;
}

void print_point(t_point *point)
{
    printf("y: %d, x: %d\n", point->y, point->x);
}

t_mlx_image	*new_raycasting_image(
	const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height)
{
    t_mlx_image		*image;
    t_point         *collision_point;
    double          wall_raito;

    image = new_image_struct(mlx, width, height);
    for (int x=0; x<WINDOW_WIDTH; x++)
    {
        double ray_dir = ((cub3d->player.direction - (HN_FOV_ANGLE / 2.0)) + ((HN_FOV_ANGLE / (double)(WINDOW_WIDTH)) * x) + M_PI_2);
        collision_point = get_collision_point(cub3d, ray_dir);
        double wall_dis = get_distance(&cub3d->player, ray_dir, collision_point, &(cub3d->player.point));
        wall_raito = get_wall_ratio(wall_dis);
        paste_texture(image, wall_raito, get_texture_position(collision_point), get_graphic_info_by_point(cub3d, collision_point), x);
        print_point(collision_point);
        fprintf(stderr, "pos: %f\n", get_texture_position(collision_point));
        free(collision_point);
    }
    return (image);
}

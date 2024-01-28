#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d_structs.h"
# include <math.h>

t_mlx_image	*new_raycasting_image(
	const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height);

// util
double norm_dir(double dir);
bool is_west(double ray_dir);
bool is_east(double ray_dir);
bool is_south(double ray_dir);
bool is_north(double ray_dir);

#endif // RAYCASTING_H

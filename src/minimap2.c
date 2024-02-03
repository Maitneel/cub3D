#include "cub3d_structs.h"
#include "free_lib.h"
#include "mlx.h"
#include "mlx_image_proc.h"
#include "util_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	put_line(
	unsigned int **color_map,
	const int height,
	const int width,
	const double direction)
{
	int			magfication;
	int			i;
	int			j;
	int			prev_i;
	int			prev_j;

	i = (height / 2);
	j = (width / 2);
	prev_i = i;
	prev_j = j;
	magfication = 0;
	while (0 <= i && i < height && 0 <= j && j < width)
	{
		if (is_lay_end(color_map[i][j]) || \
		(is_lay_end(color_map[i][prev_j]) && is_lay_end(color_map[prev_i][j])))
			return ;
		color_map[i][j] = MINIMAP_FILED_OF_VIEW_COLOR;
		magfication++;
		prev_i = i;
		prev_j = j;
		i = (height / 2) + (int)(sin(direction) * magfication);
		j = (width / 2) + (int)(cos(direction) * magfication);
	}
}

void	coloring_filed_of_view(const t_cub3d *cub3d,
							unsigned int **color_map,
							const int height,
							const int width)
{
	size_t	i;
	int		greater_size;

	if (width < height)
		greater_size = height;
	else
		greater_size = width;
	greater_size += 30;
	i = 0;
	while (i < greater_size)
	{
		put_line(color_map, height, width, (cub3d->player.direction \
			+ HN_FOV_ANGLE / 2.0 - \
			((double)(i) *HN_FOV_ANGLE / (double)(greater_size))) + M_PI_2);
		i++;
	}
}

void	put_to_image_from_int_array(
	t_mlx_image *image, unsigned int **color_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			put_pixel_to_mlx_image(image, j, i, color_map[i][j]);
			j++;
		}
		i++;
	}
}

t_mlx_image	*new_minimap(
	const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height)
{
	t_mlx_image		*minimap;
	unsigned int	**color_map;

	minimap = new_image_struct(mlx, width, height);
	color_map = get_default_color_map(cub3d, width, height);
	coloring_filed_of_view(cub3d, color_map, height, width);
	put_to_image_from_int_array(minimap, color_map);
	free_uint_array_array(color_map, height);
	put_player_position(minimap);
	return (minimap);
}

#include "mlx.h"

#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include "util_lib.h"
#include "free_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MINIMAP_OUT_OF_MAP_COLOR 0x80000000
#define MINIMAP_EMPYT_COLOR 0x80ffffff
#define MINIMAP_WALL_COLOR 0x80303030

t_map_element get_map_element_type(const t_cub3d *cub3d, const int x, const int y)
{
	t_map_element type;

	if ((0 <= x && x < cub3d->map_width) && (0 <= y && y < cub3d->map_height))
		type = cub3d->map[y][x];
	else 
		type = OUT_OF_MAP;
	return (type);
}


// TODO //
// START_*をEMPTYに置き換えてない関係でこうなってるけど、OUT_OF_MAPをelseで返すようにしたい //
int	get_minimap_color(t_map_element type)
{
	if (type == OUT_OF_MAP || type == END_OF_LINE)
		return (MINIMAP_OUT_OF_MAP_COLOR);
	else if (type == WALL)
		return (MINIMAP_WALL_COLOR);
	else 
		return (MINIMAP_EMPYT_COLOR);
}

void put_player_position(t_mlx_image *minimap)
{
	size_t i;
	size_t j;
	const size_t player_position_size = 4;
	
	i = (minimap->height / 2) - (player_position_size / 2);
	while (i < (minimap->height / 2) + (player_position_size / 2))
	{
		j = (minimap->width / 2) - (player_position_size / 2);
		while (j < (minimap->width / 2) + (player_position_size / 2))
		{
			put_pixel_to_mlx_image(minimap, j, i, 0x80ff0000);
			j++;
		}
		i++;
	}

}

unsigned int	**get_default_color_map(const t_cub3d *cub3d, const int width, const int height)
{
	int **color_map;
	int x;
	int y;
	int i;
	int j;

	i = 0;
	color_map = ft_xcalloc(height + 1, sizeof(int *));
	while (i < height)
	{
		color_map[i] = ft_xcalloc(width + 1, sizeof(int));
		j = 0;
		while (j < width)
		{
			// TODO 何が TODO なのかぶっちゃけわからない //
			x = ((int)(cub3d->player.point.x_hoge * 15 / PLAYER_MAGFICATION + j) - (width / 2)) / 15;
			y = ((int)(cub3d->player.point.y_hoge * 15 / PLAYER_MAGFICATION  + i - (height / 2))) / 15;
			color_map[i][j] = get_minimap_color(get_map_element_type(cub3d, x, y));
			j++;
		}
		i++;
	}
	return (color_map);
}

void put_to_image_front_int_array(t_mlx_image *image, unsigned int **color_map)
{
	int i;
	int j;
	
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

t_mlx_image *new_minimap(const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height)
{
	t_mlx_image	*minimap;
	unsigned int **color_map;

	minimap = new_image_struct(mlx, width, height);
	color_map = get_default_color_map(cub3d, width, height);
	put_to_image_front_int_array(minimap, color_map);
	free_uint_array_array(color_map, height);
	put_player_position(minimap);
	return (minimap);
}
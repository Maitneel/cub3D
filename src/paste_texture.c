#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include <math.h>
#include <stdio.h>

int convert_color_to_int(t_color color)
{
	int result;

	result = 0;
	result |= color.red << 16;
	result |= color.green << 8;
	result |= color.blue << 0;
	return (result);
}

static void paste_background(
	t_cub3d *cub3d, t_mlx_image *image, const size_t image_x)
{
	size_t i;

	i = 0;
	while ((int)(i) < (image->height))
	{
		if (i < (size_t)(image->height / 2))
			put_pixel_to_mlx_image(image, image_x, i,
								   convert_color_to_int(*(cub3d->graphic_info->ceiling_color)));
		else
			put_pixel_to_mlx_image(image, image_x, i,
								   convert_color_to_int(*(cub3d->graphic_info->floor_color)));
		i++;
	}
}

int max(const int a, const int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

static bool is_wall_index(const int y, double wall_ratio)
{
	const int harf_index = WINDOW_HEIGHT / 2;
	const int _wall = (WINDOW_HEIGHT * wall_ratio) / 2.0;

	if (y > harf_index - _wall && y < harf_index + _wall)
		return true;
	return false;
}

int wall_start_idx(const int image_height, double wall_ratio)
{
	const int harf_index = image_height / 2;
	const int start_idx = harf_index - (image_height * wall_ratio) / 2.0;

	if (start_idx < 0)
		return 0;
	return start_idx;
}

int wall_end_ids(const int image_height, double wall_ratio)
{
	const int harf_index = image_height / 2;
	const int end_idx = harf_index + (image_height * wall_ratio) / 2.0;

	if (end_idx > image_height)
		return image_height;
	return end_idx;
}

#include <stdlib.h>
void paste_texture(t_cub3d *cub3d, t_mlx_image *image,
				   const t_texture *texture, t_paste_texture_info info)
{
	size_t color_x;
	int i;
	int y;
	const long long paste_height = image->height * info.mag;
	const int axis_correction = (image->height * (1.0 - info.mag) / 2.0);
	const int _wall = (WINDOW_HEIGHT * info.mag) / 2.0;

	paste_background(cub3d, image, info.image_x);
	if (image->width <= (int)(info.image_x))
		return;
	color_x = (((double)(info.texture_pos)) * ((double)(texture->width)));
	if (texture->width <= color_x)
		color_x = texture->width - 1;
	int j = 0;
	printf("%f\n", info.mag);
	for (int i = wall_start_idx(image->height, info.mag); i < wall_end_ids(image->height, info.mag); i++)
	{
		int y = j++ * ((double)texture->height / (double)paste_height);
		if (0 <= y && y < (int)(texture->height))
			put_pixel_to_mlx_image(image, info.image_x, i,
								   convert_color_to_int(texture->pixel_color[y][color_x]));
	}
}
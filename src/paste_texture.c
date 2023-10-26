#include "cub3d_structs.h"
#include "mlx_image_proc.h"


#include <stdio.h>

int convert_color_to_int(t_color color)
{
	int result;

	result = 0;
	result |= color.red << 16;
	result |= color.green << 8;
	result |= color.blue << 0;
	return result;
}

void paste_texture(t_mlx_image *image, const double magnification, const double texture_position, const t_texture *texture, const size_t image_x)
{
	size_t col;
	int i;

	if (image->width <= image_x)
		return;
	col = texture_position * (double)(texture->width);
	if (texture->width <= col)
		col = texture->width - 1;

	i = 0;
	while (i < image->height)
	{
		size_t y = ((double)(i) * magnification / image->height) * texture->height;
		if (texture->height <= y)
			y = texture->height - 1;
		size_t color_x = (double)(texture_position) * (double)(texture->width);
		if (texture->width <= color_x)
			color_x = texture->width - 1;
		put_pixel_to_mlx_image(image, image_x, i, convert_color_to_int(texture->pixel_color[y][color_x]));
		i++;
	}	
	fprintf(stderr, "image_x : '%zu'\n", image_x);
	fprintf(stderr, "texture_position : '%f'\n", texture_position);
}
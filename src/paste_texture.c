#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include <math.h>
#include <stdio.h>

int	convert_color_to_int(t_color color)
{
	int	result;

	result = 0;
	result |= color.red << 16;
	result |= color.green << 8;
	result |= color.blue << 0;
	return (result);
}

static void	paste_background(
	t_cub3d *cub3d, t_mlx_image *image, const size_t image_x)
{
	size_t	i;

	i = 0;
	while ((int)(i) < (image->height))
	{

		if (i < image->height / 2)
			put_pixel_to_mlx_image(image, image_x, i, \
			convert_color_to_int(*(cub3d->graphic_info->ceiling_color)));
		else
			put_pixel_to_mlx_image(image, image_x, i, \
			convert_color_to_int(*(cub3d->graphic_info->floor_color)));
		i++;
	}
}

void	paste_texture(t_cub3d *cub3d, t_mlx_image *image,

		const double magnification, const double texture_position,
		const t_texture *texture, const size_t image_x)
{
	size_t		color_x;
	size_t		col;
	int			i;
	int			y;
	const int	paste_height = image->height * magnification;
	const int	axis_correction = (image->height - paste_height) / 2;

	paste_background(cub3d, image, image_x);
	if (image->width <= image_x)
		return ;
	col = texture_position * (double)(texture->width);
	if (texture->width <= col)
		col = texture->width - 1;
	color_x = (((double)(texture_position)) * ((double)(texture->width)));
	if (texture->width <= color_x)
		color_x = texture->width - 1;
	i = 0;
	while (i < paste_height)
	{
		y = i * texture->height / paste_height;
		if (0 <= y && y < texture->height)
			put_pixel_to_mlx_image(image, image_x, i + axis_correction,
				convert_color_to_int(texture->pixel_color[y][color_x]));
		i++;
	}
}

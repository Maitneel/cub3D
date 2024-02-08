#include "cub3d_structs.h"
#include "mlx.h"
#include "print_lib.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_pixel_in_image(const t_mlx_image *image, const int x,
		const int y)
{
	return ((0 <= x && x < image->width) && (0 <= y && y < image->height));
}

int	put_pixel_to_mlx_image(t_mlx_image *image, const int x, const int y,
		const int color)
{
	size_t	front_pointer_at_pixel;

	if (!is_pixel_in_image(image, x, y))
		return (-1);
	if (image->bit_per_pixel / CHAR_BIT != 4 || image->endian != 0)
	{
		print_error(false, "incompatible format\n");
		exit(1);
	}
	front_pointer_at_pixel = (image->size_line * y) + (image->bit_per_pixel
			/ CHAR_BIT * x);
	image->data_addr[front_pointer_at_pixel + 0] = (color >> 8 * 0) & 0xff;
	image->data_addr[front_pointer_at_pixel + 1] = (color >> 8 * 1) & 0xff;
	image->data_addr[front_pointer_at_pixel + 2] = (color >> 8 * 2) & 0xff;
	image->data_addr[front_pointer_at_pixel + 3] = (color >> 8 * 3) & 0xff;
	return (0);
}

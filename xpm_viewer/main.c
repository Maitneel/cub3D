#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mlx.h"

#include "cub3d_structs.h"
#include "mlx_image_proc.h"
#include "print_lib.h"
#include "util_lib.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH WINDOW_HEIGHT + 200

t_texture	*new_texture(void *mlx_ptr, const char *file_name);
int convert_color_to_int(t_color color);
t_mlx_image *get_image_from_xpm_file(const void *mlx_ptr, const char *file_name);

min(a, b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

max(a, b) {
	if (a < b) {
		return b;
	} else {
		return a;
	}
} 


t_mlx_image	*new_image_struct_only_mlxptr(void *mlx, int width, int height)
{
	t_mlx_image	*mlx_image;

	mlx_image = ft_xcalloc(1, sizeof(t_mlx_image));
	mlx_image->image_ptr = mlx_new_image(mlx, width, height);
	if (mlx_image->image_ptr == NULL)
	{
		// TODO;
		print_error(false, "mlx_new_image failed\n");
		exit(1);
	}
	mlx_image->width = width;
	mlx_image->height = height;
	mlx_image->data_addr = mlx_get_data_addr(mlx_image->image_ptr, \
		&(mlx_image->bit_per_pixel), &(mlx_image->size_line), \
		&(mlx_image->endian));
	return (mlx_image);
}



int main(const argc, const char **argv) {
	if (argc != 2) {
		fprintf(stderr , "usage: %s xpm_file\n", argv[0]);
		exit(1);
	}

	void *mlx_ptr = mlx_init();
	void *window = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "xpm viewer");
	t_texture *texture_struct = new_texture(mlx_ptr, argv[1]);

	int mag = min(WINDOW_WIDTH, WINDOW_HEIGHT) / max(texture_struct->width, texture_struct->height);
	t_mlx_image *image = new_image_struct_only_mlxptr(mlx_ptr, texture_struct->width * mag, texture_struct->height * mag);
	fprintf(stderr, "mag : '%d'\n", mag);
	fprintf(stderr, "texture_struct->height : '%zu'\n", texture_struct->height);
	fprintf(stderr, "texture_struct->width : '%zu'\n", texture_struct->width);
	for (size_t i = 0; i < texture_struct->height * mag; i++) {
		for (size_t j = 0; j < texture_struct->width * mag; j++) {
			put_pixel_to_mlx_image(image, j, i, convert_color_to_int(texture_struct->pixel_color[i / mag][j / mag]));
		}		
	}
	t_mlx_image *back_ground = new_image_struct_only_mlxptr(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	for (size_t i = 0; i < WINDOW_HEIGHT; i++) {
		for (size_t j = 0; j < WINDOW_WIDTH; j++) {
			if (((i / 10 % 2) ^ (j / 10 % 2))) {
				put_pixel_to_mlx_image(back_ground, j, i, 0xffffff);
			} else {
				put_pixel_to_mlx_image(back_ground, j, i, 0xd0d0d0);
			}
		}		
	}
	
	int x, y;
	t_mlx_image *def = get_image_from_xpm_file(mlx_ptr, argv[1]);
	mlx_put_image_to_window(mlx_ptr, window, back_ground->image_ptr, 0, 0);
	mlx_put_image_to_window(mlx_ptr, window, image->image_ptr, 0, 0);
	mlx_put_image_to_window(mlx_ptr, window, def->image_ptr, WINDOW_HEIGHT, 0);


	mlx_loop(mlx_ptr);
}
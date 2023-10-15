#include <stdio.h>
#include <unistd.h>

#include "../minilibx-linux/mlx.h"

int main() {
	void *mlx = mlx_init();
	void *window = mlx_new_window(mlx, 200, 200, "xpm");
	int x, y;
	mlx_xpm_file_to_image(mlx, "xpm1.xpm", &x, &y);
	fprintf(stderr, "xpm1.xpm\n");
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
	mlx_xpm_file_to_image(mlx, "xpm2.xpm", &x, &y);
	fprintf(stderr, "xpm2.xpm\n");
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
	mlx_xpm_file_to_image(mlx, "xpm3.xpm", &x, &y);
	fprintf(stderr, "xpm3.xpm\n");
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
}
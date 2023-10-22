#include <stdio.h>
#include <unistd.h>

#include "../minilibx-linux/mlx.h"

int main(const int argc, const char **argv) {
	void *mlx = mlx_init();
	void *window = mlx_new_window(mlx, 200, 200, "xpm");
	int x, y;
#ifdef TEMPLATE
	/*
	fprintf(stderr, "xpm1.xpm\n");
	printf("%p\n", mlx_xpm_file_to_image(mlx, "xpm1.xpm", &x, &y));
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
	fprintf(stderr, "xpm2.xpm\n");
	printf("%p\n", mlx_xpm_file_to_image(mlx, "xpm2.xpm", &x, &y));
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
	fprintf(stderr, "xpm3.xpm\n");
	printf("%p\n", mlx_xpm_file_to_image(mlx, "xpm3.xpm", &x, &y));
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	sleep(3);
	// */
#else 
	if (argc != 2) {
		return 0;
	}
	const char *filename = argv[1];
	fprintf(stderr, "%s\n", filename);
	void *image = mlx_xpm_file_to_image(mlx, (char *)(filename), &x, &y);
	fprintf(stderr, "%p\n", image);
	fprintf(stderr, "x : '%d'\n", x);
	fprintf(stderr, "y : '%d'\n", y);
	if (image == NULL) {
		return 1;
	}
	int bps, size_line, endian;
	char *data = mlx_get_data_addr(image, &bps, &size_line, &endian);
	mlx_put_image_to_window(mlx, window, image, 10, 10);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			unsigned int value = *(int *)(data + (i * size_line + sizeof(int) * j));
			// fprintf(stderr, "'%08x' ", value);
			char c = (value == 0 ? '.' : 'x');
			fprintf(stderr, "%c", c);
		}
		fprintf(stderr, "\n");
	}
	char c;
	read(STDIN_FILENO, &c, 1);
#endif
}
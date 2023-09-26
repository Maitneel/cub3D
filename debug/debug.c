#include <stdio.h>

#include "cub3d_structs.h"
#include "debug.h"

void print_color(t_color *color) {
	fprintf(stderr, "color : [%3d, %3d, %3d]\n", color->red, color->green, color->blue);
}

void print_cub3d(t_cub3d *cub3d) {
	debug_string(cub3d->graphic_info->north_texture->file_name);
	debug_string(cub3d->graphic_info->south_texture->file_name);
	debug_string(cub3d->graphic_info->west_texture->file_name);
	debug_string(cub3d->graphic_info->east_texture->file_name);
	fprintf(stderr, "\n");
	fprintf(stderr, "cub3d->graphic_info->floor_color ");
	print_color(cub3d->graphic_info->floor_color);
	fprintf(stderr, "cub3d->graphic_info->ceiling_color ");
	print_color(cub3d->graphic_info->ceiling_color);
}
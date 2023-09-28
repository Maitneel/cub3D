#include <stdio.h>
#include <math.h>

#include "cub3d_structs.h"
#include "debug.h"
#include "ansi_escape_code.h"

void print_color(t_color *color) {
	fprintf(stderr, "color : [%3d, %3d, %3d]\n", color->red, color->green, color->blue);
}

void print_map(t_map_element **map) {
	for (size_t i = 0; map[i] != NULL; i++)
	{
		for (size_t j = 0; map[i][j] != END_OF_LINE; j++)
		{
			if (map[i][j] == WALL) {
				fprintf(stderr, "%s", B_BRIGHT_WHIT);
			} else if (map[i][j] == EMPTY) {
				fprintf(stderr, "%s", B_CYAN);
			} else if (map[i][j] != OUT_OF_MAP) {
				fprintf(stderr, "%s", B_RED);
			}
			fprintf(stderr, " %s", RESET_COLOR);
		}
		fprintf(stderr, "\n");
	}
}

void print_player(t_player player) {
	fprintf(stderr, "player position  : [%f, %f]\n", player.point.x, player.point.y);
	fprintf(stderr, "player direction : %d\n", (int)(round(player.direction / (2 * M_PI) * 360)));
}

void print_cub3d(t_cub3d *cub3d) {
	if (cub3d == NULL) {
		fprintf(stderr, "cub3d is NULL\n");
		return;
	}
	if (cub3d->graphic_info == NULL) {
		fprintf(stderr, "cub3d->graphic_info is NULL\n");
	}
	debug_string(cub3d->graphic_info->north_texture->file_name);
	debug_string(cub3d->graphic_info->south_texture->file_name);
	debug_string(cub3d->graphic_info->west_texture->file_name);
	debug_string(cub3d->graphic_info->east_texture->file_name);
	fprintf(stderr, "-------------------------------------------------\n");
	fprintf(stderr, "cub3d->graphic_info->floor_color ");
	print_color(cub3d->graphic_info->floor_color);
	fprintf(stderr, "cub3d->graphic_info->ceiling_color ");
	print_color(cub3d->graphic_info->ceiling_color);
	fprintf(stderr, "-------------------------------------------------\n");
	print_player(cub3d->player);
	print_map(cub3d->map);
}
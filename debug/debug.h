#ifndef DEBUG_H
# define DEBUG_H

#include <stdio.h>

#define debug_string(ARG) fprintf(stderr, "%s : '%s'\n", #ARG, ARG);
#define debug_int(ARG) fprintf(stderr, "%s : '%d'\n", #ARG, ARG);

void print_color(t_color *color);
void print_cub3d(t_cub3d *cub3d);
void print_player(t_player player);
void print_map(t_map_element **map);

void print_key_code(int key_code);

#endif
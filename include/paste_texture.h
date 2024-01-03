#ifndef PASTE_TEXTURE_H
# define PASTE_TEXTURE_H

#include "cub3d_structs.h"

void paste_texture(t_cub3d *cub3d, t_mlx_image *image, const double magnification, const double texture_position, const t_texture *texture, size_t image_x);

#endif
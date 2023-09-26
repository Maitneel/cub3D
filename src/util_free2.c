#include <stdlib.h>

#include "cub3d_structs.h"
#include "free_lib.h"

void	free_cub3d(t_cub3d *cub3d)
{
	free_graphic_info(cub3d->graphic_info);
	free_map(cub3d->map);
	free(cub3d);
}
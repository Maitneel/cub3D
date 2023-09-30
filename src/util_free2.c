#include <stdlib.h>
#include "mlx.h"

#include "cub3d_structs.h"
#include "free_lib.h"

void	free_cub3d(t_cub3d *cub3d)
{
	free_graphic_info(cub3d->graphic_info);
	free_map(cub3d->map);
	free(cub3d);
}

void	free_mlx_struct(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	// TODO
}

void	free_mlx_hook_arg(t_mlx_hook_arg *mlx_hook_arg)
{
	if (mlx_hook_arg == NULL)
		return ;
	free_mlx_struct(mlx_hook_arg->mlx);
	free_cub3d(mlx_hook_arg->cub3d);
	free(mlx_hook_arg);
	return ;
}

void	free_and_detroy_mlx_image(t_mlx_image *image, const t_mlx *mlx)
{
	if (image == NULL)
		return ;
	mlx_destroy_image(mlx->mlx, image->image_ptr);
	free(image);
}

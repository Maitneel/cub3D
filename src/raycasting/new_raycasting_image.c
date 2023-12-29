#include "cub3d_structs.h"
#include "mlx_image_proc.h"

t_mlx_image	*new_raycasting_image(
	const t_cub3d *cub3d, const t_mlx *mlx, const int width, const int height)
{
    t_mlx_image		*image;

    image = new_image_struct(mlx, width, height);
    for (int i=0;i<10;i++)
        put_pixel_to_mlx_image(image, i, 1, 0xffffff);
    return (image);
}

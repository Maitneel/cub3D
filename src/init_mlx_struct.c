#include "cub3d_structs.h"
#include "mlx.h"
#include "util_lib.h"
#include "free_lib.h"

t_mlx	*init_mlx_struct(char *title)
{
	t_mlx	*mlx;

	mlx = ft_xcalloc(1, sizeof(t_mlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		free_mlx_struct(mlx);
		return (NULL);
	}
	mlx->window = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	if (mlx->window == NULL)
	{
		free_mlx_struct(mlx);
		return (NULL);
	}
	return (mlx);
}

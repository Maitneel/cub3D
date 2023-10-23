#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# define IMAGE_SIZE 100

#include "stddef.h"

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct s_texture
{
	char			*file_name;
	size_t			height;
	size_t			width;
	t_color			**pixel_color;
}					t_texture;

typedef struct s_color_index_pair
{
	char			*key;
	t_color			color;
}					t_color_index_pair;

typedef struct s_graphic_info
{
	t_texture		*north_texture;
	t_texture		*south_texture;
	t_texture		*west_texture;
	t_texture		*east_texture;

	t_color			*floor_color;
	t_color			*ceiling_color;
}					t_graphic_info;

typedef struct s_point
{
	double			y;
	double			x;
}					t_point;

typedef struct s_player
{
	t_point			point;
	double			direction; // 0 ~ 2π
}					t_player;

typedef enum e_map_element
{
	OUT_OF_MAP = 0,
	EMPTY,
	WALL,
	START_N,
	START_S,
	START_E,
	START_W,
	END_OF_LINE,
	INCORRECTED_MAP_ELEMENT,
}		t_map_element;

typedef struct s_cub3d
{
	t_map_element	**map;
	int				map_width;
	int				map_height;
	t_graphic_info	*graphic_info;
	t_player		player;
}					t_cub3d;

typedef struct s_mlx_image
{
	void		*image_ptr;
	int			width;
	int			height;

	char		*data_addr;
	int			bit_per_pixel;
	int			size_line;
	int			endian;

	int			x_coord_to_put_image;
	int			y_coord_to_put_image;
}				t_mlx_image;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	t_mlx_image		*image[IMAGE_SIZE];
}					t_mlx;

typedef struct s_mlx_hook_arg
{
	t_mlx			*mlx;
	t_cub3d			*cub3d;
}				t_mlx_hook_arg;

t_cub3d				*init_cub3d(const char *filename);
t_mlx				*init_mlx_struct(char *title);

#endif

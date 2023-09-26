#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

typedef struct s_texture
{
	char			*file_name;
	// TODO;
}					t_texture;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

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
	double direction; // 0 ~ 2π
}					t_player;

typedef enum e_map_element
{
	OUT_OF_MAP = 0,
	EMPTY,
	WALL,
	START_N,
	START_S,
	START_W,
	START_E,
}		t_map_element;

typedef struct s_cub3d
{
	t_map_element	**map;
	t_graphic_info	*graphic_info;
	t_player		player;
}					t_cub3d;

t_cub3d				*init_cub3d(const char *filename);

#endif

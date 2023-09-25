#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

typedef struct s_texture
{
	void *north_texture;
	void *south_texture;
	void *west_texture;
	void *east_texture;

	int floor_color[3];
	int ceiling_color[3];
}	t_texture;

typedef struct s_point
{
	double	y;
	double	x;
}	t_point;

typedef struct s_player
{
	t_point	point;
	double direction; // 0 ~ 2π
}	t_player;


typedef struct s_cub3d {
	int 		**map;
	t_texture	*texture;
	t_player	player;
}	t_cub3d;

t_cub3d	*init_cub3d(const char *filename);

#endif

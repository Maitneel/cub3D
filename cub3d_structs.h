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

typedef struct s_cub3d {
	int 		**map;
	t_texture	*texture;
}	t_cub3d;

#endif

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# define IMAGE_SIZE 100
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define PLAYER_MAGFICATION 100000
# define HN_FOV_ANGLE (90 * M_PI / 180)
# define WALL_HEIGHT (PLAYER_MAGFICATION / 10)
# define VERT_FOV_ANGLE (10 * M_PI / 180)
# define SCREEN_MAGFICATION 100000
# define MINIMAP_OUT_OF_MAP_COLOR 0x80000000
# define MINIMAP_EMPYT_COLOR 0x80ffffff
# define MINIMAP_WALL_COLOR 0x80303030
# define MINIMAP_FILED_OF_VIEW_COLOR 0x80ff0000

# include "stddef.h"
# include <stdbool.h>

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
	long long		y;
	long long		x;
}					t_point;

typedef struct s_coll_point
{
	t_point			pt;
	bool			is_vert;
}					t_coll_point;

typedef struct s_player
{
	t_point			point;
	double			direction;
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
}					t_map_element;

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
	void			*image_ptr;
	int				width;
	int				height;

	char			*data_addr;
	int				bit_per_pixel;
	int				size_line;
	int				endian;

	int				x_coord_to_put_image;
	int				y_coord_to_put_image;
}					t_mlx_image;

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
}					t_mlx_hook_arg;

typedef struct s_paste_texture_info
{
	double			mag;
	double			texture_pos;
	size_t			image_x;
}					t_paste_texture_info;

t_cub3d				*init_cub3d(const void *mlx_ptr, const char *filename);
t_mlx				*init_mlx_struct(char *title);

t_point				*new_point(int y, int x);
t_point				new_point_struct(const int y, const int x);
t_coll_point		new_coll_pt_struct(const t_point pt, const bool is_vert);

// get_graphic_info
bool				is_graphic_info_element_filled(
						const t_graphic_info *graphic_info);
bool				is_texture_line(const char *line);
bool				is_color_line(const char *line);
bool				is_correct_texture_format(const char *line);
bool				is_within_0_to_255(const char *front);
bool				is_correct_color_format(const char *line);
bool				is_correct_format(const char *line);
bool				is_texture_empty(const t_graphic_info *graphic_info,
						const char identifier);
bool				is_color_empty(const t_graphic_info *graphic_info,
						const char identifier);
bool				is_element_empyt(const t_graphic_info *graphic_info,
						const char *line);
char				*get_texture_file_name(const char *line);
t_mlx_image			*get_image_from_xpm_file(const void *mlx_ptr,
						const char *file_name);
int					data_addr_to_int(const unsigned char *data_addr,
						int byte_per_pixel);
t_color				convert_data_addr_to_color_struct(const char *data_addr,
						const int byte_per_pixel);
t_texture			*convert_image_to_texture(const t_mlx_image *image,
						t_texture *texture);
t_texture			*new_texture(const void *mlx_ptr, const char *file_name);
void				set_texture(const void *mlx_ptr,
						t_graphic_info *graphic_info, const char *line);
t_color				*new_color(const char *line);
void				set_color(t_graphic_info *graphic_info, const char *line);
void				set_to_appropriate_element(const void *mlx_ptr,
						t_graphic_info *graphic_info,
						const char *line);
t_graphic_info		*get_graphic_info(const void *mlx_ptr, const int fd);

// get_map

char				**read_map(const int fd);
size_t				get_max_length(const char **map);
t_map_element		get_element_type(const char c);
t_map_element		*convert_line_to_map_element(const char *line,
						const size_t width);
t_map_element		**convert_to_map_element(const char **char_map);
t_map_element		**get_map(const int fd_of_move_to_end_of_graphic_info);

// minimap
t_map_element		get_map_element_type(const t_cub3d *cub3d, const int x,
						const int y);
int					get_minimap_color(t_map_element type);
void				put_player_position(t_mlx_image *minimap);
unsigned int		**get_default_color_map(const t_cub3d *cub3d,
						const int width,
						const int height);
bool				is_lay_end(unsigned int type);
void				put_line(unsigned int **color_map, const int height,
						const int width, const double direction);
void				coloring_filed_of_view(const t_cub3d *cub3d,
						unsigned int **color_map,
						const int height,
						const int width);
void				put_to_image_from_int_array(t_mlx_image *image,
						unsigned int **color_map);
t_mlx_image			*new_minimap(const t_cub3d *cub3d, const t_mlx *mlx,
						const int width, const int height);

#endif

#include <stdlib.h>
#include "cub3d_structs.h"

void	free_string_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_texture(t_texture *texture)
{
	if (texture == NULL)
		return ;
	free(texture->file_name);
	free(texture);
}

void	free_color(t_color *color)
{
	free(color);
}

void	free_graphic_info(t_graphic_info *graphic_info)
{
	if (graphic_info == NULL)
		return ;
	free_texture(graphic_info->north_texture);
	free_texture(graphic_info->south_texture);
	free_texture(graphic_info->west_texture);
	free_texture(graphic_info->east_texture);
	free_color(graphic_info->floor_color);
	free_color(graphic_info->ceiling_color);
	free(graphic_info);
}

void	free_map(t_map_element **map)
{
	size_t	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

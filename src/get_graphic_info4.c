/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_graphic_info4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:11 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:11 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "free_lib.h"
#include "get_next_line.h"
#include "get_xpm_data.h"
#include "libft.h"
#include "mlx.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

t_texture	*new_texture(const void *mlx_ptr, const char *file_name)
{
	t_texture	*texture;
	t_mlx_image	*image;

	texture = ft_xcalloc(1, sizeof(t_texture));
	texture->file_name = ft_strdup(file_name);
	if (texture->file_name == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	image = get_image_from_xpm_file(mlx_ptr, file_name);
	texture = convert_image_to_texture(image, texture);
	mlx_destroy_image((void *)(mlx_ptr), image->image_ptr);
	free(image);
	return (texture);
}

void	set_texture(const void *mlx_ptr, t_graphic_info *graphic_info,
		const char *line)
{
	char		*file_name;
	const char	identifier = line[0];

	file_name = get_texture_file_name(line);
	if (identifier == 'N')
		graphic_info->north_texture = new_texture(mlx_ptr, file_name);
	else if (identifier == 'S')
		graphic_info->south_texture = new_texture(mlx_ptr, file_name);
	else if (identifier == 'W')
		graphic_info->west_texture = new_texture(mlx_ptr, file_name);
	else if (identifier == 'E')
		graphic_info->east_texture = new_texture(mlx_ptr, file_name);
	free(file_name);
}

t_color	*new_color(const char *line)
{
	size_t	i;
	size_t	line_index;
	t_color	*color;

	color = ft_xcalloc(1, sizeof(t_color));
	i = 0;
	line_index = 0;
	while (i < 3)
	{
		while (!ft_isdigit(line[line_index]))
			line_index++;
		if (i == 0)
			color->red = ft_atoi(&line[line_index]);
		else if (i == 1)
			color->green = ft_atoi(&line[line_index]);
		else if (i == 2)
			color->blue = ft_atoi(&line[line_index]);
		while (ft_isdigit(line[line_index]))
			line_index++;
		i++;
	}
	return (color);
}

void	set_color(t_graphic_info *graphic_info, const char *line)
{
	const char	identifier = line[0];

	if (identifier == 'F')
		graphic_info->floor_color = new_color(line);
	else if (identifier == 'C')
		graphic_info->ceiling_color = new_color(line);
}

void	set_to_appropriate_element(const void *mlx_ptr,
		t_graphic_info *graphic_info, const char *line)
{
	if (is_texture_line(line))
	{
		set_texture(mlx_ptr, graphic_info, line);
	}
	else if (is_color_line(line))
	{
		set_color(graphic_info, line);
	}
}

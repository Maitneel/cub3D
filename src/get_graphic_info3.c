/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_graphic_info3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:08 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:09 by taksaito         ###   ########.fr       */
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

char	*get_texture_file_name(const char *line)
{
	char	*file_name;
	size_t	file_name_start_index;
	size_t	i;

	file_name_start_index = 2;
	while (ft_isspace(line[file_name_start_index]))
		file_name_start_index++;
	file_name = ft_strdup(&line[file_name_start_index]);
	if (file_name == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	i = 0;
	while (!ft_isspace(file_name[i]) && file_name[i] != '\0')
		i++;
	file_name[i] = '\0';
	return (file_name);
}

t_mlx_image	*get_image_from_xpm_file(const void *mlx_ptr, const char *file_name)
{
	t_mlx_image	*image;

	image = ft_xcalloc(1, sizeof(t_mlx_image));
	image->image_ptr = mlx_xpm_file_to_image((void *)(mlx_ptr),
			(char *)(file_name), &(image->width), &(image->height));
	if (image->image_ptr == NULL)
	{
		print_error(false, "mlx_xpm_file_to_image: ");
		print_error(false, file_name);
		print_error(false, ": failed\n");
		exit(1);
	}
	image->data_addr = mlx_get_data_addr(image->image_ptr,
			&(image->bit_per_pixel), &(image->size_line), &(image->endian));
	return (image);
}

int	data_addr_to_int(const unsigned char *data_addr, int byte_per_pixel)
{
	int	int_value;
	int	i;

	int_value = 0;
	i = 0;
	while (i < byte_per_pixel / 4)
	{
		int_value *= UCHAR_MAX;
		int_value += data_addr[i];
		i++;
	}
	return (int_value);
}

t_color	convert_data_addr_to_color_struct(const char *data_addr,
		const int byte_per_pixel)
{
	t_color	color;

	color.red = data_addr_to_int((const unsigned char *)
			(data_addr + (byte_per_pixel / 4 * 2)), byte_per_pixel);
	color.green = data_addr_to_int((const unsigned char *)
			(data_addr + (byte_per_pixel / 4 * 1)), byte_per_pixel);
	color.blue = data_addr_to_int((const unsigned char *)
			(data_addr + (byte_per_pixel / 4 * 0)), byte_per_pixel);
	return (color);
}

t_texture	*convert_image_to_texture(const t_mlx_image *image,
		t_texture *texture)
{
	size_t			i;
	size_t			j;
	const size_t	byte_per_pixel = image->bit_per_pixel / CHAR_BIT;

	texture->height = image->height;
	texture->width = image->width;
	texture->pixel_color = ft_xcalloc(texture->height, sizeof(t_texture *));
	i = 0;
	while (i < texture->height)
	{
		texture->pixel_color[i] = ft_xcalloc(texture->width, sizeof(t_texture));
		j = 0;
		while (j < texture->width)
		{
			texture->pixel_color[i][j] = convert_data_addr_to_color_struct(
					image->data_addr + (i * image->width * byte_per_pixel + (j
							* byte_per_pixel)), byte_per_pixel);
			j++;
		}
		i++;
	}
	return (texture);
}

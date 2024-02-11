/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xpm_pixel_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:06:27 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:06:28 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "get_xpm_data.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdlib.h>

t_color_index_pair	*get_color_map(const char **file_content)
{
	const size_t		char_per_pixel = get_xpm_char_per_pixel(file_content);
	const size_t		number_of_color = get_xpm_number_of_color(file_content);
	t_color_index_pair	*color_index;
	size_t				i;

	color_index = ft_xcalloc(number_of_color + 1, sizeof(t_color_index_pair));
	i = 0;
	while (i < number_of_color)
	{
		color_index[i] = get_color_index_pair(file_content[i + 1],
				char_per_pixel);
		i++;
	}
	return (color_index);
}

t_color	**get_xpm_pixel_color(const char **file_content, const size_t height,
		const size_t width)
{
	t_color				**pixel_color;
	t_color_index_pair	*color_map;
	size_t				i;
	size_t				front_of_pixel_info;
	size_t				char_per_pixel;

	front_of_pixel_info = get_xpm_number_of_color(file_content) + 1;
	pixel_color = ft_xcalloc(height + 1, sizeof(t_color *));
	color_map = get_color_map(file_content);
	char_per_pixel = get_xpm_char_per_pixel(file_content);
	i = 0;
	while (i < height && file_content[front_of_pixel_info + i] != NULL)
	{
		pixel_color[i] = get_row_of_pixel_color(file_content[front_of_pixel_info
				+ i], color_map, width, char_per_pixel);
		i++;
	}
	if (i != height || file_content[front_of_pixel_info + i] != NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(1); // eixt していい? //
	}
	free(color_map);
	return (pixel_color);
}

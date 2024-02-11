/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_index_pair.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:04:39 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:04:40 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "cub3d_structs.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"

int	get_hex_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	else if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	else
		return (-1);
}

int	convert_2digit_hex(const char *line)
{
	if (line[0] == '\0' || line[1] == '\0')
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	return (get_hex_value(line[0]) * 16 + get_hex_value(line[1]));
}

t_color	get_color_visual(const char *line)
{
	t_color	color;
	char	*front;

	front = (char *)(line);
	while (ft_isspace(*front) && *front != '\0')
		front++;
	if (*front != '#')
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	front++;
	color.red = convert_2digit_hex(front + 0);
	color.green = convert_2digit_hex(front + 2);
	color.blue = convert_2digit_hex(front + 4);
	return (color);
}

t_color	get_xpm_color_value(const char *line)
{
	t_color	value;
	char	*front;

	front = (char *)(line);
	while ((ft_isspace(*front) && *front != '\0'))
		front++;
	if (*front == '\0')
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	if (*front == 'c')
		value = get_color_visual(front + 1);
	else if (*front == 'm' || *front == 's' || *front == 'g')
	{
		print_error(false, "not support xpm fromat\n");
		exit(2);
	}
	else
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	return (value);
}

t_color_index_pair	get_color_index_pair(const char *line,
		const size_t char_per_pixel)
{
	t_color_index_pair	pair;
	size_t				line_len;

	if (line == NULL)
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	line_len = ft_strlen(line);
	if (line_len < char_per_pixel + 2)
	{
		print_error(false, "invalid xpm fromat\n");
		exit(1);
	}
	pair.key = ft_strdup(&line[1]);
	if (pair.key == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	pair.key[char_per_pixel] = '\0';
	pair.color = get_xpm_color_value(line + 1 + char_per_pixel);
	return (pair);
}

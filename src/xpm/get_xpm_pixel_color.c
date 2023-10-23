#include "cub3d_structs.h"
#include "get_xpm_data.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdlib.h>


#include <stdio.h>

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
	while (ft_isspace(*line) && *line != '\0')
		front++;
	if (*line != '#')
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

t_color_index_pair	*get_color_map(const char **file_content)
{
	const size_t		char_per_pixel= get_xpm_char_per_pixel(file_content);
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

t_color	*get_row_of_pixel_color(const char *line,
								const t_color_index_pair *color_map,
								const size_t height, const size_t width)
{
	size_t i;

	i = 0;
	while (i < height) {
		fprintf(stderr, "'%s' 0x%2X%2X%2X\n", color_map[i].key, color_map[i].color.red, color_map[i].color.green, color_map[i].color.blue);
		i++;
	}
}

t_color	**get_xpm_pixel_color(const char **file_content, const size_t height,
		const size_t width)
{
	t_color				**pixel_color;
	t_color_index_pair	*color_map;
	size_t				i;
	size_t				front_of_pixel_info;

printf("end1\n");
	front_of_pixel_info = get_xpm_number_of_color(file_content) + 1;
	pixel_color = ft_xcalloc(height + 1, sizeof(t_color *));
	color_map = get_color_map(file_content);
	i = 0;
	printf("end1\n");
	while (i < height && file_content[front_of_pixel_info + i] != NULL)
	{
		pixel_color[i] = get_row_of_pixel_color(file_content[front_of_pixel_info
				+ i], color_map, height, width);
		i++;
	}
	printf("end2\n");
	if (i != height || file_content[front_of_pixel_info + i] != NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(1); // eixt していい? //
	}
	free(color_map);
	return (pixel_color);
}

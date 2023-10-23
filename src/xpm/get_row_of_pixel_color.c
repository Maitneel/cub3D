#include "cub3d_structs.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include <stdio.h>

bool	is_include_null_in_len(const char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\0')
			return (true);
		i++;
	}
	return (false);
}

char	*get_key(const char *str, const size_t char_per_pixel)
{
	char	*key;
	size_t	i;

	key = ft_xcalloc(char_per_pixel, sizeof(char));
	i = 0;
	while (i < char_per_pixel)
	{
		key[i] = str[i];
		i++;
	}
	return (key);
}

t_color	find_color_pair(const t_color_index_pair *color_map, const char *line,
		const size_t char_per_pixel)
{
	char	*key;
	t_color	value;
	size_t	i;

	key = get_key(line, char_per_pixel);
	i = 0;
	while (color_map[i].key != NULL)
	{
		if (ft_strncmp(key, color_map[i].key, SIZE_T_MAX) == 0)
		{
			value = color_map[i].color;
			break ;
		}
		i++;
	}
	free(key);
	if (color_map[i].key == NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	return (value);
}

t_color	*get_row_of_pixel_color(const char *line,
								const t_color_index_pair *color_map,
								const size_t width,
								const size_t char_per_pixel)
{
	t_color	*color_array;
	char	*front;
	size_t	i;
	bool	is_continue;

	front = (char *)(line + 1);
	if (line == NULL || line[0] == '\0' || *front == '\0')
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	color_array = ft_xcalloc(width + 1, sizeof(t_color));
	is_continue = !is_include_null_in_len(front, char_per_pixel);
	i = 0;
	while (i < width && is_continue)
	{
		color_array[i] = find_color_pair(color_map, front, char_per_pixel);
		front += char_per_pixel;
		is_continue = !is_include_null_in_len(front, char_per_pixel);
		i++;
	}
	/*
	i = 0;
	while (i < width)
	{
		printf("%02X%02X%02X ", color_array[i].red, color_array[i].green,
				color_array[i].blue);
		i++;
	}
	printf("\n");
	// */
	return (color_array);
}

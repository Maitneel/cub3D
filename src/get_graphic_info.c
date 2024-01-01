#include "mlx.h"
#include "cub3d_structs.h"
#include "get_next_line.h"
#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"
#include "free_lib.h"
#include "get_xpm_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static bool	is_graphic_info_element_filled(const t_graphic_info *graphic_info)
{
	return (
		graphic_info->north_texture != NULL && \
		graphic_info->south_texture != NULL && \
		graphic_info->west_texture != NULL && \
		graphic_info->east_texture != NULL && \
		graphic_info->floor_color != NULL && \
		graphic_info->ceiling_color != NULL
	);
}

static bool	is_texture_line(const char *line)
{
	const char		*texture_identifier[4] = {"NO ", "SO ", "WE ", "EA "};
	const size_t	texture_identifier_size = 4;
	size_t			i;

	i = 0;
	while (i < texture_identifier_size)
	{
		if (ft_strncmp(line, texture_identifier[i], 3) == 0)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_color_line(const char *line)
{
	const char		*texture_identifier[2] = {"F ", "C "};
	const size_t	texture_identifier_size = 2;
	size_t			i;

	i = 0;
	while (i < texture_identifier_size)
	{
		if (ft_strncmp(line, texture_identifier[i], 2) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_correct_texture_format(const char *line)
{
	size_t	i;

	i = 3;
	while (ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (false);
	while (ft_isascii(line[i]) && !ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (false);
	while (ft_isspace(line[i]) && line[i] != '\0')
		i++;
	if (line[i] != '\0')
		return (false);
	return (true);
}

bool	is_within_0_to_255(const char *front)
{
	size_t	i;
	int		converted;

	converted = 0;
	i = 0;
	while (ft_isdigit(front[i]) && converted < 256)
	{
		converted *= 10;
		converted += front[i] - '0';
		i++;
	}
	if (converted < 256)
		return (true);
	return (false);
}

bool	is_correct_color_format(const char *line)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 2;
	while (j < 3)
	{
		while (ft_isspace(line[i]) && line[i] != '\0')
			i++;
		if (!ft_isdigit(line[i]) || !is_within_0_to_255(&line[i]))
			return (false);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == '\0')
			return (false);
		while (ft_isspace(line[i]) && line[i] != '\0')
			i++;
		if (line[i] != ',' && j != 2)
			return (false);
		i++;
		j++;
	}
	if (line[i - 1] != '\0')
		return (false);
	return (true);
}

static bool	is_correct_format(const char *line)
{
	size_t	i;

	if (line == NULL)
		return (false);
	if (line[0] == '\n')
		return (true);
	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (is_texture_line(&line[i]))
		return (is_correct_texture_format(&line[i]));
	if (is_color_line(&line[i]))
		return (is_correct_color_format(&line[i]));
	else
		return (false);
}

static bool	is_texture_empty(
	const t_graphic_info *graphic_info, const char identifier)
{
	t_texture	*target;

	if (identifier == 'N')
		target = graphic_info->north_texture;
	else if (identifier == 'S')
		target = graphic_info->south_texture;
	else if (identifier == 'W')
		target = graphic_info->west_texture;
	else if (identifier == 'E')
		target = graphic_info->east_texture;
	else
		return (false);
	if (target == NULL)
		return (true);
	else
		return (false);
}

static bool	is_color_empty(
	const t_graphic_info *graphic_info, const char identifier)
{
	t_color	*target;

	if (identifier == 'F')
		target = graphic_info->floor_color;
	else if (identifier == 'C')
		target = graphic_info->ceiling_color;
	else
		return (false);
	if (target == NULL)
		return (true);
	else
		return (false);
}

// なんかいい感じの関数名が思いつかない //
static bool	is_element_empyt(
	const t_graphic_info *graphic_info,
	const char *line
)
{
	if (line[0] == '\n')
		return (true);
	else if (is_texture_line(line))
		return (is_texture_empty(graphic_info, line[0]));
	else if (is_color_line(line))
		return (is_color_empty(graphic_info, line[0]));
	else
		return (false);
}

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

t_mlx_image *get_image_from_xpm_file(const void *mlx_ptr, const char *file_name) 
{
	t_mlx_image *image;
	char *error_massage;

	image = ft_xcalloc(1, sizeof(t_mlx_image));
	fprintf(stderr, "image->height : '%d'\n", image->height);
	fprintf(stderr, "image->width : '%d'\n", image->width);
	fprintf(stderr, "file_name : '%s'\n", file_name);
	image->image_ptr = mlx_xpm_file_to_image(mlx_ptr, file_name, &(image->width), &(image->height));
	fprintf(stderr, "image->height : '%d'\n", image->height);
	fprintf(stderr, "image->width : '%d'\n", image->width);
	if (image->image_ptr == NULL)
	{
		print_error(false, "mlx_xpm_file_to_image: ");
		print_error(false, file_name);
		print_error(false, ": failed\n");
		exit(1);
	}
	image->data_addr = mlx_get_data_addr(image->image_ptr, &(image->bit_per_pixel), &(image->size_line), &(image->endian));
	return (image);
}

int data_addr_to_int(const unsigned char *data_addr, int byte_per_pixel)
{
	int		int_value;
	size_t 	i;

	int_value = 0;
	i = 0;
	while (i < byte_per_pixel / 4)
	{
		int_value *= UCHAR_MAX;
 		int_value += data_addr[i];
		// fprintf(stderr, "i : '%d' ", i);
		fprintf(stderr, "%02x", data_addr[i]);
		i++;
	}
	// fprintf(stderr, "iv : '%u' ", int_value);
	return (int_value);
}

t_color convert_data_addr_to_color_struct(const char *data_addr, const int byte_per_pixel)
{
	t_color color;

	fprintf(stderr, "[%02x,", (unsigned char)(*(data_addr + 0)));
	fprintf(stderr, "%02x,", (unsigned char)(*(data_addr + 1)));
	fprintf(stderr, "%02x,", (unsigned char)(*(data_addr + 2)));
	fprintf(stderr, "%02x] ", (unsigned char)(*(data_addr + 4)));

	fprintf(stderr , "[");
	color.red = data_addr_to_int(data_addr + (byte_per_pixel / 4 * 0), byte_per_pixel);
	color.green = data_addr_to_int(data_addr + (byte_per_pixel / 4 * 1), byte_per_pixel);
	color.blue = data_addr_to_int(data_addr + (byte_per_pixel / 4 * 2), byte_per_pixel);
	fprintf(stderr, "]");
	return color;
}

t_texture *convert_image_to_texture(const t_mlx_image *image, t_texture *texture)
{
	size_t i;
	size_t j;

	texture->height = image->height;
	texture->width = image->width;
	fprintf(stderr, "texture->file_name : '%s'\n", texture->file_name);
	fprintf(stderr, "image->width : '%d'\n", image->width);
	fprintf(stderr, "image->height : '%d'\n", image->height);
	fprintf(stderr, "image->bit_per_pixel : '%d'\n", image->bit_per_pixel);
	texture->pixel_color = ft_xcalloc(texture->height, sizeof(t_texture *));

	i = 0;
	while (i < texture->height)
	{
		texture->pixel_color[i] = ft_xcalloc(texture->width, sizeof(t_texture));
		j = 0;
		fprintf(stderr, "i : '%2d'  ", i);
		while (j < texture->width)
		{
			unsigned int *i_ptr = image->data_addr;
			char *c_ptr = image->data_addr;
			fprintf(stderr, "[%06x : ", i_ptr[i * image->width + j]);

			// fprintf(stderr, "ptr : '%p' ", image->data_addr + (i * image->width * 4 + (j * 4 + 0)));
			// fprintf(stderr, "ptr2 : '%p'\n", &(image->data_addr[i * image->width * 4 + (j * 4 + 0)]));

			// fprintf(stderr, "[%02x,", (unsigned char)(image->data_addr[i * image->width * 4 + (j * 4 + 0)]));
			// fprintf(stderr, "%02x,", (unsigned char)(image->data_addr[i * image->width * 4 + (j * 4 + 1)]));
			// fprintf(stderr, "%02x,", (unsigned char)(image->data_addr[i * image->width * 4 + (j * 4 + 2)]));
			// fprintf(stderr, "%02x,] ", (unsigned char)(image->data_addr[i * image->width * 4 + (j * 4 + 3)]));

			// fprintf(stderr, "i_ptr : '%p' ", i_ptr[i * image->width + j]);
			// fprintf(stderr, "c_ptr : '%06x']  ", (unsigned int *)(image->data_addr)[(image->bit_per_pixel)]);
			// fprintf(stderr, "c_ptr : '%06x']  ", (unsigned int *)(image->data_addr)[i * image->width + j]);

			// texture->pixel_color[i][j] = convert_data_addr_to_color_struct(&image->data_addr[(image->bit_per_pixel / CHAR_BIT) * (image->width * i + j)], image->bit_per_pixel / CHAR_BIT);
			texture->pixel_color[i][j] = convert_data_addr_to_color_struct(image->data_addr + (i * image->width * 4 + (j * 4 + 0)), image->bit_per_pixel / CHAR_BIT);
			j++;
		}
		fprintf(stderr, "\n");
		i++;
	}
	fprintf(stderr, "texture --------------------------------------------\n");
	fprintf(stderr, "texture->height : '%d'\n", texture->height);
	fprintf(stderr, "texture->width : '%d'\n", texture->width);
	for (size_t i = 0; i < texture->height; i++)
	{
		fprintf(stderr, "i : '%2d'  ", i);
		for (size_t j = 0; j < texture->width; j++)
		{
			fprintf(stderr, "[%02x, ", 	texture->pixel_color[i][j].red);
			fprintf(stderr, "%02x, ", texture->pixel_color[i][j].green);
			fprintf(stderr, "%02x", texture->pixel_color[i][j].blue);
			fprintf(stderr, "] ");

		}
		fprintf(stderr, "\n");
		
	}
	
	// exit(0);
	fprintf(stderr, "texture end-----------------------------------------\n");
	return (texture);
}

t_texture	*new_texture(void *mlx_ptr, const char *file_name)
{
	t_texture	*texture;
	t_mlx_image *image;
	char		**file_content;

	texture = ft_xcalloc(1, sizeof(t_texture));
	texture->file_name = ft_strdup(file_name);
	if (texture->file_name == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	image = get_image_from_xpm_file(mlx_ptr, file_name);
	texture = convert_image_to_texture(image, texture);
	mlx_destroy_image(mlx_ptr, image->image_ptr);
	free(image);


	// file_content = get_xpm_file_content(texture->file_name);
	// texture->height = get_xpm_height((const char **)(file_content));
	// texture->width = get_xpm_width((const char **)(file_content));
	// texture->pixel_color = get_xpm_pixel_color((const char **)(file_content), texture->height, texture->width);
	// free_string_array(file_content);
	return (texture);
}

static void	set_texture(const void *mlx_ptr, t_graphic_info *graphic_info, const char *line)
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

static t_color	*new_color(const char *line)
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

static void	set_color(t_graphic_info *graphic_info, const char *line)
{
	const char	identifier = line[0];

	if (identifier == 'F')
		graphic_info->floor_color = new_color(line);
	else if (identifier == 'C')
		graphic_info->ceiling_color = new_color(line);
}

static void	set_to_appropriate_element(const void *mlx_ptr, t_graphic_info *graphic_info,
	const char *line
)
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

t_graphic_info	*get_graphic_info(const void *mlx_ptr, const int fd)
{
	t_graphic_info	*graphic_info;
	char			*line;

	graphic_info = ft_xcalloc(1, sizeof(t_graphic_info));
	while (!is_graphic_info_element_filled(graphic_info))
	{
		line = get_next_line(fd);
		if (
			line == NULL || \
			!is_correct_format(line) || \
			!is_element_empyt(graphic_info, line)
		)
		{
			free_graphic_info(graphic_info);
			return (NULL);
		}
		set_to_appropriate_element(mlx_ptr, graphic_info, line);
		free(line);
	}
	return (graphic_info);
}

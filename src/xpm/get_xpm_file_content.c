#include <sys/fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cub3d_structs.h"
#include "get_next_line.h"
#include "print_lib.h"
#include "util_lib.h"
#include "libft.h"

#ifndef DEFAULT_XPM_FILE_CONTENT_SIZE
# define DEFAULT_XPM_FILE_CONTENT_SIZE 1024
#endif
#define MINIMUM_XPM_LINE_LENGHT 3

// check to is valid line of xpm forat
// this function defined valid format
// from double quote to double quote
// becaouse last comma was removed at before proccesing
static bool	dose_add_line(const char *line)
{
	size_t	line_len;

	if (line == NULL)
	{
		return (false);
	}
	line_len = ft_strlen(line);
	if (line_len < MINIMUM_XPM_LINE_LENGHT)
	{
		return (false);
	}
	return (line[0] == '"' && line[line_len - 1] == '"');
}

static void	remove_target_at_line_end(char *line, const char target)
{
	size_t	line_len;

	if (line == NULL)
	{
		return ;
	}
	line_len = ft_strlen(line);
	if (line_len < 1)
	{
		return ;
	}
	if (line[line_len - 1] == target)
	{
		line[line_len - 1] = '\0';
	}
}

static void	add_file_content(char **file_content, char *line,
		size_t *file_content_size, size_t *last_index)
{
	if (file_content == NULL || line == NULL)
	{
		return ;
	}
	if (last_index == file_content_size - 1)
	{
		(*file_content_size) *= 2;
		expand_str_array_memory(&file_content, *file_content_size);
	}
	file_content[*last_index] = line;
	(*last_index)++;
}

static char	**read_file_content(const int fd)
{
	char	*line;
	char	**file_content;
	size_t	file_content_size;
	size_t	last_index;

	file_content_size = DEFAULT_XPM_FILE_CONTENT_SIZE;
	file_content = ft_xcalloc(file_content_size, sizeof(char *));
	last_index = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_target_at_line_end(line, '\n');
		remove_target_at_line_end(line, ',');
		if (dose_add_line(line))
		{
			add_file_content(file_content, line, &file_content_size, \
					&last_index);
		}
		else
		{
			free(line);
		}
		line = get_next_line(fd);
	}
	return (file_content);
}

char	**get_xpm_file_content(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		**file_content;

	if (fd < 0)
	{
		print_error(true, "open");
		exit(1);
	}
	file_content = read_file_content(fd);
	close(fd);
	return (file_content);
}

/*
#include <stdio.h>
int main(const int argc, const char **argv) {
	if (argc != 2) {
		return 1;
	}
	char **file_content = get_xpm_file_content(argv[1]);
	size_t i = 0;
	while (file_content[i] != NULL)
	{
		fprintf(stderr, "%s\n", file_content[i]);
		i++;
	}
	
} 
// */
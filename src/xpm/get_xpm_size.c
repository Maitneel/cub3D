#include <stddef.h>

#include "libft.h"
#include "print_lib.h"
#include "util_lib.h"

size_t	get_xpm_height(const char **file_content)
{
	char	*front;

	front = (char *)(file_content[0]);
	if (front == NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(0);
	}
	front++;
	while (ft_isspace(*front) && *front != '\0')
		front++;
	while (ft_isdigit(*front) && *front != '\0')
		front++;
	while (ft_isspace(*front) && *front != '\0')
		front++;
	if (!ft_isdigit(*front))
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	return (ft_atoi(front));
}

size_t	get_xpm_width(const char **file_content)
{
	char	*front;

	front = (char *)(file_content[0]);
	if (front == NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	front++;
	while (ft_isspace(*front) && *front != '\0')
		front++;
	if (!ft_isdigit(*front))
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	return (ft_atoi(front));
}

size_t	get_xpm_number_of_color(const char **file_content)
{
	char	*front;
	size_t	i;

	if (file_content[0] == NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(0);
	}
	front = (char *)(file_content[0]) + 1;
	i = -1;
	while (++i < 2)
	{
		while (ft_isspace(*front) && *front != '\0')
			front++;
		while (ft_isdigit(*front) && *front != '\0')
			front++;
	}
	while (ft_isspace(*front) && *front != '\0')
		front++;
	if (!ft_isdigit(*front))
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	return (ft_atoi(front));
}

size_t	get_xpm_char_per_pixel(const char **file_content)
{
	char	*front;
	size_t	i;

	if (file_content[0] == NULL)
	{
		print_error(false, "invalid xpm format\n");
		exit(0);
	}
	front = (char *)(file_content[0]) + 1;
	i = -1;
	while (++i < 3)
	{
		while (ft_isspace(*front) && *front != '\0')
			front++;
		while (ft_isdigit(*front) && *front != '\0')
			front++;
	}
	while (ft_isspace(*front) && *front != '\0')
		front++;
	if (!ft_isdigit(*front))
	{
		print_error(false, "invalid xpm format\n");
		exit(1);
	}
	return (ft_atoi(front));
}

/*
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	char **str = malloc(sizeof(char *) * 2);
	str[0] = argv[1];

	// str[0] = NULL;
	fprintf(stderr, "get_xpm_width(argv[1]) : '%zu'\n", get_xpm_width(str));
	fprintf(stderr, "get_xpm_height(argv[1]) : '%zu'\n", get_xpm_height(str));
	fprintf(stderr, "get_xpm_number_of_color(argv[1]) : '%zu'\n", get_xpm_number_of_color(str));
	fprintf(stderr, "get_xpm_char_per_pixel(argv[1]) : '%zu'\n", get_xpm_char_per_pixel(str));
	

}
// */
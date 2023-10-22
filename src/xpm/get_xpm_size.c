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

/*
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	char **str = malloc(sizeof(char *) * 2);
	str[0] = argv[1];

	fprintf(stderr, "get_xpm_width(argv[1]) : '%zu'\n", get_xpm_width(str));
	fprintf(stderr, "get_xpm_height(argv[1]) : '%zu'\n", get_xpm_height(str));

}
// */
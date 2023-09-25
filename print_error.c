#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void	print_error(bool is_system_call_error, char *optional_massage)
{
	write(STDERR_FILENO, "Error\n", ft_strlen("Error\n"));
	if (is_system_call_error)
	{
		perror(optional_massage);
	}
	else
	{
		write(STDERR_FILENO, optional_massage, ft_strlen(optional_massage));
	}
}

#include <stdlib.h>

#include "libft.h"
#include "print_lib.h"

void	*ft_xmalloc(const size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	return (ptr);
}

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
	{
		print_error(true, "malloc");
		exit(1);
	}
	return (ptr);
}

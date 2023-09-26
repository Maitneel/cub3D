#include <stddef.h>
#include <stdlib.h>

size_t	string_array_size(const char **array)
{
	size_t	size;

	if (array == NULL)
		return (0);
	size = 0;
	while (array[size] != NULL)
	{
		size++;
	}
	return (size);
}

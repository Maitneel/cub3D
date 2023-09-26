#include <stddef.h>
#include <stdlib.h>

#include "util_lib.h"

char	**expand_str_array_memory(char ***arg_src, size_t size)
{
	char	**new_memroy;
	char	**src;
	size_t	i;

	src = *arg_src;
	new_memroy = ft_xcalloc(size, sizeof(char *));
	i = 0;
	while (src[i] != NULL)
	{
		new_memroy[i] = src[i];
		i++;
	}
	free(*arg_src);
	*arg_src = new_memroy;
	return (new_memroy);
}

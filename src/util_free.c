#include <stdlib.h>

void	free_string_array(char **array)
{
	size_t i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
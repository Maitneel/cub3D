#ifndef UTIL_LIB_H
# define UTIL_LIB_H

# include <stddef.h>
# include <stdbool.h>

void	*ft_xmalloc(const size_t size);
void	*ft_xcalloc(size_t count, size_t size);

char **expand_str_array_memory(char ***arg_src, size_t size);

bool	ft_isspace(char c);
#endif

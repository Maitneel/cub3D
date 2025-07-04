/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:01:07 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:01:08 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_LIB_H
# define UTIL_LIB_H

# include <stddef.h>
# include <stdbool.h>

void	*ft_xmalloc(const size_t size);
void	*ft_xcalloc(size_t count, size_t size);

char	**expand_str_array_memory(char ***arg_src, size_t size);

bool	ft_isspace(char c);

size_t	string_array_size(const char **array);

#endif

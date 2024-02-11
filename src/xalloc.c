/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:03:17 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:03:17 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

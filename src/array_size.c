/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:01:50 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:01:51 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

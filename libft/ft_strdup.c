/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:30:38 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_size;
	char	*duplicate;

	s1_size = ft_strlen(s1) + 1;
	duplicate = malloc(s1_size * sizeof(char));
	if (duplicate == NULL)
	{
		return (duplicate);
	}
	ft_bzero(duplicate, s1_size * sizeof(char));
	duplicate[s1_size - 1] = '\0';
	while (s1_size)
	{
		*(duplicate + s1_size - 1) = *(s1 + s1_size - 1);
		s1_size--;
	}
	return (duplicate);
}

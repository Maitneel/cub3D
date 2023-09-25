/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:58:19 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	concat_len;
	char	*concat_str;

	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	concat_len = s1_len + s2_len;
	concat_str = malloc(concat_len + 1);
	if (concat_str == NULL)
		return (NULL);
	ft_bzero(concat_str, concat_len + 1);
	if (s1 != NULL)
		ft_strlcat(concat_str, s1, s1_len + 1);
	if (s2 != NULL)
		ft_strlcat(concat_str + s1_len, s2, s2_len + 1);
	return (concat_str);
}

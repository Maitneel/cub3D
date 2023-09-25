/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:37:20 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_split_size(char const *s, char c)
{
	size_t	result;
	size_t	i;

	result = 0;
	if (s[0] == '\0')
	{
		return (0);
	}
	i = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
		{
			result++;
		}
		i++;
	}
	if (i != 0)
	{
		if (s[i - 1] != c)
		{
			result++;
		}
	}
	return (result);
}

static void	*all_free(char **s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && size != 0)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*get_next_string(const char *s, char c, size_t *plus)
{
	size_t	len;
	char	*result;

	*plus = 0;
	while (*s == c && *s != '\0')
	{
		(*plus)++;
		s++;
	}
	len = 0;
	while (s[len] != c && s[len] != '\0')
	{
		(*plus)++;
		len++;
	}
	if (len == 0)
	{
		return (NULL);
	}
	result = (ft_substr(s, 0, len));
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	split_size;
	size_t	split_index;
	size_t	plus;
	char	**split;

	if (s == NULL)
		return (NULL);
	split_size = get_split_size(s, c) + 1;
	split = malloc(sizeof(char *) * split_size);
	if (split == NULL)
		return (NULL);
	plus = 0;
	while (plus < split_size && (++plus || 1))
		split[plus - 1] = NULL;
	split_index = 0;
	while (split_index < split_size - 1)
	{
		split[split_index] = get_next_string(s, c, &plus);
		s += plus;
		if (split[split_index] == NULL)
			return (all_free(split, split_index));
		split_index++;
	}
	split[split_size - 1] = NULL;
	return (split);
}

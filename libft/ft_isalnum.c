/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:21:01 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isalpha(int c)
{
	if ((int)('a') <= c && c <= (int)('z'))
	{
		return (1);
	}
	if ((int)('A') <= c && c <= (int)('Z'))
	{
		return (1);
	}
	return (0);
}

static int	ft_isnum(int c)
{
	if ((int)('0') <= c && c <= (int)('9'))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isnum(c))
	{
		return (1);
	}
	return (0);
}

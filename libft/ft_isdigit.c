/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:56:35 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c == (int)('0'))
		return (1);
	if (c == (int)('1'))
		return (1);
	if (c == (int)('2'))
		return (1);
	if (c == (int)('3'))
		return (1);
	if (c == (int)('4'))
		return (1);
	if (c == (int)('5'))
		return (1);
	if (c == (int)('6'))
		return (1);
	if (c == (int)('7'))
		return (1);
	if (c == (int)('8'))
		return (1);
	if (c == (int)('9'))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:52:49 by taksaito          #+#    #+#             */
/*   Updated: 2023/09/30 18:48:41 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"

t_vector2d	*new_vector(double y, double x)
{
	t_vector2d	*vec;

	vec = ft_xcalloc(sizeof(t_vector2d), 1);
	vec->y = y;
	vec->x = x;
	return (vec);
}

t_vector2d	*add(t_vector2d *lhs, t_vector2d *rhs)
{
	return (new_vector(lhs->y + rhs->y, lhs->x + rhs->x));
}

t_vector2d	*sub(t_vector2d *lhs, t_vector2d *rhs)
{
	return (new_vector(lhs->y - rhs->y, lhs->x - rhs->x));
}

t_vector2d	*mult(t_vector2d *vec, double d)
{
	return (new_vector(vec->y * d, vec->x * d));
}

double	mag(t_vector2d *vec)
{
	return (sqrt(vec->y * vec->y + vec->x * vec->x));
}

t_vector2d	*deep_copy(t_vector2d *vec)
{
	return (new_vector(vec->y, vec->x));
}

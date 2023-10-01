/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:37 by taksaito          #+#    #+#             */
/*   Updated: 2023/10/01 17:35:18 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray2d.h"

t_ray2d	*new_ray2d(t_vector2d *begin, t_vector2d *end)
{
	t_ray2d	*ray;

	ray = ft_xcalloc(sizeof(t_ray2d), 1);
	ray->pos = deep_copy(begin);
	ray->way = sub(end, begin);
	return (ray);
}

t_vector2d	*get_begin(t_ray2d *ray)
{
	return (ray->pos);
}

t_vector2d	*get_end(t_ray2d *ray)
{
	return (add(ray->pos, ray->way));
}

t_vector2d	*intersection(t_ray2d *ray1, t_ray2d *ray2)
{
	double	t1;
	double	t2;
	double	sx;
	double	sy;

	if (ray1->pos->x < EPS)
		ray1->pos->x = EPS;
	if (ray2->pos->x < EPS)
		ray2->pos->x = EPS;
	t1 = ray1->way->y / ray1->way->x;
	t2 = ray2->way->y / ray2->way->x;
	sx = (t1 * ray1->pos->x - t2
			* ray2->pos->x - ray1->pos->y + ray2->pos->y) / (t1 - t2);
	sy = t1 * (sx - ray1->pos->x) + ray1->pos->y;
	return (new_vector(sy, sx));
}

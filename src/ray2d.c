/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:37 by taksaito          #+#    #+#             */
/*   Updated: 2023/09/30 19:45:17 by taksaito         ###   ########.fr       */
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
	// TODO: 現在は線分の延長線上に交点があった場合も返すような実装になっているので、あとで修正する。
	double t1, t2, x1, x2, y1, y2, sx, sy;
	t1 = ray1->way->y / ray1->way->x;
	t2 = ray2->way->y / ray2->way->x;
	x1 = ray1->pos->x;
	x2 = ray2->pos->x;
	y1 = ray1->pos->y;
	y2 = ray2->pos->y;
	sx = (t1 * x1 - t2 * x2 - y1 + y2) / (t1 - t2);
	sy = t1 * (sx - x1) + y1;
	return (new_vector(sy, sx));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:52:58 by taksaito          #+#    #+#             */
/*   Updated: 2023/10/07 18:26:04 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

# include "util_lib.h"
# include <math.h>

typedef struct s_vector2ds
{
	double	y;
	double	x;
}	t_vector2d;

// vector2d
t_vector2d	*new_vector(double y, double x);
t_vector2d	*add(t_vector2d *lhs, t_vector2d *rhs);
t_vector2d	*sub(t_vector2d *lhs, t_vector2d *rhs);
t_vector2d	*mult(t_vector2d *vec, double d);
double		mag(t_vector2d *vec);
t_vector2d	*deep_copy(t_vector2d *vec);
t_vector2d	unit_vector(double theta);

#endif // VECTOR2D_H

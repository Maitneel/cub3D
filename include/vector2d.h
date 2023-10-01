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

#endif // VECTOR2D_H

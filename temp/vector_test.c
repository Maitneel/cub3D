#include "ray2d.h"
#include <stdio.h>

void print_vec(t_vector2d *vec)
{
	printf("y: %lf, x: %lf\n", vec->y, vec->x);
}

void print_ray(t_ray2d *ray)
{
	printf("pos: \n");
	print_vec(ray->pos);

	printf("way: \n");
	print_vec(ray->way);
}

int vector_test()
{
	t_vector2d *vec1;
	t_vector2d *vec2;

	vec1 = new_vector(3.0, 2.0);
	vec2 = new_vector(5.0, 8.0);

	printf("vec1\n");
	print_vec(vec1);
	printf("vec2\n");
	print_vec(vec2);

	printf("add\n");
	print_vec(add(vec1, vec2));


	printf("sub\n");
	print_vec(sub(vec1, vec2));

	printf("mult\n");
	print_vec(mult(vec1, 3.0));

	printf("mag\n");
	printf("mag: %lf\n", mag(vec1));

	t_ray2d *ray1 = new_ray2d(new_vector(0, 0), new_vector(5, 5));
	t_ray2d *ray2 = new_ray2d(new_vector(5, 0), new_vector(0, 5));
	print_vec(intersection(ray1, ray2));
}

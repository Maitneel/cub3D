#include "cub3d_structs.h"
#include "util_lib.h"

t_point *new_point(int y, int x)
{
    t_point *point;

    point = ft_xcalloc(1, sizeof(t_point));
    point->x = x;
    point->y = y;
    return (point);
}
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

t_point new_point_struct(const int y, const int x)
{
    t_point point;

    point.x = x;
    point.y = y;
    return point;
}

t_coll_point new_coll_pt_struct(t_point pt, bool is_vert)
{
    t_coll_point coll_point;

    coll_point.is_vert = is_vert;
    coll_point.pt = pt;
    return coll_point;
}
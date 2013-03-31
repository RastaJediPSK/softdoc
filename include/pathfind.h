#ifndef PATHFIND_H
#define PATHFIND_H

#include <list>
#include "map.h"
#include "unit.h"

#define MAX_PATH 10

struct position
{
    int x;
    int y;
};

class Pathfind
{
    int **path_map;
    int x_offset;
    int y_offset;
    Unit *unit;
    Map *map;

    int dist_est(int x0, int y0, int x, int y);

    public:
    Pathfind(int start_x, int start_y, Unit *unit_ptr, Map *map_ptr);
    ~Pathfind();
    int find_dist(int x, int y);
};

#endif

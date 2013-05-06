/*
 * File:  pathfind.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  31 March 2013
 * Description:  Pathfind class declaration file.
 */

#ifndef PATHFIND_H
#define PATHFIND_H

#include <list>
#include "unit.h"

#define MAX_PATH 20

class Map;

/* Struct used to store data for pathfind. */
struct position_t
{
	int x;
	int y;
};

/* 
 * Class to calculate the minimum distance to a tile, used to calculate unit
 * movement.
 */
class Pathfind
{
    int **path_map;
    int x_offset;
    int y_offset;
    Unit *unit;
    Map *map;

    int dist_est(int x0, int y0, int x, int y);

    // Unused operators to stop warnings
    Pathfind(const Pathfind &p);
    void operator=(const Pathfind &p);

public:
    Pathfind(int start_x, int start_y, Unit *unit_ptr, Map *map_ptr);
    ~Pathfind();
    int find_dist(int x, int y);
};

#endif	/* PATHFIND_H */

#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include "unit.h"

struct tile_pair
{
    int terrain;
    Unit *unit;
};

class Map
{
    tile_pair **map;
    int tile_x,tile_y;//map x,y that maps to screen (0,0)
    int map_x, map_y;//total size of map
    int scr_x, scr_y;//total size of screen
    void redraw();

    public:
    Map(int x, int y);
    ~Map();
};

#endif

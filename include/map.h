#ifndef MAP_H
#define MAP_H

#include <ncurses>
#include "unit.h"

struct tile_pair
{
    int terrain;
    UNIT *unit;
};

class MAP
{
    tile_pair **map;
    int tile_x,tile_y;//map x,y that maps to screen (0,0)
    int map_x, map_y;//total size of map
    int scr_x, scr_y;//total size of screen

    MAP(int x, int y);
    ~MAP();
};

#endif

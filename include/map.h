#ifndef MAP_H_
#define MAP_H_

#include <ncurses/curses.h>
#include "unit.h"
#include "panel.h"

struct tile_pair
{
    int terrain;
    Unit *unit;
};

class Map
{
    tile_pair **map;
    int tile_x, tile_y;//map x,y that maps to screen (0,0)
    int map_x, map_y;//total size of map
    int scr_x, scr_y;//total size of screen
    int pos_x, pos_y;//position of cursor on screen
    Panel *panel;//pointer to panel
    WINDOW *map_pad;//pad to draw map on

    public:
    Map(int x, int y, int screen_x, int screen_y, Panel *panel_ptr = NULL);
    ~Map();
    void redraw(int screen_x, int screen_y);
    void map_loop();
};

#endif

#ifndef PANEL_H
#define PANEL_H

#include <ncurses.h>
#include "unit.h"

class Panel
{
    int scr_x, scr_y;//total size of screen
    int size;//panel width
    int pos_x;//panel starting x position
    int terrain_pos;//line with terrain info
    int unit_name_pos;//line with unit name
    int move_pos;//line with unit move info

    public:
    Panel(int screen_x, int screen_y, int panel_size);
    void update(int terrain, Unit *unit);
    void resize(int screen_x, int screen_y, int terrain, Unit *unit);
    int get_size();
};

#endif

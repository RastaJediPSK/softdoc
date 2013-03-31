#ifndef BUILD_PANEL_H
#define BUILD_PANEL_H

#include <ncurses/curses.h>
#include "player.h"
#include "unit.h"

class BuildPanel
{
    WINDOW *win;
    Player *pl;

    public:
    BuildPanel(Player *play);
    Unit *use_panel();
};

#endif

/*
 * File:  build_panel.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  11 March 2013
 * Description: BuildPanel class declaration file
 */

#ifndef BUILD_PANEL_H_
#define BUILD_PANEL_H_

#include <ncurses/curses.h>
#include <vector>
#include <cstdlib>
#include "player.h"
#include "unit.h"
#include "unit_type.h"

//Class used to create a menu to build new units
class BuildPanel
{
    std::vector<UnitType *> types;
	WINDOW *win;
	Player *pl;
    int size;
    unsigned int opt;
    int screen_y;

    //unsued constructors (added to prevent warnings)
    BuildPanel(const BuildPanel &b); 
    void operator=(const BuildPanel &b);

public:
	BuildPanel(std::vector<UnitType *> &unit_types, Player *play, int scr_x, int scr_y, int panel_size);
    ~BuildPanel();
    void resize(int scr_x, int scr_y);
	Unit *use_panel(int x, int y);
};

#endif

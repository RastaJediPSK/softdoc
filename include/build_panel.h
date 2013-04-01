/*
 * File:  build_panel.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  11 March 2013
 * Description: BuildPanel class declaration file
 */

#ifndef BUILD_PANEL_H_
#define BUILD_PANEL_H_

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

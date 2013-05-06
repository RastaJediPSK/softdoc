/*
 * File:  build_panel.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  11 March 2013
 * Description:  BuildPanel class declaration file.
 */

#ifndef BUILD_PANEL_H
#define BUILD_PANEL_H

#include <vector>
#include <cstdlib>
#include <curses.h>

class Player;
class Unit;
class UnitType;

/* Class used to create a menu to build new units. */
class BuildPanel
{
	std::vector<UnitType *> types;
	WINDOW *win;
	Player *pl;
	int size;
	unsigned int opt;
	int screen_y;

	// Unsued constructors (added to prevent warnings)
	BuildPanel(const BuildPanel &b); 
	void operator=(const BuildPanel &b);

public:
	BuildPanel(std::vector<UnitType *> const &unit_types, Player *play, int scr_x, int scr_y, int panel_size);
	~BuildPanel();
	void resize(int scr_x, int scr_y);
	Unit *use_panel(int x, int y);
};

#endif	/* BUILD_PANEL_H */

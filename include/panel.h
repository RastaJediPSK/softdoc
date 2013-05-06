/*
 * File:  panel.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  16 March 2013
 * Description:  Panel class declaration file.
 */

#ifndef PANEL_H
#define PANEL_H

#include <curses.h>

class Unit;

/* Class that creates an information panel on the screen. */
class Panel
{
	int scr_x, scr_y;	// Total size of screen
	int size	;	// Panel width
	int pos_x;		// Panel starting x position
	int terrain_pos;	// Line with terrain info
	int unit_name_pos; 	// Line with unit name
	int move_pos;		// Line with unit move info
	int selected_unit_pos;
	WINDOW *panel_window;
	
	// Unsued constructors to stop warnings
	Panel(const Panel &);
	void operator=(const Panel &);
	
public:
	Panel(int screen_x, int screen_y, int panel_size);
	~Panel();
	void update(int terrain, Unit *unit, Unit *selected, int path_length);
	void resize(int screen_x, int screen_y, int terrain, Unit *unit, Unit *selected, int path);
	int get_size() const { return size; }	// Returns width of panel
};

#endif	/* PANEL_H */

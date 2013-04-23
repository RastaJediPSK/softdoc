/*
 * File:  map.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  24 March 2013
 * Description:  Map class declaration file
 */

#ifndef MAP_H_
#define MAP_H_

#include <ncurses/curses.h>
#include <vector>
#include "unit.h"
#include "unit_type.h"
#include "panel.h"
#include "build_panel.h"
#include "player.h"
#include "pathfind.h"

//Holds data for each tile on the map
struct tile_pair_t
{
    int terrain;
    Unit *unit;
};

//main map class, handels displaying the map,
//the cursor and interacting with units
class Map
{
private:
	std::vector<std::vector<tile_pair_t> > map;
	int tile_x, tile_y;	// map x,y that maps to screen (0,0)
	int map_x, map_y;	// total size of map
	int scr_x, scr_y;	// total size of screen
	int pos_x, pos_y;	// position of cursor on screen
	Panel panel;
	WINDOW *map_pad;	// pad to draw map on
    std::vector<UnitType *> types;
    Unit *selected;
    Pathfind *pathfind;
    int path_length;
	
	// Define blank copy ctor/assignment operator (for now)
	Map(const Map &);
	Map &operator=(const Map &);

	// Define blank ctor to disallow use of default ctor
	Map();

    void deselect();
    


public:
	Map(int x, int y, int screen_x, int screen_y, Panel &panel, std::vector<UnitType *> &type);
	~Map();
	void redraw(int screen_x, int screen_y);
	void map_loop(Player *player);
	tile_pair_t *get_tile(int x, int y);
};

#endif

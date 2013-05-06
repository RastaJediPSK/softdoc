/*
 * File:  map.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  24 March 2013
 * Description:  Map class declaration file.
 */

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <curses.h>
#include "panel.h"

class Pathfind;
class Player;
class UnitType;

/* Holds data for each tile on the map. */
struct tile_pair_t
{
    int terrain;
    Unit *unit;
};

/*
 * Main Map class.
 * Handles displaying the map, the cursor and interacting with units.
 */
class Map
{
	std::vector<std::vector<tile_pair_t> > map;
	int tile_x, tile_y;	// map x,y that maps to screen (0,0)
	int map_x, map_y;	// total size of map
	int scr_x, scr_y;	// total size of screen
	int pos_x, pos_y;	// position of cursor on screen
	Panel panel;
	WINDOW *map_pad;	// pad to draw map on
	std::vector<UnitType *> const &types;
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
	Map(int x, int y, int screen_x, int screen_y, Panel const &panel, std::vector<UnitType *> const &type, Player *p1, Player *p2);
	~Map();
	void redraw(int screen_x, int screen_y);
	void map_loop(Player *player);
	void createRoad(int orig_x, int orig_y, int dest_x, int dest_y);
	tile_pair_t *get_tile(int x, int y);
};

#endif	/* MAP_H */

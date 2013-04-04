/*
 * File:  map.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  24 February 2013
 * Description:  Map class definition file
 */

#include <iostream>
#include "map.h"

Map::Map(int x, int y, int screen_x, int screen_y, Panel &panel) :
 	map(),
	tile_x(0),
	tile_y(0),
	map_x(x),
	map_y(y),
	scr_x(screen_x),
	scr_y(screen_y),
	pos_x(screen_x/2),
	pos_y(screen_y/2),
	panel(panel),
	map_pad(0)
{
	scr_x -= panel.get_size();

	using std::vector;
	// reserve x map rows to avoid reallocation
	vector<vector<tile_pair_t> >::size_type sz = x;
	map.reserve(sz);

	for (int i = 0; i < x; ++i)
	{
		map.push_back(vector<tile_pair_t>());	// add a row to map
		
		// reserve y columns for this row to avoid reallocation
		vector<tile_pair_t>::size_type sz = y;
		map[i].reserve(sz);

		for (int j = 0; j < y; ++j)
		{
			map[i].push_back(tile_pair_t());	// add column to row

			map[i][j].unit = 0;
			map[i][j].terrain = 2;	// initialize all as grass
			if ( j == i ){
				map[i][j].terrain = 3;
			}
			
			// Terrain Randomizer
			/*if (j < i)	// mirrors over diagonal
				map[i][j].terrain = map[j][i].terrain;
			else if (i == 0 && j == 0 )
			{
				map[i][j].terrain = std::rand() % 5 + 1;
				if (map[i][j].terrain == 0 || map[i][j].terrain > 4)
					map[i][j].terrain = 5;
			}
			else if (i == 0)
			{
				map[i][j].terrain = std::rand() % 9;
				if (map[i][j].terrain > 4)
					map[i][j].terrain = map[i][j-1].terrain;	// Match above tile
			}
			else if (j == 0)
			{
				map[i][j].terrain = std::rand() % 9;
				if (map[i][j].terrain > 4)
					map[i][j].terrain = map[i-1][j].terrain;	// Match left tile
			}
			else
			{
				map[i][j].terrain = std::rand() % 13;
				if (map[i][j].terrain > 4)
				{
					if (map[i][j].terrain % 2 == 1)		// Match above tile
						map[i][j].terrain = map[i][j-1].terrain;
					else	// Match left tile
						map[i][j].terrain = map[i-1][j].terrain;
				}
			}*/
		}
	}

	//Terrain Procedural Generator
	//Mountains
	for( int n = 0; n < map_x/10; n++){
		int origin_x = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
		int origin_y = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
		int mount_size = ( (int) ((map_x/20) *(std::rand() / (RAND_MAX + 1.0) ) )) + 3;
		for(int j = -mount_size; j < mount_size + 1; j++){
			for(int i = abs(j) - mount_size; i < -abs(j) + mount_size + 1; i++){
				if ( (i + origin_x >= 0) && (i + origin_x < map_x) && (j + origin_y >= 0) && (j + origin_y  < map_y) ){
					map[i + origin_x][j + origin_y].terrain = 4;
				}
			}
		}
	}
	
	
	// Bases
	map[(int)(map_x - (map_x/10))][(int)(map_y/10)].terrain = 6;
	map[(int)(map_x/10) ][(int)(map_y - map_y/10)].terrain = 6;

	map_pad = newpad(y, x);
    wclear(map_pad);
	
	for (int j = 0; j < y; ++j)
	{
		wmove(map_pad, j, 0);
		for(int i = 0; i < x; ++i)
		{
			wattron(map_pad, COLOR_PAIR(map[i][j].terrain));
			waddch(map_pad,' ');
			wattroff(map_pad, COLOR_PAIR(map[i][j].terrain));
		}
	}
	redraw(scr_x, scr_y);
}

Map::~Map()
{
	delwin(map_pad);
}

void Map::redraw(int screen_x, int screen_y)
{
	scr_x = screen_x;
	scr_y = screen_y;
	/* Check map bounds */
	if (pos_x > scr_x)
		pos_x = scr_x;
	if (pos_y > scr_y)
		pos_y = scr_y;
	
	pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);

	panel.resize(screen_x + panel.get_size(), screen_y,
			map[pos_x + tile_x][pos_y + tile_y].terrain,
			map[pos_x + tile_x][pos_y + tile_y].unit);
	doupdate();
	move(pos_y, pos_x);
}

void Map::map_loop()
{
	int ch;
	bool quit = true;

	move(pos_y, pos_x);

	while (quit)
	{
		ch = getch();
		switch (ch)	// may want to add a wait time to redraws
		{
		case 'q':
		case KEY_EXIT:
			quit = false;
			break;
		case KEY_UP:
			if (pos_y == 0)
			{
				if (tile_y == 0)
					// beep
					(void)0;	// no-op
				else
					--tile_y;

				redraw(scr_x, scr_y);
			}
			else
			{
				--pos_y;
				move(pos_y, pos_x);
				
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit);
				doupdate();
			}

			break;
		case KEY_DOWN:
			if (tile_y + scr_y == map_y)
			{
				// beep
				break;
			}

			if (pos_y >= scr_y - 1)
			{
				++tile_y;
				redraw(scr_x, scr_y);
			}
			else
			{
				++pos_y;
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit);
				doupdate();
			}

			break;
		case KEY_LEFT:
			if (pos_x == 0)
			{
				if (tile_x == 0)
					// beep
					(void)0;	// no-op
				else
				{
					--tile_x;
					redraw(scr_x, scr_y);
				}
			}
			else
			{
				--pos_x;
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit);
				doupdate();
			}

			break;
		case KEY_RIGHT:
			if (tile_x + scr_x == map_x)
			{
				// beep
				break;
			}
			
			if (pos_x >= scr_x - 1)
			{
				++tile_x;
				redraw(scr_x, scr_y);
			}
			else
			{
				++pos_x;
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit);
				doupdate();
			}

			break;
		default:
			break;
		}
	}
}

tile_pair_t *Map::get_tile(int x, int y)
{
	if (x >= map_x || y >= map_y)
		return 0;
	return &map[x][y];
}

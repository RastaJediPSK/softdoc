/*
 * File:  map.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  24 February 2013
 * Description:  Map class definition file
 */

#include <iostream>
#include "map.h"

Map::Map(int x, int y, int screen_x, int screen_y, Panel &panel, std::vector<UnitType *> &type) :
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
	map_pad(0),
    types(type)
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
			//map[i][j].terrain = (i+j) % 6 + 1;	// temp
			
			// Terrain Generator
			if (j < i)	// mirrors over diagonal
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

void Map::map_loop(Player *player)
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
			if (pos_y >= scr_y - 1)
			{
                if (tile_y + scr_y >= map_y)
                {
                    break;
                }
				++tile_y;
				redraw(scr_x, scr_y);
			}
			else
			{
                if(tile_y + pos_y + 1 >= map_y)
                    break;
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
			if (pos_x >= scr_x - 1)
			{
                if (tile_x + scr_x >= map_x)
                {
                    break;
                }
				++tile_x;
				redraw(scr_x, scr_y);
			}
			else
			{
                if(tile_x+pos_x+1 >= map_x)
                    break;
				++pos_x;
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit);
				doupdate();
			}
			break;
        case 'z':
            if(map[pos_x][pos_y].terrain == 2 && map[pos_x][pos_y].unit == NULL)
            {
                BuildPanel *bp;
                bp = new BuildPanel(types,player,scr_x,scr_y,panel.get_size());
                map[pos_x+tile_x][pos_y+tile_y].unit = bp->use_panel(pos_x+tile_x,pos_y+tile_y);
                delete bp;
                panel.resize(scr_x,scr_y,map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                if(map[pos_x+tile_x][pos_y+tile_y].unit)
                {
                    wattron(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain));
                    mvwaddch(map_pad,pos_y+tile_y,pos_x+tile_x,map[pos_x+tile_x][pos_y+tile_y].unit->symbol());
                    wattroff(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain));
	                pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                }
				move(pos_y, pos_x);
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

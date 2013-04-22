/*
 * File:  map.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  24 February 2013
 * Description:  Map class definition file
 */

#include <cstdlib>
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

	srand(time(NULL));
	int center_x = map_x/2;
	int center_y = map_y/2;
	
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

		}
	}
	
	//Terrain Procedural Generator
	
	//Rivers
	//Picks a side and a direction. River will originate from that side
	//and head in that direction. Will have random width limited by map size.
	for(int n = 0; n < map_x/10; n++){
		int side = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
		int dir = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
		//int width = (int) ((map_x/50) * ( std::rand() / (RAND_MAX + 1.0))) + 1;
		if (side == 1){ //originate from left side
			int pos = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
			if (dir == 1){ //head up-right
				for (int i = 0; i < map_x; i++){
					if ( pos - i < 0 ){
						break;
					}
					if ( pos - i >= 1 ){
						map[i][pos - i - 1].terrain = 1;
					}
					map[i][pos - i].terrain = 1;
				}
			}
			else{ //head down-right
				for (int i = 0; i < map_x; i++){
					if ( pos + i >= map_y ){
						break;
					}
					if ( pos + i + 1 < map_y ){
						map[i][pos - i - 1].terrain = 1;
					}
					map[i][pos + i].terrain = 1;
				}
			}
		}
		else { //originate from bottom side
			int pos = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
			if (dir == 1){ //head up-left
				for (int i = 0; i < map_y; i++){
					if ( pos - i < 0 ){
						break;
					}
					if ( map_y - i - 2 >= 0 ){
						map[pos - i][map_y - i - 2].terrain = 1;
					}
					map[pos - i][map_y -1 - i].terrain = 1;
				}
			}
			else{ //head up-right
				for (int i = 0; i < map_y; i++){
					if ( pos + i <= map_x ){
						break;
					}
					if ( map_y - i - 2 >= 0 ){
						map[pos + i][map_y - i - 2 ].terrain = 1;
					}
					map[pos + i][map_y -1 - i].terrain = 1;
				}
			}
		}
	}
	
	//Mountains
	//Places randomly sized mountains (diamonds) in random locations.
	//More and larger mountains for larger maps
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
	
	// Roads
	//Will go from base 1 to center, going only in cardinal directions.
	int n = (map_x/10);
	int	m = (map_y - map_y/10);
	while( n+1 <= center_x || m+1 >= center_y ){
		if ( n+1 > center_x ){	//moved as right as possible
			m--;
			map[n][m].terrain = 3;
		}
		else if ( m+1 < center_y ){	//moved as up as possible
			n++;
			map[n][m].terrain = 3;
		}
		else{	//pick either up or right
			int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
			if (rand == 1){ //up
				m--;
				map[n][m].terrain = 3;
			}
			else{ //right
				n++;
				map[n][m].terrain = 3;
			}
		}
	}
	
	//Other Buildings
	//Will be randomly distributed, one per 50x50 quadrant
	n = 0;
	while ( n < map_x /50){
		m = 0;
		while ( m < map_y / 50){
			int rand_x = (int) (50 * ( std::rand() / (RAND_MAX + 1.0)));
			int rand_y = (int) (50 * ( std::rand() / (RAND_MAX + 1.0)));
			if (map[(n*50)+rand_x][(m*50)+rand_y].terrain != 6){
				map[(n*50)+rand_x][(m*50)+rand_y].terrain = 5;
				m++;
			}
		}
		n++;
	}
	
	
	// Reflect map over diagonal (\) and flip
	//0-0 1-0 2-0 3-0 4-0		0-0 3-4 2-4 1-4 0-4
	//0-1 1-1 2-1 3-1 4-1		0-1 1-1 
	//0-2 1-2 2-2 3-2 4-2		0-2 1-2 2-2 
	//0-3 1-3 2-3 3-3 4-3		0-3 1-3 2-3 3-3
	//0-4 1-4 2-4 3-4 4-4		0-4 1-4 2-4 3-4 4-4
	for (int i = 0; i < map_x; ++i){
		for (int j = 0; j < map_y; ++j){
			if ( i > j ){
				//Reflects and flips
				//map[i][j].terrain = map[center_x + (center_x-i) ][center_y + (center_y-j)].terrain;
				
				//Only reflects
				map[i][j].terrain = map[j][i].terrain;
			}
		}
	}
	
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

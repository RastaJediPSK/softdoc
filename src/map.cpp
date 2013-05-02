/*
 * File:  map.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  24 February 2013
 * Description:  Map class definition file
 */

#include <cstdlib>
#include <iostream>
#include "map.h"

//Map constructor, generates, draws and displays the map
Map::Map(int x, int y, int screen_x, int screen_y, Panel &panel, std::vector<UnitType *> &type, Player *p1, Player *p2) :
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
    types(type),
    selected(NULL),
    pathfind(NULL),
    path_length(-1)
{

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
	//Create a lake as an origin, 
	//then send river from lake to a random side of the map
	for(int n = 0; n < map_x/10; n++){
	
		//Makes a lake
		int origin_x = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
		int origin_y = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
		int lake_size = ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 2;
		for(int j = -lake_size; j < lake_size + 1; j++){
			for(int i = abs(j) - lake_size; i < -abs(j) + lake_size + 1; i++){
				if ( (i + origin_x >= 0) && (i + origin_x < map_x) && (j + origin_y >= 0) && (j + origin_y  < map_y) ){
					map[i + origin_x][j + origin_y].terrain = 1;
				}
			}
		}
		
		//Picks a diagonal and makes a river that heads out that way
		int side = (int) (4 * ( std::rand() / (RAND_MAX + 1.0)));
		if (side == 0){ //Up-left
			while( origin_x > 0 && origin_y > 0 ){
				//pick either up or left
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //up
					origin_y--;
				}
				else{ //left
					origin_x--;
				}
				map[origin_x][origin_y].terrain = 1;
			}
		}
		else if (side == 1){ //Up-right
			while( origin_x < map_x - 1 && origin_y > 0 ){
				//pick either up or right
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //up
					origin_y--;
				}
				else{ //right
					origin_x++;
				}
				map[origin_x][origin_y].terrain = 1;
			}
		}
		else if (side == 2){ //Down-right
			while( origin_x < map_x - 1 && origin_y < map_y - 1 ){
				//pick either down or right
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //down
					origin_y++;
				}
				else{ //right
					origin_x++;
				}
				map[origin_x][origin_y].terrain = 1;
			}
		}
		else if (side == 3){ //Down-left
			while( origin_x > 0 && origin_y < map_y - 1 ){
				//pick either down or left
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //down
					origin_y++;
				}
				else{ //left
					origin_x--;
				}
				map[origin_x][origin_y].terrain = 1;
			}
		}
	}
	
	//Mountains
	//Creates mountain ranges (groups of red diamonds).
	//More and larger mountains for larger maps
	
	//Create ranges
	int mountain_ranges = ( (int) ((map_x/20) *(std::rand() / (RAND_MAX + 1.0) ) )) + 3;
	for( int n = 0; n < mountain_ranges; n++){
		int range_size = ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 2;
		int direction = (int) (8 * ( std::rand() / (RAND_MAX + 1.0)));
		int origin_x = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
		int origin_y = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
		
		//Create each mountain in the range
		for( int i = 0; i < range_size; i++){
			int mount_size = ( (int) ((map_x/20) *(std::rand() / (RAND_MAX + 1.0) ) )) + 3;
			for(int j = -mount_size; j < mount_size + 1; j++){
				for(int i = abs(j) - mount_size; i < -abs(j) + mount_size + 1; i++){
					if ( (i + origin_x >= 0) && (i + origin_x < map_x) && (j + origin_y >= 0) && (j + origin_y  < map_y) ){
						map[i + origin_x][j + origin_y].terrain = 4;
					}
				}
			}
			//CHANGE TO NEXT ORIGIN
			if (direction == 0){ //Right and a little up
				origin_x += ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y -= ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 1){ //Right and a little down
				origin_x += ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y += ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 2){ //Left and a little up
				origin_x -= ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y -= ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 3){ //Left and a little down
				origin_x -= ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y += ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			
			else if (direction == 4){ //Up and a little right
				origin_x += ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y -= ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 5){ //Up and a little left
				origin_x -= ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y -= ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 6){ //Down and a little right
				origin_x += ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y += ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
			else if (direction == 7){ //Down and a little left
				origin_x -= ( (int) ((map_x/30) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
				origin_y += ( (int) ((map_x/10) *(std::rand() / (RAND_MAX + 1.0) ) )) + 1;
			}
		}
	}
	
	
	// Bases
	int p2_base_x = (map_x - (map_x/10));
	int p2_base_y = (map_y/10);
	int p1_base_x = (map_x/10) ;
	int p1_base_y = (map_y - map_y/10);
	map[p2_base_x][p2_base_y].terrain = 5;
	p2->add_base(p2_base_x, p2_base_y);
	map[p1_base_x][p1_base_y].terrain = 6;
	p1->add_base(p1_base_x, p1_base_y);
	
	// Road between main bases
	createRoad(p1_base_x, p1_base_y, p2_base_x, p2_base_y);
	
	//Other Buildings
	//Will be randomly distributed, at least 2 per player, more for larger maps
	int n = (map_x/50) + 2;
	while ( n > 0){
		//Player 1's
		int rand_x = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
		int rand_y = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
		if (rand_x < rand_y && map[rand_x][rand_y].terrain != 6 && map[rand_x][rand_y].terrain != 5){
			map[rand_x][rand_y].terrain = 6;
			p1->add_base(rand_x, rand_y);
			n--;
			
			//build road from p1 base to this building
			createRoad(p1_base_x, p1_base_y, rand_x, rand_y);
		}
	}
	n = (map_x/50) + 2;
	while ( n > 0 ){
		//Player 2's
		int rand_x = (int) (map_x * ( std::rand() / (RAND_MAX + 1.0)));
		int rand_y = (int) (map_y * ( std::rand() / (RAND_MAX + 1.0)));
		if (rand_x > rand_y && map[rand_x][rand_y].terrain != 6 && map[rand_x][rand_y].terrain != 5){
			map[rand_x][rand_y].terrain = 5;
			p2->add_base(rand_x, rand_y);
			n--;
			
			//build road from p2 base to this building
			createRoad(p2_base_x, p2_base_y, rand_x, rand_y);
		}
	}
	
	//END PROCEDURAL GENERATOR
	
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

//Map deconstuctor, deletes map window
Map::~Map()
{
	delwin(map_pad);
}

//redraws the map with a new size
void Map::redraw(int screen_x, int screen_y)
{
	scr_x = screen_x;
	scr_y = screen_y;
	/* Check map bounds */
	if (pos_x > scr_x-1)
		pos_x = scr_x-1;
	if (pos_y > scr_y-1)
		pos_y = scr_y-1;
    if(pos_x > map_x-1)
        pos_x = map_x-1;
    if(pos_y > map_y-1)
        pos_y = map_y-1;
	
	pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);

	panel.resize(screen_x + panel.get_size(), screen_y,
			map[pos_x + tile_x][pos_y + tile_y].terrain,
			map[pos_x + tile_x][pos_y + tile_y].unit,selected,path_length);
	doupdate();
	move(pos_y, pos_x);
}

//main loop for a players turn
//controls the cursor and allows for 
//interacting with units on the map
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
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				redraw(scr_x, scr_y);
			}
			else
			{
				--pos_y;
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				move(pos_y, pos_x);
				
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit,selected,path_length);
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
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				redraw(scr_x, scr_y);
			}
			else
			{
                if(tile_y + pos_y + 1 >= map_y)
                    break;
				++pos_y;
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit,
                        selected,path_length);
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
                    if(pathfind == NULL)
                    {
                        path_length = -1;
                    }else{
                        path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                    }
					redraw(scr_x, scr_y);
				}
			}
			else
			{
				--pos_x;
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit,
                        selected,path_length);
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
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				redraw(scr_x, scr_y);
			}
			else
			{
                if(tile_x+pos_x+1 >= map_x)
                    break;
				++pos_x;
                if(pathfind == NULL)
                {
                    path_length = -1;
                }else{
                    path_length = pathfind->find_dist(pos_x+tile_x,pos_y+tile_y);
                }
				move(pos_y, pos_x);
				panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
						map[pos_x + tile_x][pos_y + tile_y].unit,
                        selected,path_length);
				doupdate();
			}
			break;
        case 'z':
            if(selected == NULL)
            {
                if(map[pos_x+tile_x][pos_y+tile_y].unit == NULL)
                {
                    if(map[pos_x+tile_x][pos_y+tile_y].terrain == 6-player->get_id())
                    {
                        //open the buildpanel to constuct a new unit
                        BuildPanel *bp;
                        bp = new BuildPanel(types,player,scr_x+panel.get_size(),scr_y,panel.get_size());
                        map[pos_x+tile_x][pos_y+tile_y].unit = bp->use_panel(pos_x+tile_x,pos_y+tile_y);
                        delete bp;
                        panel.resize(scr_x+panel.get_size(),scr_y,map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit,selected,path_length);
                        if(map[pos_x+tile_x][pos_y+tile_y].unit)
                        {
                            wattron(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id()));
                            mvwaddch(map_pad,pos_y+tile_y,pos_x+tile_x,map[pos_x+tile_x][pos_y+tile_y].unit->symbol());
                            wattroff(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain)+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id());
                            pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                        }
                        move(pos_y, pos_x);
                        doupdate();
                    }
                }else{
                    Unit *hovered_unit = map[pos_x+tile_x][pos_y+tile_y].unit;
                    if(hovered_unit->get_player() == player && !hovered_unit->get_used())
                    {
                        //select the unit
                        selected = hovered_unit;
                        pathfind = new Pathfind(pos_x+tile_x,pos_y+tile_y,selected,this);
                        panel.update(map[pos_x + tile_x][pos_y + tile_y].terrain,
                                map[pos_x + tile_x][pos_y + tile_y].unit,
                                selected,path_length);
                    }
                }
            }else{
                Unit *hovered_unit = map[pos_x+tile_x][pos_y+tile_y].unit;
                if(path_length != -1 && path_length <= selected->get_move())
                {
                    if(hovered_unit == NULL)
                    {
                        //Move the unit
                        map[pos_x+tile_x][pos_y+tile_y].unit = selected;
                        map[selected->get_x()][selected->get_y()].unit = NULL;
                        wattron(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id()));
                        mvwaddch(map_pad,pos_y+tile_y,pos_x+tile_x,map[pos_x+tile_x][pos_y+tile_y].unit->symbol());
                        wattroff(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id()));
                        wattron(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                        mvwaddch(map_pad,selected->get_y(),selected->get_x(),' ');
                        wattroff(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                        pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                        selected->move(pos_x+tile_x,pos_y+tile_y);
                        selected->set_used(true);
                        deselect();
                    }else{
                        if(hovered_unit->get_player() != player)
                        {
                            //Unit combat
                            int result = selected->attack(hovered_unit->get_label());
                            switch(result)
                            {
                                case 0: //Win
                                    delete map[pos_x+tile_x][pos_y+tile_y].unit;
                                    map[pos_x+tile_x][pos_y+tile_y].unit = selected;
                                    map[selected->get_x()][selected->get_y()].unit = NULL;
                                    wattron(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id()));
                                    mvwaddch(map_pad,pos_y+tile_y,pos_x+tile_x,map[pos_x+tile_x][pos_y+tile_y].unit->symbol());
                                    wattroff(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain+6*map[pos_x+tile_x][pos_y+tile_y].unit->get_player()->get_id()));
                                    wattron(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    mvwaddch(map_pad,selected->get_y(),selected->get_x(),' ');
                                    wattroff(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                                    selected->move(pos_x+tile_x,pos_y+tile_y);
                                    selected->set_used(true);
                                    break;
                                case 1: //Tie
                                    delete map[pos_x+tile_x][pos_y+tile_y].unit;
                                    map[pos_x+tile_x][pos_y+tile_y].unit = NULL;
                                    map[selected->get_x()][selected->get_y()].unit = NULL;
                                    wattron(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain));
                                    mvwaddch(map_pad,pos_y+tile_y,pos_x+tile_x,' ');
                                    wattroff(map_pad,COLOR_PAIR(map[pos_x+tile_x][pos_y+tile_y].terrain));
                                    wattron(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    mvwaddch(map_pad,selected->get_y(),selected->get_x(),' ');
                                    wattroff(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                                    delete selected;
                                    break;
                                case 2: //Lose
                                    map[selected->get_x()][selected->get_y()].unit = NULL;
                                    wattron(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    mvwaddch(map_pad,selected->get_y(),selected->get_x(),' ');
                                    wattroff(map_pad,COLOR_PAIR(map[selected->get_x()][selected->get_y()].terrain));
                                    pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
                                    delete selected;
                                    break;
                                default:
                                    break;
                            }
                            deselect();
                        }
                    }
                    move(pos_y, pos_x);
                    doupdate();
                }
            }

            break;    
        case 'x':
            deselect();
		default:
			break;
		}
	}
    deselect();
}

//returns the tile at a specific (x,y)
tile_pair_t *Map::get_tile(int x, int y)
{
	if (x >= map_x || y >= map_y)
		return 0;
    if(x < 0 || y < 0)
        return 0;
	return &map[x][y];
}

//clears the selected unit and all related data
void Map::deselect()
{
    selected = NULL;
    delete pathfind;
    pathfind = NULL;
}



//creates a road from one coordinate to another.
void Map::createRoad(int orig_x, int orig_y, int dest_x, int dest_y){
	if (orig_y < dest_y){	//Will swap points if origin is above destination
		int temp_x = orig_x;
		orig_x = dest_x;
		dest_x = temp_x;
		int temp_y = orig_y;
		orig_y = dest_y;
		dest_y = temp_y;
	}
	int n = orig_x;
	int m = orig_y;
	if (orig_x > dest_x){ //Going left
		int ups = 0;
		int lefts = 0;
		while ( n-1 >= dest_x || m-1 >= dest_y ){
			if ( n == dest_x ){	//moved as left as possible
				m--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( m == dest_y ){	//moved as up as possible
				n--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( ups > 0){
				ups--;
				m--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( lefts > 0 ){
				lefts--;
				n--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else{	//pick either up or left
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //up
					ups = 3;
						m--;
					if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
						map[n][m].terrain = 3;
					}
				}
				else{ //left
					lefts = 3;
					n--;
					if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
						map[n][m].terrain = 3;
					}
				}
			}
		}
	}
	else{	//Going right
		int ups = 0;
		int rights = 0;
		while ( n+1 <= dest_x || m-1 >= dest_y ){
			if ( n == dest_x ){	//moved as right as possible
				m--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( m == dest_y ){	//moved as up as possible
				n++;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( ups > 0){
				ups--;
				m--;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else if ( rights > 0 ){
				rights--;
				n++;
				if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
					map[n][m].terrain = 3;
				}
			}
			else{	//pick either up or right
				int rand = (int) (2 * ( std::rand() / (RAND_MAX + 1.0)));
				if (rand == 1){ //up
					ups = 3;
					m--;
					if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
						map[n][m].terrain = 3;
					}
				}
				else{ //right
					rights = 3;
					n++;
					if( map[n][m].terrain != 5 && map[n][m].terrain != 6){
						map[n][m].terrain = 3;
					}
				}
			}
		}
	}
}

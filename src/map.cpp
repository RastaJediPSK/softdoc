#include "map.h"

Map::Map(int x, int y, int screen_x, int screen_y, Panel *panel_ptr) :
    map(NULL),
    tile_x(0),
    tile_y(0),
    map_x(x),
    map_y(y),
    scr_x(screen_x),
    scr_y(screen_y),
    pos_x(screen_x/2),
    pos_y(screen_y/2),
    panel(panel_ptr)
{
    if(panel != NULL)
        scr_x -= panel->get_size();
    map = new tile_pair * [x];
    for (int i = 0; i < x; i++)
    {
        map[i] = new tile_pair [y];
        for (int j = 0; j < y; j++)
        {
            map[i][j].unit = NULL;
            map[i][j].terrain = (i+j) % 6 + 1;	//temp
        }
    }
	for (int i = 0; i < scr_x; i++)
    {
        for(int j=0;j<scr_y; j++)
        {
            if (i >= x || j >= y)
            {
                attron(COLOR_PAIR(14));
                mvaddch(j,i,' ');
                attroff(COLOR_PAIR(14));
            }
            else
            { if (map[i][j].unit == NULL)
                            {
                    attron(COLOR_PAIR(map[i][j].terrain));
                    mvaddch(j,i,' ');
                    attroff(COLOR_PAIR(map[i][j].terrain));
                }
            }
        }
    }
}

Map::~Map()
{
	for(int i = 0; i < map_x; i++)
		delete [] map[i];
}

void Map::redraw(int screen_x, int screen_y)
{
    scr_x = screen_x;
    scr_y = screen_y;
    if(pos_x > scr_x)
        pos_x = scr_x;
    if(pos_y > scr_y)
        pos_y = scr_y;
    curs_set(0);
	for (int i = 0; i < scr_x; i++)
	{
		for (int j = 0; j < scr_y; j++)
		{
			if (i + tile_x >= map_x || j + tile_y >= map_y)
			{
				attron(COLOR_PAIR(14));
				mvaddch(j,i,' ');
				attroff(COLOR_PAIR(14));
			}

			else
			{
				if (map[i + tile_x][j + tile_y].unit == NULL)
				{                
					attron(COLOR_PAIR(map[i + tile_x][j + tile_y].terrain));
					mvaddch(j,i,' ');
					attroff(COLOR_PAIR(map[i + tile_x][j + tile_y].terrain));
				}
			}
		}
	}
    if(panel != NULL)
        panel->resize(screen_x+panel->get_size(),screen_y,map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
    move(pos_y,pos_x);
    curs_set(1);
}

void Map::map_loop()
{
    int ch;
    bool quit = 1;

    move(pos_y,pos_x);
    while(quit)
    {
        ch = getch();
        switch(ch) //may want to add a wait time to redraws
        {
            case 'q':
            case KEY_EXIT:
                quit = 0;
                break;
            case KEY_UP:
                if(pos_y==0)
                {
                    if(tile_y==0)
                    {
                        //beep
                    }else{
                        tile_y--;
                        redraw(scr_x,scr_y);
                    }
                }else{
                    pos_y--;
                    move(pos_y,pos_x);
                    if(panel != NULL)
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                }
                break;
            case KEY_DOWN:
                if(pos_y>=scr_y-1)
                {
                    if(tile_y+scr_y==map_y)
                    {
                        //beep
                    }else{
                        tile_y++;
                        redraw(scr_x,scr_y);
                    }
                }else{
                    pos_y++;
                    move(pos_y,pos_x);
                    if(panel != NULL)
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                }
                break;
            case KEY_LEFT:
                if(pos_x==0)
                {
                    if(tile_x==0)
                    {
                        //beep
                    }else{
                        tile_x--;
                        redraw(scr_x,scr_y);
                    }
                }else{
                    pos_x--;
                    move(pos_y,pos_x);
                    if(panel != NULL)
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                }
                break;
            case KEY_RIGHT:
                if(pos_x>=scr_x-1)
                {
                    if(tile_x+scr_x==map_x)
                    {
                        //beep
                    }else{
                        tile_x++;
                        redraw(scr_x,scr_y);
                    }
                }else{
                    pos_x++;
                    move(pos_y,pos_x);
                    if(panel != NULL)
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                }
                break;
            default:
                break;
        }
    }
}

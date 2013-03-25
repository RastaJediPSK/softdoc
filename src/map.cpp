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
    panel(panel_ptr),
    map_pad(NULL)
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
    map_pad = newpad(y,x);
    for(int j=0;j<y;j++)
    {
        wmove(map_pad,j,0);
        for(int i=0;i<x;i++)
        {
            wattron(map_pad,COLOR_PAIR(map[i][j].terrain));
            waddch(map_pad,' ');
            wattroff(map_pad,COLOR_PAIR(map[i][j].terrain));
        }
    }
    redraw(scr_x,scr_y);
}

Map::~Map()
{
	for(int i = 0; i < map_x; i++)
		delete [] map[i];
    delwin(map_pad);
}

void Map::redraw(int screen_x, int screen_y)
{
    scr_x = screen_x;
    scr_y = screen_y;
    if(pos_x > scr_x)
        pos_x = scr_x;
    if(pos_y > scr_y)
        pos_y = scr_y;
    pnoutrefresh(map_pad,tile_y,tile_x,0,0,scr_y-1,scr_x-1);
    if(panel != NULL)
        panel->resize(screen_x+panel->get_size(),screen_y,map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
    doupdate();
    move(pos_y,pos_x);
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
                    {
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                        doupdate();
                    }
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
                    {
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                        doupdate();
                    }
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
                    {
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                        doupdate();
                    }
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
                    {
                        panel->update(map[pos_x+tile_x][pos_y+tile_y].terrain,map[pos_x+tile_x][pos_y+tile_y].unit);
                        doupdate();
                    }
                }
                break;
            default:
                break;
        }
    }
}

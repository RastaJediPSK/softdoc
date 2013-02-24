#include "map.h"

MAP::MAP(int x, int y)
{
        getmaxyx(stdscr,scr_y,scr_x);
        tile_x = tile_y = 0;
        map_x = x;
        map_y = y;
        map = new (tile_pair *) [x];
        for(int i=0;i<x;i++)
        {
            map[i] = new tile_pair [y];
            for(int j=0;j<y;j++)
            {
                map[i][j].unit = NULL;
                map[i][j].terrain = map[i][j].terrain % 12 + 1;//temp
            }
        }
        for(int i=0, i<scr_x && i<map_x; i++)
        {
            for(int j=0;j<scr_y && j<map_y; j++)
            {
                attron(COLOR_PAIR(map[i][j].terrain));
                if(map[i][j] == NULL)
                    mvaddch(i,j,' ');
                attroff(COLOR_PAIR(map[i][j].terrain));
            }
        }
}

MAP::~MAP()
{
    for(int i=0;i<map_x;i++)
        delete [] map[i];
}

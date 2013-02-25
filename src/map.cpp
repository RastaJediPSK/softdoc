#include "map.h"

Map::Map(int x, int y)
{
        getmaxyx(stdscr,scr_y,scr_x);
        tile_x = 0;
        tile_y = 0;
        map_x = x;
        map_y = y;
        map = new tile_pair * [x];
        for(int i=0;i<x;i++)
        {
            map[i] = new tile_pair [y];
            for(int j=0;j<y;j++)
            {
                map[i][j].unit = NULL;
                map[i][j].terrain = map[i][j].terrain % 6 + 1;//temp
            }
        }
        for(int i=0; i<scr_x; i++)
        {
            for(int j=0;j<scr_y; j++)
            {
                if(i >= x || j >= y)
                {
                    attron(COLOR_PAIR(14));
                    mvaddch(j,i,' ');
                    attroff(COLOR_PAIR(14));
                }else{
                    if(map[i][j].unit == NULL)
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
    for(int i=0;i<map_x;i++)
        delete [] map[i];
}

void Map::redraw()
{
    getmaxyx(stdscr,scr_y,scr_x);
    for(int i=0;i<scr_x;i++)
    {
        for(int j=0;j<scr_y;j++)
        {
            if(i+tile_x >= map_x || j+tile_y >= map_y)
            {
                attron(COLOR_PAIR(14));
                mvaddch(j,i,' ');
                attroff(COLOR_PAIR(14));
            }else{
                if(map[i+tile_x][j+tile_y].unit == NULL)
                {
                    attron(COLOR_PAIR(map[i+tile_x][j+tile_y].terrain));
                    mvaddch(j,i,' ');
                    attroff(COLOR_PAIR(map[i+tile_x][j+tile_y].terrain));
                }
            }
        }
    }
}

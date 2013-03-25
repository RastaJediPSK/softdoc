#include "panel.h"

Panel::Panel(int screen_x, int screen_y, int panel_size) :
    scr_x(screen_x),
    scr_y(screen_y),
    size(panel_size),
    pos_x(screen_x-size+1),
    terrain_pos(1),
    unit_name_pos(screen_y/4),
    move_pos(screen_y/4 + 1),
    panel_window(NULL)
{
    resize(scr_y,scr_x,0,NULL);
}

void Panel::update(int terrain, Unit *unit)
{
    int i;

    wmove(panel_window,terrain_pos,9);
    switch(terrain)
    {
        case 1:
            waddstr(panel_window,"Water");
            break;
        case 2:
            waddstr(panel_window,"Grass");
            break;
        case 3:
            waddstr(panel_window,"Road");
            break;
        case 4:
            waddstr(panel_window,"???");
            break;
        case 5:
            waddstr(panel_window,"Mountin");
            break;
        case 6:
            waddstr(panel_window,"???");
            break;
        default:
            break;
    }
    getyx(panel_window,terrain,i);
    for(;i<scr_x;i++)
        waddch(panel_window,' ');
    wnoutrefresh(panel_window);
}

void Panel::resize(int screen_x, int screen_y, int terrain, Unit *unit)
{
    pos_x = screen_x-size+1;
    unit_name_pos = screen_y/4;
    move_pos = screen_y/4+1;
    panel_window = newwin(scr_y,scr_x-size,0,pos_x);
    wattron(panel_window,COLOR_PAIR(15));
    mvwprintw(panel_window,terrain_pos,0,"Terrain: ");
    mvwprintw(panel_window,unit_name_pos,0,"Unit Name: ");
    mvwprintw(panel_window,move_pos,0,"Move Left: ");
    update(terrain,unit);
}

int Panel::get_size()
{
    return size;
}

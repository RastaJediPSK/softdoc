#include "panel.h"

Panel::Panel(int screen_x, int screen_y, int panel_size) :
    scr_x(screen_x),
    scr_y(screen_y),
    size(panel_size),
    pos_x(screen_x-size+1),
    terrain_pos(1),
    unit_name_pos(screen_y/4),
    move_pos(screen_y/4 + 1),
    panel_window(NULL),
    selected(NULL)
{
    resize(scr_y,scr_x,0,NULL);
}

Panel::~Panel()
{
    delwin(panel_window);
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
            waddstr(panel_window,"Mountain");
            break;
        case 5:
            waddstr(panel_window,"Building");
            break;
        case 6:
            waddstr(panel_window,"Base");
            break;
        default:
            break;
    }
    getyx(panel_window,terrain,i);
    for(;i<scr_x;i++)
        waddch(panel_window,' ');
    wmove(panel_window,unit_name_pos,11);
    if(unit != NULL)
    {
        waddstr(panel_window,unit->get_name().c_str());
    }else{
        getyx(panel_window,terrain,i);
        for(;i<scr_x;i++)
            waddch(panel_window,' ');
    }
    wnoutrefresh(panel_window);
}

void Panel::resize(int screen_x, int screen_y, int terrain, Unit *unit)
{
    pos_x = screen_x-size+1;
    unit_name_pos = screen_y/4;
    move_pos = screen_y/4+1;
    panel_window = newwin(scr_y,scr_x-size,0,pos_x);
    wattron(panel_window,COLOR_PAIR(15));
    werase(panel_window);
    mvwprintw(panel_window,terrain_pos,0,"Terrain: ");
    mvwprintw(panel_window,unit_name_pos,0,"Unit Name: ");
    mvwprintw(panel_window,move_pos,0,"Move Left: ");
    update(terrain,unit);
}

int Panel::get_size()
{
    return size;
}

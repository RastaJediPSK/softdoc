#include "panel.h"

//Panel constructor
Panel::Panel(int screen_x, int screen_y, int panel_size) :
    scr_x(screen_x),
    scr_y(screen_y),
    size(panel_size),
    pos_x(screen_x-size+1),
    terrain_pos(1),
    unit_name_pos(screen_y/4),
    move_pos(screen_y/2 + 1),
    selected_unit_pos(screen_y/2),
    panel_window(NULL)
{
    resize(scr_y,scr_x,0,NULL,NULL,-1);
}

//Panel deconstructor, deletes the panel window
Panel::~Panel()
{
    delwin(panel_window);
}

//updates the data displayed on the panel
void Panel::update(int terrain, Unit *unit, Unit *selected, int path_length)
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
        wmove(panel_window,unit_name_pos+2,9);
        if(unit->get_used())
        {
            waddstr(panel_window,"No ");
        }else{
            waddstr(panel_window,"Yes");
        }
    }else{
        getyx(panel_window,terrain,i);
        for(;i<scr_x;i++)
            waddch(panel_window,' ');
        mvwprintw(panel_window,unit_name_pos+2,9,"   ");
    }
    wmove(panel_window,selected_unit_pos,11);
    if(selected != NULL)
    {
        waddstr(panel_window,selected->get_name().c_str());
    }else{
        getyx(panel_window,terrain,i);
        for(;i<scr_x;i++)
            waddch(panel_window,' ');
    }
    wmove(panel_window,move_pos,11);
    if(selected != NULL)
    {
        if(path_length != -1 && path_length <= selected->get_move())
        {
            waddstr(panel_window,"yes");
        }else{
            waddstr(panel_window,"no ");
        }

    }else{
        waddstr(panel_window,"   ");
    }
    wnoutrefresh(panel_window);
}

//redraws and resizes the entire panel
void Panel::resize(int screen_x, int screen_y, int terrain, Unit *unit, Unit *selected, int path)
{
    pos_x = screen_x-size+1;
    unit_name_pos = screen_y/4;
    move_pos = (screen_y/2)+2;
    panel_window = newwin(scr_y,scr_x-size,0,pos_x);
    wattron(panel_window,COLOR_PAIR(15));
    werase(panel_window);
    mvwprintw(panel_window,terrain_pos,0,"Terrain: ");
    mvwprintw(panel_window,unit_name_pos,0,"Unit Name: ");
    mvwprintw(panel_window,unit_name_pos+2,0,"Can Use: ");
    mvwprintw(panel_window,move_pos,0,"Move Here: ");
    mvwprintw(panel_window,selected_unit_pos,0,"Held Unit: ");
    update(terrain,unit,selected,path);
}

//returns the width of the panel
int Panel::get_size()
{
    return size;
}

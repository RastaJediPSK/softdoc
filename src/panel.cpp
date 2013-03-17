#include "panel.h"

Panel::Panel(int screen_x, int screen_y, int panel_size) :
    scr_x(screen_x),
    scr_y(screen_y),
    size(panel_size),
    pos_x(screen_x-size+1),
    terrain_pos(1),
    unit_name_pos(screen_y/4),
    move_pos(screen_y/4 + 1)
{
    attron(COLOR_PAIR(15));
    mvprintw(terrain_pos,pos_x,"Terrain: ");
    mvprintw(unit_name_pos,pos_x,"Unit Name: ");
    mvprintw(move_pos,pos_x,"Move Left: ");
    attroff(COLOR_PAIR(15));
}

void Panel::update(int terrain, Unit *unit)
{
    int curx, cury, i;

    getyx(stdscr,cury,curx);
    move(terrain_pos,pos_x+9);
    switch(terrain)
    {
        case 1:
            addstr("Water");
            break;
        case 2:
            addstr("Grass");
            break;
        case 3:
            addstr("Road");
            break;
        case 4:
            addstr("???");
            break;
        case 5:
            addstr("Mountin");
            break;
        case 6:
            addstr("???");
            break;
        default:
            break;
    }
    getyx(stdscr,terrain,i);
    for(;i<scr_x;i++)
        addch(' ');

    move(cury,curx);
}

void Panel::resize(int screen_x, int screen_y, int terrain, Unit *unit)
{
    pos_x = screen_x-size+1;
    unit_name_pos = screen_y/4;
    move_pos = screen_y/4+1;
    attron(COLOR_PAIR(15));
    mvprintw(terrain_pos,pos_x,"Terrain: ");
    mvprintw(unit_name_pos,pos_x,"Unit Name: ");
    mvprintw(move_pos,pos_x,"Move Left: ");
    attroff(COLOR_PAIR(15));
    update(terrain,unit);
}

int Panel::get_size()
{
    return size;
}

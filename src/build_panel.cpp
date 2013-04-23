#include "build_panel.h"

//Constructor for BuildPanel Class
BuildPanel::BuildPanel(std::vector<UnitType *> &unit_types, Player *play, int scr_x, int scr_y, int panel_size) :
    types(unit_types),
    win(NULL),
    pl(play),
    size(panel_size),
    opt(0),
    screen_y(scr_y)
{
    resize(scr_x,scr_y);
}

//Deconstuctor for BuildPanel
BuildPanel::~BuildPanel()
{
    delwin(win);
}

//creates and writes a new window for the panel
//used to initially create the window and to resize it
void BuildPanel::resize(int scr_x, int scr_y)
{
    screen_y = scr_y;
    if(win != NULL)
        delwin(win);
    win = newwin(scr_y-1,scr_x-size,0,scr_x-size+1);
    wattron(win,COLOR_PAIR(15));
    werase(win);
    clearok(win,true);
    for(unsigned int i=0;i<types.size();i++)
    {
        if(opt==i)
        {
            wattroff(win,COLOR_PAIR(15));
            wattron(win,COLOR_PAIR(16));
        }
        mvwprintw(win,4+2*i,0,types[i]->get_unit_name().c_str());
        //wprintw(win," %d",types[i]->get_unit_cost());
        if(opt==i)
        {
            wattroff(win,COLOR_PAIR(15));
            wattron(win,COLOR_PAIR(16));
        }
    }
    if(opt == types.size())
    {
        wattroff(win,COLOR_PAIR(15));
        wattron(win,COLOR_PAIR(16));
        mvwprintw(win,scr_y-2,0,"EXIT");
        wattroff(win,COLOR_PAIR(16));
        wattron(win,COLOR_PAIR(15));
    }else{
        mvwprintw(win,scr_y-2,0,"EXIT");
    }
}

//Abstract Factory that takes control of input to
//allow the user to select a unit to create
//the unit is then created and a pointer is returned
//otherwise NULL is returned
Unit *BuildPanel::use_panel(int x, int y)
{
    Unit *temp_ptr = NULL;

    wnoutrefresh(win);
    doupdate();
    while(true)
    {
        int ch = getch();
        switch(ch)
        {
            case KEY_DOWN:
                if(opt == types.size())
                {
                    mvwprintw(win,screen_y-2,0,"EXIT");
                    opt = 0;
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name().c_str());
                    opt++;
                }
                wattroff(win,COLOR_PAIR(15));
                wattron(win,COLOR_PAIR(16));
                if(opt == types.size())
                {
                    mvwprintw(win,screen_y-2,0,"EXIT");
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name().c_str());
                }
                wattroff(win,COLOR_PAIR(16));
                wattron(win,COLOR_PAIR(15));
                break;
            case KEY_UP:
                if(opt == types.size())
                {
                    mvwprintw(win,screen_y-2,0,"EXIT");
                    opt--;
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name().c_str());
                    if(opt==0)
                    {
                        opt = types.size();
                    }else{
                        opt--;
                    }
                }
                wattroff(win,COLOR_PAIR(15));
                wattron(win,COLOR_PAIR(16));
                if(opt == types.size())
                {
                    mvwprintw(win,screen_y-2,0,"EXIT");
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name().c_str());
                }
                wattroff(win,COLOR_PAIR(16));
                wattron(win,COLOR_PAIR(15));
                break;
            case 'z':
                if(opt==types.size())
                    return NULL;
                temp_ptr = new Unit(types[opt],pl,x,y);
                return temp_ptr;
                break;
            default:
                break;
        }
        wnoutrefresh(win);
        doupdate();
    }
    return NULL;
}

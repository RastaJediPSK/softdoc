/*
 * File:  build_panel.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  11 March 2013
 * Description:  BuildPanel class definition file.
 */

#include "build_panel.h"

#include "unit.h"
#include "unit_type.h"

/* Constructor for BuildPanel Class. */
BuildPanel::BuildPanel(std::vector<UnitType *> const &unit_types, Player *play, int scr_x, int scr_y, int panel_size) :
	types(unit_types),
	win(0),
	pl(play),
	size(panel_size),
	opt(0),
	screen_y(scr_y)
{
	resize(scr_x, scr_y);
}

/* Deconstuctor for BuildPanel. */
BuildPanel::~BuildPanel()
{
	delwin(win);
}

/*
 * Creates and writes a new window for the panel.
 * Used to initially create the window and to resize it.
 */
void BuildPanel::resize(int scr_x, int scr_y)
{
	screen_y = scr_y;
	// Check for existing wnidow
	if (win != 0)
		delwin(win);
	win = newwin(scr_y - 1, scr_x - size, 0, scr_x - size + 1);
	wattron(win, COLOR_PAIR(15));
	werase(win);
	clearok(win, true);
	for (unsigned int i = 0; i < types.size(); ++i)
	{
		if (opt == i)
		{
			wattroff(win, COLOR_PAIR(15));
			wattron(win, COLOR_PAIR(16));
		}
		mvwprintw(win, 4 + 2*i, 0, types[i]->get_unit_name().c_str());
		if (opt == i)
		{
			wattroff(win, COLOR_PAIR(16));
			wattron(win, COLOR_PAIR(15));
		}
	}

	if (opt == types.size())
	{
		wattroff(win, COLOR_PAIR(15));
		wattron(win, COLOR_PAIR(16));
		mvwprintw(win, scr_y - 2, 0, "EXIT");
		wattroff(win, COLOR_PAIR(16));
		wattron(win, COLOR_PAIR(15));
	}
	else
		mvwprintw(win, scr_y - 2, 0, "EXIT");
}

/*
 * Factory that takes control of input to allow the user to select a unit to
 * create the unit is then created and a pointer is returned otherwise NULL is
 * returned.
 */
Unit *BuildPanel::use_panel(int x, int y)
{
	Unit *temp_ptr = 0;

	curs_set(0);
	wnoutrefresh(win);
	doupdate();

	while (true)
	{
		int ch = getch();
		switch (ch)
		{
		case KEY_DOWN:
			if (opt == types.size())
			{
				mvwprintw(win, screen_y - 2, 0, "EXIT");
				opt = 0;
			}
			else
			{
				mvwprintw(win, 4 + 2*opt, 0, types[opt]->get_unit_name().c_str());
				++opt;
			}

			wattroff(win, COLOR_PAIR(15));
			wattron(win, COLOR_PAIR(16));

			if (opt == types.size())
				mvwprintw(win, screen_y - 2, 0, "EXIT");
			else
				mvwprintw(win, 4 + 2*opt, 0, types[opt]->get_unit_name().c_str());

			wattroff(win, COLOR_PAIR(16));
			wattron(win, COLOR_PAIR(15));
			break;
		case KEY_UP:
			if (opt == types.size())
			{
				mvwprintw(win, screen_y - 2, 0, "EXIT");
				--opt;
			}
			else
			{
				mvwprintw(win, 4 + 2*opt, 0, types[opt]->get_unit_name().c_str());
				if (opt == 0)
					opt = types.size();
				else
					--opt;;
			}

			wattroff(win, COLOR_PAIR(15));
			wattron(win, COLOR_PAIR(16));

			if (opt == types.size())
				mvwprintw(win,screen_y - 2, 0, "EXIT");
			else
				mvwprintw(win, 4 + 2*opt, 0, types[opt]->get_unit_name().c_str());

			wattroff(win, COLOR_PAIR(16));
			wattron(win, COLOR_PAIR(15));
			break;
		case 'z':
			if (opt == types.size())
			{
				curs_set(1);
				return 0;
			}

			temp_ptr = new Unit(types[opt], pl, x, y);
			temp_ptr->set_used(true);
			curs_set(1);
			return temp_ptr;
		}

		wnoutrefresh(win);
		doupdate();
	}

	curs_set(1);
	return 0;
}

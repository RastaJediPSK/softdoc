/*
 * File:  main.cpp
 * Authors:  Steve Erikson, Michael, Kelly, James
 * Date:  12 February 2013
 * Description:
 */

#include <curses.h>
#include <iostream>
#include <signal.h>
#include "menu.h"
#include "map.h"
#include "panel.h"
#include "unit.h"

//Main function, starts Ncurses and the menu
int main()
{
	// START NCURSES
	initscr();
	noecho();
	raw();
	refresh();
	keypad(stdscr,TRUE);
	// START COLORS
	start_color();
	// player 1 colors
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_CYAN);
	init_pair(4, COLOR_WHITE, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_YELLOW);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	// player 2 colors
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	// error colors
	init_pair(13, COLOR_RED, COLOR_WHITE);
	init_pair(14, COLOR_BLACK, COLOR_BLACK);
	// panel color
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
    init_pair(16, COLOR_BLACK, COLOR_WHITE);
	// RESIZE FUNC
	//signal(SIGWINCH, );//i(void *)resizefunc(int));
	
	Menu menu;
	menu.show();

	// end ncurses
	endwin();

	return 0;
}

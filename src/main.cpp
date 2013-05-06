/*
 * File:  main.cpp
 * Authors:  Steve Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  12 February 2013
 * Description:  Null Pointer's Game.
 */

#include <iostream>
#include <curses.h>
#include <signal.h>
#include "map.h"
#include "menu.h"
#include "panel.h"
#include "unit.h"

/* Main function, starts ncurses and the menu. */
int main()
{
	/* Start ncurses */
	initscr();
	noecho();
	raw();
	refresh();
	keypad(stdscr, true);
	
	/* Start colors */
	start_color();
	// Player 1 colors
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_CYAN);
	init_pair(4, COLOR_WHITE, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_YELLOW);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	// Player 2 colors
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	// Error colors
	init_pair(13, COLOR_RED, COLOR_WHITE);
	init_pair(14, COLOR_BLACK, COLOR_BLACK);
	// Panel color
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(16, COLOR_BLACK, COLOR_WHITE);
	// Player switching screen colors
	init_pair(17, COLOR_GREEN, COLOR_BLACK);
	init_pair(18, COLOR_RED, COLOR_BLACK);
	
	/* Initialize menu */
	Menu menu;
	menu.show();

	/* End ncurses */
	endwin();

	return 0;
}

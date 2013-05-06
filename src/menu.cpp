/*
 * File:  menu.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class definition file.
 */

#include "menu.h"

#include <iostream>
#include <curses.h>
#include "game.h"

/* Menu deconstructor, quits the game. */
Menu::~Menu()
{
	quit_game();
}

/* Displays and interacts with the menu. */
void Menu::show()
{
	//Ddisplay menu
	WINDOW *title;

	int scr_x, scr_y;
	getmaxyx(stdscr, scr_y, scr_x);
	title = newwin(scr_y, scr_x, 0, 0);
	mvwprintw(title, scr_y / 3, (scr_x - 20) / 2, "Null Pointer's Game");
	mvwprintw(title, 2 * scr_y / 3, (scr_x - 24) / 2, "Press any key to continue");

	curs_set(0);
	wrefresh(title);
	wgetch(title);
	curs_set(1);
	delwin(title);

	game = new_game();
}

/* Creates a new game. */
Game *Menu::new_game()
{
	// First delete any possible game to avoid memory leaks
	quit_game();

	return new Game();
}

/* Quits game by deleting the game object. */
void Menu::quit_game()
{
	delete game;	// delete is no-op for nullptr
	game = 0;
}

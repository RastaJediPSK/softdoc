/*
 * File:  menu.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze III, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class definition file
 */

#include <iostream>
#include <curses.h>
#include "menu.h"

//Menu deconstructor, quits the game
Menu::~Menu()
{
	quit_game();
}

//Displays and interacts with the menu
void Menu::show()
{
	// display menu
    WINDOW *title;
	int choice;


	int scr_x, scr_y;
	getmaxyx(stdscr, scr_y, scr_x);
    title = newwin(scr_y,scr_x,0,0);
    mvwprintw(title,scr_y/3,(scr_x-20)/2,"Null Pointer's Game");
    mvwprintw(title,2*scr_y/3,(scr_x-24)/2,"Press any key to continue");

    curs_set(0);
    wrefresh(title);
	choice = getch();
    curs_set(1);
    delwin(title);

    game=new_game();
	
	if (game == 0)
	{
		// don't have a game, disable continue/save
	}

	else
	{
		// this is just a pause, we do have a game
		// display quit game option
	}
}

//creates a new game
Game *Menu::new_game()
{
	/* first delete any possible game to avoid memory leaks */
	quit_game();

	return new Game();
}

//continues game (future feature)
void Menu::continue_game()
{
	// un-pause game
}

//loads game (future feature)
void Menu::load_game(int save_num)
{
	// check to see if save save_num exists
	
	// load game
}

//saves game (future feature)
void Menu::save_game(int save_num)
{
	// save game
}

//quits game by deleting the game object
void Menu::quit_game()
{
	delete game;	/* delete is no-op for nullptr */
	game = 0;
}

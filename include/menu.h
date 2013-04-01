/*
 * File:  menu.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class declaration file
 */

#ifndef MENU_H_
#define MENU_H_

#include "game.h"

class Menu
{
	Game *game;
	Menu(const Menu &);	/* declaring copy ctor as private to forbid use of it */
	Menu &operator=(const Menu &);	/* same with assignment operator */

public:
	Menu() : game(new_game()) { }
	~Menu();
	void show();	/* display startup/pause menu on screen */
	Game *new_game();
	void continue_game();
	void load_game(int);
	void save_game(int);
	void quit_game();
};

#endif

/*
 * File:  menu.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze III, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class definition
 */

#ifndef MENU_H_
#define MENU_H_

#include "game.h"

class Menu
{
	Game *game;
public:
	Menu();
	~Menu();
	void show();
	Game *new_game();
	void continue_game();
	void load_game(int save_num);
	void save_game(int save_num);
};

#endif

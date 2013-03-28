/*
 * File:  menu.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze III, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class implementation
 */

#include "menu.h"

Menu::Menu() : game(0)
{
	game = new_game();
}

Menu::~Menu()
{
	delete game;
	game = 0;
}

void Menu::show()
{
	// display menu
	
	if (game == 0)
	{
		// don't have a game, disable continue/save
	}

	else
	{
		// this is just a pause, we do have a game
	}
}

Game *Menu::new_game()
{
	return new Game();
}

void Menu::continue_game()
{
	// un-pause game
}

void Menu::load_game(int save_num)
{
	// check to see if save_num exists
	
	// load game
}

void Menu::save_game(int save_num)
{
	// save game
}

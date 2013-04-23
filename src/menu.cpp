/*
 * File:  menu.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze III, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class definition file
 */

#include <iostream>
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
	int choice;
	std::cout << "Enter choice:\r\n";
	std::cout << "[1]: New Game\r\n" << std::flush;
	choice = getch();

	switch (choice)
	{
	case '1':
		game = new_game();
		break;
	default:
		break;
	}
	
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

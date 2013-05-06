/*
 * File:  menu.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Main Menu class declaration file.
 */

#ifndef MENU_H
#define MENU_H

class Game;

/* Menu class, creates the game and provides a starting interface. */
class Menu
{
	Game *game;
	Menu(const Menu &);		// declaring copy ctor as private to forbid use of it
	Menu &operator=(const Menu &);	// same with assignment operator

public:
	Menu() : game(0) { }		// ctor
	~Menu();
	void show();
	Game *new_game();
	void quit_game();
};

#endif	/* MENU_H */

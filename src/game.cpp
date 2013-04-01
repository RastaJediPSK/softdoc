/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition file
 */

#include <ncurses/curses.h>
#include "game.h"
#include "panel.h"
#include "map.h"

Game::Game() : players()
{
	const int num_players = 2;
	// Add num_players to the game
	for (int i = 0; i < num_players; ++i)
		players.push_back(Player());

	// Start ncurses
	initscr();
	noecho();
	raw();
	refresh();
	keypad(stdscr,TRUE);

	// Start colors
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
	
	// Resize funct.
	//signal(SIGWINCH, /*i(void *)resizefunc(int)*/);
	int scr_x, scr_y;
	getmaxyx(stdscr, scr_y, scr_x);
	//Panel *panel = new Panel(scr_x, scr_y, 20);
	Panel panel(scr_x, scr_y, 20);
	//Map *gamemap = new Map(200, 200, scr_x, scr_y, panel);
	Map map(200, 200, scr_x, scr_y, panel);
	//gamemap->map_loop();
	map.map_loop();
}

Game::~Game()
{
	//delete gamemap;
	//delete panel;

	// end ncurses
	endwin();
}

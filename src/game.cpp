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
}

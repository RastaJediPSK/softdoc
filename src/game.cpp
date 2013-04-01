/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition file
 */

#include "game.h"

Game::Game() : players()
{
	const int num_players = 2;
	/* Add num_players to the game */
	for (int i = 0; i < num_players; ++i)
		players.push_back(Player());
}

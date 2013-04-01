/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition file
 */

#include "game.h"

Game::Game()
{
	for (int i = 0; i < this->num_players; ++i)
		players.push_back(Player);
}

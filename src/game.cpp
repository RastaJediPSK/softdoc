/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class implementation
 */

#include "game.h"

Game::Game()
{
	for (int i = 0; i < 2; ++i)
		players[i] = new Player();
}

Game::~Game()
{
	for (int i = 0; i < 2; ++i)
	{
		delete players[i];
		players[i] = 0;
	}
}

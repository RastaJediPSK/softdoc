/*
 * File:  game.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class declaration file
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "player.h"

class Game
{
	std::vector<Player> players;
	
public:
	Game();
};

#endif

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
#include "unit_type.h"

class Game
{
	std::vector<Player *> players;
    std::vector<UnitType *> types;
	
public:
	Game();
	~Game();
};

#endif

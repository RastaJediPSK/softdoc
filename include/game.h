/*
 * File:  game.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition
 */

#ifndef GAME_H_
#define GAME_H_

#include "player.h"

class Game
{
	Player *players[2];
	
public:
	Game();
	~Game();
};

#endif

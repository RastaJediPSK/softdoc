/*
 * File:  game.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class declaration file.
 */

#ifndef GAME_H
#define GAME_H

#include <vector>

class Player;
class UnitType;

class Game
{
	std::vector<Player *> players;
	std::vector<UnitType *> types;
	
public:
	Game();
	~Game();
	bool end_turn(bool player);
};

#endif	/* GAME_H */
